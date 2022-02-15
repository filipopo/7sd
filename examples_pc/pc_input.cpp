// Getting the mode, order and some string from the PC user
#include <seven.h>
#include <cstring>

using namespace std;

int main() {
  seven A;
  A.print_table();
  char s[50];
  cout << endl << "Enter a message" << endl;
  cin >> s;

  uint8_t *msg = A.message(s);
  cout << hex;
  for (int i = 0; i < strlen((char *)msg); i++)
    cout << "0x" << + msg[i] << endl;
}
