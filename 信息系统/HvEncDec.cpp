#include <iostream>
using namespace std;
#include "HvEncDec.h"
#include "Dec.h"

int HvEncDec::EncDate(unsigned char *plain, int plainlen, unsigned char *crypt, int *cryptlen)
{
	int ret = 0;
	ret = DesEnc(plain, plainlen, crypt, cryptlen);
	if (ret != 0)
	{
		printf("DesEnc() err:%d\n", ret);
	}

	return 0;
}
int HvEncDec::DecDate(unsigned char *crypt, int cryptlen, unsigned char *plain, int *plainlen) 
{
	int ret = 0;
	ret = DesDec(crypt, cryptlen, plain, plainlen);
	if (ret != 0)
	{
		printf("DesDec() err:%d\n", ret);
	}

	return 0;
}