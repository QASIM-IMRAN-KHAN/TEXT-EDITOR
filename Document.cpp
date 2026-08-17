#include<iostream>
#include<vector>
#include"Document.h"
Document::Document()
{
	doc.push_back(Chapter());
}
void Document::addnewDocument()
{
	doc.push_back(Chapter());
}
void Document::removeDocument(int i)
{
	doc.erase(doc.begin() + i);
}
Chapter& Document::getchapter(int i)
{
	return doc[i];
}
int Document::documentsize()
{
	return doc.size();
}
