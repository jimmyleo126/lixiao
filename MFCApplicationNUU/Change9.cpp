//引用第三方接口的实现文件

#include "StdAfx.h"
#include "changeExport.h"



//DLL的句柄
static HINSTANCE ghDll = 0;

//各方法原型声明
typedef void (WINAPI *pVV)(void);
typedef long (WINAPI *pLV)(void);
typedef long (WINAPI *pLVP)(void *);
typedef long (WINAPI *pLLDP)(long, DOWNINFO *);
typedef long (WINAPI *pLL2DP)(long, long, DOWNINFO *);
typedef long (WINAPI *pLUPCP)(UPLOADINFO *, char *);
typedef long (WINAPI *pLL3CPL64PLP2)(long, long, long, char *, __int64 *, long *, long *);

//各方法引用变量定义
static pVV pClose = 0, pDisConn = 0;
static pLV pOpen = 0, pBC = 0, pDC = 0, pCC = 0;
static pLVP pFind = 0, pRead = 0, pConn = 0, pBL = 0, pDL = 0, pCL = 0;
static pLLDP pDci = 0;
static pLL2DP pDciN = 0;
static pLUPCP pUpload = 0;
static pLL3CPL64PLP2 pWrite = 0;


//初始化加载DLL
bool initDLL(void)
{
	if (ghDll == NULL || ghDll == INVALID_HANDLE_VALUE)
	{
		//ghDll = ::ghDll = LoadLibraryEx(_T("Change.dll"), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		ghDll = ::ghDll = LoadLibrary(_T("Change.dll"));
		if (ghDll == NULL || ghDll == INVALID_HANDLE_VALUE)
			return false;
	}

	if (!pClose)
	{
		pClose = (pVV)(::GetProcAddress(ghDll, "CloseCom"));
		if (!pClose)
			return false;
	}
	if (!pDisConn)
	{
		pDisConn = (pVV)(::GetProcAddress(ghDll, "CapDBDiscon"));
		if (!pClose)
			return false;
	}
	if (!pOpen)
	{
		pOpen = (pLV)(::GetProcAddress(ghDll, "OpenCom"));
		if (!pOpen)
			return false;
	}
	if (!pBC)
	{
		pBC = (pLV)(::GetProcAddress(ghDll, "CapDownBlacklistCount"));
		if (!pBC)
			return false;
	}
	if (!pDC)
	{
		pDC = (pLV)(::GetProcAddress(ghDll, "CapGetDepCount"));
		if (!pDC)
			return false;
	}
	if (!pCC)
	{
		pCC = (pLV)(::GetProcAddress(ghDll, "CapGetCustomerCount"));
		if (!pCC)
			return false;
	}
	if (!pFind)
	{
		pFind = (pLVP)(::GetProcAddress(ghDll, "CapNBQueryCard"));
		if (!pFind)
			return false;
	}
	if (!pRead)
	{
		pRead = (pLVP)(::GetProcAddress(ghDll, "CapGetNBCardInfo"));
		if (!pRead)
			return false;
	}
	if (!pConn)
	{
		pConn = (pLVP)(::GetProcAddress(ghDll, "CapDBConnect"));
		if (!pConn)
			return false;
	}
	if (!pBL)
	{
		pBL = (pLVP)(::GetProcAddress(ghDll, "CapDownBlacklist"));
		if (!pBL)
			return false;
	}
	if (!pDL)
	{
		pDL = (pLVP)(::GetProcAddress(ghDll, "CapGetDepList"));
		if (!pDL)
			return false;
	}
	if (!pCL)
	{
		pCL = (pLVP)(::GetProcAddress(ghDll, "CapGetCustomerList"));
		if (!pCL)
			return false;
	}
	if (!pDci)
	{
		pDci = (pLLDP)(::GetProcAddress(ghDll, "CapDownCustomerInfo"));
		if (!pDci)
			return false;
	}
	if (!pDciN)
	{
		pDciN = (pLL2DP)(::GetProcAddress(ghDll, "CapGetCustomerByNum"));
		if (!pDciN)
			return false;
	}
	if (!pUpload)
	{
		pUpload = (pLUPCP)(::GetProcAddress(ghDll, "CapUpload"));
		if (!pUpload)
			return false;
	}
	if (!pWrite)
	{
		pWrite = (pLL3CPL64PLP2)(::GetProcAddress(ghDll, "CapSetNBCardInfo"));
		if (!pWrite)
			return false;
	}

	return true;
}

//卸载DLL
void UinitDLL(void)
{
	pClose = pDisConn = 0;
	pOpen = pBC = pDC = pCC = 0;
	pFind = pRead = pConn = pBL = pDL = pCL = 0;
	pDci = 0;
	pDciN = 0;
	pUpload = 0;
	pWrite = 0;

	if (ghDll != NULL && ghDll != INVALID_HANDLE_VALUE)
	{
		::FreeLibrary(ghDll);
		ghDll = 0;
	}
}


long OpenCom()
{
	return (*pOpen)();
}

void CloseCom()
{
	(*pClose)();
}

long CapNBQueryCard(long *uid)
{
	return (*pFind)(uid);
}

long CapGetNBCardInfo(CUSTOMERINFO *fvst)
{
	return (*pRead)(fvst);
}

long CapSetNBCardInfo(long CustomerID, long opFare, long objNo, LPSTR jyDT, __int64 *psamID, long *psamJyNo, long *tac)
{
	return (*pWrite)(CustomerID, opFare, objNo, jyDT, psamID, psamJyNo, tac);
}


long CapDBConnect(LPCTSTR lpSID)
{
	return (*pConn)((char *)lpSID);
}

void CapDBDiscon()
{
	(*pDisConn)();
}

long CapDownBlacklistCount()
{
	return (*pBC)();
}

long CapDownBlacklist(long *pList)
{
	return (*pBL)(pList);
}

long CapGetDepCount()
{
	return (*pDC)();
}

long CapGetDepList(DOWNDEPINFO *pINFO)
{
	return (*pDL)(pINFO);
}

long CapDownCustomerInfo(long CustomerID, DOWNINFO *downInfo)
{
	return (*pDci)(CustomerID, downInfo);
}

long CapGetCustomerByNum(long CustomerID, long num, DOWNINFO *pINFO)
{
	return (*pDciN)(CustomerID, num, pINFO);
}

long CapGetCustomerCount()
{
	return (*pCC)();
}

long CapGetCustomerList(DOWNINFO *pINFO)
{
	return (*pCL)(pINFO);
}

long CapUpload(UPLOADINFO *uploadInfo, LPSTR msg)
{
	return (*pUpload)(uploadInfo, msg);
}
