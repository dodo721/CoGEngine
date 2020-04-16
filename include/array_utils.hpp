#ifndef ARRAY_UTILS_HPP
#define ARRAY_UTILS_HPP

#include <vector>

using namespace std;

template <class T>
T* vectorToArray (vector<T> vec) {
    return &vec[0];
}

template <class T>
vector<T> arrayToVector (T* array, int length) {
    return vector<T>(array, array+length);
}

#endif