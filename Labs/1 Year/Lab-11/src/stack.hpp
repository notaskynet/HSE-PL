#include <cstddef>
#include <iterator>

#define STACK_CAPASITY 128
#define MIN_LOAD_FACTOR 4
// MIN_LOAD_FACTOR - соотношение capacity_ и size_, при котором будет выполняться понижение кол-ва выделяемой памяти


template<typename T>
class Stack {
    size_t capacity_; // Внутренний параметр для работы с динамическим размером нашего стэка
    size_t size_;
    T      *data_;

    // -- Private functions --

    void addMemory() {
        /* Метод для добавления памяти при переполнении стека */
        T *buffer = data_;

        capacity_ *= 2;
        data_ = new T[capacity_];

        for(size_t i = 0; i < size_; ++i) {
            data_[i] = buffer[i];
        }
        delete[] buffer;
    }


    void reduceMemory() {
        T *buffer = data_;

        capacity_ /= 2;
        data_ = new T[capacity_];

        for(size_t i = 0; i < size_; ++i) {
            data_[i] = buffer[i];
        }
        delete[] buffer;
    }

public:

    class Iterator;

    // -- Member types --

    typedef T                      value_type;
    typedef value_type&            reference;
    typedef const value_type&      const_reference;
    typedef T*                     pointer;
    typedef const T*               const_pointer; 
    typedef Iterator               iterator;
    typedef const Iterator         const_iterator;

    //-- Member functions --

    Stack<T>() {
        capacity_ = STACK_CAPASITY;
        data_ = new value_type[capacity_];
        size_ = 0;
    }

    Stack<T>( const Stack& other ) {
        size_    = other.size;
        capacity_ = other.capacity_;

        if( data_ != NULL )  delete[] data_;
        data_ = new T[capacity_];

        for(size_t i = 0; i < capacity_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    ~Stack<T>() {
        delete[] data_;
        data_ = NULL;
    }

    Stack<T>& operator=( const Stack& other ) {
        size_    = other.size;
        capacity_ = other.capacity_;

        if( data_ != NULL )  delete[] data_;
        data_ = new T[capacity_];

        for(size_t i = 0; i < capacity_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    // -- Element access

    value_type top() const {  return data_[ size_ - 1 ];  }

    // -- Capacity 

    bool empty() const { return ( size_ == 0 ); }

    size_t size() const { return size_; }

    void push(const value_type& value) {
        if( size_ >= capacity_ ) addMemory();
        data_[size_++] = value;
    }

    void pop() {
        if(capacity_ / size_ > MIN_LOAD_FACTOR)
            reduceMemory();
        --size_;
    }

    // -- Iterators

    iterator begin() { return Iterator(data_); }

    iterator end() { return Iterator(data_ + size_); }

    const_iterator cbegin() const { return Iterator(data_); }

    const_iterator cend() const { return Iterator(data_ + size_); }

    // -- Non-member functions --

    friend bool operator==( const Stack<T>& lhs, const Stack<T>& rhs ) {
        if( lhs.size_ != rhs.size_ )
            return false;

        for(size_t i = 0; i < lhs.size_; ++i) {
            if(lhs.data_[i] != rhs.data_[i] )
                return false;
        }
        return true;
    }

    friend bool operator!=( const Stack<T>& lhs, const Stack<T>& rhs ) {
        return !( lhs == rhs );
    }

    friend bool operator<( const Stack<T>& lhs, const Stack<T>& rhs ) {
        if( lhs.size_ < rhs.size_ ) {
            return true;
        }
        else if( lhs.size_ > rhs.size_ ) {
            return false;
        }

        for(size_t i = 0; i < lhs.size_; ++i) {
            if(lhs.data_[i] < rhs.data_[i] ) {
                return true;
            }
                
            else if(lhs.data_[i] > rhs.data_[i]) {
                return false;
            }
        }
        return false;
    }


    friend bool operator<=( const Stack<T>& lhs, const Stack<T>& rhs ) {
        return ( lhs == rhs ) || ( lhs < rhs );
    }

    friend bool operator>( const Stack<T>& lhs, const Stack<T>& rhs ) {
        if( lhs.size_ > rhs.size_ ) {
            return true;
        }
        else if( lhs.size_ < rhs.size_ ) {
            return false;
        }

        for(size_t i = 0; i < lhs.size_; ++i) {
            if(lhs.data_[i] > rhs.data_[i] ) {
                return true;
            }
                
            else if(lhs.data_[i] < rhs.data_[i]) {
                return false;
            }
        }
        return false;
    }

    friend bool operator>=( const Stack<T>& lhs, const Stack<T>& rhs ) {
        return ( lhs == rhs ) || ( lhs > rhs );
    }
};


template<typename T>
class Stack<T>::Iterator {
    template<typename Iter>
    friend struct std::iterator_traits;
    pointer ptr_; // ptr_ - pointer(Точнее указатель на pointer)

public:

    // -- Member types --

    typedef ptrdiff_t				        difference_type;
    typedef std::forward_iterator_tag	    iterator_category;

    // -- Member functions --

    Iterator() : ptr_( NULL ) {}

    Iterator( const Iterator & other) : ptr_( other.ptr_ ) {}

    Iterator( pointer other ) : ptr_( other ) {}

    reference operator*()  const { return *ptr_; }

    pointer   operator->() { return ptr_; }

    // Prefix increment
    Iterator& operator++() { ptr_++; return *this; }  

    // Postfix increment
    Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

    // -- Non-member functions --

    friend bool operator==( const Iterator& lhs, const Iterator& rhs )
    { return ( lhs.ptr_ == rhs.ptr_ ); }

    friend bool operator!=( const Iterator& lhs, const Iterator& rhs )
    { return ( lhs.ptr_ != rhs.ptr_ ); }
};
