#include <iostream>
#include <chrono>
#include <cstring>
#include "memoryPool.hpp"
using namespace std;

const static uint32_t nSize = 10 ;
const static uint32_t nBlockSize = 1024;

void testMemoryPool(){
    MemoryPool pool16(nBlockSize, nSize);
    void * pArr[2*nSize];

    pool16.showMsg();
    pool16.init();
    pool16.showMsg();

    chrono::system_clock::time_point st = chrono::system_clock::now();
    for(int i=0; i<nSize * 2; ++i){
        pArr[i] = (void*) pool16.allocMem(nBlockSize);
    }
    chrono::system_clock::time_point et = chrono::system_clock::now();
    cout<< "malloc cost: " << 1.0 * chrono::duration_cast<chrono::milliseconds>(et - st).count() 
        * chrono::milliseconds::period::num / chrono::milliseconds::period::den << " s"<<endl; 
    
    chrono::system_clock::time_point st2 = chrono::system_clock::now();  
    for(int i=0; i<nSize * 2; ++i){
        pool16.freeMem(pArr[i]);
    }
    chrono::system_clock::time_point et2 = chrono::system_clock::now();
    cout<< "free cost: " << 1.0 * chrono::duration_cast<chrono::milliseconds>(et2 - st2).count() 
        * chrono::milliseconds::period::num / chrono::milliseconds::period::den << " s"<<endl; 

}

void test(){
    void * pArr[nSize];
    chrono::system_clock::time_point st = chrono::system_clock::now();
    for(int i=0; i<nSize; ++i){
        pArr[i] = malloc(nBlockSize);
    }
    chrono::system_clock::time_point et = chrono::system_clock::now();
    cout<< "malloc cost: " << 1.0 * chrono::duration_cast<chrono::milliseconds>(et - st).count() 
        * chrono::milliseconds::period::num / chrono::milliseconds::period::den << " s"<<endl; 
    
    chrono::system_clock::time_point st2 = chrono::system_clock::now();   
    for(int i=0; i<nSize; ++i){
        free(pArr[i]);
    }
    chrono::system_clock::time_point et2 = chrono::system_clock::now();
    cout<< "free cost: " << 1.0 * chrono::duration_cast<chrono::milliseconds>(et2 - st2).count() 
        * chrono::milliseconds::period::num / chrono::milliseconds::period::den << " s"<<endl; 
}

int main(){
    testMemoryPool();
    return 0;
}

