#pragma once
#include <string>

class Person {
private:
    int id;
    std::string name;

public:
    // Constructor mặc định
    Person();

    // Constructor tham số
    Person(int id, const std::string& name);

    // Getter và Setter cho ID
    int getId() const;
    void setId(int id);

    // Getter và Setter cho Name
    std::string getName() const;
    void setName(const std::string& name);

    // Phương thức hiển thị thông tin
    void display() const;
};

