#include"otherfunc.h"

void listFiles(const char * dir)
{
	char dirNew[200];
	strcpy(dirNew, dir);

	intptr_t handle; //intptr_t��Ϊ�˿�ƽ̨���䳤����������ƽ̨��λ����������ŵ�ַ�� 
	_finddata_t findData; // _finddata_t �������洢�ļ�������Ϣ�Ľṹ�塣

	handle = _findfirst(dirNew, &findData);  //��һ������Ϊ�ļ�����������"*.*"�����������ļ���Ҳ������"*.cpp"������.cpp�ļ����ڶ���������_finddata_t�ṹ��ָ�롣�����ҳɹ��������ļ��������ʧ�ܣ�����-1��
	if (handle == -1)        // ����Ƿ�ɹ�
		return;

	do
	{
		if (findData.attrib & _A_SUBDIR) //����ļ���Ŀ¼
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)  //����ļ����͵�ǰĿ¼�͸�Ŀ¼��ͬ�������������ֻ�����ǰĿ¼
				continue;
			
			std::cout << findData.name << "\t<Ŀ¼>\n";

			// ��Ŀ¼�������"\\"����������Ŀ¼��������һ������
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);

			listFiles(dirNew);
		}
		else
			std::cout << findData.name << "\t" << findData.size << " bytes.\n";
	} while (_findnext(handle, &findData) == 0); //_findnext��һ������Ϊ�ļ�������ڶ�������ͬ��Ϊ_finddata_t�ṹ��ָ�롣�����ҳɹ�������0��ʧ�ܷ��� - 1��

	_findclose(handle);    // �ر��������
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
	

	intptr_t handle; //intptr_t��Ϊ�˿�ƽ̨���䳤����������ƽ̨��λ����������ŵ�ַ�� 
	_finddata_t findData; // _finddata_t �������洢�ļ�������Ϣ�Ľṹ�塣

	handle = _findfirst(dirNew, &findData);  //��һ������Ϊ�ļ�����������"*.*"�����������ļ���Ҳ������"*.cpp"������.cpp�ļ����ڶ���������_finddata_t�ṹ��ָ�롣�����ҳɹ��������ļ��������ʧ�ܣ�����-1��
	if (handle == -1)        // ����Ƿ�ɹ�
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
		if (findData.attrib & _A_SUBDIR) //����ļ���Ŀ¼
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)  //����ļ����͵�ǰĿ¼�͸�Ŀ¼��ͬ�������������ֻ�����ǰĿ¼
				continue;

			std::cout << findData.name << "\t<Ŀ¼>\n";

			// ��Ŀ¼�������"\\"����������Ŀ¼��������һ������
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
	} while (_findnext(handle, &findData) == 0); //_findnext��һ������Ϊ�ļ�������ڶ�������ͬ��Ϊ_finddata_t�ṹ��ָ�롣�����ҳɹ�������0��ʧ�ܷ��� - 1��

	_findclose(handle);    // �ر��������
	return temp;
}