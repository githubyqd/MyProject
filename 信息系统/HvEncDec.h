#include "CEncDesProtocol.h"
class HvEncDec:public CEncDesProtocol
{
public:
	virtual int EncDate(unsigned char *plain, int plainlen, unsigned char *crypt, int *cryptlen);
	virtual int DecDate(unsigned char *crypt, int cryptlen, unsigned char *plain, int *plainlen);
};