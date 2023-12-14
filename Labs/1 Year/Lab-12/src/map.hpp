#ifndef __MAP__
#define __MAP__

#include <cstddef>
#include <cstring>
#include <iterator>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "vector.hpp"
#include "crc32.hpp"


template<class Key, class T>
class Map {
    typedef typename CRC32<Key>::hash_type   hash_type;
    
    Vector< std::pair<hash_type, T> > data;
    CRC32<Key> crc32;
    
    // -- Private functions --

    static bool key_cmp(const std::pair<uint32_t,T>& a,
                        const std::pair<uint32_t,T>& b)
    {
        return (a.first < b.first);
    }

public:

    class Iterator;

    // -- Member types --

    typedef Key                                 key_type;
    typedef T                                   mapped_type;
    typedef typename std::pair<hash_type, T>    value_type;
    typedef std::size_t                         size_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef value_type&                         reference;
    typedef const value_type&                   const_reference;
    typedef value_type*                         pointer;
    typedef const value_type*                   const_pointer;
    typedef Iterator                            iterator;
    typedef const Iterator                      const_iterator;

    // -- Member functions --

    Map() : data() {}

    Map( const Map& other ) : data(other.data) {}
    
    ~Map() {}
    
    Map& operator=( const Map& other ) {
        if(this == &other)
            return *this;
        data = other.data;
        return (*this);
    }

    // -- Element access key

    T& at( const Key& key ) {
        hash_type hashed_key = crc32(key);
    
        for (iterator it = begin(); it != end(); ++it) {
            if (it->first == hashed_key)
                return it->second;
        }
        throw std::out_of_range("No element with this key\n");
    }

    const T& at( const Key& key ) const {
        hash_type hashed_key = crc32(key);

        for (iterator it = begin(); it != end(); ++it) {
            if (it->first == hashed_key)
                return it->second;
        }
        throw std::out_of_range("No element with this key\n");
    }

    T &operator[]( const Key &key ) {
        hash_type hashed_key = crc32(key);
        iterator it;

        for (it = this->begin(); it != this->end(); ++it) {
            if (hashed_key == it->first)
                break;
        }

        if (it == this->end()) {
            this->insert(std::pair<Key, T>{key, T()});
            for (it = this->begin(); it != this->end(); ++it) {
                if (hashed_key == it->first)
                    break;
            }
        }
        return it->second;
    }
    
    // -- Iterators

    iterator begin() {
        return Iterator(data.data());
    }

    iterator end() {
        return Iterator(data.data() + data.size());
    }

    const_iterator begin() const {
        return Iterator(data.data());
    }

    const_iterator end() const {
        return Iterator(data.data() + data.size());
    }

    const_iterator cbegin() const {
        return Iterator(data.data());
    }

    const_iterator cend() const {
        return Iterator(data.data() + data.size());
    }

    // -- Capacity

    bool empty() const {
        return data.empty();
    }

    size_type size() const {
        return data.size();
    }

    size_type max_size() const {
        return data.max_size();
    }

    // -- Modifiers

    void clear() {
        data.clear();
    }

    std::pair<iterator, bool> insert(const std::pair<Key, T> &val) {
        hash_type hashed_key = crc32(val.first);
        iterator it;

        for (it = this->begin(); it != this->end(); ++it) {
            if (it->first == hashed_key)
            return std::pair<iterator, bool>(it, false); 
        }
        data.push_back(std::pair<hash_type, T>{hashed_key, val.second});
        std::sort(data.begin(), data.end(), key_cmp);
        return std::pair<iterator, bool>(this->find(val.first), true);
    }

    iterator erase( iterator pos ) {
        data.erase();
        std::sort(data.begin(), data.end(), key_cmp);
        return ++pos;
    }

    size_type erase( const Key& key ) {
        iterator it = find(key);

        if(it == end()) {
            return 0;
        } else {
            this->erase(it);
            return 1;
        }
    }

    void swap( Map& other )
    {
        Map<Key, T> tmp = *this;
        *this = other;
        other = tmp;
    }

    // -- Lookup 

    size_type count( const Key& key ) const {
        return ( this->find(key) == this->end() ) ? (0) : (1);
    }

    iterator find( const Key& key ) {
        hash_type hashed_key = crc32(key);
        iterator map_it = this->begin();

        for(auto vec_it = data.begin(); vec_it == data.end(); ++vec_it, map_it) {
            if(hashed_key == vec_it->first)
                break;
        }
        return map_it;
    }
    
    const_iterator find( const Key& key ) const {
        hash_type hashed_key = crc32(key);
        iterator map_it = this->begin();

        for(auto vec_it = data.begin(); vec_it != data.end(); ++map_it, ++vec_it) {
            if(hashed_key == vec_it->first)
                break;
        }
        return map_it;
    }

