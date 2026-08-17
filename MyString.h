#pragma once
class Mystring
{
	int size;
	char* Cs;
	int strlength(const char* A);
	void stringcopy(char* A, const char* B);
public:
	Mystring();
	Mystring(char ch);
	Mystring(const char* p);
	Mystring(int s, char ch);
	Mystring(int num);
	bool isEqual(const Mystring& M);
	int Length(const Mystring A);
	char CharacterAt(int i);

};
