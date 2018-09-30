#ifndef LINQ_H_
#define LINQ_H_

#include <iterator>
#include <utility>
#include <vector>

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;


template<typename T>
class enumerator {
  public:
	virtual const T& operator*() const = 0; // Получает текущий элемент.
	virtual enumerator<T>& operator++() = 0;  // Переход к следующему элементу
	virtual operator bool() const = 0;  // Возвращает true, если есть текущий элемент

	auto drop(int count) {
		return drop_enumerator<T>(*this, count);
	}

	auto take(int count) {
		return take_enumerator<T>(*this, count);
	}
	
	template<typename U = T, typename F>
	auto select(F&& func) {
		return select_enumerator<U, T, F>(*this, std::forward<F>(func));
	}

	template<typename F>
	auto until(F&& func) {
		return until_enumerator<T, F>(*this, std::forward<F>(func));
	}

	auto until_eq(const T& v) {
		return until([&v](const T& t) {return t == v; });
	}
	
	template<typename F>
	auto where(F&& func) {
		return where_enumerator<T, F>(*this, std::forward<F>(func));
	}

	auto where_neq(const T& v) {
		return where([&v](const T& t) {return t != v; });
	}
	
	std::vector<T> to_vector() {
		std::vector<T> v;
		while (*this) {
			T cur = **this;
			v.push_back(cur), ++*this; 
		}
		return v;
	}

	template<typename Iter>
	void copy_to(Iter it) {
		while (*this)
			*it = (**this), ++it, ++*this; 
	}
};


template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
  public:
	range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) { }
	
	const T& operator*() const {
		return *begin_;
	}
	
	enumerator<T>& operator++() {
		++begin_;
		return *this;
	}
	
	operator bool() const {
		return begin_ != end_;
	}
	
  private:
	Iter begin_, end_;
};


template<typename T>
	auto from(T begin, T end) {
	  return range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
	}


template<typename T>
class drop_enumerator : public enumerator<T> {
  public:
	drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
		while (count && parent_)
			++parent_, --count;
	}
		
	const T& operator*() const {
		return *parent_;
	}
	
	enumerator<T>& operator++() {
		++parent_;
		return *this;
	}
	
	operator bool() const {
		return parent_;
	}

  private:
  	enumerator<T> &parent_; 
};


template<typename T>
class take_enumerator : public enumerator<T> {
  public:
	take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) { }
		
	const T& operator*() const {
		return *parent_;
	}
	
	enumerator<T>& operator++() {
		if (--count_ > 0)
			++parent_;
		return *this;
	}
	
	operator bool() const {
		return parent_ && count_ > 0;
	}

  private:
  	enumerator<T> &parent_;
  	int count_; 
};


template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
  public:
	select_enumerator(enumerator<U> &parent, F&& func) : parent_(parent), func_(std::forward<F>(func)) {
		if (parent_)
			elem_ = func_(*parent_);
	}
	
	const T& operator*() const {
		return elem_;
	}
	
	enumerator<T>& operator++() {
		if (++parent_)
			elem_ = func_(*parent_);
		return *this;
	}
	
	operator bool() const {
		return parent_;
	}

  private:
  	enumerator<U> &parent_; 
  	F func_;
  	T elem_;
};


template<typename T, typename F>
class until_enumerator : public enumerator<T> {
  
  public:
	until_enumerator(enumerator<T> &parent, F&& predicate) : parent_(parent), predicate_(std::forward<F>(predicate)) { }	
	
	const T& operator*() const {
		return *parent_;
	}
	
	enumerator<T>& operator++() {
		if (*this)
			++parent_;
		return *this;
	}
	
	operator bool() const {
		return parent_ && !predicate_(*parent_);
	}

  private:
  	enumerator<T> &parent_;
  	F predicate_;
};


template<typename T, typename F>
class where_enumerator : public enumerator<T> {
  
  public:
	where_enumerator(enumerator<T> &parent, F&& predicate) : parent_(parent), predicate_(std::forward<F>(predicate)) { 
		while (parent_ && !predicate_(*parent_)) {
			++parent_;
		}
	}	
	
	const T& operator*() const {
		return *parent_;
	}
	
	enumerator<T>& operator++() {
		++parent_;
		while (parent_ && !predicate_(*parent_))
			++parent_;
		return *this;
	}
	
	operator bool() const {
		return parent_;
	}

  private:
  	enumerator<T> &parent_;
  	F predicate_;
};

#endif
