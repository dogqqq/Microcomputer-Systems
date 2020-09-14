#include<iostream>
#include<stack>
#include<iostream>

using namespace std;

unsigned int nibble(unsigned int val, int k) {
    return (val >> (4*k)) & 0x0F;
}

int main(int argc, char const *argv[]){
	unsigned int num;
	int cnt = 1;
	stack<unsigned int> s;

	while(cin >> num){
		
		cout << "Case " << dec << cnt << ": " << num << endl;
		cnt++;
		for (int i = 0; i < 8; ++i){
			unsigned int ans = nibble(num, i);
			s.push(ans);
		}
		while(!s.empty()){
			cout << uppercase << hex << s.top() << " " ;
			s.pop();
		}
		cout << endl;
	}
	return 0;
}


