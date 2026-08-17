#include<iostream>
#include<vector>
#include"Section.h"
Section::Section()
{
	sec.push_back(Paragraph());
}
void Section::addSection()
{
	sec.push_back(Paragraph());
}
void Section::deleteParagraph(int i)
{
	sec.erase(sec.begin() + i);
}

Paragraph& Section::getpara(int i)
{
	return sec[i];
}
int Section::sectionsize()
{
	return sec.size();
}
