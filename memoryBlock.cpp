#include "memoryBlock.hpp"

// MemoryBlock Definition
MemoryBlock::MemoryBlock(uint32_t nId, 
        MemoryPool* pPool, 
        uint32_t extended ){
    __nId = nId;
    __nRef = 0;
    __extended = extended;
    __pPool = pPool;
    __pNext = nullptr;
}

MemoryBlock::~MemoryBlock(){
}

void MemoryBlock::showBlockMsg(){
    std::cout<< "-----\t Block Message \t-----" <<std::endl;
    std::cout<<"Block Address:\t\t"<< std::hex << (void*)this << std::dec << std::endl;
    std::cout<<"Block id:\t\t"<< __nId <<std::endl;
    std::cout<<"number of reference:\t"<< __nRef <<std::endl;
    std::cout<<"Is block extended:\t"<< (__extended ? "true" : "false") <<std::endl;
    std::cout<<"Belong to pool address:\t"<< std::hex << (void*)__pPool << std::dec << std::endl;
}
