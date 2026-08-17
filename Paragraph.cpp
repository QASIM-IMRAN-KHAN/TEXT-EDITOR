#include<iostream>
#include<vector>
#include"Paragraph.h"
Paragraph::Paragraph()
{
	p.push_back(Line());


}
void Paragraph::addline()
{
	p.push_back(Line());
}
Line& Paragraph::getline(int i)
{
	return p[i];
}
int Paragraph::parasize()const
{
	return p.size();
}
void Paragraph::removeline(int i)
{
	p.erase(p.begin() + i);

}