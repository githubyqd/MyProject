#include <stdio.h>
#include "mxml.h"

int main(void)
{
	FILE *fp = fopen("xxx.xml", "r");
	
	mxml_node_t *xml = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
	
	mxml_node_t *title = mxmlFindElement(xml, xml, "title", NULL, NULL, MXML_DESCEND);
	
	printf("title text:%s\n", mxmlGetText(title, NULL));
	
	mxml_node_t *p = mxmlFindElement(xml, xml, "p", "style", NULL, MXML_DESCEND);
	if(p == NULL)
	{
		printf("p not found\n");
	}
	else
	{
		printf("p style:%s\n", mxmlElementGetAttr(p, "style"));
	}
	printf("p text:%s\n", mxmlGetText(p, NULL));
	
	mxmlDelete(xml);
	fclose(fp);
	return 0;
}

