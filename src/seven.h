// Seven segment specific header file
#ifndef seven_h
#define seven_h

#include "display.h"

#ifndef min_res
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
		#ifndef Arduino_h
		seven();
		#endif // Arduino_h
		seven(String order, String mode = "cathode");

		uint8_t number(uint8_t num, bool hex = 1);
};
#endif // min_res

#endif // even_h
