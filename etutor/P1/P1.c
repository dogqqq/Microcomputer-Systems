#include<stdio.h>


unsigned int nibble(unsigned int val, int k) {
    return (val >> (4*k)) & 0x0F;
}

int main(int argc, char const *argv[]){
	unsigned int num;
	int cnt = 1;
	unsigned int arr[10] = {0};

	while(scanf("%u", &num) != EOF){

		printf("Case %d: %u\n", cnt, num);
		cnt++;
		for (int i = 0; i < 8; ++i){
			unsigned int ans = nibble(num, i);
			arr[7-i] = ans;
		}
		for (int i = 0; i < 8; ++i)
			printf("%X ", arr[i]);

		printf("\n");
	}
	return 0;
}


