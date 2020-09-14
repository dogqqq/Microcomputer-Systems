#include<stdio.h>


unsigned int nibble(unsigned int val, int k) {
    return (val >> (4*k)) & 0x0F;
}

int main(int argc, char const *argv[]){
	unsigned int num;
	int cnt = 1;

	while(scanf("%u", &num) != EOF){

		printf("Case %d: %u\n", cnt, num);
		cnt++;
		for (int i = 7; i >= 0; --i){
			unsigned int ans = nibble(num, i);
			printf("%X ", ans);
		}

		printf("\n");
	}
	return 0;
}


