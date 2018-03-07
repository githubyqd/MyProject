#pragma once

class CEncDesProtocol
{
public:
	CEncDesProtocol()
	{
	}
	virtual ~CEncDesProtocol()
	{
	}
	virtual int EncDate(unsigned char *plain, int plainlen, unsigned char *crypt, int *cryptlen) = 0;
	virtual int DecDate(unsigned char *crypt, int cryptlen, unsigned char *plain, int *plainlen) = 0;
};