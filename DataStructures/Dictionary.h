#pragma once
#include "MutableSegmentedDeque.h"
#include "IDictionary.h"
#include <stdexcept>

template <typename T, typename U>
class Dictionary: public IDictionary<T, U> {
    class Pair {
    friend class Dictionary<T, U>;
    private:
        T key;
        U value;

        const U& getItem() const {
            return value;
    };
        
    public:
        Pair(const T& key, const U& value): key(key), value(value) {}
        Pair() = default;
        Pair(const Pair& other): key(other.key), value(other.value) {}

        const T& getKey() const {
            return key;
        }

        Pair& operator=(const Pair& other) {
            key = other.key;
            value = other.value;
            return *this;
        }
    };

private:
    int size = 0;
    MutableSegmentedDeque<Pair>* deque = new MutableSegmentedDeque<Pair>(100);

public:
    const U& getValue(const T& key) const override {
        for (int i = 0; i < deque->getLength(); ++i) {
            if ((deque->get(i)).getKey() == key) {
                return (deque->get(i)).getItem();
            }
        }
        throw std::invalid_argument("Key wasn't find");
    }

    void append(const T& key, const U& value) override {
        deque->append(Pair(key, value));
        ++size;
    }

    void remove(const T& key) override {
        for (int i = 0; i < deque->getLength(); ++i)  {
            if ((deque->get(i)).getKey() == key) {
                deque->removeAt(i);
                --size;
                return;
            }
        }
        throw std::invalid_argument("The wrong key. You can't delete non-existent pair");
    }

    int getSize() const {
        return size;
    }

    MutableSegmentedDeque<T>* getKeys() const {
        MutableSegmentedDeque<T>* keys = new MutableSegmentedDeque<T>();
        for (int i = 0; i < getSize(); ++i) {
            keys->append(deque->get(i).getKey());
        }
        return keys;
    }

    ~Dictionary() {
        delete deque;
    }
};


/*
template <typename T, typename U>
class IDictionary;

template <typename T, typename U>
class Pair {
friend class IDictionary<T, U>;
private:
    T key;
    U value;

    const U& getItem() const {
        return value;
};
    
public:
    Pair(const T& key, const U& value): key(key), value(value) {}
    Pair() = default;
    Pair(const Pair& other): key(other.key), value(other.value) {}

    const T& getKey() const {
        return key;
    }

    Pair& operator=(const Pair& other) {
        key = other.key;
        value = other.value;
        return *this;
    }
};
*/
