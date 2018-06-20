#pragma once
#include "util.h"
#include "changeExport.h"
#import "msado15.dll"  no_namespace rename("EOF", "adoEOF")


void uploadcustominfo(tagUpLoadInfo uploadrecord);
void InsertLogoutRecord(string certid, string &re);
string getStuName(string xh);
BOOL DataSql(string xh, long cardNo);