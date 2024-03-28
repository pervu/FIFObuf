#include <Arduino.h>
#include <FIFObuf.h>

#define MAX_FIFO_SIZE 10

void setup()
{
    Serial.begin(115200);
    delay(300);
    Serial.printf("FIFO example\n\n");

    // FIFO object for int
    FIFObuf<int> int_fifo(MAX_FIFO_SIZE);

    // Add num to FIFO buffer
    for (int i = 0; i < MAX_FIFO_SIZE; ++i) {
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

    // FIFO buffer for strings
    FIFObuf<String> string_fifo(MAX_FIFO_SIZE);

    // Push strings to FIFO
    string_fifo.push("FIFO");
    string_fifo.push("Buffer");
    string_fifo.push("Strings");

    // Pop elements from FIFO buffer
    Serial.printf("Pops from FIFO string buffer:\n");
    while (string_fifo.size() > 0) {
        Serial.printf("%s ", string_fifo.pop().c_str());
    }
    Serial.printf("\n");
    
    // If we try to pop element from empty buf, it returns notjing
    String s = string_fifo.pop().c_str();
    s = string_fifo.pop().c_str();
    Serial.printf("Pop element from empty buffer: \nBuf size: %d  Val: %s\n", string_fifo.size(), s);
    // Add some new value to buffer
    status = string_fifo.push("NewElement");
    Serial.printf("Push status: %d\n", status);

    s = string_fifo.pop().c_str();
    Serial.printf("Pop element from string buffer: \nBuf size: %d  Val: %s\n", string_fifo.size(), s);
}

void loop()
{

}