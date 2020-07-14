// 7 segment display configurator header file
#ifndef ssd_h
#define ssd_h

#ifndef Arduino_h
	#include <iostream>
	#define String std::string
#endif // Arduino_h

//#define min_res // Makes the library bare boned

// Defines which classes to ship with, technically because table is a pointer in the display class any other classes aren't necessary
#define seven_seg

#define amount 63
#define TM1637 "pgfedcba"

class display {
	uint8_t *table; // Pointer to an array containing conversion values

	#ifndef min_res
	String order; // Pin order
	char mode; // Is the connection a common anode or common cathode type

	protected:
		// Udates the table for the given order and mode
		void calculate(uint8_t *table);
	#endif // min_res
	public:
		#ifndef Arduino_h
		display(); // Default instance which asks you for the options
		#endif // Arduino_h

		// Instances with predefined options
		display(uint8_t *table);
		#ifndef min_res
		display(String order, String mode = "cathode");
		#endif // min_res

        // Converts a number into data that can be sent to the display
		uint8_t number(uint8_t num);
        // Converts a letter into data that can be sent to the display
		uint8_t letter(char c);
        // Converts a string into an array of data that can be sent to the display
		uint8_t *message(unsigned char msg[]);

		#ifdef Arduino_h
        // Sends data to the display
		void send(uint8_t data);
        // Sends an array of data to the display in a cycle
		void send(uint8_t data[], uint8_t sleep = 200);
		#else
        // Prints the order and the values to be sent for each member of the conversion array
		void print_table(uint8_t limit = 10, uint8_t s = 0, bool mode = 1);
		void dev(); // // Prints pseudocode resembling the implementation of the conversion array
		#endif // Arduino_h
};

#if defined(seven_seg) && !defined(min_res)
class seven : public display {
	uint8_t table_7[amount] = {
		// anode values for 0-9, A-Z, a-z
		//abcdefgdp
		0b00000011, // 0
		0b10011111, // 1
		0b00100101, // 2
		0b00001101, // 3
		0b10011001, // 4
		0b01001001, // 5
		0b01000001, // 6
		0b00011111, // 7
		0b00000001, // 8
		0b00001001, // 9
		0b00010001, // A
		0b00000001, // B
		0b01100011, // C
		0b00000111, // D
		0b01100001, // E
		0b01110001, // F
		0b01000011, // G
		0b10010001, // H
		0b11110011, // I
		0b10001111, // J
		0b10100001, // K
		0b11100011, // L
		0b01010111, // M
		0b10010001, // N
		0b00000011, // O
		0b00110001, // P
		0b00100011, // Q
		0b00100001, // R
		0b01001001, // S
		0b01110011, // T
		0b10000011, // U
		0b10001011, // V
		0b10101001, // W
		0b01101101, // X
		0b10001001, // Y
		0b00100101, // Z
		0b11001101, // a
		0b11000001, // b
		0b11100101, // c
		0b10000101, // d
		0b11100111, // e
		0b01110001, // f
		0b01110101, // g
		0b11010011, // h
		0b11110111, // i
		0b10001111, // j
		0b01101001, // k
		0b11110011, // l
		0b01010111, // m
		0b11010101, // n
		0b11000101, // o
		0b00110001, // p
		0b00010001, // q
		0b11110101, // r
		0b11101101, // s
		0b11100001, // t
		0b11000111, // u
		0b11001111, // v
		0b10101011, // w
		0b11101101, // x
		0b10001001, // y
		0b11101101, // z
		0b11111111
	};

	public:
		seven(String order, String mode = "cathode") : display(order, mode) { calculate(table_7); };
		#ifndef Arduino_h
		seven() { calculate(table_7); };
		#endif
};
#endif // seven_seg && !min_res

class displays {
	public:
		displays(display dps[]);
};

#endif // ssd_h
