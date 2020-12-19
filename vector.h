#ifndef PROJECT_2_VECTOR_H
#define PROJECT_2_VECTOR_H



static const unsigned char bit_mask[8] = {
        0x80,  //10000000
        0x40,  //01000000
        0x20,  //00100000
        0x10,  //00010000
        0x08,  //00001000
        0x04,  //00000100
        0x02,  //00000010
        0x01   //00000001

};


class BF {
public:
    int size;
    int numberOfRecords;
    char* array;
    int numberOfUpdates;
    int nextUpdate;
    BF(int,int);
    bool insert(const char*);
    void updateBit(int);
    bool checkBit(int);
    bool find(const char*);
    bool search(const char*);
    void resetNextUpdate();
    ~BF();
};


int hash1(const char* x, int size){
    int h = 5381;
    int length = (int) strlen(x);
    for(int i = 0; i < length; i++){
        h = ((h*13) + x[i]) % size;
    }
    return h;
}

int hash2(const char* x, int size){
    int h = 631;
    int length = (int) strlen(x);
    for(int i = 0; i < length; i++){
        h = ((h*31) + x[i]) % size;
    }
    return h;
}

int hash3(const char* x, int size){
    int h = 1789;
    int length = (int) strlen(x);
    for(int i = 0; i < length; i++){
        h = ((h*17) + x[i]) % size;
    }
    return h;
}

bool checkIfPrime(int n){ //checks if number n is prime
    if (n%2 == 0 || n%3 == 0)
        return false;

    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
            return false;

     return true;

}

int findNextPrime(int n){   // Checks if n is prime, if not
    // finds the next bigger number from n that is prime
    if (n<=3)
        return n;
    bool isPrime = false;
    if (checkIfPrime(n))
        isPrime = true;
    while(isPrime==false){
        n++;
        isPrime = checkIfPrime(n);
    }
    return n;
}



BF::BF(int suggestedSize,int nou){

    size = findNextPrime(suggestedSize);
    numberOfUpdates = nextUpdate = nou;
    numberOfRecords = 0;
    array = new char[(size/8)+1];

}

bool BF::insert(const char* id) { //inserts a  record
    //returns true if the bloom filter needs to resize because the required number of updates have been reached.

    int bit = hash1(id,size);
    updateBit(bit);
    bit = hash2(id,size);
    updateBit(bit);
    bit = hash3(id,size);
    updateBit(bit);
    numberOfRecords++;
    nextUpdate--;
    if(nextUpdate ==0) {
        return true;
    }
    return false;
}

void BF::updateBit(int bit) { //updating the bit to 1
    int indexA = bit/8; // indexA + indexB = bit
    int indexB = bit%8;
    array[indexA] = array[indexA] | bit_mask[indexB];
}

bool BF::find(const char* id) { //tries to find if the id exists, if so it returns 'true'. If it doesn't exist it returns 'false'
    int bit = hash1(id,size);
    if (!checkBit(bit))
        return false;
    bit = hash2(id,size);
    if (!checkBit(bit))
        return false;
    bit = hash3(id,size);
    return checkBit(bit);
}

bool BF::checkBit(int bit) { //checks if the bit is set to 1
    int indexA = bit/8; // indexA + indexB = bit
    int indexB = bit%8;
    return (array[indexA] & bit_mask[indexB]) != 0;
}

BF::~BF() {
    delete array;
}



bool BF::search(const char* key) {
    int bit = hash1(key,size);
    if(!checkBit(bit))
        return false;
    bit = hash2(key,size);
    if(!checkBit(bit))
        return false;
    bit = hash3(key,size);
    return checkBit(bit);
}

void BF::resetNextUpdate() {
    nextUpdate = numberOfUpdates;
}



template <class T>
class myVector {
public:
    T **sBuffer;
    T *buffer;
    int size, maxCapacity;
    bool sparse;
    myVector(int, bool);
    int pushBack(T, int = 0);
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
        buffer = NULL;
    } else {
        buffer = new T[maxCapacity];
        sBuffer = NULL;
    }
}

template<class T>
int myVector<T>::pushBack(T data, int index) {
    if(!sparse) {
        if (size == maxCapacity) expand(maxCapacity + 5);
        buffer[size++] = data;
        return size;
    } else {
        if (size == maxCapacity) expand(maxCapacity + 5);
        sBuffer[size][0] = index;
        sBuffer[size++][1] = data;
        return size;
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
