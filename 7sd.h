// 7 segment display configurator header file
#ifndef ssd_h
#define ssd_h

#ifndef Arduino_h
	#include <iostream>
	#define String std::string
#endif // Arduino_h

//#define min_res // Makes the library bare boned

// Technically because table is a pointer in the display class any other classes aren't necessary
#ifndef min_res
	#define seven_seg
#endif // min_res

#ifdef seven_seg
	#define TM1637 "hgfedcba"
#endif // seven_seg

#define amount 68

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
		#if !defined(Arduino_h) && !defined(min_res)
		display(); // Default instance which asks you for the options
		#endif // !Arduino_h && !min_res

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

#if defined(seven_seg) && !defined(min_res)
class seven : public display {
	//     A
	//    ---
	// F |   | B
	//    -G-
	// E |   | C
	//    ---
	//     D  -H-
	uint8_t table_7[amount] = {
		//hgfedcba, cathode values
		0b00111111, // 0                                                                                                                                                      
		0b00000110, // 1                                                                                                                                               
		0b01011011, // 2
		0b01001111, // 3
		0b01100110, // 4
		0b01101101, // 5
		0b01111101, // 6
		0b00000111, // 7
		0b01111111, // 8
		0b01101111, // 9
		0b01110111, // A
		0b01111111, // B
		0b00111001, // C
		0b00011111, // D
		0b01111001, // E
		0b01110001, // F
		0b00111101, // G
		0b01110110, // H
		0b00110000, // I
		0b00001110, // J
		0b01111010, // K
		0b00111000, // L
		0b00010101, // M
		0b01110110, // N
		0b00111111, // O
		0b01110011, // P
		0b00111011, // Q
		0b01111011, // R
		0b01101101, // S
		0b00110001, // T
		0b00111110, // U
		0b00101110, // V
		0b01101010, // W
		0b01001001, // X
		0b01101110, // Y
		0b01011011, // Z
		0b01001100, // a
		0b01111100, // b
		0b01011000, // c
		0b01011110, // d
		0b00011000, // e
		0b01110001, // f
		0b01010001, // g
		0b00110100, // h
		0b00010000, // i
		0b00001110, // j
		0b01101001, // k
		0b00110000, // l
		0b00010101, // m
		0b01010100, // n
		0b01011100, // o
		0b01110011, // p
		0b01110111, // q
		0b01010000, // r
		0b01001000, // s
		0b01111000, // t
		0b00011100, // u
		0b00001100, // v
		0b00101010, // w
		0b01001000, // x
		0b01101110, // y
		0b01001000, // z
		0b00100010, // "
		0b00100000, // '
		0b01001000, // :
		0b01000000, // -
		0b00001000, // _
		0b00000000
	}; // https://en.wikipedia.org/wiki/Seven-segment_display_character_representations

	public:
		seven(String order, String mode = "cathode") : display(order, mode) { calculate(table_7); };
		#ifndef Arduino_h
		seven() { calculate(table_7); };
		#endif // Arduino_h

		uint8_t number(uint8_t num, bool hex = 1);
};
#endif // seven_seg && !min_res

class displays {
	public:
		displays(display *dps);
};

#endif // ssd_h
