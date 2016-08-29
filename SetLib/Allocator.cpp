//
// Created by Сергей on 29.08.2016.
//

#include "Allocator.h"



void* Allocator::alloc( std::size_t size )
{

    if ((currentUsedSize + size) > currentBlockSize)
        realloc(size);
    void* allocatedMem = (uint8_t*) mem + currentUsedSize;
    currentUsedSize += size;
    return allocatedMem;

}



void Allocator::realloc( std::size_t size )
{
    uint8_t* oldMem = (uint8_t*) mem;
    uint8_t* newMem;
    currentBlockSize *= 2;
    while (currentBlockSize < size + currentUsedSize)
        currentBlockSize *= 2;
    newMem = (uint8_t*)( mem = operator new (currentBlockSize));
    for (uint32_t i = 0; i < currentUsedSize; ++i) {
        newMem[i] = oldMem[i];
    }
    delete(oldMem);
}

