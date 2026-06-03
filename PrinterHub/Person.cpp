#include "pch.h"
#include "Person.h"
#include <iostream>

// Constructor mặc định
Person::Person() : id(0), name("") {}

// Constructor tham số
Person::Person(int id, const std::string& name) : id(id), name(name) {}

// Getter và Setter cho ID
int Person::getId() const {
    return id;
}

void Person::setId(int id) {
    this->id = id;
}

// Getter và Setter cho Name
std::string Person::getName() const {
    return name;
}

void Person::setName(const std::string& name) {
    this->name = name;
}

// Phương thức hiển thị thông tin
void Person::display() const {
    std::cout << "ID: " << id << " | Name: " << name << std::endl;
}