
#include "stdafx.h"
#include "library.h"

#include "FileLogger.h"
#include "LogManager.h"

ns1__getAccountsResponse getAccount(string certid)
{
	LibServicePortBindingProxy proxy;
	time_t nowtimelibrary = time(0);
	struct tm timeinfolibrary;
	localtime_s(&timeinfolibrary, &nowtimelibrary);
	string nowdatelibrary = DatetimeToString(&timeinfolibrary);
	string newnowdatelibrary = nowdatelibrary.substr(0, nowdatelibrary.length() - 3);
	string message = "libsysNJSFDX" + newnowdatelibrary;

	//进行MD5加密，生成签证
	string result1 = stomd5(message);
	ns1__getAccounts *account = new ns1__getAccounts();
	// accountp = new ns1__getAccountsResponse();
	long resultacconts;
	account->arg0 = new string("libsys");
	account->arg1 = new string(newnowdatelibrary);
	account->arg2 = new string(result1);
	account->arg3 = new string(certid);
	ns1__getAccountsResponse accountp;// = new ns1__getAccountsResponse();
	resultacconts = proxy.getAccounts(account, &accountp);
	delete account->arg0;
	delete account->arg1;
	delete account->arg2;
	delete account->arg3;
	delete account;
	return accountp;
}


void getDebts(string certid, string &re, float &amount)
{
	LibServicePortBindingProxy proxy;
	time_t nowtimelibrary = time(0);
	struct tm timeinfolibrary;
	localtime_s(&timeinfolibrary, &nowtimelibrary);
	string nowdatelibrary = DatetimeToString(&timeinfolibrary);
	string newnowdatelibrary = nowdatelibrary.substr(0, nowdatelibrary.length() - 3);
	string message = "libsysNJSFDX" + newnowdatelibrary;
	string result1 = stomd5(message);
	ns1__getDebts *debts = new ns1__getDebts();
	//ns1__getDebtsResponse *debtp = new ns1__getDebtsResponse();
	long resultdebts;
	debts->arg0 = new string("libsys");
	debts->arg1 = new string(newnowdatelibrary);
	debts->arg2 = new string(result1);
	debts->arg3 = new string(certid);

	ns1__getDebtsResponse *debtp = new ns1__getDebtsResponse();
	resultdebts = proxy.getDebts(debts, debtp);
	string msg = "";
	int count = debtp->return_.size();
	for (int i = 0; i < count; i++) { //循环将扣款金额相加

		ns1__getBook *getbook = new ns1__getBook();
		getbook->arg0 = new string("libsys");
		getbook->arg1 = new string(newnowdatelibrary);
		getbook->arg2 = new string(result1);
		getbook->arg3 = 1;
		string propNotemp; 
		Wchar_tToString(propNotemp, debtp->return_[i]->propNo);
		getbook->arg4 = new string(propNotemp);
		ns1__getBookResponse *getbookp = new ns1__getBookResponse();
		proxy.getBook(getbook, getbookp);
		string temp;
		Wchar_tToString(temp, getbookp->return_->title);
		msg = msg + std::to_string(i + 1) + ". 书名：" + temp + "\t";
		char buf[10];
		sprintf_s(buf, 10, "%.2f", debtp->return_[i]->dueFineAmount);
		msg = msg + "欠款：" + buf + "元\t";
		Wchar_tToString(temp, debtp->return_[i]->lendDate);
		msg = msg + "借书日期：" + temp.substr(0, 10) + "\t";
		Wchar_tToString(temp, debtp->return_[i]->retDate);
		msg = msg + "应还日期：" + temp.substr(0, 10) + "\r\n";
		float duefineamount = debtp->return_[i]->dueFineAmount;
		amount = amount + duefineamount;
	}
	delete debts->arg0;
	delete debts->arg1;
	delete debts->arg2;
	delete debts->arg3;
	delete debts;
	re = msg;
	delete debtp;
}

void getAllDebtAmount()
{

}

BOOL exceedFines(string certid, float &sumamount) {
	LibServicePortBindingProxy proxy;
	ns1__getDebtsResponse *debtp = new ns1__getDebtsResponse();
	time_t nowtimelibrary = time(0);
	struct tm timeinfolibrary;
	localtime_s(&timeinfolibrary, &nowtimelibrary);
	string nowdatelibrary = DatetimeToString(&timeinfolibrary);
	string newnowdatelibrary = nowdatelibrary.substr(0, nowdatelibrary.length() - 3);
	string message = "libsysNJSFDX" + newnowdatelibrary;
	string result1 = stomd5(message);
	ns1__getDebts *debts = new ns1__getDebts();
	//ns1__getDebtsResponse *debtp = new ns1__getDebtsResponse();
	long resultdebts;
	debts->arg0 = new string("libsys");
	debts->arg1 = new string(newnowdatelibrary);
	debts->arg2 = new string(result1);
	debts->arg3 = new string(certid);
	proxy.getDebts(debts, debtp);
	int count = debtp->return_.size();
	int cc = 100;

	//用来将检查是不是所有注销都成功了
	BOOL checkflag = TRUE;
	for (int i = 0; i < count; i++) { //循环扣款
		wchar_t *prono = debtp->return_[i]->propNo;
		wchar_t *lenddate = debtp->return_[i]->lendDate;
		float fineamount = debtp->return_[i]->dueFineAmount;

		long resultexceedFine1 = -1;
		int exceedFc = 0;
		while (resultexceedFine1 != 0 && exceedFc < 3)
		{
			resultexceedFine1 = singlexceedfinel(certid, prono, lenddate, fineamount, cc);
			Sleep(100);
			exceedFc++;
		}
		if (resultexceedFine1 == 0)
		{
			sumamount = sumamount + fineamount;
		}

		string newprono;
		Wchar_tToString(newprono, prono);
		if (resultexceedFine1) {
			checkflag = FALSE;
			//string msg = "财产号:" + newprono + "销账失败!";
			char msg[64];
			std::memset(msg, 0, sizeof(msg));
			sprintf_s(msg, 64, "财产号：%s 销账失败!", newprono.c_str());
			INFO(msg);
		}
		cc++;
	}
	return checkflag;
}

