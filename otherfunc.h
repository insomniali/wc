#pragma once
#include <iostream>
#include <cstring>        // for strcpy(), strcat()
#include <io.h>
#include<string>

void listFiles(const char * dir);

std::string* listFiles(const char * dir,std::string *str);