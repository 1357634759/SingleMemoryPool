#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H
#include <iostream>

class MemoryPool;
class MemoryBlock { 
// 内存块类
public:
    MemoryBlock(uint32_t nId, MemoryPool* pPool, uint32_t extended=0);
    ~MemoryBlock();
    void showBlockMsg();                    // 显示内存块信息
    // 禁用
    MemoryBlock(const MemoryBlock& obj) = delete;
    MemoryBlock& operator = (const MemoryBlock& obj) = delete;
private:
    uint32_t        __nId;          // 内存块编号
    uint32_t        __nRef;         // 引用次数
    uint32_t        __extended;     // 表明该块是否是额外扩展的
    MemoryPool*     __pPool;        // 所属内存池类
    MemoryBlock*    __pNext;        // 指向下一块的位置
    friend class MemoryPool;
};

#endif