#include "MyStringSso.h"
#include <cstring>

#pragma warning (disable : 4996)

MyString::MyString() : MyString("")
{}

MyString::MyString(size_t size)
{
    _data = new char[size + 1];
    this->_size = size; 
}
MyString::MyString(const char* data)
{
	size_t currentSize = strlen(data);

	if (currentSize <= 15) //SSO
	{	
		ssoData[sizeof(_data) + sizeof(_size) - 1] = 15 - currentSize;
		strcpy(ssoData, data);
	}
	else
	{
		_size = currentSize;
		_data = new char[_size + 1];
		strcpy(_data, data);
		notUsingSso();
	}
}
void MyString::notUsingSso()
{
    ssoData[sizeof(_data) + sizeof(_size) - 1] |= (1 << 7);
}

MyString::MyString(MyString&& other) noexcept
{
	if (isSso())
	{
		_data = other._data;
		_size = other._size;
	}
	else
	{
		_data = other._data;
		other._data = nullptr;
		_size = other._size;
		notUsingSso();
	}
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();

		if (isSso())
		{
			_data = other._data;
			_size = other._size;
		}
		else
		{
			_data = other._data;
			other._data = nullptr;
			_size = other._size;
			notUsingSso();
		}
		return *this;
	}
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}


void MyString::free()
{
	if(!isSso())
		delete[] _data;
	_data = nullptr;
}
MyString::~MyString()
{
	free();
}

bool MyString::isSso() const
{
	return (ssoData[sizeof(_data) + sizeof(_size) - 1] & (1 << 7)) == 0;
}

const char* MyString::c_str() const
{
	if (isSso())
		return ssoData;
	else 
		return _data;
}

size_t MyString::length() const
{
	if(isSso())
	{
		return 15 - ssoData[sizeof(_data) + sizeof(_size) - 1];
	}
	else
	{
		size_t realSize = _size;
		size_t mask = ~(1 << 31); //we remove the bit of the size that shows us that SSO is aplied.
		return realSize & mask;
	}
}

void MyString::copyFrom(const MyString& other)
{
	if(!other.isSso())
	{
	    _data = new char[other.length() + 1];
	    strcpy(_data, other._data);
	    _size = other._size;
	}
	else
	{
        strcpy(ssoData, other.ssoData);
        ssoData[sizeof(_data) + sizeof(_size) - 1] = other.ssoData[sizeof(_data) + sizeof(_size) - 1]; //copy the size
	}
}

MyString& MyString::operator+=(const MyString& other)
{
    size_t newStrSize = length() + other.length();
    
    if(newStrSize <= 15)
    { //sso is aplied in the current object
        strcat(ssoData, other.ssoData);
        ssoData[sizeof(_data) + sizeof(_size) - 1] = 15 - newStrSize;
        return *this;
    }
    else
    {
        char* newData = new char[newStrSize + 1]{'\0'};
        
        strcpy(newData, c_str());
        strcat(newData, other.c_str());

        if(!isSso())
            delete[] _data;
        _data = newData;
        _size = newStrSize;
        notUsingSso();
    }
    return *this;
}


char& MyString::operator[](size_t index) 
{
	return isSso() ? ssoData[index] : _data[index];
}

char MyString::operator[](size_t index) const
{
	return isSso() ? ssoData[index] : _data[index];
}
std::ostream& operator<<(std::ostream& os, const MyString& obj)
{
	return os << obj.c_str();
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
    size_t newStrSize = lhs.length() + rhs.length();
    
    if(newStrSize <= 15)
    {
        MyString res(lhs);
        res += rhs;
        return res;
    }
    else
    {
        MyString res(newStrSize + 1);
        strcpy(res._data, lhs.c_str());
        strcat(res._data, rhs.c_str());
        res.notUsingSso();
        return res;
    }
}