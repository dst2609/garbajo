#include "myarraylist.h"
#include <iostream>
using namespace std;

#include <chrono>
using namespace std::chrono;

template <class elemType> arrayListType<elemType>::arrayListType(int size):maxSize(size), length(0) {
    list = new elemType[size];
}

template <class elemType> arrayListType<elemType>::~arrayListType() {
    delete[] list;
}

template <class elemType>
void arrayListType<elemType>::insertEnd(const elemType &insertItem) {
    if (length == maxSize){
        cout << "FULL! \n" << endl;
        return;
    }
    list[length++] = insertItem;
 
}

template <class elemType>
int arrayListType<elemType>::seqSearch(const elemType &item) const {
    for (int i = 0; i < length; i++) {
        if (list[i] == item) return i;
    }
    return -1;
}

template <class elemType>
int arrayListType<elemType>::binarySearch(const elemType &item, int start, int end) const {
    if (end == -1) end = length;    //end will be 1 even for 1 length of element
    if (start >= end) return -1;
    int mid = start + (end-start)/2;
    if (list[mid] == item) return mid;
    if (list[mid] > item) end = mid;
    else start = mid+1; //[start, end) end not included so mid+1
    return binarySearch(item, start, end);

}

template <class elemType>
bool arrayListType<elemType>::isFull(bool printMessage) const {

}



template <class elemType> void arrayListType<elemType>::print() const {
    cout << "len " << length << " max size " << maxSize << endl;
    int i = 0;
    for (; i < 10 && i < length; i++) {
        cout << "[" << i << "] " << list[i] << endl;
    }
    if (length - i > 10) {
        cout << "..." << endl;
        i = length - i;
    }
    for (; i < length; i++) {
        cout << "[" << i << "] " << list[i] << endl;
    }
}
int main() {
    auto mylist = arrayListType<int>(2000000);
    for (int i = 0; i < 2000000; i++) {
        mylist.insertEnd(i*100 + 17);
    }

    // int to_find = 100000017;
    int to_find = 199999917;
    // int to_find = 117;
    auto start = high_resolution_clock::now();
    int ind = mylist.seqSearch(to_find);
    duration<double, micro> duration = high_resolution_clock::now() - start;
    cout << to_find << " seq found at " << ind << " took " << duration.count() << endl;


    start = high_resolution_clock::now();
    ind = mylist.binarySearch(to_find);
    duration = high_resolution_clock::now() - start;
    cout << to_find << " binary found at " << ind << " took " << duration.count() << endl;

    mylist.print();
}