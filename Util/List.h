//
// Created by Сергей on 26.07.2016.
//

#ifndef MAIN_LIST_H
#define MAIN_LIST_H


#include <stdexcept>


template<class T>
class List
{
private:
    class Link
    {
    private:
        T data_;
        Link* next_;
    public:

        Link( const T& data ) : data_(data), next_(nullptr) { }


    };

    Link* first_;
public:
    void push( const T& a );
    T& pop();
    T& peek() const;
};







#endif //MAIN_LIST_H
