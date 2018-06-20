#pragma once


#include "changeExport.h"
#include "util.h"
#include "DataBase.h"
#include "library.h"


void Initnuu();
void Endnuu();
void ThreadFunc(int num);
int ThreadopenCom(int num);
void OpenOrClose();
void ControlReadThread(int num);
void NoDebt();
BOOL hasDebt(string xh, string re, float amount);
void LogOutSchool(string xh);
string setLogOutUrl(string strcode, string certid);
void getCircs(string certid);