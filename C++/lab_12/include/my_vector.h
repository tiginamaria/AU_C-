#include <cstddef>
#include <algorithm>
#include <iostream>

template <class T>
class my_vector {
private:
	size_t capacity_ = 0;
	size_t size_ = 0;
	T* array_;

public:
	my_vector() {
		reserve(capacity_);
	}

	my_vector(size_t n) {
		resize(n);
	}

	my_vector(const my_vector& other) {
		size_ = other.size_;
		reserve(other.capacity_);
		for (size_t i = 0; i < size_; i++)
			new(&array_[i]) T(other.array_[i]);
	}

	void swap(my_vector& other) {
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
		std::swap(array_, other.array_);
	}

	my_vector& operator=(my_vector other) {
		swap(other);
		return *this;
	}

	~my_vector() {
		clear();
		delete [] reinterpret_cast<char*>(array_);
	}

	size_t size() const {
		return size_;
	}

	size_t capacity() const {
		return capacity_;
	}

	bool empty() const {
		return size_ == 0;
	}

	void resize(size_t n) {
	
		for (size_t i = n; i < size_; i++)
			array_[i].~T();
			
		reserve(n);
		
		for (size_t i = size_; i < n; i++)
			new(&array_[i]) T();
			
		size_ = n;
	}

	void reserve(size_t n) {
		size_t cp = 2;
		while (n > cp)
			cp = cp << 1;
			
		if (capacity_ == 0) {
			array_ = reinterpret_cast<T*> (new char [cp * sizeof(T)]);
			capacity_ = cp;
		} else if (n > capacity_) {
			T* new_array_ = reinterpret_cast<T*> (new char [cp * sizeof(T)]);
			for (size_t i = 0; i < size_; i++)
				new(&new_array_[i]) T(array_[i]);
				 
			std::swap(new_array_, array_);
			for (size_t i = 0; i < size_; i++)
				new_array_[i].~T();
	
			delete [] reinterpret_cast<char*>(new_array_);
			capacity_ = cp;
		}
	}	

	const T& operator[](size_t index) const {
		return array_[index];
	}

	T& operator[](size_t index) {
		return array_[index];
	}

	void push_back(const T& t) {
		if (size_ == capacity_)
			reserve(2 * capacity_);
		new(&array_[size_]) T(t);
		size_++;
	}

	void pop_back() {
		size_--;
		array_[size_].~T();
	}

	void clear() {
		for(size_t i = 0; i < size_; i++)
			array_[i].~T();
	
		delete [] reinterpret_cast<char*>(array_);
		size_ = 0;
		capacity_ = 0;
		reserve(capacity_);
	}
};

template <class T>
std::ostream& operator<<(std::ostream& os, const my_vector<T>& v) {
	for (size_t i = 0; i < v.size(); i++)
		os << v[i] << ' ';
	return os;
}
