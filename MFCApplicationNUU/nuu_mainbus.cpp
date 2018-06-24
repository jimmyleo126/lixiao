
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

//�ж϶�������ѭ��
bool flag = TRUE;
HANDLE hThread;
//model������ʾѭ�������̵߳�ʱ��Ҫ������һ��ģ�飬���������߿۷ѻ����ڽ��ѯ
int model = 0;
//TimeFlag������ʾ�Ƿ��Ѿ���ʱ�����������������,��ʼֵΪFALSE����ת
BOOL TimeFlag = FALSE;
//������Ķ�ʱ����ÿ�ν���ģ��ѭ����ʱ�򣬿�ʼ�����������
int TimeCount = 0;
void Initnuu() {
	//���س�ʼ��Chang.dll
	if (!initDLL())
	{
		MessageBox(NULL, "����Change.dllʧ�ܣ�", "��ʼ��", MB_OK);
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

//��ҵ֤��ע��
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
			dlg.t_tipMsg = "����δ�ύ!";
			dlg.DoModal();
			return;
		}
	}
	//����http�ӿڣ�1��ʾע����0��ʾ�鿴�Ƿ�ע��
	httpClient.HttpGet(setLogOutUrl("1", xh).c_str(), "", result);

	//���result������ʲô
	char debugresult[512];
	std::memset(debugresult, 0, sizeof(debugresult));
	sprintf_s(debugresult, sizeof(debugresult), "ѧ�ţ�%s, DEBUG------- ���ԭ��%s", xh.c_str(), result.c_str());
	INFO(debugresult);

	long resultcount = 0;
	resultcount = result.length();
	CTipDlg dlg;
	if (resultcount == 0)
	{
		dlg.t_tipMsg = "����ԭ��������ˢ��!";
	}
	else
	{
		string tag = result.substr(3, 1);
		string msg = "";
		if (s2l(tag) == 0)
		{
			result = result.substr(4);
			dlg.t_tipMsg = result.c_str();
			msg = "ʧ��!";
			int islogout = result.find("ע��");
			if (islogout >= 0) {
				msg = "�ɹ�!";
				string re;
				InsertLogoutRecord(xh, re);
			}
		}
		else if (s2l(tag) == 1)
		{
			httpClient.HttpGet(setLogOutUrl("1", xh).c_str(), "", result);
			result = result.substr(4);
			dlg.t_tipMsg = "֤����ע����ͼ�����֤���!";
			msg = "�ɹ�!";
			string re;
			InsertLogoutRecord(xh, re);
		}
		char strlogout[512];
		std::memset(strlogout, 0, sizeof(strlogout));
		sprintf_s(strlogout, sizeof(strlogout), "ѧ�ţ�%s��ע��%s, ���ԭ��%s", xh.c_str(), msg.c_str(), result.c_str());
		//��¼��־ע��
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
	//amount = (float)0.01; //���Խ��
	double consumtemp = amount * 100;
	long consumption = consumtemp;

	char firstreadamount[64];
	std::memset(firstreadamount, 0, sizeof(firstreadamount));
	sprintf_s(firstreadamount, 64, "ѧ�ţ�%s����ʼ���Խ�%1.2f Ԫ!", certid.c_str(), amount);
	INFO(firstreadamount);

	//�жϽ�����û��Ƿ�����amount����0
	if (consumption <= 0) {
		//ģ��Ի��򵯳���Ƿ�ѽ�������
		NoDebt();
		return;
	}

	//�жϽ�������Ƿ�����amount����0
	if (!hasDebt(certid, re, amount))
	{
		return;
	}

	//�жϷ����е�����Ƿ����
	if (info.Ye < consumption) {
		CTipDlg cdlg;
		cdlg.t_tipMsg = "��������!";
		cdlg.DoModal();
		return;
	}

	char firstread[64];
	std::memset(firstread, 0, sizeof(firstread));
	sprintf_s(firstread, 64, "ѧ�ţ�%s���ۿ��%1.2f Ԫ��׼���ۿ�!", certid.c_str(), amount);
	INFO(firstread);


	//���û��Ľӿ��������߷�����в����鼮�޷��������
	BOOL ef = FALSE;
	float shouldamount = 0;
	int countexceedfine = 0;
	//ÿ��ѭ�����ýӿ�10000000�Σ������ɲ��ɹ���
	while (!ef && countexceedfine < 10000000)
	{
		ef = exceedFines(certid, shouldamount);
		countexceedfine++;
	}

	consumption = shouldamount * 100;
	if (consumption == 0)
	{
		CTipDlg cdlg;
		cdlg.t_tipMsg = "���ʧ�ܣ�������!";
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
	//�۷ѳɹ���set����Ϊ0
	long set = -1;
	int setcardcount = 0;

	__int64 psamID = 0;
	long psamJyNo = 0;
	long tac = 0;

	while (set != 0 && setcardcount < 100) {
		set = CapSetNBCardInfo(info.CustomerID, consumption, 0, jyDT, &psamID, &psamJyNo, &tac);
		setcardcount++;
	}

	//��¼��־��Ǯ
	char strdebt[512];
	std::memset(strdebt, 0, sizeof(strdebt));
	sprintf_s(strdebt, sizeof(strdebt), "ѧ�ţ�%s���ۿ��%1.2f���ۿ�%s", certid.c_str(), shouldamount, set == 0?"�ɹ�!":"ʧ��!");
	INFO(strdebt);

	if (set != 0) {
		CTipDlg cdlg;
		cdlg.t_tipMsg = "�ۿ�ʧ��!";
		cdlg.DoModal();
		return;
	}

	tagUpLoadInfo uploadrecord;
	//�ն˻�ID
	uploadrecord.termID = 1017;
	//�˺�
	uploadrecord.custID = info.CustomerID;
	//����
	uploadrecord.cardNO = info.CardNO;
	//�����
	uploadrecord.cardSn = info.CardSN;
	//�����ͣ�4-M1����8-CPU��
	uploadrecord.cardClass = info.CardClass == 8 ? 2 : 1;
	//��Ӧ�����к�
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

	//�ۿ��������ʾ�Ѿ��ۿ���ɣ�
	CTipDlg cdlg;
	if (amount > shouldamount) {
		cdlg.t_tipMsg = "���ֿۿ�����������ԣ�";
	}
	else {
		cdlg.t_tipMsg = "�ۿ�ɹ�!";
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

//ѧ��û��Ƿ��������ʼע��
void NoDebt()
{
	CTipDlg ctipDlg;
	ctipDlg.t_tipMsg = "��Ƿ�ѽ��!";
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
	cdlg.t_tipMsg = "���ѹ�ʧ!";
	cdlg.DoModal();
}

//ѧ���ۿ�ע���߳�
void ThreadFunc(int num) {
	bool CanRead = TRUE;
	CUSTOMERINFO info;
	//CTipBooksDlg tipbooksDlg;
	//tipbooksDlg.t_readingbook = "�����ڽ��鼮!";
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
			//�����뵽ĳ��ģ����TimeCount��ʼ����ѭ����100�ߣ���Ż���10�����ң���ʼ��TimeFlagֵ��ΪTrue
			TimeFlag = TRUE;
		}
		TimeCount++;
		long uid = 0;
		long query = CapNBQueryCard(&uid);
		//delete &uid;
		if ((query == 0) && (CanRead))
		{
			//ֻҪˢ��֮��TimeCount��������TimeFlagֵ��0��FALSE
			TimeCount = 0;
			TimeFlag = FALSE;
			
			std::memset(&info, 0, sizeof(CUSTOMERINFO));
			CapGetNBCardInfo(&info);
			string Certid = info.xh;
			char strinfo[64];
			std::memset(strinfo, 0, sizeof(strinfo));
			sprintf_s(strinfo, 64, "ѧ�ţ�%s, ��ʼˢ��!", Certid.c_str());
			INFO(strinfo);
			long CardNo = info.CardNO;
			long isValidStu = 0;
			//���isValidStuΪ0��ʾ��У�飬Ϊ1��ʾҪУ��
			isValidStu = GetPrivateProfileInt(TEXT("Service"), TEXT("isValidStu"), -1, TEXT("./Config1.ini"));
			if (isValidStu == 1) { 
				if (DataSql(Certid, CardNo)) {
					//model��ʾ��������ѡ���ģ��0��ʾ���1��ʾ��ѯ�ڶ���Ϣ
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
				//model��ʾ��������ѡ���ģ��0��ʾ���1��ʾ��ѯ�ڶ���Ϣ
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

//ѭ���̶߳���
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

//���ƶ�ȡ�̣߳�ʲôʱ���ֹͣ��ʲôʱ�������
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
		MessageBox(NULL, _T("���Ӷ�����ʧ�ܣ�"), _T("��ʾ"), MB_OK);
	}
}


//����һ���̣߳�ȥ�ļ����ҵ��ļ��ϴ����Ѽ�¼
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

//����¼�嵽�ļ��У�Ȼ���ٽ��ļ��е��ֶ���Ϣ�ϴ������ݿ��У��ϳɹ����ٰ��ļ�ɾ��������������ʱ����
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
		MessageBox(NULL, _T("ConnectionPtr����ָ��ʵ����ʧ�ܣ�����"), _T("Sql"), MB_OK);
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
			newopdt = opdt.c_str();//��������ÿͻ���ϵͳʱ��
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
		//����4���ر�����Դ
		//�ر����ݿⲢ�ͷ�ָ��
		try
		{
			sqlSp->Close();//�ر����ݿ�
			sqlSp.Release();//�ͷ����Ӷ���ָ��
		}
		catch (_com_error &e)
		{
			cout << e.Description() << endl;
			cout << e.HelpFile() << endl;
		}
	}
}*/