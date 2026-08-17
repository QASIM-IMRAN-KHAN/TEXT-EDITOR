#pragma once
#include<iostream>
#include<vector>
#include"Line.h"
class Paragraph
{
	vector < Line > p;
	public:
	Paragraph();
	void addline();
	Line& getline(int i);
int parasize()const;
void removeline(int i);
};

