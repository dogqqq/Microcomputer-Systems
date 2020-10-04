#include<bits/stdc++.h>

using namespace std;

void displayBits(int value){
	cout << char(value) << ":\n";
	cout << value << " = ";
	for (int i = 31; i >= 0; --i){
		cout << (value >> i & 1);
		if(i%8 == 0)	cout << " ";
	}
	cout << endl;
}

unsigned int packCharacters(char c1, char c2, char c3, char c4) {
	unsigned int tmp = 0;
	char arr[4] = {c1, c2, c3, c4};
	for (int i = 0; i < 4; ++i){
		tmp += (int(arr[i]) << (3-i)*8 );
	}
	return tmp;
}

int main(int argc, char const *argv[]) {
	char c1, c2, c3, c4;
	while(cin >> c1 >> c2 >> c3 >> c4){
		displayBits(int(c1));
		displayBits(int(c2));
		displayBits(int(c3));
		displayBits(int(c4));
		cout << "'" << c1 << "' and '" << c2 << "' and '" \
			<< c3 << "' and '" << c4 << "' packed in an unsigned int:" << endl;
		unsigned int ans = packCharacters(c1, c2, c3, c4);
		cout << ans << " = ";
		for (int i = 31; i >= 0; --i){
			cout << (ans >> i & 1);
			if (i % 8 == 0)	cout << " ";
		}
		cout << endl;
	}
	return 0;
}