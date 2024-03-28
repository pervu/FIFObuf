# FIFObuf
Simple and lightweight FIFO\LIFO buffer library for the Arduino and ESP boards.

## Usage
```cpp
FIFObuf<TYPE> fifo(BUFFER_SIZE);  // create FIFO buffer
LIFObuf<TYPE> lifo(BUFFER_SIZE);  // create LIFO buffer
void push(TYPE data);         // Add data to buffer
TYPE pop();                   // Get and delete data from buffer
TYPE at(unsigned int index);  // Read data without deleting at index position
size_t size();                // Get elements quantity in the buffer
void clear();                 // Clear buffer
```

## QuickStart
```cpp
#include <Arduino.h>

// include FIFObuf.h for FIFO buffer, or LIFObuf.h for LIFO buffer
#include <FIFObuf.h>
#include <LIFObuf.h>

// define buffer size
#define BUF_SIZE 10

// FIFO buffer for int
FIFObuf<int> int_fifo(BUF_SIZE);
// LIFO buffer for strings
LIFObuf<String> string_lifo(BUF_SIZE);

void setup()
{
    Serial.begin(115200);
    delay(300);

    // LIFO example part
    // Add num to FIFO buffer
    for (int i = 0; i < BUF_SIZE; ++i) {
        int_fifo.push(i);
    }

    // If we try to add element to full buffer, it returns false
    bool status = int_fifo.push(100);
    Serial.printf("Try to push to full buffer. Push status: %d\n", status);
    // Look element at index 4
    Serial.printf("Elem value at forth position: %d\n", int_fifo.at(4));

    // Pop elements from FIFO buffer
    Serial.printf("Pops from FIFO int buffer:\n");
    while (int_fifo.size() > 0) {
        Serial.printf("%d ", int_fifo.pop());
    }
    Serial.printf("\n");

    // If we try to pop element from empty buf, it returns 0
    int n = int_fifo.pop();
    Serial.printf("Pop element from empty buffer. \nBuf size: %d  Val: %d\n\n", int_fifo.size(), n);

    // LIFO example part
    // Push strings to LIFO
    string_lifo.push("LIFO");
    string_lifo.push("Buffer");
    string_lifo.push("Strings");

    // Pop elements from LIFO buffer
    Serial.printf("Pops from LIFO string buffer:\n");
    while (string_lifo.size() > 0) {
        Serial.printf("%s ", string_lifo.pop().c_str());
    }
    Serial.printf("\n");
    
    // If we try to pop element from empty buf, it returns nothing
    String s = string_lifo.pop().c_str();
    s = string_lifo.pop().c_str();
    Serial.printf("Pop element from empty buffer: \nBuf size: %d  Val: %s\n", string_lifo.size(), s);
    // Add some new value to buffer
    status = string_lifo.push("NewElement");
    Serial.printf("Push status: %d\n", status);

    s = string_lifo.pop().c_str();
    Serial.printf("Pop element from string buffer: \nBuf size: %d  Val: %s\n", string_lifo.size(), s);
}
void loop(){}
```