    std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
        iterator lower_it, upper_it;
        iterator it = begin();
        hash_type hashed_key = crc32(key);

        while(it->first < hashed_key) ++it;
        lower_it = it;
        while(it->first <= hashed_key) ++it;
        upper_it = it;
        return std::pair<const_iterator,const_iterator>(lower_it, upper_it);
    }

    iterator lower_bound( const Key& key ) {
        iterator it = begin();
        hash_type hashed_key = crc32(key);
    
        while(it->first < hashed_key) ++it;
        return it;
    }

    const_iterator lower_bound( const Key& key ) const {
        iterator it = begin();
        hash_type hashed_key = crc32(key);

        while(it->first < hashed_key) ++it;
        return it;
    }

    iterator upper_bound( const Key& key ) {
        iterator it = begin();
        hash_type hashed_key = crc32(key);

        while(it->first <= hashed_key) ++it;
        return it;
    }

    const_iterator upper_bound( const Key& key ) const {
        iterator it = begin();
        hash_type hashed_key = crc32(key);

        while(it->first <= hashed_key) ++it;
        return it;
    }

    friend void swap(Map &lhs, Map& rhs) {
        Map tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }

    // -- Non-member functions

    friend bool operator==(const Map<Key, T>& lhs,
                           const Map<Key, T>& rhs) {
        iterator l = lhs.begin();
        iterator r = rhs.begin();
        
        if (lhs.size() != rhs.size())
            return false;
        
        for(; l != lhs.end(); ++l, ++r)
            if(*l != *r) return false;
        return true;
    }

    friend bool operator!=(const Map<Key, T>& lhs,
                           const Map<Key, T>& rhs){
        return !(lhs == rhs);
    }

    friend bool operator>(const Map<Key, T>& lhs,
                          const Map<Key, T>& rhs) {
        iterator right_it = rhs.begin();
        iterator left_it = lhs.begin();
        
        if (lhs.size() != rhs.size())
            return lhs.size() > rhs.size();
        
        for(; left_it != lhs.end(); ++left_it, ++right_it) {
            if(*left_it != *right_it)
                return *left_it > *right_it;
        }
        return false;
    }

    friend bool operator<(const Map<Key, T>& lhs,
                          const Map<Key, T>& rhs) {
        iterator right_it = rhs.begin();
        iterator left_it = lhs.begin();
        
        if (lhs.size() != rhs.size())
            return lhs.size() < rhs.size();
        
        for(; left_it != lhs.end(); ++left_it, ++right_it) {
            if(*left_it != *right_it)
                return *left_it < *right_it;
        }
        return false;
    }

    friend bool operator<=(const Map<Key, T>& lhs,
                           const Map<Key, T>& rhs) {
        return !(lhs > rhs);
    }

    friend bool operator>=(const Map<Key, T>& lhs,
                           const Map<Key, T>& rhs) {
        return !(lhs < rhs);
    }
};


template <class Key, class T>
class Map<Key, T>::Iterator {
    typedef Map<Key, T>::hash_type hash_type;
    
    std::pair<hash_type, T>* ptr;

public:
    
    // -- Member types --

    typedef ptrdiff_t                           difference_type;
    typedef typename Map<Key, T>::value_type	value_type;
    typedef typename Map<Key, T>::pointer		pointer;
    typedef typename Map<Key, T>::reference		reference;
    typedef std::bidirectional_iterator_tag     iterator_category;

    // -- Member functions --

    Iterator() : ptr(NULL) {}

    Iterator(const_iterator &other) : ptr(other.ptr) {}

    Iterator(pointer cont) : ptr(cont) {}

    ~Iterator() {}

    Iterator &operator=(const_iterator &other) {
        ptr = other.ptr;
        return *this;
    }

    Iterator &operator=(pointer rhs) {
        ptr = rhs;
        return *this;
    }
    
    reference operator*() const {
        return *ptr;
    }

    pointer operator->() const {
        return ptr;
    }

    Iterator &operator++() {
        ++ptr; return *this;
    }

    Iterator operator++(int) {
        Iterator old = ptr;
        ++ptr;
        return old;
    }

    Iterator &operator--() {
        --ptr;
        return *this;
    }

    Iterator operator--(int) {
        Iterator tmp = ptr;
        --ptr;
        return tmp;
    }

    bool operator==(const Iterator& rhs) const {
        return ptr == rhs.ptr;
    }

    bool operator!=(const Iterator& rhs) const {
        return ptr != rhs.ptr;
    }
};

#endif // __CRC32__
