
#ifndef LIBRARY_H
#define LIBRARY_H
	#include "util.h"
	#include "soapLibServicePortBindingProxy.h"
	ns1__getAccountsResponse getAccount(string certid);
	void getDebts(string certid, string &re, float &amount);
	BOOL exceedFines(string certid, float &sumamount);
	string getCircss(string certid);
	int singlexceedfinel(string certid, wchar_t *prono, wchar_t *lenddate, float fineamount, int cc);
#endif // !LIBRARY_H
