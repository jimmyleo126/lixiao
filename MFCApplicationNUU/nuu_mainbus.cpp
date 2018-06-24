
#include "stdafx.h"
#include "nuu_mainbus.h"
#include "afxwin.h"
#include "TipDlg.h"
#include "TipFeeAndBookDlg.h"
#include "TipBooksDlg.h"
#include "util.h"
#include "HttpClient.h"
#include <algorithm>
#include "FileLogger.h"
#include "LogManager.h"

//判断读卡器的循环
bool flag = TRUE;
HANDLE hThread;
//model用来表示循环读卡线程的时候，要进入哪一个模块，读卡，或者扣费或者在借查询
int model = 0;
//TimeFlag用来表示是否已经过时，用来跳到主界面的,初始值为FALSE不跳转
BOOL TimeFlag = FALSE;
//主界面的定时器，每次进入模块循环的时候，开始递增这个变量
int TimeCount = 0;
void Initnuu() {
	//加载初始化Chang.dll
	if (!initDLL())
	{
		MessageBox(NULL, "加载Change.dll失败！", "初始化", MB_OK);
	}

	OpenCom();

	
	//HANDLE hThread1;
	HANDLE hThreadopenCom;
	DWORD ThreadID;

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, (void *)1, CREATE_SUSPENDED, &ThreadID);
	//hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadUploadRecord, (void *)1, 0, &ThreadID);
	hThreadopenCom = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadopenCom, (void *)1, 0, &ThreadID);

	//CloseHandle(hThread);
	//CloseHandle(hThread1);
	CloseHandle(hThreadopenCom);
	LOG_INSTANCE->AppendLoger(new FileLogger());
}

void Endnuu() {
	flag = false;
	Sleep(500);
	CloseCom();
	UinitDLL();
}


string setLogOutUrl(string strcode, string certid)
{
	string loginstr;
	loginstr = "?strcode="+ strcode +"&accid=";
	loginstr = loginstr + certid;
	SYSTEMTIME tS;
	GetLocalTime(&tS);
	char timestr[20];
	std::memset(timestr, 0, sizeof(timestr));
	sprintf_s(timestr, 20, "%d%d%d%d%d%d%d", tS.wYear, tS.wMonth, tS.wDay, tS.wHour, tS.wMinute, tS.wSecond, tS.wMilliseconds);
	string sn = timestr + string("JSJM_njnu") + certid;
	string md5sn = stomd5(sn);
	transform(md5sn.begin(), md5sn.end(), md5sn.begin(), toupper);
	md5sn = md5sn.substr(7, 6);
	loginstr = loginstr + "&time=" + timestr + "&sn=" + md5sn;
	string url = "http://202.119.108.28/reader/hw_logout.php" + loginstr;
	return url;
}

//毕业证件注销
void LogOutSchool(string xh)
{
	if (xh.empty())
		return;
	string result;
	CHttpClient httpClient;
	if (xh.length() == 9)
	{
		string lunwenresult;
		string lunwenget = "http://202.119.108.211/lunwen/sthesis.asp?stuno=";
		httpClient.HttpGet((lunwenget + xh).c_str(), "", lunwenresult);
		if (lunwenresult.compare("OK") != 0)
		{
			CTipDlg dlg;
			dlg.t_tipMsg = "论文未提交!";
			dlg.DoModal();
			return;
		}
	}
	//调用http接口，1表示注销，0表示查看是否注销
	httpClient.HttpGet(setLogOutUrl("1", xh).c_str(), "", result);

	//检查result到底是什么
	char debugresult[512];
	std::memset(debugresult, 0, sizeof(debugresult));
	sprintf_s(debugresult, sizeof(debugresult), "学号：%s, DEBUG------- 结果原因：%s", xh.c_str(), result.c_str());
	INFO(debugresult);

	long resultcount = 0;
	resultcount = result.length();
	CTipDlg dlg;
	if (resultcount == 0)
	{
		dlg.t_tipMsg = "网络原因，请重新刷卡!";
	}
	else
	{
		string tag = result.substr(3, 1);
		string msg = "";
		if (s2l(tag) == 0)
		{
			result = result.substr(4);
			dlg.t_tipMsg = result.c_str();
			msg = "失败!";
			int islogout = result.find("注销");
			if (islogout >= 0) {
				msg = "成功!";
				string re;
				InsertLogoutRecord(xh, re);
			}
		}
		else if (s2l(tag) == 1)
		{
			httpClient.HttpGet(setLogOutUrl("1", xh).c_str(), "", result);
			result = result.substr(4);
			dlg.t_tipMsg = "证件已注销，图书馆清证完成!";
			msg = "成功!";
			string re;
			InsertLogoutRecord(xh, re);
		}
		char strlogout[512];
		std::memset(strlogout, 0, sizeof(strlogout));
		sprintf_s(strlogout, sizeof(strlogout), "学号：%s，注销%s, 结果原因：%s", xh.c_str(), msg.c_str(), result.c_str());
		//记录日志注销
		INFO(strlogout);
	}
	dlg.DoModal();
}

