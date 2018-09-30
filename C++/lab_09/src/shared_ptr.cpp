#include "shared_ptr.h"
#include "matrix.h"
#include "algorithm"

shared_ptr::shared_ptr(Matrix* obj) {
	storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
	other.storage_->incr();
	storage_ = other.storage_;
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
	std::swap(storage_, other.storage_);
	return *this;
}

bool shared_ptr::isNull() const {
	return !(storage_->getObject());
}

void shared_ptr::reset(Matrix* obj) {
	storage_->decr();
	storage_ = new Storage(obj);
}

Matrix* shared_ptr::operator->() const {
	return ptr();
}

Matrix& shared_ptr::operator*() const {
	return *ptr();
}

Matrix* shared_ptr::ptr() const {
	return storage_->getObject();
}

shared_ptr::~shared_ptr() {
	storage_->decr();
}

shared_ptr::Storage::Storage(Matrix* mtx) {
	data_ = mtx;
	ref_count_ = 1;
}

void shared_ptr::Storage::incr() {
	ref_count_++;
}

void shared_ptr::Storage::decr() {
	ref_count_--;
	if (ref_count_ == 0)
		delete this;
}

int shared_ptr::Storage::getCounter() const {
	return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
	return data_;
}

shared_ptr::Storage::~Storage() {
	delete data_;
}


