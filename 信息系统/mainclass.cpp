#include "iostream"
using namespace std;
#include "CSocketProtocol.h"
#include "CSckFactoryImp1.h"
#include "CEncDesProtocol.h"
#include "HvEncDec.h"

//功能增强	多继承、组合
//不建议使用多继承
class MainOp
{
public:
	MainOp()
	{
		sp = NULL;
		ed = NULL;
	}
	MainOp(CSocketProtocol *sp, CEncDesProtocol *ed)
	{
		this->sp = sp;
		this->ed = ed;
	}
	void SetSp(CSocketProtocol *sp)
	{
		this->sp = sp;
	}
	void SetEd(CEncDesProtocol *ed)
	{
		this->ed = ed;
	}
	int sckSendAndRev_EncDec(unsigned char *in, int inlen, unsigned char *out, int *outlen )
	{
		int ret = 0;
		unsigned char data[4096];
		int datalen = 0;
		ret = sp->cltSocketInit();
		if (ret != 0)
		{
			goto End;
		}

		//ed->EncDate(in, inlen, data, &datalen);
		ret = sp->cltSocketSend(in, inlen);
		if (ret != 0)
		{
			goto End;
		}

		ret = sp->cltSocketRev(in, outlen);
		if (ret != 0)
		{
			goto End;
		}
		//ed->DecDate(data, datalen, out, outlen);

		//ret = sp->cltSocketDestory();
		if (ret != 0)
		{
			goto End;
		}
	End:
		return 0;
	}
private:
	CSocketProtocol *sp;
	CEncDesProtocol *ed;
};

int main()
{
	int ret = 0;
	unsigned char in[4096];
	unsigned char out[4096];
	int inlen;
	int outlen = 0;

	strcpy((char*)in, "fsdjjjkkkkkkkkkkkkkkkkkkkjjjfd");
	inlen = 9;
	CSocketProtocol *sp = new CSckFactoryImp1;
	CEncDesProtocol *ed = new HvEncDec;
	MainOp *myop = new MainOp;
	myop->SetSp(sp);
	myop->SetEd(ed);
	ret = myop->sckSendAndRev_EncDec(in, inlen, out, &outlen);
	{
		if (ret!=0)
		{
			printf ("sckSendAndRev_EncDec() err:%d\n", ret);
			return ret;
		}
	}
	delete sp, ed, myop;
	system ("pause");
	return ret;
}