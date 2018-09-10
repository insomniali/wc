#pragma once
#include<stdio.h>
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

class WCclass
{
public:
	
	WCclass();
	~WCclass();
	void wordcount();
	void rowcount();
	void charcount();
	void cnwordcount();
	void digitcount();
	void fileoperate(string filename,string paramater);
	void emptyrowcount();
	void noterowcount();

private:

	int wordnums;
	int rownums;
	int charnums;
	int cnwordnums;
	int digitnums;
	string *filegroup;
	int emptyrow;
	int noterow;
};