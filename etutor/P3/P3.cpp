#include<iostream>
#include<set>
#include<string>

using namespace std;

bool bool_all, bool_exist;
set<int> s;

void check(unsigned int num){
	for (auto i:s){
		if((num >> i) & 1)
			bool_exist = true;
		else
			bool_all = false;
	}
}

int main(int argc, char const *argv[]){

	int num, cnt = 1;
	unsigned int ch_num;
	string all = "(all bits 1)", exit = "(exist bits 1)";
	string tr = "true", fa = "false";
	s.clear();

	while(cin >> num && num != -1)
		s.insert(num);
	
	for (auto i : s)
		cout << i << ' ';

	cout << endl;

	while(cin >> ch_num){
		cout << "Case " << cnt++ << ": " << ch_num << endl;
		bool_all = true;
		bool_exist = false;
		check(ch_num);
		cout << (bool_all ? tr : fa) << all << endl;
		cout << (bool_exist ? tr : fa) << exit << endl;

	}
	return 0;
}
