#ifndef PROJECT_2_VECTOR_H
#define PROJECT_2_VECTOR_H

template <class T>
class vector {
public:
    T *buffer;
    int size, maxCapacity;
    bool dimension;
    vector(int, bool);
    void pushBack(T, int = 0);
    void expand(int);
    ~vector();
};


#endif
