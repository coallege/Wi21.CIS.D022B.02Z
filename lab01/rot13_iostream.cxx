#include <string>
#include <iostream>

using namespace std;

string askEncrypt();

void input(string *input);
void rot13(string *original);
void output(string *output);

int main() {
	while (true) {
		string whatToDo = askEncrypt();
		if (whatToDo == "encrypt" || whatToDo == "decrypt") {
			string *inputString = new string;

			input (inputString);
			rot13 (inputString);
			output(inputString);

			delete inputString;
			inputString = nullptr;

			continue;
		}
		break;
	}
}

string askEncrypt() {
	cout << "Options:\nencrypt, decrypt, quit [default]\n> ";
	string option;
	getline(cin, option);
	return option;
}

void input(string *input) {
	cout << "Input string to be encrypted/decrypted\n> ";
	getline(cin, *input);
}

void rot13(string *strptr) {
	string &input = *strptr;
	int inputSize = input.size();
	int index = 0;
	while(index != inputSize) {
		if (input[index] >= 97 && input[index] <= 109) {
			input[index] = input[index] + 13;
		} else if (input[index] >= 110 && input[index] <= 122) {
			input[index] = input[index] - 13;
		} else if(input[index] >= 65 && input[index] <= 77) {
			input[index] = input[index] + 13;
		} else if(input[index] >= 78 && input[index] <= 90) {
			input[index] = input[index] - 13;
		}
		index++;
	}
}

void output(string *output) {
	cout << "Your encrypted/decrypted string is\n> " << *output << "\n\n";
}
