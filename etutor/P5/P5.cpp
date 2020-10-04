#include<bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
	unsigned int num;
	while(cin >> num){
		cout << "The packed character representation is:" << endl;
		cout << num << " = ";
		for (int i = 31; i >= 0; --i){
			cout << (num >> i & 1);
			if(i%8 == 0)	cout << " ";
		}
		cout << "\n\n";
		char arr[4];
		for (int i = 0; i < 4; ++i){
			arr[i] = char((num & (0xFF000000 >> 8*i) ) >> (24 - 8*i));
		}
		for (int i = 0; i < 4; ++i){
		 	cout << int(arr[i]) << " = ";
		 	for (int j = 31; j >= 0; --j){
		 		cout << (arr[i] >> j & 1);
		 		if(j % 8 == 0)	cout << " ";
		 	}
		 	cout << endl;
		 }
	}
	return 0;
}