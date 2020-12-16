#ifndef PROJECT_2_VECTOR_H
#define PROJECT_2_VECTOR_H

template <class T>
class myVector {
public:
    T **sBuffer;
    T *buffer;
    int size, maxCapacity;
    bool sparse;
    myVector(int, bool);
    void pushBack(T, int = 0);
    void expand(int);
    ~myVector();
};

template<class T>
myVector<T>::myVector(int arrSize, bool dim): size(0), maxCapacity(arrSize), sparse(dim) {
    if(sparse){
        sBuffer = new T*[maxCapacity];
        for(int i = 0; i < maxCapacity; i++){
            sBuffer[i] = new T[2];
        }
    } else {
        buffer = new T[maxCapacity];
    }
}

template<class T>
void myVector<T>::pushBack(T data, int index) {
    if(!sparse) {
        if (size == maxCapacity) expand(maxCapacity + 5);
        buffer[size++] = data;
    } else {
        if (size == maxCapacity) expand(maxCapacity + 5);
        sBuffer[size][0] = index;
        sBuffer[size++][1] = data;
    }
}

template<class T>
void myVector<T>::expand(int newCapacity) {
    if(!sparse) {
        T *newBuffer = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newBuffer[i] = buffer[i];
        }
        maxCapacity = newCapacity;
        delete []buffer;
        buffer = newBuffer;
    } else {
        T **newBuffer = new T*[newCapacity];
        for(int i = 0; i < newCapacity; i++){
            newBuffer[i] = new T[2];
        }
        for (int i = 0; i < size; i++) {
            newBuffer[i][0] = sBuffer[i][0];
            newBuffer[i][1] = sBuffer[i][1];
        }
        for (int i = 0; i < maxCapacity; i++) {
            delete[]sBuffer[i];
        }
        delete []sBuffer;
        maxCapacity = newCapacity;
        sBuffer = newBuffer;
    }

}

template<class T>
myVector<T>::~myVector() {
    if(sparse) {
        for (int i = 0; i < maxCapacity; i++) {
            delete[]sBuffer[i];
        }
        delete[]sBuffer;
    } else {
        delete []buffer;
    }

}



#endif
