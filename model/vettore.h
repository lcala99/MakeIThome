#include <iostream>
#include <string>
#ifndef VETTORE_H
#define VETTORE_H

typedef unsigned int u_int;

template <class T> class Vettore;

class Iteratore;
class const_Iteratore;

template<class T>
class Vettore{

    friend class Iteratore;
    friend class const_Iteratore;

    private:
        T* info;
        u_int size;
        u_int capacity;

    public:
        class Iteratore{
            friend class Vettore<T>;
            private:
                Vettore<T>* punt;
                u_int index;

                Iteratore(Vettore<T>& v, u_int ind=0);
            public:
                Iteratore(const Iteratore& it);
                // overloading OPERATOR
                Iteratore operator++(int);
                Iteratore& operator++();
                Iteratore operator--(int);
                Iteratore& operator--();
                T& operator*() const;
                T* operator->()const;
                Iteratore operator+(u_int ind) const;
                Iteratore operator-(u_int ind) const;
                bool operator!=(const Iteratore& it) const;
                bool operator==(const Iteratore& it) const;
        };

        class const_Iteratore{
            friend class Vettore<T>;
            private:
                const Vettore<T>* punt;
                u_int index;
                const_Iteratore(const Vettore<T>& v, u_int ind=0);
            public:
                const_Iteratore(const const_Iteratore& it);
                // overloading OPERATOR
                const_Iteratore operator++(int);
                const_Iteratore& operator++();
                const_Iteratore operator--(int);
                const_Iteratore& operator--();
                const T& operator*() const;
                const T* operator->()const;
                const_Iteratore operator+(u_int ind) const;
                const_Iteratore operator-(u_int ind) const;
                bool operator!=(const const_Iteratore& it) const;
                bool operator==(const const_Iteratore& it) const;
        };

        Vettore();
        Vettore(T t);
        Vettore(u_int n, T t);

        Vettore(typename Vettore<T>::Iteratore first, typename Vettore<T>::Iteratore second );
        Vettore(const Vettore& vec); //ok

        T& operator[](u_int ind);
        const T& operator[](u_int ind) const;
        bool operator==(const Vettore& vec)const;

        // Vettore METHOD
        Iteratore begin() ;
        Iteratore end() ;
        const_Iteratore cbegin() const;
        const_Iteratore cend() const;
        u_int Size() const;

        void push_back(const T& val);

        void insert(Iteratore it, T val); //perche non è per rif?
        void insert(const_Iteratore it, T val);
        //void insert(const T& val);
        void remove(Iteratore it); //rimuove l'elemento in posizione it
        void remove(const_Iteratore it);

        void remove(const T& value); //rimuove elemento con valore value
        T pop_back(); //rimuove ultimo elemento
        bool empty(); //true se il vettore è vuoto
        Vettore& merge(Vettore& vec);

};


/********************************************** ITERATORE ***************************************/
template <class T>
Vettore<T>::Iteratore::Iteratore(Vettore<T>& v , u_int ind){
    punt = &v;
    if(ind < 0) index=0;
    else if(ind>punt->Size()) index=punt->Size();
    else index=ind;
}

template <class T>
Vettore<T>::Iteratore::Iteratore(const Iteratore& it):
    punt(it.punt), index(it.index) {}

template <class T>
typename Vettore<T>::Iteratore Vettore<T>::Iteratore::operator++(int){
    Iteratore ret(*this);
    if(punt != nullptr) {
        if(index < punt->Size()) {
            index++;
        }
    }
    return ret;
}

template <class T>
typename Vettore<T>::Iteratore& Vettore<T>::Iteratore::operator++(){
      if(punt != nullptr) {
        if(index < punt->Size()) {
            index++;
        }

      }
      return *this;
}

template <class T>
typename Vettore<T>::Iteratore Vettore<T>::Iteratore::operator--(int){
    if(index>0){
        index--;
    }
    return *this;
}

template <class T>
typename Vettore<T>::Iteratore& Vettore<T>::Iteratore::operator--(){
    Iteratore ret(*this);
    if(index>0){
        index--;
    }
      return ret;
}

