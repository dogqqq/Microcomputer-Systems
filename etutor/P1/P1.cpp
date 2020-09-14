#include<iostream>

using namespace std;

unsigned int nibble(unsigned int val, int k) {
    return (val >> (4*k)) & 0x0F;
}

int main(int argc, char const *argv[]){
	unsigned int num;
	int cnt = 1;

	while(cin >> num){
		
		cout << "Case " << dec << cnt << ": " << num << endl;
		cnt++;
		for (int i = 7; i >= 0; --i){
			unsigned int ans = nibble(num, i);
			cout << uppercase << hex << ans << " " ;
		}
		cout << endl;
	}
	return 0;
}


