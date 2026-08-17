#pragma once
#include<iostream>
#include<vector>
#include"Chapters.h"
class Document {

	vector<Chapter>doc;
public:
	Document();
	void addnewDocument();
	void removeDocument(int i);
	Chapter& getchapter(int i);
	int documentsize();




};