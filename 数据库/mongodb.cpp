/*开发类似网盘功能，支持大文件上传下载
技术实现要求：Mysql+mongo，用mysql存储用户信息，文件上传和下载的对应关系。Mongo存放文件

需求---需求分析---概要设计---详细设计---编码---测试---上线---维护---下线
可行性分析：经济可行、技术可行

create database ods charater set utf8;		//创建ods数据库
use ods 									//选择库

//创建用户资料表
create table t_user_info(
	user_id varchar(30),
	user_name vachar(30),
	pass_word varchar(16),
	reg_date timestamp,
	remark vachar(100));

//创建文件信息，status0代表正在上传，1上传成功，2失败
create table t_file_info(
	file_id int primary key auto_increment,
	local_file vachar(100),
	mongo_file vachar(100),
	upload_date timestamp,
	file_size int,
	user_id varchar(30),
	status varchar(2),
	remark vachar(100));

//添加两个用户
insert into t_user_info(user_id, user_name, pass_word, remark)values('xxx', 'xxx', '123', 'xxx');
insert into t_user_info(user_id, user_name, pass_word, remark)values('xxx', 'xxx', '123', 'xxx');

//编码设计
./command user passwd					进入<ods管理台

//命令设计
quit									退出
list									查看
upload localfile mongo_file 			上传
download localfile mongo_file			下载
./main xxx '0' or '1=1'  				//防范sql注入
*/
----------------------------------------------------------------------------

#include <iostream>
#include <vector>

using namespace std;

//delim分隔符
void splitString(const char *src, char delim, vector<string> &vsplit)
{
	string tmp = src;
	vsplit.clear();
	int index = 0;
	size_t last = 0;
	last = tmp.find_first_not_of(delim, last);
	index = tmp.find_first_of(delim, last);
	while(index!=string::npos)		//字符串结尾npos
	{
		string target = tmp.substr(last, index-last);
		vsplit.push_back(target);
		
		last = tmp.find_first_not_of(delim, last);
		index = tmp.find_first_of(delim, last);
	}
	
	if(index == string::npos && tmp.length() > last) //说明还有一个字符
	{
		vsplit.push_back(last);
	}
	cout<<vsplit.size()<<endl;
	for(size_t i=0; i<vsplit.size(); i++)
	{
		cout<<"i="<<i<<","<<vsplit[i].c_str()<<endl;
	}
}

//登录验证
int connect()
{
	if(!mysql = mysql_init(NULL))
	{
		printf("mysql_init err\n");
		return -1;
	}
	if(!mysql = mysql_real_connect(mysql, "localhost", "root", "123", "ods", 0, NULL, 0))
	{
		printf("mysql_real_connect err\n");
		return -1;
	}
	return 0;
}

//用户登录，判断用户名密码是否与mysql数据匹配，相当于做一个查询
int UserLogin(const char *User, const char *Passwd)
{
	char rsql[512];
	memset(rsql, 0x00, sizeof(rsql));
	sprintf(rsql, "select user_id from t_user_info where user_id='%s' and pass_word='%s'", User, Passwd);
	if(mysql_query(mysql, rsql))
	{
		printf("mysql_query err:%s\n", rsql);
		return -1;
	}
	
	//验证是否有数据
	MYSQL_RES *result = mysql_store_result(mysql);
	if(result->row_count)
	{
		printf("login success:%s, row_count=%lld\n", User, result->row_count);
		return 1;
	}
	return 0;		//密码不正确
}

//mongodb上传
unsigned long long UploadFileMongo(const char *OrgFile, const char *MongoFile)
{
	GridFs fs(*conn, "ods");	//参数分别是客户端连接、库名
	fs.storeFile(OrgFile, MongoFile); //相当于上传文件，参数本地文件名、mongo文件名
	return fs.findFile(MongoFile).getContentLength();
}
//mysql上传
int UploadFileMysql(const char *User, const char *LocalFile, const char *MongoFile)
{
	char rsql[512];
	memset(rsql, 0x00, sizeof(rsql));
	sprintf(rsql, "insert into t_file_info(local_file, mongo_file, file_size, user_id, status, remark)values('%s', '%s', 0, '%s', '0', 'uploading')",  LocalFile, MongoFile, User);
	if(mysql_query(mysql, rsql))
	{
		printf("UploadFile err:%s\n", rsql);
		return -1;
	}
	return 0;
}

//更新文件对应关系
int UpdateFileInfo(const char*User, const char *LocalFile, const char *MongoFile, unsigned long long nFileSize)
{
	char rsql[512] = {0};
	sprintf(rsql, "update t_file_info set file_size=%lld, status='1', remark='upload success' where user_id='%s' and local_file='%s' and mongo_file='%s'", nFileSize, User, LocalFile, MongoFile);
	if(mysql_query(mysql, rsql))
	{
		printf("update file info err:%s\n", rsql);
		return -1;
	}
	return 0;
}

//下载
int DownLoad(const char *OrgFile, const char *MongoFile)
{
	GridFs fs(*conn, "ods");	//参数分别是客户端连接、库名
	fs.findFile(MongoFile).write(LocalFile);	
	return 0;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout<<"./main user passwd"<<endl;
		return -1;
	}
	//管理台实现
	while(true)
	{
		cout<<"ods>";
		char linestr[512];
		memset(linestr, 0x00, sizeof(linestr));
		getline(linestr, cin);
		splitString(linestr.c_str(), ' ', vCmd);
		if(vCmd.size() == 1)
		{
			if(vCmd[0].compare("quit") == 0)
			{
				cout<<vCmd[0]<<endl;
				cout<<"bye!"<<endl;
			}
			else if(vCmd[0].compare("list") == 0)
			{
				cout<<vCmd[0]<<endl;
			}
		}
		else if(vCmd.size() == 3)
		{
			if(vCmd[0].compare("upload") == 0)
			{
				cout<<"upload:"vCmd[1]<<","<<vCmd[2]<<endl;
				
				//mysql生成对应关系
				UploadFileMysql(argv[1], vCmd[1].c_str(), vCmd[2].c_str());
				
				//mongo上传
				unsigned long long llsize = UploadFileMongo(vCmd[1].c_str(), vCmd[2].c_str());
				
				//mysql更改对应关系
				UploadFileMysql(argv[1], vCmd[1].c_str(), vCmd[2].c_str(), llsize);
			}
			else if(vCmd[0].compare("download") == 0)
			{
				cout<<"download:"vCmd[1]<<","<<vCmd[2]<<endl;
			}
		}
	}
	return 0;
}

