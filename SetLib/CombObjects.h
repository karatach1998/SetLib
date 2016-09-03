//
// Created by Сергей on 30.08.2016.
//

#ifndef CPP_SET_LIB_COMBOBJECTS_H
#define CPP_SET_LIB_COMBOBJECTS_H


#include <vector>
#include "SetBase.h"


class CombObjects
{
private:

public:
    typedef std::vector<bool>& BinaryVector;

    static void bitVector( unsigned n, void (*f)( BinaryVector ));

    template <typename T>
    static void placing( SetBase<T>& set, unsigned k, void (* f)( std::vector<T>& ));
};


#endif //CPP_SET_LIB_COMBOBJECTS_H
