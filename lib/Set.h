
#include "List.h"

#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <iostream>

template<typename Key, size_t Size = 23>
class Set {
public:
    using value_type = Key;
    using key_type = Key;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using key_equal = std::equal_to<key_type>;
    using hasher = std::hash<key_type>;

private:
    List<key_type>* buckets;

    size_type hash(const_reference k) const {
        return hasher{}(k);
    }

    void mkBuckets() {
        this->buckets = new List<key_type>[Size];
        for (size_t iBucket = 0; iBucket < Size; iBucket++) {
            this->buckets[iBucket] = List<key_type>{};
        }
    }

public:
    Set();

    Set(std::initializer_list<Set::key_type> initializerList);

    template<typename InputIt>
    Set(InputIt first, InputIt last);

    ~Set();

    void insert(Key key);

    template<typename InputIt>
    void insert(InputIt first, InputIt last);

    void erase(Key key);
    bool contains(Key key);

    Set::size_type count(const key_type& key) const;

    Set::size_type size() const;
    bool empty();

    void dump(std::ostream& o = std::cerr) const;
};

template<typename Key, size_t Size>
Set<Key, Size>::Set() {
    mkBuckets();
}

template<typename Key, size_t Size>
Set<Key, Size>::Set(std::initializer_list<Key> initializerList) {
    mkBuckets();
    for (const auto& key : initializerList) {
        this->insert(key);
    }
}

template<typename Key, size_t Size>
template<typename InputIt>
Set<Key, Size>::Set(InputIt first, InputIt last) {
    mkBuckets();
    this->insert(first, last);
}

template<typename Key, size_t Size>
typename Set<Key, Size>::size_type  Set<Key, Size>::size() const {
    Set::size_type size = 0;
    for (size_t iBucket = 0; iBucket < Size; iBucket++) {
        size += this->buckets[iBucket].size();
    }
    return size;
}

template<typename Key, size_t Size>
void Set<Key, Size>::insert(Key key) {
    if (this->contains(key)) {
        return;
    }
    const auto bucketIdx = this->hash(key) % Size;
    this->buckets[bucketIdx].push_front(key);
}

template<typename Key, size_t Size>
void Set<Key, Size>::erase(Key key) {
    const auto bucketIdx = this->hash(key) % Size;
    this->buckets[bucketIdx].remove(key);
}

template<typename Key, size_t Size>
bool Set<Key, Size>::contains(Key key) {
    const auto bucketIdx = this->hash(key) % Size;
    return this->buckets[bucketIdx].contains(key);
}

template<typename Key, size_t Size>
bool Set<Key, Size>::empty() {
    return this->size() == 0;
}

template<typename Key, size_t Size>
typename Set<Key, Size>::size_type Set<Key, Size>::count(const key_type &key) const {
    if (this->contains(key)) {
        return 1;
    }
    return 0;
}

template<typename Key, size_t Size>
void Set<Key, Size>::dump(std::ostream &o) const {
    for (size_t iBucket = 0; iBucket < Size; iBucket++) {
        this->buckets[iBucket].dump(o);
    }
}

template<typename Key, size_t Size>
template<typename InputIt>
void Set<Key, Size>::insert(InputIt first, InputIt last) {
    InputIt current = first;
    while (current != last) {
        this->insert(*current);
        current++;
    }
}

template<typename Key, size_t Size>
Set<Key, Size>::~Set() {
    for (size_t iBucket = 0; iBucket < Size; iBucket++) {
        this->buckets[iBucket].clear();
    }
    delete[] this->buckets;
}
