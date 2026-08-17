#pragma once
#include<iostream>
#include<vector>
using namespace std;
class Line {
	vector<char>text;
public:
	
	void inserttext(int c, char ch);
	void removetext(int c);
	int linelength()const;
vector<char>gettext()const;
void copyline(vector<char>& n);
void settext(const vector<char>& n);
char getchar(int c)const;
void deleteline();
void print()const;
};
