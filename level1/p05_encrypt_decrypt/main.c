#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 加密函数
void xor_encrypt(unsigned char* cleartext, unsigned char* key, int length)
{
	for (int i = 0; i < length; i++)
	{
		cleartext[i] ^= key[i % strlen(key)];
	}
}
// 解密函数
void xor_decrypt(unsigned char* cleartext, unsigned char* key, int length)
{
	for (int i = 0; i < length; i++)
	{
		cleartext[i] ^= key[i % strlen(key)];
	}
}
int main()
{

	system("chcp 65001");

	unsigned char cleartext[] = "周正奇";
	unsigned char key[] = "一把钥匙";

	int cleartext_length = strlen(cleartext);
	printf("原始明文：%s\n", cleartext);
	// 加密
	xor_encrypt(cleartext, key, cleartext_length);
	printf("加密后的密文:\n");
	printf("%s \n", cleartext);
	// 解密
	xor_decrypt(cleartext, key, cleartext_length);
	printf("解密后的明文：%s\n", cleartext);
	printf("%llu ", strlen(key));
	return 0;
}