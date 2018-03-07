/*GCC=gcc
IncPath=/usr/inclue/mysql/
LibPath=/usr/lib64/mysql/
PubLib=-lmysqlclient –lstdc++ -ldl –lpthread –lrt
SrcFiles=$(wildcard *.c)
TargetFiles=$(patsubst %.c %, $( SrcFiles))

all:$(TargetFiles)
%:%.c
	$(GCC) $? –o $@ -I $(IncPath) –L $(LibPath) $(PubLib)
clean:
	rm –f $(TargetFiles)*/
----------------------------------------------------------------------------
#include "mysql.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SET_TRAN 	"SET_AUTOCOMMIT=0"				//手动commit
#define UNSET_TRAN 	"SET_AUTOCOMMIT=1"				//自动commit

#define _HOST_ 		"127.0.0.1" 	//主机
#define _USER_ 		"root"			//用户
#define _PASSWD_ 	"123"			//密码
#define _DB_		"scott"			//库

#define STRING_SIZE 50
#define DROP_SAMPLE_TABLE "DROP TABLE IF EXISTS test_table"
#define CREATE_SAMPLE_TABLE "CREATE TABLE test_table(col1 INT, col2 VARCHAR(10), col3 VARCHAR(10))"
//#define INSERT_SAMPLE "INSERT INTO test_table(col1, col2, col3)VALUES(?, ?, ?)"
#define sql01 "INSERT INTO test_table(col1, col2, col3)VALUES(10, 'AAA', 'A1')"
#define sql02 "INSERT INTO test_table(col1, col2, col3)VALUES(20, 'BBB', 'B2')"
#define sql03 "INSERT INTO test_table(col1, col2, col3)VALUES(30, 'CCC', 'C3')"
#define sql04 "INSERT INTO test_table(col1, col2, col3)VALUES(40, 'DDD', 'D4')"
																			
//设置事务为手动提交
int mysql_OperationTran(MYSQL *mysql)
{
	//开启事务
	int ret = mysql_query(mysql, "start transaction");
	if(ret !=0 )
	{
		printf("mysql_OperationTran query set err: %s\n", mysql_error(mysql));
		return ret;
	}
	
	//设置事务
	ret = mysql_query(mysql, SET_TRAN);
	if(ret !=0 )
	{
		printf("mysql_OperationTran query set err: %s\n", mysql_error(mysql));
		return ret;
	}
	return ret;
}

//设置事务为自动提交
int mysql_AUTOTran(MYSQL *mysql)
{
	int ret = mysql_query(mysql, "start transaction");
	if(ret !=0 )
	{
		printf("mysql_AUTOTran query set err: %s\n", mysql_error(mysql));
		return ret;
	}
	ret = mysql_query(mysql, UNSET_TRAN);
	if(ret !=0 )
	{
		printf("mysql_OperationTran query set err: %s\n", mysql_error(mysql));
		return ret;
	}
	return ret;
}
//执行手动commit事务
int mysql_Commit(MYSQL *mysql)
{
	int ret = mysql_query(mysql, "COMMIT");	//提交
	if(ret !=0 )
	{
		printf("mysql_Commit err: %s\n", mysql_error(mysql));
		return ret;
	}
	return ret;
}
//执行rollback回滚事务
int mysql_Rollback(MYSQL *mysql)
{
	int ret = mysql_query(mysql, "ROLLBACK");	
	if(ret !=0 )
	{
		printf("mysql_Rollback err: %s\n", mysql_error(mysql));
		return ret;
	}
	return ret;
}																

