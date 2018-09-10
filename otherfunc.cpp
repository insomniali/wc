#include"otherfunc.h"

void listFiles(const char * dir)
{
	char dirNew[200];
	strcpy(dirNew, dir);

	intptr_t handle; //intptr_t是为了跨平台，其长度总是所在平台的位数，用来存放地址。 
	_finddata_t findData; // _finddata_t 是用来存储文件各种信息的结构体。

	handle = _findfirst(dirNew, &findData);  //第一个参数为文件名，可以用"*.*"来查找所有文件，也可以用"*.cpp"来查找.cpp文件。第二个参数是_finddata_t结构体指针。若查找成功，返回文件句柄，若失败，返回-1。
	if (handle == -1)        // 检查是否成功
		return;

	do
	{
		if (findData.attrib & _A_SUBDIR) //如果文件是目录
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)  //如果文件名和当前目录和父目录相同则跳过，否则会只输出当前目录
				continue;
			
			std::cout << findData.name << "\t<目录>\n";

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);

			listFiles(dirNew);
		}
		else
			std::cout << findData.name << "\t" << findData.size << " bytes.\n";
	} while (_findnext(handle, &findData) == 0); //_findnext第一个参数为文件句柄，第二个参数同样为_finddata_t结构体指针。若查找成功，返回0，失败返回 - 1。

	_findclose(handle);    // 关闭搜索句柄
}

std::string* listFiles(const char * dir,std::string* str)
{
	char dirNew[200];
	strcpy(dirNew, dir);
	int filenum = 0;
	std::string* temp = str;
	int partcount = 0;
	std::string filepath;
	char**filepathpart;
	filepathpart = (char**)malloc(sizeof(char) * 256);
	std::string filepathtemp = dir;
	

	intptr_t handle; //intptr_t是为了跨平台，其长度总是所在平台的位数，用来存放地址。 
	_finddata_t findData; // _finddata_t 是用来存储文件各种信息的结构体。

	handle = _findfirst(dirNew, &findData);  //第一个参数为文件名，可以用"*.*"来查找所有文件，也可以用"*.cpp"来查找.cpp文件。第二个参数是_finddata_t结构体指针。若查找成功，返回文件句柄，若失败，返回-1。
	if (handle == -1)        // 检查是否成功
		return nullptr;
	
	filepathpart[partcount] = strtok((char*)filepathtemp.c_str(), "\\");

	while (filepathpart[partcount] != NULL)
	{
		partcount++;
		filepathpart[partcount] = strtok(NULL, "\\");
	}

	for (int i = 0; i < partcount - 1; i++) {
		filepath += filepathpart[i] ;
		filepath += "\\";
	}
	
	do
	{
		if (findData.attrib & _A_SUBDIR) //如果文件是目录
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)  //如果文件名和当前目录和父目录相同则跳过，否则会只输出当前目录
				continue;

			std::cout << findData.name << "\t<目录>\n";

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);

			listFiles(dirNew);

		}
		else {
			temp[filenum] = filepath;
			temp[filenum] += findData.name;
			filenum++;
		    std::cout << findData.name << "\t" << findData.size << " bytes.\n";
	    }
	} while (_findnext(handle, &findData) == 0); //_findnext第一个参数为文件句柄，第二个参数同样为_finddata_t结构体指针。若查找成功，返回0，失败返回 - 1。

	_findclose(handle);    // 关闭搜索句柄
	return temp;
}