#include <stdio.h>
void printf_bin(int num)
{
	int i, j, k;
	unsigned char *p = (unsigned char*)&num + 3;//p先指向num后面第3个字节的地址，即num的最高位字节地址

	for (i = 0; i < 4; i++) //依次处理4个字节(32位）
	{
		j = *(p - i); //取每个字节的首地址，从高位字节到低位字节，即p p-1 p-2 p-3地址处
		for (int k = 7; k >= 0; k--) //处理每个字节的8个位，注意字节内部的二进制数是按照人的习惯存储！
		{
			if (j & (1 << k))//1左移k位，与单前的字节内容j进行或运算，如k=7时，00000000&10000000=0 ->该字节的最高位为0
				printf("1");
			else
				printf("0");
		}
		printf(" ");//每8位加个空格，方便查看
	}
	printf("\r\n");
}

int main(){
    int a = 0b00000001;
    printf_bin(~(a<<2));
}