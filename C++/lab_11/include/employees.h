#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED
#include <iostream>
#include <stdint.h>

class Employee {
public:
	Employee();
	virtual ~Employee();
	virtual int salary() const = 0;	
protected:
	Employee(const Employee& e);
	void operator=(const Employee& e);
	friend std::ostream& operator<<(std::ostream& os, Employee& e);
	friend std::ofstream& operator<<(std::ofstream& file, Employee& e);
	friend std::istream& operator>>(std::istream& s, Employee& e);
	friend std::ifstream& operator>>(std::ifstream& file, Employee& e);
	virtual void read(std::istream& is) = 0;
	virtual void readf(std::ifstream& file) = 0;
	virtual void write(std::ostream& os) const = 0;
	virtual void writef(std::ofstream& file) const = 0;
};

class Developer : Employee {
public:
	Developer();
	~Developer();
	int salary() const;
private:
    void read(std::istream& is);
	void readf(std::ifstream& file);
	void write(std::ostream& os) const;
	void writef(std::ofstream& file) const;
	char *_name;
	int32_t _base_salary;
	bool _has_bonus;
};

class SalesManager : Employee {
public:
	SalesManager();
	~SalesManager();
	int salary() const;
private:
	void read(std::istream& is);
	void readf(std::ifstream& file);
	void write(std::ostream& os) const;
	void writef(std::ofstream& file) const;
	char *_name;
	int32_t _base_salary;
	int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
	EmployeesArray();
	~EmployeesArray();
	void add(Employee *e);
	int total_salary() const;
	friend std::ifstream& operator>>(std::ifstream& file, EmployeesArray& arr); 
	friend std::ostream& operator<<(std::ostream& os, const EmployeesArray& arr);
	friend std::ofstream& operator<<(std::ofstream& file, const EmployeesArray& arr);
private:
	int32_t _size;
	int32_t _capasity;
	Employee **_employees;
};

#endif
