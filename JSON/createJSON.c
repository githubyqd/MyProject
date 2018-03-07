#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

int main(void)
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "name", cJSON_CreateString("王大锤"));
	cJSON_AddItemToObject(json, "age", cJSON_CreateNumber(29));
	cJSON_AddNumberToObject(json, "score", 59);
	
	cJSON *array = NULL;
	cJSON *obj = NULL;
	cJSON_AddItemToObject(json, "love", array = cJSON_CreateArray());
	cJSON_AddItemToArray(array, cJSON_CreateString("LOL"));
	cJSON_AddItemToArray(array, cJSON_CreateString("Go Shopping"));
	cJSON_AddItemToArray(array, obj = cJSON_CreateObject());
	cJSON_AddItemToObject(obj, "address", cJSON_CreateString("beijing"));
	
	//将json结构格式化到缓冲区
	char *buf = cJSON_Print(json);
	
	//打开文件写入
	FILE *fp = fopen("create.json", "w");
	fwrite(buf, 1, strlen(buf), fp);
	
	free(buf);
	fclose(fp);
	cJSON_Delete(json);
	return 0;
}