template <class T>
T& Vettore<T>::Iteratore::operator*() const{
    return (*punt)[index];
}

template <class T>
T* Vettore<T>::Iteratore::operator->() const {
    return &(*punt)[index];
}

template <class T>
typename Vettore<T>::Iteratore Vettore<T>::Iteratore::operator+(u_int ind) const{
    return Iteratore(*punt, index+ind);
}

template <class T>
typename Vettore<T>::Iteratore Vettore<T>::Iteratore::operator-(u_int ind) const{
    return Iteratore(*punt, index-ind);
}

template <class T>
bool Vettore<T>::Iteratore::operator==(const Iteratore& it) const{
    return punt == it.punt && index == it.index;
}

template <class T>
bool Vettore<T>::Iteratore::operator!=(const Iteratore& it) const{
    return !(it==*this);
}


/********************************************** CONST ITERATORE ***************************************/

template <class T>
Vettore<T>::const_Iteratore::const_Iteratore(const Vettore<T>& v , u_int ind){
    punt = &v;
    if(ind < 0) index=0;
    else if(ind>punt->Size()) index=punt->Size();
    else index=ind;
}

template <class T>
Vettore<T>::const_Iteratore::const_Iteratore(const const_Iteratore& it):
    punt(it.punt), index(it.index) {}

template <class T>
typename Vettore<T>::const_Iteratore Vettore<T>::const_Iteratore::operator++(int){
    const_Iteratore ret(*this);
    if(punt != nullptr) {
        if(index < punt->Size()) {
            index++;
        }
    }
    return ret;
}

template <class T>
typename Vettore<T>::const_Iteratore& Vettore<T>::const_Iteratore::operator++(){
      if(punt != nullptr) {
        if(index < punt->Size()) {
            index++;
        }

      }
      return *this;
}

template <class T>
typename Vettore<T>::const_Iteratore Vettore<T>::const_Iteratore::operator--(int){
    if(index>0){
        index--;
    }
    return *this;
}

template <class T>
typename Vettore<T>::const_Iteratore& Vettore<T>::const_Iteratore::operator--(){
    Iteratore ret(*this);
    if(index>0){
        index--;
    }
      return ret;
}

template <class T>
const T& Vettore<T>::const_Iteratore::operator*() const{
    return (*punt)[index];
}

template <class T>
const T* Vettore<T>::const_Iteratore::operator->() const {
    return &(*punt)[index];
}

template <class T>
typename Vettore<T>::const_Iteratore Vettore<T>::const_Iteratore::operator+(u_int ind) const{
    return Iteratore(*punt, index+ind);
}

template <class T>
typename Vettore<T>::const_Iteratore Vettore<T>::const_Iteratore::operator-(u_int ind) const{
    return Iteratore(*punt, index-ind);
}

template <class T>
bool Vettore<T>::const_Iteratore::operator==(const const_Iteratore& it) const{
    return punt == it.punt && index == it.index;
}

template <class T>
bool Vettore<T>::const_Iteratore::operator!=(const const_Iteratore& it) const{
    return !(it==*this);
}


/********************************************** VETTORE ***************************************/
template <class T>
Vettore<T>::Vettore():info(nullptr), size(0), capacity(0){}

template <class T>
Vettore<T>::Vettore(T t): info(new T[1]), size(0),capacity(1){
    push_back(t);
}

template <class T>
Vettore<T>::Vettore(u_int n, T t): info(new T[n]), size(0), capacity(n){
    for(int i=1; i<n; i++){
        push_back(t);
    }
}

template <class T>
Vettore<T>::Vettore(typename Vettore<T>::Iteratore first, typename  Vettore<T>::Iteratore second): info(nullptr), size(0), capacity(0){
    if((first.punt==second.punt) && first.index<second.index){
        info=new T[second.index-first.index];
        capacity=second.index-first.index;
        for(auto it=first; it!=second; it++){
            push_back(*it);
        }
    }
}

template <class T>
Vettore<T>::Vettore(const Vettore& vec): info(new T[vec.size]), size(0), capacity(vec.size){
    for(auto it=vec.cbegin(); it!=vec.cend(); it++){
        push_back(*it);
    }

}

