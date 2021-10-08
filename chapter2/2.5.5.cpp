#include <iostream>
using namespace std;

char swapCase(char letter) {
	int asciiCode = (int)letter;
	if (asciiCode >= 0x41 && asciiCode <= 0x5A) {
		// Letter is uppercase
		letter = (char)(asciiCode + 32);
	}
	else if (asciiCode >= 0x61 && asciiCode <= 0x7A) {
		// Letter is lowercase
		letter = (char)(asciiCode - 32);
	}

	return letter;
}

int main() {
    // Tests
    cout << "A -> " << swapCase('A') << endl;
    cout << "Z -> " << swapCase('Z') << endl;
    cout << "a -> " << swapCase('a') << endl;
    cout << "z -> " << swapCase('z') << endl;
    cout << "5 -> " << swapCase('5') << endl;

    return 0;
}