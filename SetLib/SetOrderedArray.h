//
// Created by Сергей on 14.08.2016.
//

#ifndef SETASSORTEDARRAY_H
#define SETASSORTEDARRAY_H


#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include "Allocator.h"
#include "SetBase.h"


template<class T>
class SetOrderedArray;

template<class T>
class IteratorSetOA : public std::iterator<std::input_iterator_tag, T>
{
    friend class SetOrderedArray<T>;

private:
    SetOrderedArray<T>& soa;
    int currentPos;

private:
    IteratorSetOA( SetOrderedArray<T>& soa, int cPos = 0 ) : soa(soa), currentPos(cPos) { }


public:

    bool operator==( const IteratorSetOA& other ) const;
    bool operator!=( const IteratorSetOA& other ) const;

    T& operator*() { return soa.pData[currentPos]; }

    const T& operator++();
    const T& operator++( int );
};



template<class T>
class SetOrderedArray : public SetBase<T>
{
private:
    Allocator allocator;
    T* pData;
    int power;


public:
    friend class IteratorSetOA<T>;

    typedef IteratorSetOA<T> iterator;
    typedef IteratorSetOA<const T> const_iterator;


    // Конструктор по умолчанию.
    SetOrderedArray() : pData(nullptr), power(0) { };

    // Консструктор копирования
    SetOrderedArray( const SetOrderedArray& other );


#if __cplusplus >= 201103L

    // Инициализация списком
    SetOrderedArray( std::initializer_list<T> list );

#endif



    // Деструктор по умолчанию.
    ~SetOrderedArray() { ; }


    // Геттер для power
    int getPower() const
    {
        return power;
    }


// Методы для управления итератором
    // iterator
    iterator begin();
    iterator end();


    // const_iterator
    const_iterator cbegin() const;
    const_iterator cend() const;


    // Операции над множествами.
    virtual SetOrderedArray<T>& operator&( const SetOrderedArray<T>& ) const;
    virtual SetOrderedArray<T>& operator|( const SetOrderedArray<T>& ) const;
    virtual SetOrderedArray<T>& operator-( const SetBase<T>& ) const ;
    virtual SetOrderedArray<T>& operator^( const SetOrderedArray<T>& ) const;


    // Операции сравнения множеств.
    virtual bool operator==( const SetOrderedArray<T>& ) const;
    virtual bool operator!=( const SetOrderedArray<T>& ) const;
    virtual bool operator< ( const SetOrderedArray<T>& ) const;
    virtual bool operator<=( const SetOrderedArray<T>& ) const;
    virtual bool operator> ( const SetOrderedArray<T>& ) const;
    virtual bool operator>=( const SetOrderedArray<T>& ) const;


    void add( const T& a );

private:
//    static void* operator new[]( std::size_t count ) { return allocator(count); }
//    static void* operator new( std::size_t count ) { return allocator(count); }

void insert( const T& a );
};



/**
 * Реализация методов класса IteratorSetOA
 **/




template<class T>
const T& IteratorSetOA<T>::operator++()
{
    return soa.pData[++currentPos];
}



template<class T>
const T& IteratorSetOA<T>::operator++( int )
{
    return soa.pData[currentPos++];
}



template<class T>
inline bool IteratorSetOA<T>::operator==( const IteratorSetOA<T>& other ) const
{
    return &soa == &other.soa && currentPos == other.currentPos;
}



template<class T>
inline bool IteratorSetOA<T>::operator!=( const IteratorSetOA<T>& other ) const
{
    return &soa != &other.soa || currentPos != other.currentPos;
}




/**
 * Реализация методов класса SetOrderedArray
 **/



#if __cplusplus >= 201103L



template<class T>
SetOrderedArray<T>::SetOrderedArray( std::initializer_list<T> list ) : allocator(sizeof(T)), pData((T*) allocator.alloc(
        sizeof(T) * list.size()))
{
    for (T x : list) {
        insert(x);
        ++power;
    }
}



#endif



template<class T>
SetOrderedArray<T>::SetOrderedArray( const SetOrderedArray<T>& other ) : pData(
        (T*) allocator.alloc(sizeof(T) * other.power)), power(other.power)
{
    for (int i = 0; i < power; ++i)
        pData[i] = other.pData[i];
}



////////////////////////////////////////////////////////////////////////////////////////////////////



template<class T>
typename SetOrderedArray<T>::iterator SetOrderedArray<T>::begin()
{
    return IteratorSetOA<T>(*this);
}



template<class T>
typename SetOrderedArray<T>::iterator SetOrderedArray<T>::end()
{
    return IteratorSetOA<T>(*this, power);
}



