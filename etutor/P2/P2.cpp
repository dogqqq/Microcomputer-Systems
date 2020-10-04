#include<iostream>

using namespace std;
char arr[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void printBinary(unsigned int num){
	for (int i = 31; i >= 0; --i)
		cout << ((num >> i) & 0x01);
	cout << endl;
}

void printOctal(unsigned int num){
	cout << "0";
	for (int i = 10; i >= 0; i--)
		cout << ((num >> (i*3)) & 0x07);
	cout << endl;
}

void printHexidecimal(unsigned int num){
	cout << "0x";
	for (int i = 7; i >= 0 ; --i)
		cout << arr[(num >> (i*4)) & 0x0F];
	cout << endl;
}

int main(int argc, char const *argv[]){
	int cases = 1;
	unsigned int in;

	while(cin >> in){
		cout << "Case " << cases << ": " << in << endl;
		printBinary(in);
		printOctal(in);
		printHexidecimal(in);
		cases++;
	}
	return 0;
}