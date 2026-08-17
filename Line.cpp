#include<iostream>
#include<vector>
#include"Line.h"
using namespace std;
void Line::inserttext(int c, char ch)
{
	if (c <= text.size())
	{
		text.insert(text.begin() + c, ch);
	}
}
void Line::removetext(int c)
{

	if (c >= 0)
	{
		text.erase(text.begin() + c);

	}


}
int Line::linelength()const
{
	return text.size();
}
vector<char>Line::gettext()const
{
	return text;
}
void Line::copyline(vector<char>& n)
{
	n = text;
}
void Line::settext(const vector<char>& n)
{
	text = n;
}
char Line::getchar(int c)const
{
	return text[c];
}
void Line::deleteline()
{
	text.clear();
}
void Line::print()const
{
	for (auto c : text)
	{
		cout << c;
	}
}