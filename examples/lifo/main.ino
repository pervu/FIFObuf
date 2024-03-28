#include <Arduino.h>
#include <FIFObuf.h>
#include <LIFObuf.h>

#define BUF_SIZE 10

void setup()
{
    Serial.begin(115200);
    delay(300);

    Serial.printf("LIFO example\n\n");

    // LIFO object for int
    LIFObuf<int> int_lifo(BUF_SIZE);
    Serial.printf("Pulls from LIFO int buffer:\n");
    // Add num to FIFO buffer
    for (int i = 0; i < BUF_SIZE; ++i) {
        Serial.printf("%d ", i);
        int_lifo.push(i);
    }
    Serial.printf("\n");
    // If we try to add element to full buffer, it returns false
    bool status = int_lifo.push(100);
    Serial.printf("Try to push to full buffer. Push status: %d\n", status);

    // Look element at index 4
    Serial.printf("Elem value at forth position: %d\n", int_lifo.at(4));

    // Pop elements from LIFO buffer
    Serial.printf("Pops from LIFO int buffer:\n");
    while (int_lifo.size() > 0) {
        Serial.printf("%d ", int_lifo.pop());
    }
    Serial.printf("\n\n");

    // FIFO buffer for strings
    LIFObuf<String> string_lifo(BUF_SIZE);

    // Push strings to FIFO
    string_lifo.push("LIFO");
    string_lifo.push("Buffer");
    string_lifo.push("Strings");

    // Pop elements from FIFO buffer
    Serial.printf("Pops from LIFO string buffer:\n");
    while (string_lifo.size() > 0) {
        Serial.printf("%s ", string_lifo.pop().c_str());
    }
    Serial.printf("\n");
    
    // If we try to pop element from empty buf, it returns notjing
    String s = string_lifo.pop().c_str();
    s = string_lifo.pop().c_str();
    Serial.printf("Pop element from empty buffer: \nBuf size: %d  Val: %s\n", string_lifo.size(), s);
    // Add some new value to buffer
    status = string_lifo.push("NewElement");
    Serial.printf("Push status: %d\n", status);

    s = string_lifo.pop().c_str();
    Serial.printf("Pop element from string buffer: \nBuf size: %d  Val: %s\n", string_lifo.size(), s);
}

void loop()
{

}