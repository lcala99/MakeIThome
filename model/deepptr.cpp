#ifndef DEEPPTR_H
#define DEEPPTR_H
#include <iostream>
using namespace std;

template<class T>
class DeepPtr {
    private:
        T* ptr;
    public:
        T* get();
        DeepPtr();
        explicit DeepPtr(const T* punt);
        DeepPtr(const DeepPtr& dptr);
        DeepPtr& operator=(const DeepPtr& dptr);
        ~DeepPtr();
        T& operator*();
        T* operator->();
        operator bool() const;
};

template <class T>
T* DeepPtr<T>::get(){return ptr;}

template <class T>
DeepPtr<T>::DeepPtr() : ptr(nullptr) {}


template <class T>
DeepPtr<T>::DeepPtr(const T* punt):ptr(punt->clone()){}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr& dptr):ptr(dptr.ptr){}

template <class T>
typename DeepPtr<T>::DeepPtr& DeepPtr<T>::operator=(const DeepPtr& dptr){
    if(this != &dptr){
        if(dptr){
            delete ptr;
            ptr = dptr.ptr->clone();
        }else {
            ptr = nullptr;
        }
    }
    return *this;
}

template <class T>
DeepPtr<T>::~DeepPtr(){
    delete[] ptr;
}

template <class T>
T& DeepPtr<T>::operator*(){
    return *ptr;
}

template <class T>
T* DeepPtr<T>::operator->(){
    return ptr;
}

template <class T>
DeepPtr<T>::operator bool() const{
    return ptr;
}

#endif // DEEPPTR_H
