#include<bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
	int cnt = 1;
	unsigned int num, change_num;

	while(cin >> num){
		if(cnt != 1)	cout << endl;
		cnt ++;
		cout << "Before bits are reversed:\n";
		cout << num << " = ";
		for (int i = 31; i >= 0; --i){
			cout << ((num >> i) & 1);
			if(i % 8 == 0)	cout << ' ';
		}

		change_num = 0;
		for (int i = 0; i < 32; ++i){
			if(num >> i & 1)
				change_num += (1 << 31-i);
		}

		cout << "\n\nAfter bits are reversed:\n";
		cout << change_num << " = ";
		for (int i = 31; i >= 0; --i){
			cout << ((change_num >> i) & 1);
			if(i % 8 == 0)	cout << ' ';
		}
		cout << endl;
	}
	
	return 0;
}