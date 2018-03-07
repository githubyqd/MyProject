#include <stdio.h>
#include "mxml.h"

int main(void)
{
	FILE *fp = fopen("xxx.xml", "w");
	
	mxml_node_t *xml = mxmlNewXML("1.0");
	
	mxml_node_t *note = mxmlNewElement(xml, "note");
	
	mxml_node_t *to = mxmlNewElement(note, "to");
	mxmlNewText(to, 0, "乐");
	mxmlElementSetAttr(to, "time", "0214");
	
	mxml_node_t *from = mxmlNewElement(note, "from");
	mxmlNewText(from, 0, "Jani");
	
	mxml_node_t *heading = mxmlNewElement(note, "heading");
	mxmlNewText(heading, 0, "Reminder");
	
	mxml_node_t *body = mxmlNewElement(note, "body");
	mxmlNewText(body, 0, "Don't forget me this weekend!");
	
	mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);
	
	fclose(fp);
	return 0;
}

