
#include "stdafx.h"
#include "apiutil.h"

void httplogout(string suffixUrl, string &result)
{
	vector<char> v;
	//通过配置读取URL
	//string URL = readURL();
	//string URL = "http://192.168.109.17:8080/m/api1/rinfo.php";
	//string NewURL = URL + "?certId=" + xh + "&random=123456&timeStamp=1469003420655&signature=" + result;
	string NewURL = "http://www.baidu.com";//"http://202.119.108.28/reader//hw_logout.php" + suffixUrl;
	string USER_AGENT = "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET4.0C; .NET4.0E; .NET CLR 2.0.50727)";
	HINTERNET hInternet, hInternetUrl;
	hInternet = InternetOpen(USER_AGENT.c_str(), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	if (!hInternet) {
		wprintf(L"InternetOpen error: %d\n", GetLastError());
	}
	hInternetUrl = InternetOpenUrl(hInternet, NewURL.c_str(), NULL, 0, INTERNET_FLAG_HYPERLINK, NULL);
	if (!hInternetUrl) {
		wprintf(L"InternetOpenUrl error: %d\n", GetLastError());
		InternetCloseHandle(hInternet);
	}
	DWORD dwMaxDataLength = 500;
	PBYTE pBuf = (PBYTE)malloc(dwMaxDataLength * sizeof(TCHAR));
	if (NULL == pBuf)
	{
		InternetCloseHandle(hInternetUrl);
		InternetCloseHandle(hInternet);
	}
	DWORD dwReadDataLength = NULL;
	BOOL bRet = TRUE;
	do
	{
		ZeroMemory(pBuf, dwMaxDataLength * sizeof(TCHAR));
		bRet = InternetReadFile(hInternetUrl, pBuf, dwMaxDataLength, &dwReadDataLength);
		for (DWORD dw = 0; dw < dwReadDataLength; dw++)
		{
			v.push_back(pBuf[dw]);
		}
	} while (NULL != dwReadDataLength);
	vector<char>::iterator i;
	string json = "";
	for (i = v.begin(); i != v.end(); i++) {
		json += *i;
	}
	result = json;
	size_t fore = json.find("debtFlag");
	size_t back = json.find("releSendAddr");
	int aas = back - fore - 14;
	string debit = "";
	try {
		debit = json.substr(fore + 11, aas);
	}
	catch (...) {
		MessageBox(NULL, _T("请检查配置文件"), _T("提示"), MB_OK);
		return;
	}
}
