// Using the library to make a conversion table for the TM1637 7 segment display
// and linking that table to the display class instead of using any other class
#include <seven.hpp>

using namespace std;

int main() {
  seven dev(TM1637);
  cout << "Complete TM1637 table:" << endl;
  dev.dev();
  cout << endl;

  // Table generated via dev() method
  uint8_t table_tm1637[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
  };

  display d = display(table_tm1637);
  cout << hex;
  cout << "For the number zero on a tm1637 display send 0x" << + d.number(0) << endl;
}