string getCircss(string certid)
{
	LibServicePortBindingProxy proxy;
	time_t nowtimelibrary = time(0);
	struct tm timeinfolibrary;
	localtime_s(&timeinfolibrary, &nowtimelibrary);
	string nowdatelibrary = DatetimeToString(&timeinfolibrary);
	string newnowdatelibrary = nowdatelibrary.substr(0, nowdatelibrary.length() - 3);
	string message = "libsysNJSFDX" + newnowdatelibrary;
	string result1 = stomd5(message);
	ns1__getCircs *circs = new ns1__getCircs();
	circs->arg0 = new string("libsys");
	circs->arg1 = new string(newnowdatelibrary);
	circs->arg2 = new string(result1);
	circs->arg3 = new string(certid);
	ns1__getCircsResponse *circsp = new ns1__getCircsResponse();
	proxy.getCircs(circs, circsp);
	string msg = "";
	if (circsp->return_.size() > 0)
	{
		for (int i = 0; i < circsp->return_.size(); i++)
		{
			string temp;
			//msg = msg.append( circsp->return_[i]->name);
			wchar_t *ptitle =  circsp->return_[i]->title;
			Wchar_tToString(temp, ptitle);
			msg = msg + std::to_string(i+1) + ". 书名：" + temp + "\t";
			wchar_t *pbarcode = circsp->return_[i]->barcode;
			Wchar_tToString(temp, pbarcode);
			msg = msg + "图书条形码：" + temp + "\t";
			//float price = circsp->return_[i]->price;
			//msg = msg + "定价：" + to_string(price) + "\t";
			wchar_t *plendDate = circsp->return_[i]->lendDate;
			Wchar_tToString(temp, plendDate);
			msg = msg + "借书日期：" + temp.substr(0, 10) + "\t";
			wchar_t *pdueDay = circsp->return_[i]->dueDay;
			Wchar_tToString(temp, pdueDay);
			msg = msg + "应还日期：" + temp + "\r\n";
		}
	}
	else
	{
		msg = "暂无在借书目!";
	}
	return msg;
}

int singlexceedfinel(string certid, wchar_t *prono, wchar_t *lenddate, float fineamount, int cc) {
	LibServicePortBindingProxy proxy;

	time_t nowtime2 = time(0);
	struct tm timeinfo2;
	localtime_s(&timeinfo2, &nowtime2);
	string nowdate2 = DatetimeToString(&timeinfo2);
	string dateh = nowdate2.substr(0, nowdate2.length() - 6);
	string dates = nowdate2.substr(nowdate2.length() - 3, nowdate2.length());
	string newnowdate2 = dateh + dates;
	string message2 = "libsysNJSFDX" + newnowdate2;
	//进行MD5加密，生成签证
	MD5 md6(message2);
	string result2 = md6.md5();

	/*wchar_t *prono = debtp->return_[i]->propNo;
	wchar_t *lenddate = debtp->return_[i]->lendDate;
	float fineamount = debtp->return_[i]->dueFineAmount;*/

	char arr[10];
	time_t t1;
	int num;
	srand((unsigned int)time(&t1));
	for (int i = 0; i != 6; ++i)
	{
		num = rand() % 10;
		arr[i] = '0' + num;
	}
	string s;
	for (int i = 0; i != 6; ++i)
	{
		s += arr[i];
	}
	cout << s;
	long tt = time(0);
	string strtt = ltos(tt);
	string billno = "D" + strtt + s + ltos(cc);

	ns1__exceedFine1 *exceedFine1 = new ns1__exceedFine1();

	exceedFine1->arg0 = new string("libsys");
	exceedFine1->arg1 = new string(newnowdate2);
	exceedFine1->arg2 = new string(result2);
	exceedFine1->arg3 = new string(certid);       //学号
	string newprono;
	Wchar_tToString(newprono, prono);
	exceedFine1->arg4 = new string(newprono);     //财产号
	string newlenddate;
	Wchar_tToString(newlenddate, lenddate);
	exceedFine1->arg5 = new string(newlenddate);  //借书日期
	exceedFine1->arg6 = new string(billno);    //账单号
	exceedFine1->arg7 = -1;               //销账金额
	exceedFine1->arg9 = new string("DRKF");           //经手人
	exceedFine1->arg10 = 1;          //罚款支付方式

	ns1__exceedFine1Response *exceedFine1p = new ns1__exceedFine1Response();

	int resultexceedFine1 = proxy.exceedFine1(exceedFine1, exceedFine1p);

	string resultinfo = "学号：" + certid + ",图书财产号：" + newprono + ",账单号：" + billno + ", 罚款处理结果：" + ltos(resultexceedFine1) + "\n";
	INFO(resultinfo.c_str());

	delete exceedFine1;
	delete exceedFine1p;

	return resultexceedFine1;

}