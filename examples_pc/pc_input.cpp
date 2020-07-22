// Getting the mode, order and some string from the PC user
#include <seven.h>
#include <cstring>

int main() {
	seven A;
	A.print_table();
	char s[50];
	std::cout << std::endl << "Enter a message" << std::endl;
	std::cin >> s;

	uint8_t *msg = A.message(s);
	std::cout << std::hex;
	for (int i = 0; i < strlen((char *)msg); i++)
		std::cout << "0x" << +msg[i] << std::endl;
}