template <class T>
typename Vettore<T>::Iteratore Vettore<T>::begin() {
    return Iteratore(*this,0);
}

template <class T>
typename Vettore<T>::Iteratore Vettore<T>::end() {
    return Iteratore(*this, size);
}

template <class T>
typename Vettore<T>::const_Iteratore Vettore<T>::cbegin() const{
    return const_Iteratore(*this, 0);
}

template <class T>
typename Vettore<T>::const_Iteratore Vettore<T>::cend() const{
    return const_Iteratore(*this, size);
}

template <class T>
u_int Vettore<T>::Size() const{
    return size;
}

template <class T> //ok
void Vettore<T>::push_back(const T& val){
    if(info){ //l'array non è vuoto
        if(size == capacity){ //l'array è pieno
            capacity *= 2; //raddoppio capacity
            T* aux  = new T[capacity];
            for(u_int i=0; i<size; i++){
                aux[i]=info[i];
            }
            delete[] info;
            info = aux;
            info[size]=val; //metto in coda l'elemento da aggiungere
        } else info[size]= val;
        size++;
    }
    else{ //array vuoto
        info = new T[1];
        info[0] = val;
        size = 1;
        capacity = 1;
    }
    return;
}

template <class T>
void Vettore<T>::insert(Iteratore it, T val){
    if( end() == it ){
        push_back(val);
        return;
    }
    if(size==capacity){
        capacity *= 2;
        T* aux  = new T[capacity];
        for(int i = 0; i < size; i++){
            aux[i]=info[i];
        }
        delete[] info;
        info = aux;
    }
    for(int i=size; i!=it.index; i--){
        info[i]=info[i-1];
    }
    info[it.index]=val;
    size++;
}

template <class T>
void Vettore<T>::insert(const_Iteratore it, T val){
    if( end() == it ){
        push_back(val);
        return;
    }
    if(size==capacity){
        capacity *= 2;
        T* aux  = new T[capacity];
        for(int i = 0; i < size; i++){
            aux[i]=info[i];
        }
        delete[] info;
        info = aux;
    }
    for(int i=size; i!=it.index; i--){
        info[i]=info[i-1];
    }
    info[it.index]=val;
    size++;
}

template <class T>
void Vettore<T>::remove(const T& value){
    bool ctr = true;
    for(auto it=begin(); ctr && it!=end(); it++){
        if(*it==value){
            remove(it);
            ctr=false;
        }
    }
}

template <class T>
void Vettore<T>::remove(Iteratore iter){
    if( iter.index < size ){
        for(u_int i = iter.index; i < size-1; i++){
            info[i]=info[i+1];
        }
        size--;
     }
}

template <class T>
void Vettore<T>::remove(const_Iteratore iter){
    if( iter.index < size ){
        for(int i = iter.index; i < size-1; i++){
            info[i]=info[i+1];
        }
        size--;
     }
}

template <class T>
T Vettore<T>::pop_back(){
    T ret = info[size-1];
    size--;
    return ret;
}

template <class T>
bool Vettore<T>::empty(){
    return size==0;
}

template <class T>
Vettore<T>& Vettore<T>::merge(Vettore<T>& vec){
    for(auto it=vec.begin(); it!=vec.end(); it++){
        push_back(*it);
    }
    return *this;
}

template <class T>
bool Vettore<T>::operator==(const Vettore& vec)const{
    if(info == vec.info) return true;
    if(size != vec.Size()) return false;
    bool control = true;
    for( Vettore<T>::const_Iteratore cont = cbegin(); cont != cend() && control; cont++ ){
        for( Vettore<T>::const_Iteratore cont_vec = cbegin(); cont_vec != vec.cend() && control; cont_vec++ ){
            if( *cont != *cont_vec ) control = false;
        }
    }
    return control;
}



template <class T>
T& Vettore<T>::operator[](u_int ind) {
    return info[ind];
}

template <class T>
const T& Vettore<T>::operator[](u_int ind) const {
    return info[ind];
}

#endif
