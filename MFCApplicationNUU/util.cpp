#include "stdafx.h"
#include "DataBase.h"
#include "util.h"

string DatetimeToString(tm *tm_)
{
	//tm *tm_ = localtime(&time);                // 将time_t格式转换为tm结构体
	int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
	year = tm_->tm_year + 1900;                // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
	month = tm_->tm_mon + 1;                   // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
	day = tm_->tm_mday;                        // 临时变量，日。
	hour = tm_->tm_hour;                       // 临时变量，时。
	minute = tm_->tm_min;                      // 临时变量，分。
	second = tm_->tm_sec;                      // 临时变量，秒。
	char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// 定义时间的各个char*变量。
	sprintf_s(yearStr, 5, "%d", year);              // 年。
	sprintf_s(monthStr, 3, "%d", month);            // 月。
	sprintf_s(dayStr, 3, "%d", day);                // 日。
	sprintf_s(hourStr, 3, "%d", hour);              // 时。
	sprintf_s(minuteStr, 3, "%d", minute);          // 分。
	if (monthStr[1] == '\0')                  // 如果月为一位，如5，则需要转换字符串为两位，如05。
	{
		monthStr[2] = '\0';
		monthStr[1] = monthStr[0];
		monthStr[0] = '0';
	}
	if (dayStr[1] == '\0')                  // 如果日为一位，如5，则需要转换字符串为两位，如05。
	{
		dayStr[2] = '\0';
		dayStr[1] = dayStr[0];
		dayStr[0] = '0';
	}
	if (hourStr[1] == '\0')                  // 如果时为一位，如5，则需要转换字符串为两位，如05。
	{
		hourStr[2] = '\0';
		hourStr[1] = hourStr[0];
		hourStr[0] = '0';
	}
	if (minuteStr[1] == '\0')                  // 如果分为一位，如5，则需要转换字符串为两位，如05。
	{
		minuteStr[2] = '\0';
		minuteStr[1] = minuteStr[0];
		minuteStr[0] = '0';
	}
	sprintf_s(secondStr, 3, "%d", second);          // 秒。
	if (secondStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
	{
		secondStr[2] = '\0';
		secondStr[1] = secondStr[0];
		secondStr[0] = '0';
	}
	char s[20];                                // 定义总日期时间char*变量。
	sprintf_s(s, 20, "%s-%s-%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// 将年月日时分秒合并。
	string str(s);                             // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
	return str;                                // 返回转换日期时间后的string变量。
}

string getServiceTime()
{
	return "";
}

void SendKey(string str)
{
	int m;//m为长度
	m = str.length(); //同上面size功能一样，都是求字符串长度的
					  //cout << "Read : "<< m << endl;
	string b;
	for (int i = 0; i<m; i++)
	{
		b = str.substr(i, 1); //切割字符串
		int key_value = b[0];
		//cout << "Read : "<< key_value << endl;
		keybd_event(key_value, MapVirtualKey(key_value, 0), 0, 0);
		Sleep(10);
		keybd_event(key_value, MapVirtualKey(key_value, 0), KEYEVENTF_KEYUP, 0);
		Sleep(10);
	}
	keybd_event(VK_RETURN, 0, 0, 0);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
}

void getFiles(string path, string exd, vector<string>& files)
{
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string pathName, exdName;

	if (0 != strcmp(exd.c_str(), "")) {
		exdName = "\\*." + exd;
	}
	else {
		exdName = "\\*";
	}

	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1) {
		do {
			//如果是文件夹中仍有文件夹,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR)) {
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(pathName.assign(path).append("\\").append(fileinfo.name), exd, files);
			}
			else {
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

string stomd5(string msg)
{
	MD5 md5(msg);
	string result1 = md5.md5();
	return result1;
}

string ltos(long l)
{
	ostringstream os;
	os << l;
	string result;
	istringstream is(os.str());
	is >> result;
	return result;
}

string __int64tos(__int64 l)
{
	ostringstream os;
	os << l;
	string result;
	istringstream is(os.str());
	is >> result;
	return result;
}

LPTSTR String2LPTSTR(string str)
{
	_bstr_t bstr(str.c_str());
	LPTSTR str2 = (LPTSTR)bstr;
	return str2;
}

long s2l(string str)
{
	long result;
	istringstream is(str);
	is >> result;
	return result;
}

double s2d(string str)
{
	double result;
	istringstream is(str);
	is >> result;
	return result;
}

__int64 HexToDec(char *s)
{
	char *p = s;

	//空串返回0。
	if (*p == '\0')
		return 0;

	//忽略开头的'0'字符
	while (*p == '0')
		p++;

	__int64 dec = 0;
	char c;

	//循环直到字符串结束。
	while (c = *p++)
	{
		//dec乘16
		dec <<= 4;

		//数字字符。
		if (c >= '0' && c <= '9')
		{
			dec += c - '0';
			continue;
		}

		//小写abcdef。
		if (c >= 'a' && c <= 'f')
		{
			dec += c - 'a' + 10;
			continue;
		}

		//大写ABCDEF。
		if (c >= 'A' && c <= 'F')
		{
			dec += c - 'A' + 10;
			continue;
		}

		//没有从任何一个if语句中结束，说明遇到了非法字符。
		return -1;
	}
	//正常结束循环，返回10进制整数值。
	return dec;
}

string Int_to_String(__int64 n)
{
	ostringstream stream;
	stream << n;  //n为int类型
	return stream.str();
}

void Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
	char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
}

string d2s(double d) {
	ostringstream os;
	if (os << d) return os.str();
	return "invalid conversion";
}