template<class T>
typename SetOrderedArray<T>::const_iterator SetOrderedArray<T>::cbegin() const
{
    return IteratorSetOA<const T>(const_cast<SetOrderedArray<T>>(*this));
}



template<class T>
typename SetOrderedArray<T>::const_iterator SetOrderedArray<T>::cend() const
{
    return IteratorSetOA<const T>(const_cast<SetOrderedArray<T>>(*this), power - 1);
}



/////////////////////////////////////////////////////////////////////////////////////////////////



template<class T>
SetOrderedArray<T>& SetOrderedArray<T>::operator&( const SetOrderedArray<T>& setB ) const
{
    SetOrderedArray<T> setC;

    for (int i = 0, j = 0; i < power && j < setB.power;) {
        if (pData[i] == setB.pData[j]) {
            setC.add(pData[i]);
            ++i;
            ++j;
        } else if (pData[i] > setB.pData[j])
            ++j;
        else
            ++i;
    }

    return setC;
}



template<class T>
SetOrderedArray<T>& SetOrderedArray<T>::operator|( const SetOrderedArray<T>& setB ) const
{
    SetOrderedArray<T> setC;
    int i, j;


    for (i = j = 0; i < power && j < setB.power;) {
        if (pData[i] == setB.pData[j]) {
            setC.add(pData[i]);
            ++i;
            ++j;
        } else if (pData[i] > setB.pData[j]) {
            setC.add(setB.pData[j++]);
        } else {
            setC.add(pData[i++]);
        }
    }


    while (i < power)
        setC.add(pData[i++]);

    while (j < setB.power)
        setC.add(setB.pData[j++]);

    return setC;
}



template<class T>
SetOrderedArray<T>& SetOrderedArray<T>::operator-( const SetBase<T>& setB ) const
{
    SetOrderedArray<T> setC;
    int i, j;

    for (i = j = 0; i < power && j < setB.power;) {
        if (pData[i] >= setB.pData[j]) {
            i += pData[i] == setB.pData[j];
            ++j;
        } else
            setC.add(pData[i++]);
    }

    while (i < power)
        setC.add(pData[i++]);

    return setC;
}



template<class T>
SetOrderedArray<T>& SetOrderedArray<T>::operator^( const SetOrderedArray<T>& setB ) const
{
    SetOrderedArray<T> setC;
    int i, j;

    for (i = j = 0; i < power && j < setB.power;) {
        if (pData[i] == setB.pData[j]) {
            ++i;
            ++j;
        } else if (pData[i] > setB.pData[j])
            setC.add(setB.pData[j++]);
        else
            setC.add(pData[i++]);
    }

    while (i < power)
        setC.add(pData[i++]);

    while (j < setB.power)
        setC.add(setB.pData[j++]);

    return setC;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////



template<class T>
bool SetOrderedArray<T>::operator==( const SetOrderedArray<T>& setB ) const
{
    if (power != setB.power)
        return false;
    for (int i = 0; i < power; ++i)
        if (pData[i] != setB.pData[i])
            return false;
    return true;
}



template<class T>
inline bool SetOrderedArray<T>::operator!=( const SetOrderedArray<T>& setB ) const
{
    return !operator==(setB);
}



template<class T>
bool SetOrderedArray<T>::operator<( const SetOrderedArray<T>& setB ) const
{
    if (power >= setB.power)
        return false;
    for (int i = 0, j = 0; i < power; i += (pData[i] == setB.pData[j]), ++j) {
        if (pData[i] < setB.pData[j])
            return false;
    }
    return true;
}



template<class T>
bool SetOrderedArray<T>::operator<=( const SetOrderedArray<T>& setB ) const
{
    if (power > setB.power)
        return false;
    for (int i = 0, j = 0; i < power; i += (pData[i] == setB.pData[j]), ++j) {
        if (pData[i] < setB.pData[j])
            return false;
    }
    return true;
}



template<class T>
bool SetOrderedArray<T>::operator>( const SetOrderedArray<T>& setB ) const
{
    return false;
}



template<class T>
bool SetOrderedArray<T>::operator>=( const SetOrderedArray<T>& setB ) const
{
    return false;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////



template<class T>
void SetOrderedArray<T>::add( const T& a )
{
    int i;
    static constexpr std::size_t sizeT = sizeof(T);

    pData = (T*) allocator.alloc(sizeT) - power;
    for (i = ++power - 2; i >= 0 && pData[i] > a; i--)
        pData[i + 1] = pData[i];

    pData[i + 1] = a;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////



template <class T>
void SetOrderedArray<T>::insert( const T& a )
{
    for (int i = power - 1; i >= 0 && pData[i] > a; --i)
        pData[i + 1] = pData[i];
}



#endif //CPP_SET_LIB_SETASSORTEDARRAY_H
