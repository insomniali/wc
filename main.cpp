#include"wcclass.h"
#include"otherfunc.h"

int main(int argc ,char* argv[]) {
	string filepath = "C:\\Users\\L\\Desktop\\Èí¼þ¹¤³Ì\\test";
	string filename;
	string temp;
	string operateword;
    string paramater=argv[1];
	WCclass test;
		
	for (int i = 2; i < argc + 1; i++) 
	{
			temp = filepath;
			filename = argv[i];
			filename = temp + "\\" + filename;
			test.fileoperate(filename, paramater);
	}
		
	return 0;

}