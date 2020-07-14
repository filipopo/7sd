// A demonstration of the 7 segment display libray's educative features
#include "../../7sd.h"

using namespace std;

int main() {
	seven circut("abcdefgp", "anode");
	circut.print_table(11);

	std::cout << std::hex;
	cout << "For the number 5 send: " << "0x" << +circut.number(5) << endl;
	cout << "For the letter A send: " << "0x" << +circut.letter('A') << endl;
	cout << "For the letter b send: " << "0x" << +circut.letter('b') << endl;
}
