#pragma once
#include<iostream>
#include<vector>
#include"Section.h"
class Chapter
{
	vector<Section>chap;
public:
	Chapter();
	void addnewChapter();
	void deleteChapter(int i);
	Section& getsection(int i);
	int chaptersize();

};
