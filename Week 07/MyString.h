#pragma once
#include <iostream>

class MyString 
{
public:
    MyString();
    MyString(const char* data);
    explicit MyString(size_t stringLength);

    MyString(const MyString& other);
    MyString& operator=(const MyString& other); 
    ~MyString();

    size_t getCapacity() const;
    size_t getSize() const;

    const char* c_str() const;

    MyString& operator+=(const MyString& other);

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
    friend std::istream& operator>>(std::istream& is, MyString& ref);

private:
    void resize(unsigned newAllocatedDataSize);

    void free();
    void copyFrom(const MyString& other);

    char* _data;
    size_t _size;
    size_t _allocatedDataSize;
};

MyString operator+(const MyString& lhs, const MyString& rhs);

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