void LookReadingBooks(CUSTOMERINFO info)
{
	string certid = info.xh;
	string msg = getCircss(certid);

	INT_PTR	nRes;
	CTipBooksDlg tipbooksDlg;
	tipbooksDlg.t_readingbook = msg.c_str();
	tipbooksDlg.t_studentid = info.xh;
	nRes = tipbooksDlg.DoModal();

	if (IDCANCEL == nRes)
	{
	}
	else if (IDOK == nRes)
	{
	}
}

void WriteCard(CUSTOMERINFO info) {
	string certid = info.xh;
	float amount = 0;
	string re =  "";
	getDebts(certid, re, amount);
	//amount = (float)0.01; //测试金额
	double consumtemp = amount * 100;
	long consumption = consumtemp;

	char firstreadamount[64];
	std::memset(firstreadamount, 0, sizeof(firstreadamount));
	sprintf_s(firstreadamount, 64, "学号：%s，初始调试金额：%1.2f 元!", certid.c_str(), amount);
	INFO(firstreadamount);

	//判断金额如果没有欠款就是amount等于0
	if (consumption <= 0) {
		//模拟对话框弹出无欠费金额，并返回
		NoDebt();
		return;
	}

	//判断金额如果有欠款就是amount大于0
	if (!hasDebt(certid, re, amount))
	{
		return;
	}

	//判断饭卡中的余额是否充足
	if (info.Ye < consumption) {
		CTipDlg cdlg;
		cdlg.t_tipMsg = "卡中余额不足!";
		cdlg.DoModal();
		return;
	}

	char firstread[64];
	std::memset(firstread, 0, sizeof(firstread));
	sprintf_s(firstread, 64, "学号：%s，扣款金额：%1.2f 元，准备扣款!", certid.c_str(), amount);
	INFO(firstread);


	//调用汇文接口消除读者罚款，会有部分书籍无法消除情况
	BOOL ef = FALSE;
	float shouldamount = 0;
	int countexceedfine = 0;
	//每次循环调用接口10000000次，看它成不成功！
	while (!ef && countexceedfine < 10000000)
	{
		ef = exceedFines(certid, shouldamount);
		countexceedfine++;
	}

	consumption = shouldamount * 100;
	if (consumption == 0)
	{
		CTipDlg cdlg;
		cdlg.t_tipMsg = "清款失败，请重试!";
		cdlg.DoModal();
		return;
	}

	time_t nowtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &nowtime);
	string nowdate = DatetimeToString(&timeinfo);
	char jyDT[24];
	for (int i = 0; i < 24; i++) {
		jyDT[i] = 0;
	}
	for (int i = 0; i < nowdate.length(); i++) {
		jyDT[i] = nowdate[i];
	}
	//扣费成功，set返回为0
	long set = -1;
	int setcardcount = 0;

	__int64 psamID = 0;
	long psamJyNo = 0;
	long tac = 0;

	while (set != 0 && setcardcount < 100) {
		set = CapSetNBCardInfo(info.CustomerID, consumption, 0, jyDT, &psamID, &psamJyNo, &tac);
		setcardcount++;
	}

	//记录日志扣钱
	char strdebt[512];
	std::memset(strdebt, 0, sizeof(strdebt));
	sprintf_s(strdebt, sizeof(strdebt), "学号：%s，扣款金额：%1.2f，扣款%s", certid.c_str(), shouldamount, set == 0?"成功!":"失败!");
	INFO(strdebt);

	if (set != 0) {
		CTipDlg cdlg;
		cdlg.t_tipMsg = "扣款失败!";
		cdlg.DoModal();
		return;
	}

	tagUpLoadInfo uploadrecord;
	//终端机ID
	uploadrecord.termID = 1017;
	//账号
	uploadrecord.custID = info.CustomerID;
	//卡号
	uploadrecord.cardNO = info.CardNO;
	//卡序号
	uploadrecord.cardSn = info.CardSN;
	//卡类型：4-M1卡，8-CPU卡
	uploadrecord.cardClass = info.CardClass == 8 ? 2 : 1;
	//卡应用序列号
	strcpy_s(uploadrecord.cardASN, sizeof(uploadrecord.cardASN), info.CardASN);
	uploadrecord.sumFare = info.Ze;
	uploadrecord.mngFare = 0;
	uploadrecord.objNo = 0;
	uploadrecord.opFare = consumption;
	uploadrecord.oddFare = info.Ye - consumption;
	uploadrecord.opCount = info.OpCount + 1;
	strcpy_s(uploadrecord.jyDT, sizeof(uploadrecord.jyDT), nowdate.c_str());
	uploadrecord.psamID = psamID;
	uploadrecord.psamJyNo = psamJyNo;
	uploadrecord.tac = tac;
	uploadrecord.rtn = 0;
	uploadcustominfo(uploadrecord);

	//扣款结束，提示已经扣款完成！
	CTipDlg cdlg;
	if (amount > shouldamount) {
		cdlg.t_tipMsg = "部分扣款清除，请重试！";
	}
	else {
		cdlg.t_tipMsg = "扣款成功!";
	}
	cdlg.DoModal();

	//bool UploadSql(string samcardno,string iscpucard, string customid, string cardno, string cardsn, string opcount,
	//	string sumfare, string oddfare,string opfare,string opdt, string recno, 
	//	string samtradeno, string tac, string cardasn, string termid)
	/*		CString path = "Record";
	if (!PathIsDirectory(path)){
	::CreateDirectory(path, 0);
	}
	string tempupload[16];
	tempupload[0] = __int64tos(psamID);
	tempupload[1] = ltos(info.CardClass == 8 ? 2 : 1);
	tempupload[2] = ltos(info.CustomerID);
	tempupload[3] = ltos(info.CardNO);
	tempupload[4] = ltos(info.CardSN);
	tempupload[5] = ltos(info.OpCount + 1);

	tempupload[6] = ltos(info.Ze);
	tempupload[7] = ltos(info.Ye - consumption);
	tempupload[8] = ltos(consumption);
	tempupload[9] = nowdate;
	tempupload[10] = "0";

	tempupload[11] = ltos(psamJyNo);
	tempupload[12] = stringtac;
	tempupload[13] = stringcardasn;
	tempupload[14] = "1017";

	ofstream outfile;
	time_t now = time(0);
	string filename = "Record/" + ltos(now) + ".txt";
	outfile.open(filename);
	for (int i = 0; i < 15; i++) {
	outfile << tempupload[i] << endl;
	}
	outfile.close();*/

	/*UploadSql(__int64tos(psamID), ltos(info.CardClass == 8 ? 2 : 1), ltos(info.CustomerID), ltos(info.CardNO), ltos(info.CardSN), ltos(info.OpCount + 1),
	ltos(info.Ze), ltos(info.Ye - consumption), ltos(consumption), nowdate, "0",
	ltos(psamJyNo), stringtac, stringcardasn, "1017");*/
}

