
#include <cstdlib>
#include <array>
#include <list>
#include <functional>
#include <initializer_list>
#include <iostream>

template<typename Key, size_t Size = 23>
class Set {
    std::array<std::list<Key>, Size> buckets;

    size_t hash(const Key& k) const {
        return Set::hasher{}(k);
    }

public:

    using value_type = Key;
    using key_type = Key;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using key_equal = std::equal_to<key_type>;
    using hasher = std::hash<key_type>;

    Set() = default;

    Set(std::initializer_list<Set::key_type> initializerList);

    template<typename InputIt>
    Set(InputIt first, InputIt last);

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
Set<Key, Size>::Set(std::initializer_list<Key> initializerList) {
    for (const auto& key : initializerList) {
        this->insert(key);
    }
}

template<typename Key, size_t Size>
template<typename InputIt>
Set<Key, Size>::Set(InputIt first, InputIt last) {
    this->insert(first, last);
}

template<typename Key, size_t Size>
typename Set<Key, Size>::size_type  Set<Key, Size>::size() const {
    Set::size_type size = 0;
    for (const auto& bucket : this->buckets) {
        size += bucket.size();
    }
    return size;
}

template<typename Key, size_t Size>
void Set<Key, Size>::insert(Key key) {
    if (this->contains(key)) {
        return;
    }
    const auto bucket = this->hash(key) % Size;
    this->buckets.at(bucket).push_front(key);
}

template<typename Key, size_t Size>
void Set<Key, Size>::erase(Key key) {
    const auto bucket = this->hash(key) % Size;
    this->buckets.at(bucket).erase(key);
}

template<typename Key, size_t Size>
bool Set<Key, Size>::contains(Key key) {
    const auto bucket = this->hash(key);
    const auto equals = Set::key_equal{};
    for (const auto& e : this->buckets.at(bucket)) {
        if (equals(e, key)) {
            return true;
        }
    }
    return false;
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
    for (const auto& bucket : this->buckets) {
        for (const auto& key : bucket) {
            o << key << " ";
        }
    }
}

template<typename Key, size_t Size>
template<typename InputIt>
void Set<Key, Size>::insert(InputIt first, InputIt last) {
    while (first != last) {
        this->insert(*first);
        first++;
    }
}
