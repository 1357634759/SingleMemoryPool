#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H
#include <iostream>
#include <cassert>
#include "memoryBlock.hpp"

class MemoryBlock;

// 内存池类，利用栈式对内存块进行管理
class MemoryPool{
public:
    MemoryPool(uint32_t nBlockSize, uint32_t nSize);
    ~MemoryPool();
    void init();                            // 初始化
    void* allocMem(uint32_t nSize);         // 申请内存
    void* allocMem(void* p);                  
    void freeMem(void* p);                  // 释放内存
    void showMsg();                         // 显示内存池信息
    void showFreedBlockMsg();               // 显示内存块信息

    // 禁用
    MemoryPool(const MemoryPool& ) = delete;      
    MemoryPool& operator =(const MemoryPool& ) = delete; 
protected:
    uint32_t             __nBlockSize;     // 内存块大小
    uint32_t             __nSize;          // 内存池中块的数量
    MemoryBlock*         __pHead;          // 空闲的内存块的头指针
    char*                __pBuff;          // 整个内存池块的首地址
};

#endif