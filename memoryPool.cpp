#include "memoryPool.hpp"

// MemoryPool Definition

MemoryPool::MemoryPool(uint32_t nBlockSize, uint32_t nSize):
    __nBlockSize(nBlockSize),
    __nSize(nSize),
    __pHead(nullptr),
    __pBuff(nullptr){
}

MemoryPool::~MemoryPool(){
    if(__pBuff) { 
        free(__pBuff);
        __pBuff = nullptr;
    }
    __pHead = nullptr;
    __nBlockSize = 0;
    __nSize = 0;
}

// 初始化内存池，申请整个内存池中buff大小 = （块buff大小 + 块结构体大小） * 块数量
void MemoryPool::init(){

    if(__pBuff){        // 已初始化
        return ;
    }
    // 申请内存池buff
    __pBuff = (char *) malloc(__nSize * (__nBlockSize + sizeof(MemoryBlock)));
    if(!__pBuff){       // 申请失败
        std::cout<<"malloc failed"<<std::endl;
        exit(1);
    }

    // 初始化第一个内存块 
    __pHead = (MemoryBlock*)__pBuff;
    __pHead->__nId = 0;
    __pHead->__extended = 0;
    __pHead->__pPool = this;
    __pHead->__pNext = nullptr;

    // 初始化剩下的内存块 
    MemoryBlock* p = __pHead;
    for(int i=1; i<__nSize; ++i){
        MemoryBlock* pTemp = (MemoryBlock*)((char*)(p + 1) + __nBlockSize);
        pTemp->__nId = p->__nId + 1;
        pTemp->__extended = 0;
        pTemp->__pPool = this;
        pTemp->__pNext = nullptr;
        
        p->__pNext = pTemp;
        p = pTemp;
    }
}

// 分配内存
void* MemoryPool::allocMem(uint32_t nSize){
    if(!__pBuff) {      // 未初始化
        init();
    }

    MemoryBlock* pRet = nullptr;
    if(!__pHead){       // __pHead为nulllptr说明池中块已经分配完毕       
        pRet = (MemoryBlock*)malloc(nSize + sizeof(MemoryBlock));
        if(!pRet){      // 申请失败
            std::cout<<"malloc failed"<<std::endl;
            exit(1);
        }
        pRet->__nId = -1;
        pRet->__extended = 1; 
        pRet->__nRef = 1;
        pRet->__pNext = nullptr;
    }else{      // 池中未分配完毕，内存块出栈
        pRet = __pHead;
        __pHead = __pHead->__pNext;
        pRet->__nRef++;
    }

    return (void*)(pRet+1); // 返回内存块结构下的size大小的内存。
}

void* MemoryPool::allocMem(void* p){
    assert(p!=nullptr);

    MemoryBlock* pHead = ((MemoryBlock*)p) - 1;
    ++(pHead->__nRef);      // 引用位置加一

    return p;
}


void MemoryPool::freeMem(void* p){
    MemoryBlock* pHead = ((MemoryBlock*)p) - 1;

    if(--(pHead->__nRef) != 0){     // 引用不为0
        return;
    }

    // 释放内存块
    if(pHead->__extended == 0){ // 池内，内存块入栈
        pHead->__pNext = __pHead;
        __pHead = pHead;
    }else{      // 池外，显示释放
        free((void*)pHead);
    }
    return;
}

// 打印内存池的信息
void MemoryPool::showMsg(){
    std::cout<< "-----\t Pool Message \t-----" <<std::endl;
    std::cout<<"Block size:\t\t"<< __nBlockSize <<std::endl;
    std::cout<<"Number of block:\t"<< __nSize <<std::endl;
    std::cout<<"Pool buff address:\t"<< std::hex << (void*)__pBuff <<std::endl;
    std::cout<<"Pool buff size:\t\t"<< std::dec <<__nBlockSize * __nSize << "B" <<std::endl;
}

// 打印所有块的信息
void MemoryPool::showFreedBlockMsg(){
    if(!__pBuff){
        std::cout<< "Not yet initialized." <<std::endl;
        return;
    }

    MemoryBlock* pHead = __pHead;
    if(pHead){
        while(pHead){
            pHead->showBlockMsg();
            pHead = pHead->__pNext;
        }
    }else{
        std::cout<< "No freed block." <<std::endl;
    }   
}