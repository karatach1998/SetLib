//
// Created by Сергей on 01.09.2016.
//

#include <functional>
#include "CombObjects.h"
#include "SetBase.h"



void CombObjects::bitVector( unsigned n, void (*f)( std::vector<bool>& ))
{
    std::vector<bool> vect(n, false);
    std::function<void(unsigned)> genBitVector = [&]( unsigned i ) {
        for (int x = 0; x <= 1; ++x) {
            vect[i] = x == 1;
            if (i == n - 1)
                f( vect );
            else
                genBitVector(i + 1);
        }
    };


    genBitVector(0);
}



template<typename T>
void CombObjects::placing( SetBase<T>& set, unsigned k, void (* f)( std::vector<T> ))
{
    std::vector<T> v(k, 0);
    unsigned n = (unsigned int) set.getPower();

    std::function<void(SetBase<T>, unsigned)> genPlacing = [&]( SetBase<T> M, unsigned i ) {
        for (T x : M) {
            v[i] = x;
            if (i == k - 1)
                f(v);
            else
                genPlacing(M - {x}, i + 1);
        }
    };

    genPlacing(set, 0);
}


