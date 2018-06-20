#pragma once
#include "stdafx.h"
#include <iostream>  
#include <string>  
#include <fstream> 
#include <Windows.h>
using namespace std;
bool readConfigFile(string cfgfilepath, string  key, string value);
void writeConfigFile(string cfgfilepath, string  key, string value);

