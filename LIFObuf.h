/*
  LIFObuf.h - It is a simple lightweight LIFO buffer library for the Arduino.
  It is written in C++, and can easily be modified to work with other platforms.  
  It can buffer any fixed size object (ints, floats, structs, etc...).
  Created by Pavel Pervushkin, March, 2024.
  Released into the public domain.
*/

#ifndef __LIFObuf__
#define __LIFObuf__

#include <Arduino.h>

template <typename T>
class LIFObuf {
private:
    int _top;
    size_t _bufferSize;
    T* _buffer;

public:
    LIFObuf(size_t bufferSize)
    {
        _top = 0;
        _bufferSize = bufferSize;
        _buffer = new T[bufferSize];
    }

    ~LIFObuf()
    {
        if (_buffer != nullptr){
            delete[] _buffer;
        }
    }

    bool push(T data)
    {
        if (_top == _bufferSize) {
            return false;
        } 
        else 
        {
            _buffer[_top] = data;
            _top++;
            return true;
        }
    }

    T pop()
    {
        if (_top <= 0)
        {
            return T();
        } 
        else
        {
            _top--;
            T data = _buffer[_top];
            return data;
        }
    }

    T at(int index)
    {
        if (index < _top) 
        {
            return _buffer[index];
        }
        else
        {
            return T();
        }
    }    

    size_t size()
    {
        return _top;
    }

    void clear()
    {
        _top = 0;
    }

};

#endif