#include "vector.h"

template<class T>
vector<T>::vector(int arrSize, bool dim): size(0), maxCapacity(arrSize), dimension(dim) {
    if(dimension){
        buffer = new T[size][2];
    } else {
        buffer = new T[size];
    }
}

template<class T>
void vector<T>::pushBack(T data, int index) {
    if(!dimension) {
        if (size == maxCapacity) expand(maxCapacity + 5);
        buffer[size++] = data;
    } else {
        if (size == maxCapacity) expand(maxCapacity + 5);
        buffer[size][0] = index;
        buffer[size++][1] = data;
    }
}

template<class T>
void vector<T>::expand(int newCapacity) {
    if(!dimension) {
        T *newBuffer = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newBuffer[i] = buffer[i];
        }
        maxCapacity = newCapacity;
        delete []buffer;
        buffer = newBuffer;
    } else {
        T *newBuffer = new T[newCapacity][2];
        for (int i = 0; i < size; i++) {
            newBuffer[i][0] = buffer[i][0];
            newBuffer[i][1] = buffer[i][1];
        }
        maxCapacity = newCapacity;
        delete []buffer;
        buffer = newBuffer;
    }

}

template<class T>
vector<T>::~vector() {
    delete []buffer;
}
