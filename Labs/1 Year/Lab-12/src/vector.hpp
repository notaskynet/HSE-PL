#ifndef __VECTOR__
#define __VECTOR__

#include <cstddef>
#include <stdexcept>
#include <cmath>

#define STD_VECTOR_CAPACITY 256


template <typename T>
class Vector {
    size_t size_;
    size_t capacity_;
    T*     data_;

    // -- Private functions --

    inline size_t calculateCapacity(size_t size) {
        return static_cast<size_t>( pow(2, log2(size)) );
    }

public:

    class Iterator;

    // -- Member types --

    typedef T               value_type;
    typedef std::size_t     size_type;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef Iterator        iterator;
    typedef const Iterator  const_iterator;


    // -- Member functions --
    
    Vector() {
        size_ = 0;
        capacity_ = STD_VECTOR_CAPACITY;
        data_ = new value_type[capacity_];
    }

    Vector(size_type count) {
        capacity_ = calculateCapacity(count);
        size_     = count;
        data_     = new value_type[capacity_];
    }
    
    Vector(size_type count, const T& val = T()) {
        capacity_ = calculateCapacity(count);
        size_     = count;
        data_     = new value_type[capacity_];

        for (size_type i = 0; i < size_; ++i)
            data_[i] = val;
    }

    Vector(const Vector& other) {
        capacity_ = other.capacity_;
        size_     = other.size_;
        data_     = new value_type[capacity_];
        
        for (size_type i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    template <typename InputIt>
    Vector(InputIt first, InputIt last) {
        capacity_ = calculateCapacity( last - first );
        size_ = last - first;
        data_ = new value_type[capacity_];
    
        for (size_type i = 0; first != last; ++first, ++i)
            data_[i] = *first;
    }

    Vector& operator=(const Vector& other) {
        if(this == &other)
            return *this;
        delete[] data_;

        capacity_ = other.capacity_;
        data_ = new value_type[capacity_];
        size_ = other.size_;
        for(size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    ~Vector() {
        delete[] data_;
    }

    // -- Size and capacity

    size_type size() const {
        return size_;
    }

    size_type capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    // -- Member access

    reference operator[](size_type i) {
        return data_[i];
    }

    const_reference operator[](size_type i) const {
        return data_[i];
    }
    
    reference at(size_type i) {
        return data_[i];
    }

    const_reference at(size_type i) const {
        return data_[i];
    }
    
    reference front() {
        return data_[0];
    }

    const_reference front() const {
        return data_[0];
    }

    reference back() {
        return data_[size_ - 1];
    }

    const_reference back() const {
        return data_[size_ - 1];
    }

    pointer data() {
        return data_;
    }
    
    const_pointer data() const {
        return data_;
    }

    // -- Iterators
    
    iterator begin() {
        return iterator(data_);
    }
    
    iterator end() {
        return iterator(data_ + size_);
    }

    const_iterator begin() const {
        return const_iterator(data_);
    }

    const_iterator end() const {
        return const_iterator(data_ + size_);
    }

    const_iterator cbegin() const {
        return const_iterator(data_);
    }

    const_iterator cend() const {
        return const_iterator(data_ + size_);
    }
    
    // -- Member modification

    void clear() {
        size_ = 0;
    }

    void push_back(const T& val) {
        if (size_ >= capacity_)
            reserve( capacity_ * 2 );
        data_[size_++] = val;
    }

    void pop_back() {
        if (size_ > 0)
            --size_;
    }

    void reserve(size_type capacity) {
        if (capacity <= capacity_)
            return;
        capacity = calculateCapacity(capacity);
        
        T* buf = new T[capacity];
        for (size_type i = 0; i < size_; ++i)
            buf[i] = data_[i];
        delete[] data_;
        data_ = buf;
        capacity_ = capacity;
    }

    void resize(size_type size) {
        if (size > capacity_)
            reserve(size);
        
        if (size > size_) {
            for (size_type i = size_; i < size; ++i)
                data_[i] = T();
        }
        size_ = size;
    }

    void resize(size_type size, const T& val) {
        if (size > capacity_)
            reserve(size);
        
        if (size > size_) {
            for (size_type i = size_; i < size; ++i)
                data_[i] = val;
        }
        size_ = size;
    }

    void swap(Vector& other) {
        Vector<T> tmp = *this;
        *this = other;
        other = tmp;
    }

    //-- Non-member functions

    friend bool operator==( const Vector<T>& lhs, const Vector<T>& rhs ) {
        if(lhs.size() != rhs.size())
            return false;
        
        Vector::iterator left_it  = lhs.begin();
        Vector::iterator right_it = rhs.begin();

        for(; left_it != lhs.end(); ++left_it, ++right_it) {
            if(*left_it != *right_it)
                return false;
        }
        return true;
    }

    friend bool operator!=( const Vector<T>& lhs, const Vector<T>& rhs ) {
        return !(lhs == rhs);
    }

    friend bool operator< ( const Vector<T>& lhs, const Vector<T>& rhs ) { 
        if(lhs.size() != rhs.size())
            return (lhs.size() < rhs.size());
        
        Vector::iterator left_it  = lhs.begin();
        Vector::iterator right_it = rhs.begin();

        for(; left_it != lhs.end(); ++left_it, ++right_it) {
            if(*left_it != *right_it)
                return *left_it < *right_it;
        }
        return false;
    }
        
    friend bool operator<=( const Vector<T>& lhs, const Vector<T>& rhs ) {
        return !(lhs > rhs);
    }

    friend bool operator>( const Vector<T>& lhs, const Vector<T>& rhs ) {
        return !(lhs == rhs || lhs < rhs);
    }
    
    friend bool operator>=( const Vector<T>& lhs, const Vector<T>& rhs ) {
        return !(lhs < rhs);
    }
};


template<typename T>
class Vector<T>::Iterator {
    public:

    // -- Member types --

    typedef Vector<T>::value_type               value_type;
    typedef Vector<T>::reference                reference;
    typedef Vector<T>::pointer                  pointer;
    typedef std::ptrdiff_t                      difference_type;
    typedef std::random_access_iterator_tag     iterator_category;

    // -- Member functions --

    Iterator() : ptr_(nullptr) {}

    Iterator(pointer ptr) : ptr_(ptr) {}

    Iterator(Iterator &other) : ptr_(other.ptr_) {}

    // Element access

    reference operator*() const {
        return *ptr_;
    }

    pointer operator->() const {
        return ptr_;
    }

    Iterator& operator++() {
        ++ptr_;
        return *this;
    }

    iterator operator++(int) {
        iterator tmp(*this);
        ++ptr_;
        return tmp;
    }
        
    iterator& operator--() {
        --ptr_;
        return *this;
    }
    
    iterator operator--(int) {
        iterator tmp(*this);
        --ptr_;
        return tmp;
    }

    iterator& operator+=(difference_type n) {
        ptr_ += n;
        return *this;
    }

    iterator operator+(difference_type n) const {
        return iterator(ptr_ + n);
    }

    iterator& operator-=(difference_type n) {
        ptr_ -= n;
        return *this;
    }

    iterator operator-(difference_type n) const {
        return iterator(ptr_ - n);
    }

    difference_type operator-(const iterator& other) const {
        return ptr_ - other.ptr_;
    }

    reference operator[](difference_type n) const {
        return *(ptr_ + n);
    }
    
    // -- Logic operators

    bool operator==(const iterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const iterator& other) const {
        return ptr_ != other.ptr_;
    }

    bool operator<(const iterator& other) const {
        return ptr_ < other.ptr_;
    }

    bool operator>(const iterator& other) const {
        return ptr_ > other.ptr_;
    }

    bool operator<=(const iterator& other) const {
        return ptr_ <= other.ptr_;
    }

    bool operator>=(const iterator& other) const {
        return ptr_ >= other.ptr_;
    }

private:
    pointer ptr_;
};

#endif // __VECTOR__