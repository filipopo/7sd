// 7 segment display configurator cpp file
#include "7sd.h"
#ifndef Arduino_h
#include <cstring>
#endif

// Instance with predefined options
display::display(String order, String mode) {
	this->order = order;
    this->mode = tolower(mode[0]);

    calculate();
}

#ifndef Arduino_h
// Default instance which asks you for the options
display::display() {
    std::cout << "Common cathode or anode? ";
	String mode;
    std::cin >> mode;
	this->mode = tolower(mode[0]);
    std::cout << "Enter the order: ";
    std::cin >> order[0] >> order[1] >> order[2] >> order[3] >> order[4] >> order[5] >> order[6] >> order[7];
	std::cout << order;

    calculate();
    print_table();
}
#endif

// For the input options creates a table and pre-defines conversion values
// This is done with so that the program doesn't need to do a for loop 8 times every time it's sending something
void display::calculate() {
	//Creates a temporary matrix because we don't know the order and need the original one
	bool table_b[amount][8];
	for (short i = 0; i < amount;i++) {
		B[i] = 0;
		for (short j = 0; j < 8;j++) {
			bool b = 0;
			switch (order[j]) {
				case 'a': b = table[i][0];break;
				case 'b': b = table[i][1];break;
				case 'c': b = table[i][2];break;
				case 'd': b = table[i][3];break;
				case 'e': b = table[i][4];break;
				case 'f': b = table[i][5];break;
				case 'g': b = table[i][6];break;
				case 'p': b = table[i][7];break;
			}

			// Cathode values are just inverted anode values
			if (mode == "c") // FixMe, mode should be a char
				b = !b;

			table_b[i][j] = b;
			if (b)
				B[i] |= (1u << 7 - j); //Sets the bit on the 7-j position of the B[i] element to 1
		}
	}

	//Copies over our temporary matrix into the real one
	memcpy(table, table_b, sizeof(table));
}

// A big ascii mess
short display::letter(char c) {
    if (c >= 65 && c <= 90)
        c -= 55;
    else if (c >= 97 && c <= 122)
        c -= 61;
    else
        c = amount - 1;

    return B[c];
}

// Coverts a string to data a 7 segment display can parse
char* display::message(char msg[]) {
    for (short i = 0; i < strlen(msg); i++)
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
// Prints out the order and then prints the table + conversion values for each number
void display::print_table(short limit, short s, bool mode) {
	if (mode) {
		std::cout << std::hex;
		for (short i = 0;i < 8;i++)
			std::cout << order[i] << ' ';
		std::cout << std::endl;
	} else
		std::cout << std::dec;

	for (s;s < limit;s++) {
		if (!mode)
			std::cout << "0b";
		for (short j = 0; j < 8;j++) {
			std::cout << table[s][j];
			if (mode)
				std::cout << ' ';
		}

		if (mode) {
			String start = "0x";
			if (B[s] <= 0xF)
				start += '0';
			std::cout << start << B[s] << ' ' << s;
		} else {
			std::cout << ", // ";
			if (s > 9 && s < 36)
        		std::cout << char(s + 55);
    		else if (s >= 36 && s < 62)
       		 	std::cout << char(s + 61);
			else
				std::cout << s;
		}

		std::cout << std::endl;
	}
}
#endif
