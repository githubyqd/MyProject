#include <stdio.h>
#include "mxml.h"

int main(void)
{
	FILE *fp = fopen("QQPicConfig.xml", "w");
	
	mxml_node_t *xml = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
	
	mxml_node_t *pic = NULL;
	mxml_node_t *resrurl = NULL;
	mxml_node_t *thumbnail = NULL;
	
	pic = mxmlFindElement(xml, xml, "title", NULL, NULL, MXML_DESCEND);
	while(pic)
	{
		resrurl = mxmlFindElement(pic, xml, "resrurl", "md5", NULL, MXML_DESCEND);
		if(resrurl == NULL)
		{
			printf("resrurl == NULL");
		}
		else
		{
			printf("md5:%s\n", mxmlElementGetAttr(resrurl, "md5"));
			printf("text:%s\n", mxmlGetText(resrurl, NULL));
		}
		thumbnail = mxmlFindElement(pic, xml, "thumbnail", "md5", NULL, MXML_DESCEND);
		if(thumbnail == NULL)
		{
			printf("thumbnail == NULL");
		}
		else
		{
			printf("md5:%s\n", mxmlElementGetAttr(thumbnail, "md5"));
			printf("text:%s\n", mxmlGetText(thumbnail, NULL));
		}
		pic = mxmlFindElement(pic, xml, "pic", NULL, NULL, MXML_DESCEND);
	}
	
	mxmlDelete(xml);
	fclose(fp);
	return 0;
}

