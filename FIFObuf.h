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
    int _head = 0;
    int _tail = 0;
    size_t _bufferSize;
    T* _buffer;

public:
    FIFObuf(size_t bufferSize)
    {
        _head = 0;
        _tail = 0;
        _bufferSize = bufferSize + 1;
        _buffer = new T[_bufferSize];
    }

    ~FIFObuf()
    {
        if (_buffer != nullptr) {
            delete[] _buffer;
        }
    }

    bool push(T data)
    {
        size_t newHead = (_head + 1) % _bufferSize;
        if (newHead == _tail) {
            return false; // Buffer overflow
        } else {
            Serial.printf("Push data %d, head: %d, tail: %d, nextTail: %d\n", data, _head, _tail, newHead);
            _buffer[_head] = data;
            _head = newHead;
            return true;
        }
    }

    T pop()
    {
        if (_head == _tail) {
            return T(); // Buffer empty
        } else {
            T data = _buffer[_tail];
            Serial.printf("Pop data %d, head: %d, tail: %d\n", data, _head, _tail);
            _tail = (_tail + 1) % _bufferSize;
            return data;
        }
    }

    T at(unsigned int index)
    {
        if (index >= size()) {
            return T();
        }
        size_t currentInd = (_tail + index) % _bufferSize;
        return _buffer[currentInd];
    }

    size_t size()
    {
        return (_bufferSize + _head - _tail) % _bufferSize;
    }

    void clear()
    {
        _head = 0;
        _tail = 0;
    }

};

#endif

