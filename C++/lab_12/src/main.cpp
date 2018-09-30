#include <string.h>
#include "my_vector.h"
template <typename T>
void test_my_vector(T t1, T t2) {
	my_vector<T> a;
	if (a.size() != 0)
		std::cout << "FAIL___CONSTRUCTOR_()\n";
	else 
		std::cout << "DONE___CONSTRUCTOR_()\n";
	if (a.capacity() != 2)
		std::cout << "FAIL___CAPACITY\n";
	else 
		std::cout << "DONE___CAPACITY\n";
		
	a.push_back(t1);
	if (a.size() != 1)
		std::cout << "FAIL___SIZE\n";
	else 
		std::cout << "DONE___SIZE\n";
	if (a[0] != t1)
		std::cout << "FAIL___PUSH_BACK\n";
	else 
		std::cout << "DONE___PUSH_BACK\n";
	
	a.push_back(t2);
	if (a[1] != t2)
		std::cout << "FAIL___PUSH_BACK\n";
	else 
		std::cout << "DONE___PUSH_BACK\n";
	
	a[0] = a[1];
	if (a[0] != t2)
		std::cout << "FAIL___OPERATOR_[]\n";
	else 
		std::cout << "DONE___OPERATOR_[]\n";
	
	a.pop_back();
	if (a.size() != 1)
		std::cout << "FAIL___POP_BACK\n";
	else 
		std::cout << "DONE___POP_BACK\n";

	my_vector<T> d(10);
	if (d.size() != 10)
		std::cout << "FAIL___CONSTRUCTOR_(N)\n";
	else 
		std::cout << "DONE___CONSTRUCTOR_(N)\n";
		
	my_vector<T> b(2);
	b[0] = a[0];
	if (a[0] != b[0])
		std::cout << "FAIL___OPERATOR_[]\n";
	else 
		std::cout << "DONE___OPERATOR_[]\n";
	
	my_vector<T> c(b);
	bool mistake = false;
	if (c.size() != b.size())
		mistake = true;
	else 
		for (size_t i = 0; i < b.size(); i++)
			if (c[i] != b[i])
				mistake = true;
	if (mistake)
		std::cout << "FAIL___COPY_CONSTRUCTOR\n";
	else 
		std::cout << "DONE___COPY_CONSTRUCTOR\n";
	
	c = a;
	if (c.size() != a.size())
		mistake = true;
	else 
		for (size_t i = 0; i < a.size(); i++)
			if (c[i] != a[i])
				mistake = true;
	if (mistake)
		std::cout << "FAIL___OPERATOR_=\n";
	else 
		std::cout << "DONE___OPERATOR_=\n";

	a.pop_back();
	if (a.empty())
		std::cout << "DONE___EMPTY\n";
	else 
		std::cout << "FAIL___EMPTY\n";
}

class Product {
public:
	Product();
    Product(const char* name, int quantity, double price);
    Product(const Product& other);
	Product& operator=(Product other);
	bool operator!=(const Product& other);
	~Product();
	void swap(Product& other);
    friend std::ostream& operator<<(std::ostream& os, const Product& p);
    
private:
    char *name_;
    int quantity_;
    double price_;
};

Product::Product() {
	name_ = new char[1];
	name_[0] = '\0';
	quantity_ = 0;
	price_ = 0;
}

Product::Product(const char* name, int quantity, double price) {
	name_ = new char[strlen(name) + 1];
	strcpy(name_, name);
	quantity_ = quantity;
	price_ = price;
}

void Product::swap(Product& other) {
	std::swap(name_, other.name_);
	std::swap(quantity_, other.quantity_);
	std::swap(price_, other.price_);
}

Product::Product(const Product& other) {
	name_ = new char[strlen(other.name_) + 1];
	strcpy(name_, other.name_);
	quantity_ = other.quantity_;
	price_ = other.price_;
}

Product& Product::operator=(Product other) {
	swap(other);
	return *this;
}

bool Product::operator!=(const Product& other) {
	return (strcmp(name_, other.name_) && quantity_ == other.quantity_ && price_ == other.price_);
}
	
Product::~Product() {
	delete [] name_;
}

void print(const my_vector<Product>& v) {
    std::cout << v << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Product& p) {
	os << p.name_ << ' ' << p.quantity_ << ' ' << p.price_;
	return os;
}
	
int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

    return 0;
}

