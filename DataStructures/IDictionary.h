#pragma once
#include "MutableSegmentedDeque.h"

template <typename T, typename U>
class IDictionary {
public:
    virtual void remove(const T& key) = 0;

    virtual void append(const T& key, const U& value) = 0;

    virtual const U& getValue(const T& key) const = 0;

    virtual int getSize() const = 0;

    virtual MutableSegmentedDeque<T>* getKeys() const = 0;
};