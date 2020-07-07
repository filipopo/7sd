// A demonstration of the 7 segment display libray's educative features
#include "../7sd.h"
#include <cstring>

using namespace std;

int main() {
	display A;
	char s[100];
	cout << "Enter a message" << endl;
	cin >> s;

	char* msg = A.message(s);
	for (int i = 0; i < strlen(msg); i++)
		cout << msg[i] << endl;
}
