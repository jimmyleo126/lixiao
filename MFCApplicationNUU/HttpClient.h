#pragma once

#include <afxinet.h>
#include <string>

#define IE_AGENT _T("Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)")

//操作成功
#define NUU_HTTP_SUCCESS 0;
//操作失败
#define NUU_HTTP_FAILURE 1;
//操作差超时
#define NUU_HTTP_TIMEOUT 2;

class CHttpClient
{
public:
	CHttpClient(LPCTSTR strAgent = IE_AGENT);
	virtual ~CHttpClient(void);

	int HttpGet(LPCTSTR strUrl, LPCTSTR strPostData, std::string &strResponse);
	int HttpPost(LPCTSTR strUrl, LPCTSTR strPostData, std::string &strResponse);

private:
	CInternetSession *m_pSession;
	CHttpConnection *m_pConnection;
	CHttpFile *m_pFile;

	int ExecuteRequest(LPCTSTR strMethod, LPCTSTR strUrl, LPCTSTR strPostData, std::string &strResponse);
	void Clear();


};