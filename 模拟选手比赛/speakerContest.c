#include <iostream>
using namespace std;
#include<string>
#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<functional>
#include<numeric>
#include<map>
#include<deque>
#include<iterator>
class Speaker
{
public:
	string m_name;
	int m_sore;
};
int GenSpeaker(map<int, Speaker> &mapSpeaker, vector<int> &v)
{
	string str = "ABCDEFGHJKLMNOPQRSTUVWXYZ";
	random_shuffle(str.begin(), str.end());		//随机洗牌
	for(int i=0; i<24; i++)
	{
		Speaker temp;
		temp.m_name = "选手";
		temp.m_name = temp.m_name + str[i];
		mapSpeaker.insert(pair<int, Speaker>(100+i, temp));
	}
	for(int i=0; i<24; i++)
	{
		v.push_back(100+i);
	}
	return 0;
} 
int speach_contest_draw(vector<int> &v)
{
	random_shuffle(v.begin(), v.end());
	return 0;
}
int speach_contest(int index, vector<int> &v1, map<int, Speaker> &mapSpeaker, 
vector<int> &v2)
{
	int temcount = 0;
	multimap<int, int, greater<int>> GroupScore;
	for(vector<int>::iterator it=v1.begin(); it!=v1.end(); it++)
	{
		temcount++;
		//打分
		deque<int> dscore;
		for(int i=0; i<10; i++)
		{
			int score = 50 + rand()%50;
			dscore.push_back(score);
		}
		sort(dscore.begin(), dscore.end());
		dscore.pop_back();
		dscore.pop_front();
		int scoresum = accumulate(dscore.begin(), dscore.end(), 0);
		int scoreavg = scoresum/dscore.size();
		mapSpeaker[*it].m_sore = scoreavg;
		GroupScore.insert(pair<int, int>(scoreavg, *it));
		//处理分组
		if(temcount % 6 == 0)
		{
			cout<<"小组比赛成绩"<<GroupScore.size()<<endl;//编号  姓名  得分 
			for(multimap<int, int, greater<int>>::iterator mit=
						GroupScore.begin(); mit!=GroupScore.end(); mit++)
			{
				cout<<mit->second<<"\t"<<mapSpeaker[mit->second].m_name
										<<"\t"<<mit->first<<endl;
			}
			//前三名晋级
			while(GroupScore.size()>3)
			{
				multimap<int, int, greater<int>>::iterator it1 =
												 GroupScore.begin();
				v2.push_back(it1->second);
				GroupScore.erase(it1);
			}
			GroupScore.clear();
		}
	}
	return 0;
}
int speach_contest_print(int index, map<int, Speaker> &mapSpeaker, 
															vector<int> &v)
{
	printf("第%d几轮 晋级名单\n", index+1);
	for(vector<int>::iterator it=v.begin(); it!=v.end(); it++)
	{
		cout<<"参赛编号："<<*it<<"\t"<<mapSpeaker[*it].m_name
										<<"\t"<<mapSpeaker[*it].m_sore<<endl;
	}
	return 0;
}
void main()
{
	map<int, Speaker> mapSpeaker;			//参赛选手
	vector<int> v1;							//第一轮选手编号
	vector<int> v2;							//第二轮
	vector<int> v3;							//第三轮
	vector<int> v4;							//第四轮
	int a = 1; int b = 1; int c = 1;
	GenSpeaker(mapSpeaker, v1);						//产生选手
	cout<<"任意键开始第一轮比赛"<<endl;
	cin.get();
	speach_contest_draw(v1);						//选手抽签
	speach_contest(0, v1, mapSpeaker, v2);			//选手比赛
	speach_contest_print(0, mapSpeaker, v2);		//查看比赛结果
	cout<<"任意键开始第二轮比赛"<<endl;
	cin.get();
	speach_contest_draw(v2);						//选手抽签
	speach_contest(1, v2, mapSpeaker, v3);			//选手比赛
	speach_contest_print(1, mapSpeaker, v3);		//查看比赛结果
	cout<<"任意键开始第三轮比赛"<<endl;
	cin.get();
	speach_contest_draw(v3);//选手抽签
	speach_contest(2, v3, mapSpeaker, v4);			//选手比赛
	speach_contest_print(2, mapSpeaker, v4);		//查看比赛结果
	system("pause");
}

