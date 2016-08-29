//
// Created by Сергей on 29.08.2016.
//

#ifndef CPP_SET_LIB_ALLOCATOR_H
#define CPP_SET_LIB_ALLOCATOR_H


#include <cstdint>
#include <new>


struct Allocator
{
    Allocator( std::size_t size = 4 ) : currentBlockSize(size * 16), currentUsedSize(0),
                                       mem(operator new(currentBlockSize)) { }

//    void* operator()( std::size_t size ) { return alloc(size); }

    void* alloc( std::size_t size );

    ~Allocator() { operator delete(mem); }

private:
    void realloc(std::size_t size);

private:
    void* mem;
    std::size_t currentUsedSize;
    std::size_t currentBlockSize;
};


#endif //CPP_SET_LIB_ALLOCATOR_H
