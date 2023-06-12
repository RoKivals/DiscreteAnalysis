#ifndef DISKRETANALYSIS_COUNTINGSORT_H
#define DISKRETANALYSIS_COUNTINGSORT_H

#include <functional>
#include "vector.h"

template<class T>
void CountingSort(Vector<T> &, std::function<size_t(T)>);


#endif //DISKRETANALYSIS_COUNTINGSORT_H
