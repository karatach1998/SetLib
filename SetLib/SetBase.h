//
// Created by Сергей on 13.08.2016.
//

#ifndef SETBASE_H
#define SETBASE_H

//#include <typeinfo>
#include <initializer_list>


template<typename T>
class SetBase
{
public:
    // Конструктор по умолчанию.
    SetBase() = default;
    virtual ~SetBase() = default;
    SetBase( std::initializer_list<T> );


    virtual int getPower() const = 0;


    // Операции над множествами.
//    virtual SetBase<T>& operator&( const SetBase<T>& ) const = 0;
//    virtual SetBase<T>& operator|( const SetBase<T>& ) const = 0;
    virtual const SetBase<T>& operator-( const SetBase<T>& ) const = 0;
//    virtual SetBase<T>& operator^( const SetBase<T>& ) const = 0;


    // Операции сравнения множеств.
//    virtual bool operator==( const SetBase<T>& ) const = 0;
//    virtual bool operator!=( const SetBase<T>& ) const = 0;
//    virtual bool operator< ( const SetBase<T>& ) const = 0;
//    virtual bool operator<=( const SetBase<T>& ) const = 0;
//    virtual bool operator> ( const SetBase<T>& ) const = 0;
//    virtual bool operator>=( const SetBase<T>& ) const = 0;


//    void add( const T& );

//    friend SetBase<T> operator+( const SetBase<T>& A, const SetBase<T>& B );
};



/*
template <typename T>
auto operator+( const SetBase<T>& A, const SetBase<T>& B ) -> decltype(A)
{
    if (typeid(A) != typeid(B))
        throw std::bad_typeid();
    else
        dynamic_cast<>
}
*/



#endif //SETBASE_H
