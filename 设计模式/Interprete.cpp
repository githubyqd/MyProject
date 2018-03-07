#include <iostream>
using namespace std;

class Context
{
public:
	Context(int num)
	{
		m_num = num;
	}
	int getNum()
	{
		return m_num;
	}
	void setRes(int res)
	{
		m_res =res;
	}
	int getRes()
	{
		return m_res;
	}
private:
	int m_num;
	int m_res;
};

class Expression
{
public:
	virtual void interpreter(Context *context) = 0;
private:
	Context *m_context;
};
class PlusExpression:public Expression
{
public:
	virtual void interpreter(Context *context)
	{
		int num = context->getNum();
		num++;
		context->setRes(num);
	}
private:
	Context *m_context;
};
class MinusExpression:public Expression
{
public:
	virtual void interpreter(Context *context)
	{
		int num = context->getNum();
		num--;
		context->setRes(num);
	}
private:
	Context *m_context;
};

void main()
{
	Context* context = new Context(10);
	Expression* expression1 = new PlusExpression;
	expression1->interpreter(context);
	cout<<context->getRes()<<endl;

	system("pause");
}