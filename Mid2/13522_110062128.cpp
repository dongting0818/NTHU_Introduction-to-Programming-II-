//#include "13522.h"
#include "function.h"

int& Darray::operator[](int a){
    if(a<size){
        return data[a];
    }
}

void Darray::pushback(int x){
    if(size == capacity) resize();
    data[size] = x;
    size++;
}

void Darray::popback(void){
    if(size == capacity) resize();
    if(size!=0){
        data[size] = 0;
    }
    size--;
}

void Darray::clear(void){
    for(int i=0;i<size;i++){
        data[i] = 0;
    }
    size = 0;
}

int Darray::length(void){
    return size;
}

void Darray::resize(void){
    int* temp = new int[size];
    for(int i=0;i<size;i++){
        temp[i] = data[i];
    }
    delete[] data;
    capacity*=2;
    data = new int[capacity];
    for(int i=0;i<capacity;i++){
        if(i<size) data[i] = temp[i];
        else data[i] = 0;
    }
    delete[] temp;
}

Darray::~Darray(){
    delete[] data;
}



