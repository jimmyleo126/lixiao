#include "stdafx.h"
#include "DataBase.h"
#include "util.h"

string DatetimeToString(tm *tm_)
{
	//tm *tm_ = localtime(&time);                // ��time_t��ʽת��Ϊtm�ṹ��
	int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
	year = tm_->tm_year + 1900;                // ��ʱ�������꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬������ʱ����intΪtm_year����1900��
	month = tm_->tm_mon + 1;                   // ��ʱ�������£�����tm�ṹ����·ݴ洢��ΧΪ0-11��������ʱ����intΪtm_mon����1��
	day = tm_->tm_mday;                        // ��ʱ�������ա�
	hour = tm_->tm_hour;                       // ��ʱ������ʱ��
	minute = tm_->tm_min;                      // ��ʱ�������֡�
	second = tm_->tm_sec;                      // ��ʱ�������롣
	char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// ����ʱ��ĸ���char*������
	sprintf_s(yearStr, 5, "%d", year);              // �ꡣ
	sprintf_s(monthStr, 3, "%d", month);            // �¡�
	sprintf_s(dayStr, 3, "%d", day);                // �ա�
	sprintf_s(hourStr, 3, "%d", hour);              // ʱ��
	sprintf_s(minuteStr, 3, "%d", minute);          // �֡�
	if (monthStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		monthStr[2] = '\0';
		monthStr[1] = monthStr[0];
		monthStr[0] = '0';
	}
	if (dayStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		dayStr[2] = '\0';
		dayStr[1] = dayStr[0];
		dayStr[0] = '0';
	}
	if (hourStr[1] == '\0')                  // ���ʱΪһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		hourStr[2] = '\0';
		hourStr[1] = hourStr[0];
		hourStr[0] = '0';
	}
	if (minuteStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		minuteStr[2] = '\0';
		minuteStr[1] = minuteStr[0];
		minuteStr[0] = '0';
	}
	sprintf_s(secondStr, 3, "%d", second);          // �롣
	if (secondStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		secondStr[2] = '\0';
		secondStr[1] = secondStr[0];
		secondStr[0] = '0';
	}
	char s[20];                                // ����������ʱ��char*������
	sprintf_s(s, 20, "%s-%s-%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// ��������ʱ����ϲ���
	string str(s);                             // ����string����������������ʱ��char*������Ϊ���캯���Ĳ������롣
	return str;                                // ����ת������ʱ����string������
}

string getServiceTime()
{
	return "";
}

void SendKey(string str)
{
	int m;//mΪ����
	m = str.length(); //ͬ����size����һ�����������ַ������ȵ�
					  //cout << "Read : "<< m << endl;
	string b;
	for (int i = 0; i<m; i++)
	{
		b = str.substr(i, 1); //�и��ַ���
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
	//�ļ����
	long   hFile = 0;
	//�ļ���Ϣ
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
			//������ļ����������ļ���,����֮
			//�������,�����б�
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

	//�մ�����0��
	if (*p == '\0')
		return 0;

	//���Կ�ͷ��'0'�ַ�
	while (*p == '0')
		p++;

	__int64 dec = 0;
	char c;

	//ѭ��ֱ���ַ���������
	while (c = *p++)
	{
		//dec��16
		dec <<= 4;

		//�����ַ���
		if (c >= '0' && c <= '9')
		{
			dec += c - '0';
			continue;
		}

		//Сдabcdef��
		if (c >= 'a' && c <= 'f')
		{
			dec += c - 'a' + 10;
			continue;
		}

		//��дABCDEF��
		if (c >= 'A' && c <= 'F')
		{
			dec += c - 'A' + 10;
			continue;
		}

		//û�д��κ�һ��if����н�����˵�������˷Ƿ��ַ���
		return -1;
	}
	//��������ѭ��������10��������ֵ��
	return dec;
}

string Int_to_String(__int64 n)
{
	ostringstream stream;
	stream << n;  //nΪint����
	return stream.str();
}

void Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte������
	char *psText;  // psTextΪchar*����ʱ���飬��Ϊ��ֵ��std::string���м����
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte���ٴ�����
	szDst = psText;// std::string��ֵ
	delete[]psText;// psText�����
}

string d2s(double d) {
	ostringstream os;
	if (os << d) return os.str();
	return "invalid conversion";
}