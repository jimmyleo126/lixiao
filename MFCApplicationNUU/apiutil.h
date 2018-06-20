#pragma once
#include "apiutil.h"
#include <Wininet.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include "util.h"
#pragma comment(lib,"Wininet.lib")

void httplogout(string xh, string &result);
