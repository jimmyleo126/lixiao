#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <io.h>
#include <sstream>
#include "md5.h"
using namespace std;
std::string DatetimeToString(tm *tm_);
void SendKey(string str);
void getFiles(string path, string exd, vector<string>& files);
string ltos(long l);
string __int64tos(__int64 l);
LPTSTR String2LPTSTR(string str);
long s2l(string str);
double s2d(string str);
__int64 HexToDec(char *s);
string Int_to_String(__int64 n);
void Wchar_tToString(std::string& szDst, wchar_t *wchar);
string d2s(double d);
string stomd5(string msg);