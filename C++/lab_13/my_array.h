#pragma once
#include <cstddef>
#include <algorithm>
#include <cassert>
#include <iostream>

template<typename T, std::size_t N>
class my_array {
private:
	T array_[N];
public:
	T& at(std::size_t index) {
		assert(index >= 0 && index < N);
		return array_[index];
	}
	
	const T& at(std::size_t index) const {
		assert(index >= 0 && index < N);
		return array_[index];
	}
	
	T& operator[](std::size_t index) {
		return array_[index];
	}
	
	const T& operator[](std::size_t index) const {
		return array_[index];
	}	
	
	bool empty() const {
		return (N == 0);
	}
	
	size_t size() const {
		return N;
	}
	
	void fill(const T& val) {
		for (size_t i = 0; i < N; i++)
			array_[i] = val;
	}
};
template <size_t N>
class my_array<bool, N> {
private:
	class Proxy {
		private:
			char* byte;
			size_t bit;
			
		public:
			Proxy(char* byte, size_t bit) : byte(byte), bit(bit) {}
				
			operator bool() const {
				return *byte & (1 << bit);
			}
			
			bool operator=(Proxy& p) {
				return *this = (bool)p;
			}
			
			bool operator=(bool b) {
				if ((bool)(*byte & (1 << bit)) != b) {
					*byte ^= (1 << bit);
				}
				return *this;
			}
			
			~Proxy() {}
	};		
public:
	my_array() {		
		for (size_t i = 0; i < N / 8 + 1; i++)
			array_[i] = 0;
	}
	
	Proxy at(std::size_t index) {
		assert(index >= 0 && index < N);
		return Proxy(&array_[index / 8], index % 8);
	}
	
	bool at(std::size_t index) const {
		assert(index >= 0 && index < N);
		return array_[index / 8] & (1 << (index % 8));
	}
	
	Proxy operator[](std::size_t index) {
		return Proxy(&array_[index / 8], index % 8);
	}
	
	bool operator[](std::size_t index) const {
		return array_[index / 8] & (1 << (index % 8));
	}	
	
	bool empty() const {
		return (N == 0);
	}
	
	size_t size() const {
		return N;
	}
	
	void fill(const bool val) {
		for (size_t i = 0; i < N; i++)
			Proxy(&array_[i / 8], i % 8) = val;
	}

private:
	char array_[N / 8 + 1];
};
