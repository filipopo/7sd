// 7 segment display configurator cpp file
#include "7sd.h"
#ifndef Arduino_h
	#include <cstring>
#endif // Arduino_h

#if !defined(Arduino_h) && !defined(min_res)
display::display() {
	std::cout << "Common cathode or anode? ";
	String mode;
	std::cin >> mode;
	this->mode = tolower(mode[0]);

	std::cout << "Enter the order: ";
	std::cin >> order[0] >> order[1] >> order[2] >> order[3] >> order[4] >> order[5] >> order[6] >> order[7];
}
#endif // !Arduino_h && !min_res

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
			bool b;
			switch (order[j]) {
				case 'a': b = *(table + i) >> 0 & 1; break;
				case 'b': b = *(table + i) >> 1 & 1; break;
				case 'c': b = *(table + i) >> 2 & 1; break;
				case 'd': b = *(table + i) >> 3 & 1; break;
				case 'e': b = *(table + i) >> 4 & 1; break;
				case 'f': b = *(table + i) >> 5 & 1; break;
				case 'g': b = *(table + i) >> 6 & 1; break;
				case 'h': b = *(table + i) >> 7 & 1; break;
			}

			// Anode values are just inverted cathode values
			if (mode == 'a')
				b = !b;

			if (b)
				table_b[i] |= (1 << 7 - j); // Sets the bit on the 7-j position of the B[i] element to 1
		}
	}

	// Copies over our temporary matrix into the real one
	memcpy(table, table_b, sizeof(table_b));
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
	else {
		switch (c) {
			case 34: c = 62; break;
			case 39: c = 63; break;
			case 58: c = 64; break;
			case 45: c = 65; break;
			case 95: c = 66; break;
			default: c = 67; break; // FixMe, do amount - 1 in the preprocessor
		}
	}

	return *(table + c);
}

uint8_t *display::message(char *msg) {
	for (uint8_t i = 0; i < strlen(msg); i++)
		msg[i] = letter(*(msg + i));

	return (uint8_t *)msg;
}

#ifdef Arduino_h
void display::send(uint8_t data) {

}

void display::send(uint8_t *data, uint8_t sleep) {
	for (uint8_t i = 0; i < strlen(msg); i++) {
		send(*(data + i));
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
			std::cout << (*(table + s) >> j & 1);
			if (mode)
				std::cout << ' ';
		}

		if (mode) {
			String start = "0x";
			if (*(table + s) <= 0xF)
				start += '0';

			// Outputs what should be sent for this array member, in hexadecimal
			std::cout << start << +*(table + s);
		} else
			std::cout << ", //";

		// This is ugly but....
		std::cout << ' ';
		if (s >= 10 && s <= 66) {
			char c;

			if (s >= 10 && s <= 35)
				c = s + 55;
			else if (s >= 36 && s <= 61)
				c = s + 61;
			else {
				switch (s) {
					case 62: c = 34; break;
					case 63: c = 39; break;
					case 64: c = 58; break;
					case 65: c = 45; break;
					case 66: c = 95; break;
				}
			}

			std::cout << c;
		} else
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

#ifndef min_res
uint8_t seven::number(uint8_t num, bool hex) {
	if (hex) {
		switch (num) {
			case 11: num = 37; break;
			case 13: num = 39; break;
		}
	}

	return display::number(num);
}
#endif // min_res

displays::displays(display *dps) {

}
