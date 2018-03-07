#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

int main(void)
{
	FILE *fp = fopen("express_information.json", "rb");
	fseek(fp, 0x0, SEEK_END);
	int size = ftell(fp) + 1;
	char *buf = (char*)malloc(sizeof(char)*size);
	memset(buf, 0x0, sizeof(char)*size);
	
	//全部读到buf中
	rewind(fp);								//文件内部位置重新指向一个流的开头
	fread(buf, sizeof(char), size-1, fp);
	
	cJSON *json = cJSON_Parse(buf);
	
	//获取快递编号
	cJSON *node = NULL;
	if(cJSON_HasObjectItem(json, "nu") == 0)
	{
		printf("not found nu data\n");
		goto done;
	}
	node = cJSON_GetObjectItem(json, "data");
	if(node->type != cJSON_Array)
	{
		printf("data's type is not string\n");
		goto done;
	}
	
	int i;
	cJSON *dnode = NULL;
	int length = cJSON_GetArraySize(node);
	for(i = 0; i < length; ++i)
	{
		dnode = cJSON_GetArrayItem(node, i);
		if(dnode->type != cJSON_Object)
		{
			printf("snode's type is not obj\n");
			continue;
		}
		printf("-------\ntime:%s\n", cJSON_GetObjectItem(dnode, "time")->valuestring);
		printf("contex:%s\n", cJSON_GetObjectItem(dnode, "contex")->valuestring);
		printf("fime:%s\n", cJSON_GetObjectItem(dnode, "ftime")->valuestring);
	}
	
done:	
	free(buf);
	fclose(fp);
	cJSON_Delete(json);
	return 0;
}