//学生没有欠款正常开始注销
void NoDebt()
{
	CTipDlg ctipDlg;
	ctipDlg.t_tipMsg = "无欠费金额!";
	INT_PTR nRes = ctipDlg.DoModal();
}

BOOL hasDebt(string xh, string re, float amount)
{
	INT_PTR	nRes;
	CTipFeeAndBookDlg tipfeeandbookDlg;
	//int debtsize = debtp->return_.size()
	tipfeeandbookDlg.debtfamount = amount;
	tipfeeandbookDlg.t_debtBooksinfo = re.c_str();
	tipfeeandbookDlg.t_student = xh.c_str();
	nRes = tipfeeandbookDlg.DoModal();
	
	if (IDCANCEL == nRes)
	{
		return FALSE;
	}
	else if (IDOK == nRes)
	{
		return TRUE;
	}
	return FALSE;
}

void InvalidCard()
{
	CTipDlg cdlg;
	cdlg.t_tipMsg = "卡已挂失!";
	cdlg.DoModal();
}

//学生扣款注销线程
void ThreadFunc(int num) {
	bool CanRead = TRUE;
	CUSTOMERINFO info;
	//CTipBooksDlg tipbooksDlg;
	//tipbooksDlg.t_readingbook = "暂无在接书籍!";
	//tipbooksDlg.t_studentid = "12345678";
	//tipbooksDlg.DoModal();
	
	while (true)
	{
		if (!flag) {
			MSG  msg;
			if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
			{
				::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
			}
			
			continue;
		}
		Sleep(100);




		if (TimeCount > 100)
		{
			//当进入到某个模块中TimeCount开始递增循环个100边，大概花个10秒左右，开始将TimeFlag值改为True
			TimeFlag = TRUE;
		}
		TimeCount++;
		long uid = 0;
		long query = CapNBQueryCard(&uid);
		//delete &uid;
		if ((query == 0) && (CanRead))
		{
			//只要刷卡之后，TimeCount计数器和TimeFlag值置0和FALSE
			TimeCount = 0;
			TimeFlag = FALSE;
			
			std::memset(&info, 0, sizeof(CUSTOMERINFO));
			CapGetNBCardInfo(&info);
			string Certid = info.xh;
			char strinfo[64];
			std::memset(strinfo, 0, sizeof(strinfo));
			sprintf_s(strinfo, 64, "学号：%s, 开始刷卡!", Certid.c_str());
			INFO(strinfo);
			long CardNo = info.CardNO;
			long isValidStu = 0;
			//如果isValidStu为0表示不校验，为1表示要校验
			isValidStu = GetPrivateProfileInt(TEXT("Service"), TEXT("isValidStu"), -1, TEXT("./Config1.ini"));
			if (isValidStu == 1) { 
				if (DataSql(Certid, CardNo)) {
					//model表示主界面中选择的模块0表示清款1表示查询在读信息
					if (model == 0)
					{
						WriteCard(info);
					}
					else if (model == 1)
					{
						LookReadingBooks(info);
					}
					else if (model == 2)
					{
						LogOutSchool(info.xh);
					}
				}
				else {
					InvalidCard();
				}
			}
			else {
				//model表示主界面中选择的模块0表示清款1表示查询在读信息
				if (model == 0)
				{
					WriteCard(info);
				}
				else if (model == 1)
				{
					LookReadingBooks(info);
				}
				else if (model == 2)
				{
					LogOutSchool(info.xh);
				}
			}
			CanRead = FALSE;
		}
		if (query != 0) {
			CanRead = TRUE;
		}
	}
}

