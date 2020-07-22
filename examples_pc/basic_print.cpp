// A demonstration of the 7 segment display libray's educative features
#include <seven.h>

int main() {
	seven circut("abcdefgh", "anode");
	circut.print_table(11);

	std::cout << std::hex;
	std::cout << "For the number 5 send: " << "0x" << +circut.number(5) << std::endl;
	std::cout << "For the letter A send: " << "0x" << +circut.letter('A') << std::endl;
	std::cout << "For the letter b send: " << "0x" << +circut.letter('b') << std::endl;
}
