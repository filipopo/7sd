// Display base class header file
#pragma once

#ifndef Arduino_h
  #include <iostream>
  #define String std::string
#endif // Arduino_h

// Technically because table is a pointer in the display class any other classes aren't necessary
#define TM1637 "hgfedcba"

#define amount 96 // Num of characters does this library support, FixMe: the worst thing I could do

class display {
  protected:
    uint8_t *table; // Pointer to an array containing conversion values

    String order; // Pin order
    char mode; // Is the connection a common anode or common cathode type

    void calculate(); // Updates the table for the given order and mode
  public:
    #ifndef Arduino_h
    display(); // Default instance which asks you for the options
    #endif // Arduino_h

    // Instance with predefined options
    display(uint8_t *table);

    // Converts a number into data that can be sent to the display
    uint8_t number(uint8_t num);
    // Converts a letter into data that can be sent to the display
    uint8_t letter(char c);
    // Converts a string into an array of data that can be sent to the display
    uint8_t *message(char *msg);

    #ifdef Arduino_h
    // Sends data to the display
    void send(uint8_t data);
    // Sends an array of data to the display in a cycle
    void send(uint8_t *data, uint8_t sleep = 200);
    #else
    // Prints the order and the values to be sent for each member of the conversion array
    void print_table(uint8_t limit = 10, uint8_t s = 0, bool mode = 1);
    void dev(); // Prints pseudocode resembling the implementation of the conversion array
    #endif // Arduino_h
};
