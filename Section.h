#pragma once
#include<iostream>
#include<vector>
#include"Paragraph.h"
using namespace std;
class Section
{
	vector<Paragraph>sec;
public:
	Section();
	void addSection();
	void deleteParagraph(int i);
	Paragraph& getpara(int i);
	int sectionsize();

};
