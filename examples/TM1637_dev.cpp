// A demonstration of the 7 segment display libray's educative features
#include "../7sd.h"

using namespace std;

int main() {
	display dev(TM1637);
	cout << "Complete TM1637 table:" << endl;
	dev.dev();
}
