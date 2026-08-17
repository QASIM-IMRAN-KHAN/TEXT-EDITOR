#include<iostream>
#include<vector>
#include"Chapters.h"
Chapter::Chapter()
{
	chap.push_back(Section());
}
void Chapter::addnewChapter()
{
	chap.push_back(Section());
}
void Chapter::deleteChapter(int i)
{
	chap.erase(chap.begin() + i);
}
Section& Chapter::getsection(int i)
{
	return chap[i];
}
int Chapter::chaptersize()
{
	return chap.size();
}