//预处理适用反复执行，提高执行效率，二进制协议，CREATE TABLE、DELETE、DO、INSERT、REPLACE、SELECT、UPDATE、 SHOW等大多数语句可以使用预处理
void prepare_insert(MYSQL *mysql)
{
	MYSQL_STMT 			*stmt;				//预处理句柄
	MYSQL_BIND 			bind[3];			//绑定变量
	my_ulonglong 		affectted_rows;
	int 					param_count;
	short 				small_data;
	int 					int_data;
	char 				str_data[STRING_SIZE];
	unsigned long 		str_length;
	my_bool 			is_null;
	
	if(mysql_query(mysql, DROP_SAMPLE_TABLE))	//删除表
	{
		fprintf(stderr, "DROP TABLE failed\n");
		fprintf(stderr, "%s\n", mysql_error(mysql));
		exit(0);
	}
	if(mysql_query(mysql, CREATE_SAMPLE_TABLE))	//创建表
	{
		fprintf(stderr, "CREATE TABLE failed\n");
		fprintf(stderr, "%s\n", mysql_error(mysql));
		exit(0);
	}
	
	stmt = mysql_stmt_init(mysql);
	if(!stmt)
	{
		fprintf(stderr, "mysql_stmt_init, out ofmemory\n");
		exit(0);
	}
	if(mysql_stmt_prepare(stmt, INSERT_SAMPLE, strlen(INSERT_SAMPLE)))	
	{										
		fprintf(stderr, "mysql_stmt_prepare, INSERT failed\n");
		fprintf(stderr, "%s\n", mysql_stmt_error(mysql));
		exit(0);
	}
	fprintf(stdout, "prepare INSERT successful\n");
	
	param_count = mysql_stmt_param_count(stmt);			//获得参数个数
	fprintf(stdout, "total parameters in INSERT: %d\n", param_count);
	if(param_count !=3)
	{
		fprintf(stderr, "invalid parameters count returned by MySql\n");
		exit(0);
	}
	
	memset(bind, 0, sizeof(bind));
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = (char*)&int_data;  //内存地址映射
	bind[0].is_null = 0
	bind[0].length = 0;
	
	bind[1].buffer_type = MYSQL_TYPE_STRING;
	bind[1].buffer = (char*)&str_data;  //内存地址映射
	bind[1].buffer_length = STRING_SIZE;
	bind[1].is_null = 0;
	bind[1].length = &str_length;
	
	bind[2].buffer_type = MYSQL_TYPE_SHORT;
	bind[2].buffer = (char*)&small_data;  //内存地址映射
	bind[2].is_null = &is_null;
	bind[2].length = 0;
	
	if(mysql_stmt_bind_param(stmt, bind))    //		绑定变量
	{
		fprintf(stderr, "mysql_stmt_bind_param failed\n");
		fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
		exit(0);
	}
	
	//第一波赋值
	int_data = 10;
	strncpy(str_data, "MySQL", STRING_SIZE);
	str_length = strlen(str_data);
	is_null = 1;			//标志插入的第三个字段是否为null
	
	if(mysql_stmt_execute(stmt))			//第一次执行预处理
	{
		printf(stderr, "mysql_stmt_execute，1 failed\n");
		fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
		exit(0);
	}
	
	affectted_rows = mysql_stmt_affectted_rows(stmt);		//预处理的影响条数
	if(affected_rows !=1)
	{
		fprintf(stderr, "invalid affectted rows by MySql\n");
		exit(0);
	}
	fprintf(stdout, "total affected rows(insert 1): %lu\n", (unsigned long)affected_rows);
	
	//第二波赋值
	int_data = 1000;
	strncpy(str_data, "The most popular Open Source database", STRING_SIZE);
	str_length = strlen(str_data);
	small_data = 1000;
	is_null = 0;			//标志插入的第三个字段是否为null
	
	if(mysql_stmt_execute(stmt))			//第二次执行预处理
	{
		fprintf(stderr, "mysql_stmt_execute，2 failed\n");
		fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
		exit(0);
	}
	
	affectted_rows = mysql_stmt_affectted_rows(stmt);		//预处理的影响条数
	if(affected_rows !=1)
	{
		fprintf(stderr, "invalid affectted rows by MySql\n");
		exit(0);
	}
	fprintf(stdout, "total affected rows(insert 2): %lu\n", (unsigned long)affected_rows);

	if(mysql_stmt_close(stmt))
	{
		fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
		exit(0);
	}
	return;
}

void showresult(MYSQL_RES *result)	
{
	unsigned int num_fields;
	unsigned int i;
	MYSQL_FIELD *fields;
	
	num_fields = mysql_num_fields(result);		//获得字段数
	fields = mysql_fetch_fields(result);		//获得子段数组
	for(i=0; i<num_fields; i++)
	{
		printf("Field %u is %s\n", i, fields[i].name);	//打印表头
	}
	printf("\n");
	printf("+-------+-------+--------+");
	
	MYSQL_ROW row;
	if(result != NULL)			//有结果集
	{
		while(row = mysql_fetch_rows(result))
		{
			for(i=0; i<num_fields; i++)
			{
				printf("%s\t", i, row[i]);	//打印表头
			}
			printf("\n");
		}
	}
}

