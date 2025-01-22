#include <Arduino.h>
#include <unity.h>
#include "FIFObuf.h"

// Test 1: Push and pop operations
void test_fifo_push_and_pop() {
    FIFObuf<int> fifo(5); // Create a FIFO buffer with size 5

    TEST_ASSERT_TRUE(fifo.push(10)); // Push element 10
    TEST_ASSERT_TRUE(fifo.push(20)); // Push element 20
    TEST_ASSERT_TRUE(fifo.push(30)); // Push element 30

    TEST_ASSERT_EQUAL(3, fifo.size());  // FIFO size should be 3
    TEST_ASSERT_EQUAL(10, fifo.pop());  // First pushed element (10) should be popped first
    TEST_ASSERT_EQUAL(20, fifo.pop());  // Second pushed element (20) should follow
    TEST_ASSERT_EQUAL(30, fifo.pop());  // Third pushed element (30) should follow
    TEST_ASSERT_EQUAL(0, fifo.size());  // FIFO size should now be 0
}

// Test 2: Overflow behavior
void test_fifo_overflow() {
    FIFObuf<int> fifo(3); // Create a FIFO buffer with size 3

    TEST_ASSERT_TRUE(fifo.push(1)); 
    TEST_ASSERT_TRUE(fifo.push(2)); 
    TEST_ASSERT_TRUE(fifo.push(3)); 
    TEST_ASSERT_FALSE(fifo.push(4)); // Adding an element should fail due to overflow

    TEST_ASSERT_EQUAL(3, fifo.size()); // FIFO size should remain 3
}

// Test 3: Popping from an empty FIFO
void test_fifo_empty_pop() {
    FIFObuf<int> fifo(3); // Create an empty FIFO buffer

    TEST_ASSERT_EQUAL(0, fifo.pop());  // Attempting to pop should return default value (0)
    TEST_ASSERT_EQUAL(0, fifo.size()); // FIFO size should remain 0
}

// Test 4: Clear operation
void test_fifo_clear() {
    FIFObuf<int> fifo(3); // Create a FIFO buffer with size 3

    fifo.push(1);
    fifo.push(2);
    fifo.push(3);

    fifo.clear(); // Clear the FIFO

    TEST_ASSERT_EQUAL(0, fifo.size()); // FIFO size should be 0
    TEST_ASSERT_EQUAL(0, fifo.pop());  // Attempting to pop should return default value
}

// Test 5: FIFO first-in, first-out behavior
void test_fifo_first_in_first_out() {
    FIFObuf<int> fifo(5);

    fifo.push(100);
    fifo.push(200);
    fifo.push(300);

    TEST_ASSERT_EQUAL(100, fifo.pop()); // First pushed element (100) should be popped first
    TEST_ASSERT_EQUAL(200, fifo.pop()); // Second pushed element (200) should follow
    TEST_ASSERT_EQUAL(300, fifo.pop()); // Third pushed element (300) should follow
    TEST_ASSERT_EQUAL(0, fifo.size()); // FIFO should now be empty
}


void setup() {
    Serial.begin(115200);
    delay(2000);

    // Start Unity tests
    UNITY_BEGIN();

    RUN_TEST(test_fifo_push_and_pop);
    RUN_TEST(test_fifo_overflow);
    RUN_TEST(test_fifo_empty_pop);
    RUN_TEST(test_fifo_clear);
    RUN_TEST(test_fifo_first_in_first_out);

    UNITY_END();
}

void loop() {
}
