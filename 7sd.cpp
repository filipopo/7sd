// 7 segment display configurator cpp file
#include "7sd.h"
#ifndef Arduino_h
	#include <cstring>
#endif // Arduino_h

#ifndef Arduino_h
display::display() {
	std::cout << "Common cathode or anode? ";
	String mode;
	std::cin >> mode;
	this->mode = tolower(mode[0]);

	std::cout << "Enter the order: ";
	std::cin >> order[0] >> order[1] >> order[2] >> order[3] >> order[4] >> order[5] >> order[6] >> order[7];
}
#endif // Arduino_h

display::display(uint8_t *table) {
	this->table = table;
}

#ifndef min_res
display::display(String order, String mode) {
	this->order = order;
	this->mode = tolower(mode[0]);
}

void display::calculate(uint8_t *table) {
	this->table = table;

	// Creates a temporary matrix because we don't know the order and need the original one
	uint8_t table_b[amount];
	for (uint8_t i = 0; i < amount;i++) {
		table_b[i] = 0;
		for (uint8_t j = 0; j < 8;j++) {
			bool b = 0;
			switch (order[j]) {
				case 'a': b = (*(table + i) >> 7) & 1;break;
				case 'b': b = (*(table + i) >> 6) & 1;break;
				case 'c': b = (*(table + i) >> 5) & 1;break;
				case 'd': b = (*(table + i) >> 4) & 1;break;
				case 'e': b = (*(table + i) >> 3) & 1;break;
				case 'f': b = (*(table + i) >> 2) & 1;break;
				case 'g': b = (*(table + i) >> 1) & 1;break;
				case 'p': b = (*(table + i) >> 0) & 1;break;
			}

			// Cathode values are just inverted anode values
			if (mode == 'c')
				b = !b;

			if (b)
				table_b[i] |= (1 << 7 - j); // Sets the bit on the 7-j position of the B[i] element to 1
		}
	}

	// Copies over our temporary matrix into the real one
	memcpy(table, table_b, sizeof(table));
}
#endif // min_res

uint8_t display::number(uint8_t num) { 
	return *(table + num);
}

// A big ascii mess
uint8_t display::letter(char c) {
	if (c >= 65 && c <= 90)
		c -= 55;
	else if (c >= 97 && c <= 122)
		c -= 61;
	else
		c = amount - 1;

	return *(table + c);
}

uint8_t *display::message(unsigned char msg[]) {
	for (uint8_t i = 0; i < strlen((char *)msg); i++)
		msg[i] = letter(msg[i]);

	return msg;
}

#ifdef Arduino_h
void display::send(uint8_t data) {

}

void display::send(uint8_t data[], uint8_t sleep) {
	for (uint8_t i = 0; i < strlen(msg); i++) {
		send(data[i]);
		delay(sleep);
	}
}
#else
void display::print_table(uint8_t limit, uint8_t s, bool mode) {
	if (mode) {
		// Sets the output of numbers to hexadecimal
		std::cout << std::hex;
		for (uint8_t i = 0; i < 8; i++)
			std::cout << order[i] << ' ';
		std::cout << std::endl;
	}

	for (s; s < limit; s++) {
		if (!mode)
			std::cout << "0b";
		for (int8_t j = 7; j >= 0; j--) {
			std::cout << ((*(table + s) >> j) & 1);
			if (mode)
				std::cout << ' ';
		}

		if (mode) {
			String start = "0x";
			if (table[s] <= 0xF)
				start += '0';

			// Outputs what should be sent for this array member, in hexadecimal
			std::cout << start << +*(table + s);
		} else
			std::cout << ", //";

		std::cout << ' ';
		if (s >= 10 && s <= 35)
			std::cout << char(s + 55);
		else if (s >= 36 && s <= 61)
			std::cout << char(s + 61);
		else
			std::cout << +s;

		std::cout << std::endl;
	}

	// If we set the output mode to hexadecimal for this set it back to decimal
	if (mode)
		std::cout << std::dec;
}

void display::dev() {
	print_table(amount, 0 , 0);
}
#endif // Arduino_h
