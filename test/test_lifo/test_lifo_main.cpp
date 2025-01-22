#include <Arduino.h>
#include <unity.h>
#include "LIFObuf.h"

// Test 1: Push and pop operations
void test_lifo_push_and_pop() {
    LIFObuf<int> lifo(5); // Create a LIFO buffer with size 5

    TEST_ASSERT_TRUE(lifo.push(1)); // Push element 1
    TEST_ASSERT_TRUE(lifo.push(2)); // Push element 2
    TEST_ASSERT_TRUE(lifo.push(3)); // Push element 3

    TEST_ASSERT_EQUAL(3, lifo.size());  // LIFO size should be 3
    TEST_ASSERT_EQUAL(3, lifo.pop());   // Last pushed element (3) should be popped first
    TEST_ASSERT_EQUAL(2, lifo.pop());   // Next popped element should be 2
    TEST_ASSERT_EQUAL(1, lifo.pop());   // Finally, element 1 should be popped
    TEST_ASSERT_EQUAL(0, lifo.size());  // LIFO size should be 0
}

// Test 2: Overflow behavior
void test_lifo_overflow() {
    LIFObuf<int> lifo(3); // Create a LIFO buffer with size 3

    TEST_ASSERT_TRUE(lifo.push(1));
    TEST_ASSERT_TRUE(lifo.push(2));
    TEST_ASSERT_TRUE(lifo.push(3));
    TEST_ASSERT_FALSE(lifo.push(4)); // Adding an element should fail due to overflow

    TEST_ASSERT_EQUAL(3, lifo.size()); // LIFO size should remain 3
}

// Test 3: Popping from an empty LIFO
void test_lifo_empty_pop() {
    LIFObuf<int> lifo(3); // Create an empty LIFO buffer

    TEST_ASSERT_EQUAL(0, lifo.pop());  // Attempting to pop should return default value (0)
    TEST_ASSERT_EQUAL(0, lifo.size()); // LIFO size should remain 0
}

// Test 4: Clear operation
void test_lifo_clear() {
    LIFObuf<int> lifo(3); // Create a LIFO buffer with size 3

    lifo.push(1);
    lifo.push(2);
    lifo.push(3);

    lifo.clear(); // Clear the LIFO

    TEST_ASSERT_EQUAL(0, lifo.size()); // LIFO size should be 0
    TEST_ASSERT_EQUAL(0, lifo.pop());  // Attempting to pop should return default value
}

// Test 5: LIFO last-in, first-out behavior
void test_lifo_last_in_first_out() {
    LIFObuf<int> lifo(3);

    lifo.push(10);
    lifo.push(20);
    lifo.push(30);

    TEST_ASSERT_EQUAL(30, lifo.pop()); // Last pushed element (30) should be popped first
    TEST_ASSERT_EQUAL(20, lifo.pop()); // Next element (20) should follow
    TEST_ASSERT_EQUAL(10, lifo.pop()); // Finally, element 10 should be popped
    TEST_ASSERT_EQUAL(0, lifo.size()); // LIFO should now be empty
}

void setup() {
    Serial.begin(115200);
    delay(2000);

    // Start Unity tests
    UNITY_BEGIN();

    RUN_TEST(test_lifo_push_and_pop);
    RUN_TEST(test_lifo_overflow);
    RUN_TEST(test_lifo_empty_pop);
    RUN_TEST(test_lifo_clear);
    RUN_TEST(test_lifo_last_in_first_out);

    UNITY_END();
}

void loop() {
}
