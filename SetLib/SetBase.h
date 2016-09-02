//
// Created by Сергей on 13.08.2016.
//

#ifndef SETBASE_H
#define SETBASE_H

#include <typeinfo>

template<typename T>
class SetBase
{
public:
    // Конструктор по умолчанию.
    SetBase() = default;
    virtual ~SetBase() = default;


    virtual int getPower() const = 0;


    // Операции над множествами.
    virtual SetBase operator&( const SetBase& ) const = 0;
    virtual SetBase operator|( const SetBase& ) const = 0;
    virtual SetBase operator-( const SetBase& ) const = 0;
    virtual SetBase operator^( const SetBase& ) const = 0;


    // Операции сравнения множеств.
    virtual bool operator==( const SetBase& ) const = 0;
    virtual bool operator!=( const SetBase& ) const = 0;
    virtual bool operator< ( const SetBase& ) const = 0;
    virtual bool operator<=( const SetBase& ) const = 0;
    virtual bool operator> ( const SetBase& ) const = 0;
    virtual bool operator>=( const SetBase& ) const = 0;


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
