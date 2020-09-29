#include<iostream>

using namespace std;

void printBinary(unsigned int num){
	for (int i = 31; i >= 0; --i){
		bool out = (num >> i) & 0x01;
		cout << out;
	}
	cout << endl;
}

void printOctal(unsigned int num){
	cout << "0";
	for (int i = 10; i >= 0; i--){
		int out = (num >> (i*3)) & 0x07;
		cout << out;
	}
	cout << endl;
}


void printHexidecimal(unsigned int num){
	cout << "0x" << hex << uppercase;
	for (int i = 7; i >= 0 ; --i){
		int out = (num >> (i*4)) & 0x0F;
		cout << out;
	}
	cout << endl;
}
int main(int argc, char const *argv[]){
	int cases = 1;
	unsigned int in;

	while(cin >> in){
		cout << "Case " << dec << cases << ": " << dec << in << endl;
		printBinary(in);
		printOctal(in);
		printHexidecimal(in);
		cases++;

	}
	return 0;
}