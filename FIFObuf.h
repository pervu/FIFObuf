/*
  FIFObuf.h - It is a simple lightweight FIFO buffer library for the Arduino.
  It is written in C++, and can easily be modified to work with other platforms.  
  It can buffer any fixed size object (ints, floats, structs, etc...).
  Created by Pavel Pervushkin, March, 2024.
  Released into the public domain.
*/

#ifndef FIFOBuf_H
#define FIFOBuf_H

#include <Arduino.h>

template <typename T>
class FIFObuf {
private:
    int _head;
    int _tail;
    size_t _bufferSize;
    T* _buffer;

public:
    FIFObuf(size_t bufferSize)
    {
        _head = 0;
        _tail = 0;
        _bufferSize = bufferSize;
        _buffer = new T[bufferSize];
    }

    ~FIFObuf()
    {
        if (_buffer != nullptr) {
            delete[] _buffer;
        }
    }

    bool push(T data)
    {
        if (_tail == _bufferSize) {
            return false; // Buffer overflow
        } 
        else 
        {
            _buffer[_tail] = data;
            _tail++;
            return true;
        }
        return false;
    }

    T pop()
    {
        if (_head == _tail)
        {
            _head = 0;
            _tail = 0;
            return T(); // Buffer empty
        } 
        else 
        {
            T data = _buffer[_head];
            _head++;
            return data;
        }
    }

    T at(unsigned int index)
    {
        if (index < _tail) 
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
        return _tail;
    }

    void clear()
    {
        _head = 0;
        _tail = 0;
    }

};

#endif

