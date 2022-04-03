#pragma once
#include <cstddef>
#include <memory>

/**
 *  Ring Buffer
 *
 *  Data stored in simple array. When array is full and we add another item to buffer
 *  element added in place of oldest element, and index of oldest element incremented.
 *
 *  front_ tracks index of oldest item. this is index 0. It is increased when we replace oldest item
 *      When front_ becomes equal max_size_ it wraps to 0.
 *  back_ is newest item. this is index (max_size_ - 1)
 *      same as with front, but increased on every push_back() call.
 *  size_ tracks number of items in buffer.
 *
 */

template <typename T,
          typename A = std::allocator<T>>
class RingBuffer
{
public:
    typedef A allocator_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;


    /*
     * Iterators
     */

    class const_iterator
    {
    public:
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T& reference;
        typedef const T* pointer;
        typedef std::random_access_iterator_tag iterator_category;

        // ctors
        const_iterator(const RingBuffer* data, size_type ptr):ptr_(ptr),data_(data){};
        const_iterator(const const_iterator& other):ptr_(other.ptr_),data_(other.data_){};
        ~const_iterator(){};

        // equality and access
        const_iterator& operator=(const const_iterator& other) { ptr_ = other.ptr_; data_ = other.data_; return *this; };
        bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_ && data_ == other.data_; };
        bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_ || data_ != other.data_; };

        // gt, lt
        bool operator>(const const_iterator& other) const { return ptr_ > other.ptr_; };
        bool operator<(const const_iterator& other) const { return ptr_ < other.ptr_; };

        // navigation
        const_iterator& operator++() { ptr_++; return *this; }; // prefix
        const_iterator operator++(int) { const_iterator tmp(*this); ptr_++; return tmp; }; //postfix
        const_iterator& operator--() { ptr_--; return *this; }; // prefix
        const_iterator operator--(int) { const_iterator tmp(*this); ptr_--; return tmp; }; //postfix
        const_iterator& operator+=(size_type step) { ptr_ += step; return *this; };
        const_iterator operator+(size_type step) const { const_iterator tmp(*this); tmp += step; return tmp; };
//        friend const_iterator operator+(size_type step, const const_iterator& rhs) { rhs += step; return rhs; };
        const_iterator& operator-=(size_type step) { ptr_ -= step; return *this; };
        const_iterator operator-(size_type step) const { const_iterator tmp(*this); tmp -= step; return tmp; };
        difference_type operator-(const_iterator other) const { return static_cast<difference_type>(ptr_ - other.ptr_); };

        // dereferencing
        const_reference operator*() const { return data_->data_[(data_->front_ + ptr_) % data_->max_size_]; };
        pointer operator->() const { return &(data_->data_[(data_->front_ + ptr_) % data_->max_size_]); };
        const_reference operator[](size_type index) const { return data_->data_[(data_->front_ + index) % data_->max_size_]; }; //optional
    private:
        size_type ptr_; // index of buffer
        const RingBuffer<T>* data_; // pointer to buffer (not internal array)
    };

    class iterator
    {
    public:
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::random_access_iterator_tag iterator_category;

        // ctors
        iterator(const RingBuffer* data, size_type ptr):ptr_(ptr),data_(data){};
        iterator(const iterator& other):ptr_(other.ptr_),data_(other.data_){};
        iterator(const const_iterator& other):ptr_(other.ptr_),data_(other.data_){};
        ~iterator(){};

        // equality and access
        iterator& operator=(const iterator& other) { ptr_ = other.ptr_; data_ = other.data_; return *this; };
        bool operator==(const iterator& other) const { return ptr_ == other.ptr_ && data_ == other.data_; };
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_ || data_ != other.data_; };

        // gt, lt
        bool operator>(const iterator& other) const { return ptr_ > other.ptr_; };
        bool operator<(const iterator& other) const { return ptr_ < other.ptr_; };

        // navigation
        iterator& operator++() { ptr_++; return *this; }; // prefix
        iterator operator++(int) { iterator tmp(*this); ptr_++; return tmp; }; //postfix
        iterator& operator--() { ptr_--; return *this; }; // prefix
        iterator operator--(int) { iterator tmp(*this); ptr_--; return tmp; }; //postfix
        iterator& operator+=(size_type step) { ptr_ += step; return *this; };
        iterator operator+(size_type step) const { iterator tmp(*this); tmp += step; return tmp; };
//        friend iterator operator+(size_type step, const const_iterator& rhs) { rhs += step; return rhs; };
        iterator& operator-=(size_type step) { ptr_ -= step; return *this; };
        iterator operator-(size_type step) const { iterator tmp(*this); tmp -= step; return tmp; };
        difference_type operator-(iterator other) const { return static_cast<difference_type>(ptr_ - other.ptr_); };

        // dereferencing
        reference operator*() const { return data_->data_[(data_->front_ + ptr_) % data_->max_size_]; };
        pointer operator->() const { return &(data_->data_[(data_->front_ + ptr_) % data_->max_size_]); };
        reference operator[](size_type index) const { return data_->data_[(data_->front_ + index) % data_->max_size_]; };

    private:
        size_type ptr_; // index of buffer
        const RingBuffer<T>* data_; // pointer to buffer (not internal array)
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    RingBuffer(size_type size):
        max_size_(size),
        data_(std::make_unique<T[]>(size)){};
    virtual ~RingBuffer(){};

    // insert to the end
    void push_back(const T& item)
    {
        // check current size
        if(size_ == max_size_) // if maximum size
        {
            // insert item in front index, increase front and back indexes
            data_[front_] = item;
            back_ = (back_ + 1) % max_size_; // modulo so it will wrap to 0
            front_ = (front_ + 1) % max_size_; // if index becomes equal max_size_
        }
        else // not max size yet
        {
            // simply add item and increase size and back index
            data_[back_] = item;
            back_++;
            size_++;
        }
    };

    // delete last element
    void pop_back()
    {
        if(size_ > 0)
        {
            if (back_ > 0)
            {
                --back_;
            }
            else
            {
                back_ = max_size_;
            }
        }
    }

    // indexed access
    reference operator[](const size_type& index)
    {
        return data_[(front_ + index) % max_size_];
    };
    const_reference operator[](const size_type& index) const
    {
        return data_[(front_ + index) % max_size_];
    };

    // first, last and alternative indexed element
    T& front(){return data_[front_];};
    T& back(){return data_[back_ - 1];};
    T& at(const long long index){return data_[index];};

    // const_iterator
    const_iterator cbegin() const { return const_iterator(this, 0); };
    const_iterator cend() const { return const_iterator(this, size_); };
    const_iterator begin() const { return cbegin(); };
    const_iterator end() const { return cend(); };

    // iterator
    iterator begin() { return iterator(this, 0); };
    iterator end() { return iterator(this, size_); };

    // const_reverse_iterator
    const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); };
    const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); };
    const_reverse_iterator rbegin() const { return crbegin(); };
    const_reverse_iterator rend() const { return crend(); };

    // reverse_iterator
    reverse_iterator rbegin() { return reverse_iterator(end()); };
    reverse_iterator rend() { return reverse_iterator(begin()); };

    // sizes
    const size_t& size() const {return size_;};
    const size_t& max_size() const {return max_size_;};
private:
    size_type front_ = 0;
    size_type back_ = 0;
    size_type size_ = 0;
    const size_type max_size_;
    const std::unique_ptr<T[]> data_;
};
