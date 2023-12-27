// Display baseclass source file
#include "display.hpp"
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
  for (uint8_t i = 0; i < 8; i++)
    std::cin >> order[i];
}
#endif // Arduino_h

display::display(uint8_t *table) {
  this->table = table;
}

void display::calculate() {
  // Creates a temporary matrix because we don't know the order and need the original one
  uint8_t table_b[amount];

  for (uint8_t i = 0; i < amount; i++) {
    table_b[i] = 0;
    for (uint8_t j = 0; j < 8; j++) {
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
        table_b[i] |= (1 << (7 - j)); // Sets the bit on the 7 - j position to 1
    }
  }

  // Copies over our temporary matrix into the real one
  memcpy(table, table_b, sizeof(table_b));
}

// Assuming we're mapping numbers over 9 to the alphabet I'm afraid it works up to base 36
uint8_t display::number(uint8_t num) {
  // A small price to pay for ascii salvation, the basic functionality is for numbers 0 - 9
  if (num > 9)
    num += 7;

  return *(table + num);
}

// I'm gonna assume anyone who sends ascii 0 - 31 will be happy with gibberish
uint8_t display::letter(char c) {
  if (c < 48)
    c += 40;
  else
    c -= 48;

  return *(table + c);
}

// Pretty sure this needs to be malloc'd
uint8_t *display::message(char *msg) {
  for (uint8_t i = 0; i < strlen(msg); i++)
    msg[i] = letter(*(msg + i));

  return (uint8_t *)msg;
}

#ifdef Arduino_h
void display::send(uint8_t data) {

}

void display::send(uint8_t *data, uint8_t sleep) {
  for (uint8_t i = 0; i < strlen((char *)data); i++) {
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

  for (; s < limit; s++) {
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

    std::cout << ' ';
    // This can probably be done in a better way but I was dead when I rewrote this
    if (s > 9) {
      char c;
      if (s < 80)
        c = s + 48;
      else
        c = s - 48;
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
