#include"wcclass.h"
#include"otherfunc.h"

WCclass::WCclass()
{
	wordnums = 0;
	rownums = 0;
	charnums = 0;
	cnwordnums = 0;
	digitnums = 0;
	filegroup = nullptr;
	emptyrow = 0;
	noterow = 0;
}

WCclass::~WCclass()
{
	free(filegroup);
}

void WCclass::wordcount() {
	wordnums++;
}

void WCclass::rowcount() {
	rownums++;
}

void WCclass::charcount() {
	charnums++;
}

void WCclass::cnwordcount() {
	cnwordnums++;
}

void WCclass::digitcount() {
	digitnums++;
}

void WCclass::emptyrowcount() {
	emptyrow++;
}

void WCclass::noterowcount() {
	noterow++;
}

void WCclass::fileoperate(string filename, string paramater) {
	ifstream fin(filename.c_str());
	//std::cout << filename << endl;
	char ch;
	string str;
	char **strs;
	string paramater1 = "-c";
	string paramater2 = "-w";
	string paramater3 = "-l";
	string paramater4 = "-d";
	string paramater5 = "-s";
	string paramater6 = "-a";
	strs = (char**)malloc(sizeof(char) * 256);
	
	while (getline(fin, str))
	{
		int strcount = 0;
		rowcount();
		if (str.length() == 0)emptyrowcount();

		strs[strcount] = strtok((char*)str.c_str(), " ");

		while (strs[strcount] != NULL)
		{
			strcount++;
			strs[strcount] = strtok(NULL, " ");
		}
		for (int i = 0; i < strcount; i++) {
			//printf("%s\n", strs[i]);
			string temp = strs[i];
			int continuectrl = 0;//控制单词连续
			int dqmoff = 0;//双引号是否闭合
			int flag = 0;////是否相邻
			for (int j = 0; j < temp.length(); j++) {
				ch = temp[j];
				//printf("%c", ch);
				if ((ch >= 33 && ch <= 47) || (ch >= 58 && ch <= 64) || (ch >= 91 && ch <= 96) || (ch >= 123 && ch <= 126))
				{
					charcount();
					continuectrl = 0;
					if (ch == 34) {
						if (dqmoff == 1)dqmoff = 0;
						dqmoff = 1;
					}
					if (ch == 47) {
						if (dqmoff == 0)
						{
							if (flag == 1)noterowcount();
							flag = 1;
						}
					}
				}
				else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
				{
					if (continuectrl == 1)continue;
					continuectrl = 1;
					wordcount();
				}
				else if (ch >= '0'&&ch <= '9')
				{
					digitcount();
				}
				else
				{
					//printf("%c\n", ch);
					cnwordcount();
				}
			}
		}
	}
	if (paramater == paramater1)std::cout << "字符数为：" << charnums + cnwordnums / 2 << endl;
	else if (paramater == paramater2)std::cout << "单词数为：" << wordnums << endl;
	else if (paramater == paramater3)std::cout << "行数为：" << rownums << endl;
	else if (paramater == paramater4)listFiles(filename.c_str());
	else if (paramater == paramater5) 
	{
		filegroup = (string*)malloc(sizeof(string) * 256);
		filegroup=listFiles(filename.c_str(), filegroup);
		for (int i = 0; filegroup[i].length() != 0; i++) {
			std::cout << filegroup[i] << endl;
			fileoperate(filegroup[i], paramater1);
			fileoperate(filegroup[i], paramater2);
			fileoperate(filegroup[i], paramater3);
		}
		std::cout << endl;
		std::cout << "总字符数为：" << charnums + cnwordnums / 2 << endl;
		std::cout << "总单词数为：" << wordnums << endl;
		std::cout << "总行数为：" << rownums << endl;
	}
	else if (paramater == paramater6) 
	{
		std::cout << "空行数为：" << emptyrow << endl;
		std::cout << "注释行数为：" << noterow << endl;
		std::cout << "代码行数为：" << rownums-emptyrow-noterow << endl;
	}
    
	fin.clear();
	fin.close();
	free(strs);
}