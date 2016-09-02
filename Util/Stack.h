//
// Created by Сергей on 02.09.2016.
//

#ifndef CPP_SET_LIB_STACK_H
#define CPP_SET_LIB_STACK_H


#include "List.h"


template <typename T>
class Stack : private List<T>
{
    void push( const T& a ) { ; }
};


#endif //CPP_SET_LIB_STACK_H