//循环线程读卡
int ThreadopenCom(int num) {
	long res = -1;
	while (1) {
		if (res != 0) {
			res = OpenCom();
		}
		else {
			return 0;
		}
		MSG  msg;
		if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
		Sleep(5000);
	}
}

//控制读取线程，什么时候该停止，什么时候该启动
void ControlReadThread(int num)
{
	if (num == 1)
	{
		ResumeThread(hThread);
	}
	else if (num == 0)
	{
		SuspendThread(hThread);
	}
}

void OpenOrClose() {
	if (OpenCom() == 0) {

		if (flag) {
			flag = FALSE;
		}
		else {
			flag = TRUE;
		}
	}
	else {
		MessageBox(NULL, _T("连接读卡器失败！"), _T("提示"), MB_OK);
	}
}


//另起一个线程，去文件夹找到文件上传消费记录
/*void ThreadUploadRecord(int num) {
CString path = "Record";
if (PathIsDirectory(path)){
while (1) {
vector<string> files;
getFiles("Record", "txt", files);
int size = files.size();
if (size > 0) {
for (int i = 0; i < size; i++) {
string tempupload[16];
string filename = files[i];
char data[100];
ifstream infile;
infile.open(filename);
int x = 0;
while (!infile.eof()) {
infile.getline(data, 100);
tempupload[x] = data;
x++;
}
infile.close();
UploadSql(tempupload[0], tempupload[1], tempupload[2], tempupload[3],tempupload[4],tempupload[5],
tempupload[6], tempupload[7], tempupload[8], tempupload[9], tempupload[10],
tempupload[11], tempupload[12], tempupload[13], tempupload[14],filename);
}
}
MSG  msg;
if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
}
Sleep(1000);
}
}
}*/

