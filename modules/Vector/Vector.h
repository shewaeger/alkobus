#ifndef VECTOR_H
#define VECTOR_H JUN_2014

#include <Arduino.h>

//as far as I can tell placement new is not included with AVR or arduino.h
template<typename T>
void* operator new(size_t s, T* v){
    return v;
}

//*********************************************************************************
//                               Allocator for Vector
//*********************************************************************************
template<typename T> struct Simple_alloc {

    Simple_alloc() {};

    //memory allocation
    T* allocate(int n)
    { return reinterpret_cast<T*>(new char[n*sizeof(T)]); }
    void deallocate(T* p, int n)
    { delete[] reinterpret_cast<char*>(p); }

    //construction/destruction
    void construct(T* p, const T& t) { new(p) T(t); }
    void destroy(T* p) { p->~T(); }
};

//*********************************************************************************
//                               Vector
//*********************************************************************************
template<class T, class A = Simple_alloc<T> >
class Vector {

    A alloc;

    int sz;
    T* elem;
    int space;

    Vector(const Vector&);			//private copy constrution because I
    //have not got this working yet and don't
    //want to expose this for clients who might
    //be expecting it.

public:
    Vector() : sz(0), elem(0), space(0) {}
    Vector(const int s) : sz(0) {
        reserve(s);
    }

    Vector& operator=(const Vector&);	//copy assignment

    ~Vector() {
        for(int i=0; i<sz; ++i) alloc.destroy(&elem[i]);
    }

    T& operator[](int n) { return elem[n]; }
    const T& operator[](int n) const { return elem[n]; }

    int size() const { return sz; }
    int capacity() const { return space; }

    void reserve(int newalloc);
    void push_back(const T& val);

};

template<class T, class A>
Vector<T, A>& Vector<T, A>::operator=(const Vector& a) {
    if(this==&a) return *this;

    if(a.size()<=space) {	//enough space, no need for new allocation
        for(int i=0; i<a.size(); ++i) elem[i]=a[i];
        sz = a.size();
        return *this;
    }

    T* p = alloc.allocate(a.size());		//get new memory
    for(int i=0; i<a.size(); ++i) {
        alloc.construct(&p[i], a[i]);	//copy
    }
    for(int i=0; i<sz; ++i) alloc.destroy(&elem[i]);
    space = sz = a.size();
    elem = p;
    return *this;
}

template<class T, class A> void Vector<T, A>::reserve(int newalloc){
    if(newalloc <= space) return;		                    //never decrease space
    T* p = alloc.allocate(newalloc);
    for(int i=0; i<sz; ++i) alloc.construct(&p[i], elem[i]);	//copy
    for(int i=0; i<sz; ++i) alloc.destroy(&elem[i]);
    alloc.deallocate(elem, space);
    elem = p;
    space = newalloc;
}

template<class T, class A>
void Vector<T, A>::push_back(const T& val){
    if(space == 0) reserve(4);				//start small
    else if(sz==space) reserve(2*space);
    alloc.construct(&elem[sz], val);
    ++sz;
}

#endif