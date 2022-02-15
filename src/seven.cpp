// Seven segment specific source file
#include "seven.h"

#ifndef min_res

#ifndef Arduino_h
seven::seven() {
  table = table_7;
  calculate();
}
#endif // Arduino_h

seven::seven(String order, String mode) : display(table = table_7) {
  this->order = order;
  this->mode = tolower(mode[0]);

  if (order != TM1637 || mode != "cathode")
    calculate();
}

uint8_t seven::number(uint8_t num) {
  // In a seven segment display "B" is the same as "8" and "D" is ugly so send "b" and "d" instead
  // For all other numbers, default: break
  switch (num) {
    case 11: num = 37; break;
    case 13: num = 39; break;
  }

  return display::number(num);
}

#endif // min_res