//将记录插到文件中，然后再将文件中的字段信息上传到数据库中，上成功后再把文件删掉。。。方法暂时废弃
/*bool UploadSql( string samcardno, string iscpucard, string customid, string cardno, string cardsn, string opcount,
				string sumfare, string oddfare, string opfare, string opdt, string recno,
				string samtradeno, string tac, string cardasn, string termid,string filename)
{
	if (samcardno.compare("0") == 0 || samtradeno.compare("0") == 0 || tac.compare("0") == 0) {
		return false;
	}
	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr = sqlSp.CreateInstance(_uuidof(Connection));
	if (FAILED(hr))
	{
		MessageBox(NULL, _T("ConnectionPtr对象指针实例化失败！！！"), _T("Sql"), MB_OK);
		return false;
	}
	else {
		try {
			//_bstr_t strConnect = "Driver={sql server};server=211.65.216.147,1433;uid=sa;pwd=newcapec;database=transdbcpu;";
			_bstr_t strConnect = "Driver={sql server};server=202.119.108.238,1433;uid=by;pwd=123Njnu_1;database=byqz;";
			sqlSp->Open(strConnect, "", "", adModeUnknown);
		}
		catch (_com_error &e) {
			cout << e.Description() << endl;
		}
		try {
			CString newsamcardno, newiscpucard, newcustomid, newcardno, newcardsn, newopcount;
			CString newsumfare, newoddfare, newopfare, newopdt, newrecno;
			CString newsamtradeno, newtac, newcardasn, newtermid;
			newsamcardno = samcardno.c_str();
			newiscpucard = iscpucard.c_str();
			newcustomid = customid.c_str();
			newcardno = cardno.c_str();
			newcardsn = cardsn.c_str();
			newopcount = opcount.c_str();

			newsumfare = sumfare.c_str();
			newoddfare = oddfare.c_str();
			newopfare = opfare.c_str();
			newopdt = opdt.c_str();//不建议采用客户端系统时间
			newrecno = recno.c_str();

			newsamtradeno = samtradeno.c_str();
			newtac = tac.c_str();
			newcardasn = cardasn.c_str();
			newtermid = termid.c_str();
			_bstr_t sql = _T("insert into rec_cust_acc (poscode, samcardno, iscpucard, empid, customerid, ";
			sql = sql + "cardno, cardsn, saveopcount, opcount, sumfare, ";
			sql = sql + "oddfare, opfare, opdt, optype, recstate, ";
			sql = sql + " wallettype, tradeno, recno, samtradeno, mngfare,";
			sql = sql + " isoffline, mealid, tac, collectdt, cardasn, termid, acccode) values(";
			sql = sql + "0, " + newsamcardno + ", "+ newiscpucard +", 0, " + newcustomid + ", ";
			sql = sql + newcardno + "," + newcardsn + ", 0, " + newopcount + ", " + newsumfare + ", ";
			sql = sql + newoddfare + ", "+ newopfare +", getdate(), 1, 0, ";
			sql = sql + "0, 0, " + newrecno + ", " + newsamtradeno + ", 0, ";
			sql = sql + "1, 0, "+ newtac +", getdate(), "+ newcardasn +", "+ newtermid +", 217)");
			_variant_t ra;
			sqlSp->Execute((_bstr_t)sql,&ra,adCmdText);
			unsigned long affectrecords= ra.lVal;
			if ( affectrecords == 1) {
				remove(filename.c_str());
			}
		}
		catch (_com_error &e)
		{
			cout << e.Description() << endl;
		}
		//步骤4：关闭数据源
		//关闭数据库并释放指针
		try
		{
			sqlSp->Close();//关闭数据库
			sqlSp.Release();//释放连接对象指针
		}
		catch (_com_error &e)
		{
			cout << e.Description() << endl;
			cout << e.HelpFile() << endl;
		}
	}
}*/