int main()
{
	int ret = 0;
	MYSQL *mysql = mysql_init(NULL);			//初始化
	
	//连接句柄 最后三个参数分别是port端口 unix_socket套接字 client_flag标志位
	mysql = mysql_real_connect(mysql, _HOST_, _USER_, _PASSWD_, _DB_,0, NULL,0);
	if(mysql == NULL)
	{
		ret = mysql_errno(mysql);
		printf("func mysql_real_connect err: %d\n", ret);
		return ret;
	}
	printf("connect ok!\n");
	mysql_set_character_set(mysql, "utf8");    			//设置字符集
	
	//执行删除
	if(mysql_query(mysql, DROP_SAMPLE_TABLE))
	{
		fprintf(stderr, "DROP TABLE failed\n");
		fprintf(stderr, "%s\n", mysql_error(mysql));
		exit(0);
	}
	
	//创建表
	if(mysql_query(mysql, CREATE_SAMPLE_TABLE))	//创建表
	{
		fprintf(stderr, "CREATE TABLE failed\n");
		fprintf(stderr, "%s\n", mysql_error(mysql));
		exit(0);
	}
	
	//开启并设置事务为手动提交
	ret = mysql_OperationTran(MYSQL *mysql);
	if(ret !=0 )
	{
		printf("mysql_OperationTran err: %d\n", ret);
		return ret;
	}
	
	ret = mysql_query(mysql, sql01);		//向表中插入第一行数据‘AAA’
	if(ret != 0)
	{
		printf("mysql_query err:%d\n", ret);
		return ret;
	}
	ret = mysql_query(mysql, sql02);		//向表中插入第二行数据‘BBB’
	if(ret != 0)
	{
		printf("mysql_query err:%d\n", ret);
		return ret;
	}
	
	//手动提交事务
	ret = mysql_Commit(mysql);
	if(ret != 0)
	{
		printf("mysql_Commit err:%d\n", ret);
		return ret;
	}
#if 1
	ret = mysql_AUTOTran(mysql);			//测试手动
	if(ret != 0)
	{
		printf("mysql_AUTOTran err:%d\n", ret);
		return ret;
	}
#else
	ret = mysql_OperationTran(mysql);		//测试自动
	if(ret != 0)
	{
		printf("mysql_OperationTran err:%d\n", ret);
		return ret;
	}
#endif
	ret = mysql_query(mysql, sql03);		//向表中插入第三行数据‘BBB’
	if(ret != 0)
	{
		printf("mysql_query err:%d\n", ret);
		return ret;
	}
	ret = mysql_query(mysql, sql04);		//向表中插入第四行数据‘BBB’
	if(ret != 0)
	{
		printf("mysql_query err:%d\n", ret);
		return ret;
	}
	
	//能否回退取决于事务的属性
	ret = mysql_Rollback(mysql);			//回滚操作 
	if(ret != 0)
	{
		printf("mysql_Rollback err:%d\n", ret);
		return ret;
	}
	
	while(1)
	{
		printf("yekaiSQL");
		char rsql[4096];
		memset(rsql, 0x00, sizeof(rsql));
		fgets(rsql, sizeof(rsql), stdin);
		printf("rsql:%s\n", rsql);
		if(strncmp(rsql, "quit", 4) == 0 || strncmp(rsql, "QUIT", 4))
		{
			printf("bye bye\n");
			break;
		}
		
		//执行mysql
		if(mysql_query(mysql, "select * from emp"))			//失败返回非0
		{	
			printf("mysql query err:%s\n", rsql);
			mysql_close(mysql);
			exit(1);
		}
		
		//处理查询结果集
		MYSQL_RES *result = mysql_store_result(mysql);
		if(result != NULL)
		{
			showresult(result);				//打印结果集
			mysql_free_result(result);
		}
	}
	mysql_close(mysql);
	return 0;
}

