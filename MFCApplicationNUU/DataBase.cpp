#include "stdafx.h"

#include "DataBase.h"

#include "FileLogger.h"
#include "LogManager.h"

//���սṹ��tagUpLoadInfo����Ϣ��Ȼ��һ����ȡ�����ŵ�sql����в��뵽���ݿ���
void uploadcustominfo(tagUpLoadInfo uploadrecord)
{
	string tempcardasn = uploadrecord.cardASN;
	string subcardasn = tempcardasn.substr(9, 11);

	char asntemp[12];
	unsigned int i;

	for (i = 0; i<subcardasn.length(); i++)
		asntemp[i] = subcardasn[i];
	asntemp[i] = '\0';
	__int64 it64cardAsn = HexToDec(asntemp);
	string stringcardasn = Int_to_String(it64cardAsn);
	string psamid = Int_to_String(uploadrecord.psamID);
	unsigned long ultac = std::stoul(ltos(uploadrecord.tac), 0, 10);
	//long ultac = uploadrecord.tac;
	CoInitialize(NULL);
	_ConnectionPtr myconnect = NULL;
	HRESULT hr = myconnect.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
		return;
	_bstr_t strConnect = "Driver={sql server};server=211.65.216.147,1433;uid=sa;pwd=newcapec;database=transdbcpu;";
	//_bstr_t strConnect = "Driver={sql server};server=202.119.108.238,1433;uid=by;pwd=123Njnu_1;database=byqz;";
	myconnect->Open(strConnect, "", "", adModeUnknown);
	string  insertRecord;
	//poscode�豸��ӪΨһ��ţ�SamCardNo���ţ�iscpucardno�����ͣ�empidְԱ�˺ţ�customerid�û��˺�
	insertRecord = "insert into rec_cust_acc (poscode, samcardno, iscpucard, empid, customerid, ";
	//CardNo�û����ţ�CardSn�ֿ���ţ�SaveOpcount��ֵ���׼�����OpCount���ѽ��׼�����SumFare���ܶ�
	insertRecord = insertRecord + "cardno, cardsn, saveopcount, opcount, sumfare, ";
	//OddFare���׺��ܶOpFare���׽�Opdt�������ڣ�OpType�������ͣ�RecState��¼״̬
	insertRecord = insertRecord + "oddfare, opfare, opdt, optype, recstate, ";
	//WalletType����Ǯ����TradeNo������ˮ�ţ�RecNo���м�¼��ˮ�ţ�SamTradeNo��������ţ�MngFare�����
	insertRecord = insertRecord + " wallettype, tradeno, recno, samtradeno, mngfare,";
	//IsOffline����ʱʱ���ѻ���MealID�ͱ���룬Tac��֤�룬CollectDt�ɼ�ʱ�䣬ColloectAddress�ɼ���ַ��CardASN��Ψһ���кţ�TermID�ն˱�ţ�һ��ͨ�з��䣬AccCode��Ŀ����
	insertRecord = insertRecord + " isoffline, mealid, tac, collectdt, cardasn, termid, acccode) values(";
	insertRecord = insertRecord + "0, " + psamid + ", " + ltos(uploadrecord.cardClass) + ", 0, " + ltos(uploadrecord.custID) + ", ";
	insertRecord = insertRecord + ltos(uploadrecord.cardNO) + "," + ltos(uploadrecord.cardSn) + ", 0, " + ltos(uploadrecord.opCount) + ", " + ltos(uploadrecord.sumFare) + ", ";
	insertRecord = insertRecord + ltos(uploadrecord.oddFare) + ", " + ltos(uploadrecord.opFare) + ", '" + uploadrecord.jyDT + "', 1, 0, ";
	insertRecord = insertRecord + "0, 0, 0," + ltos(uploadrecord.psamJyNo) + ", 0, ";
	insertRecord = insertRecord + "1, 0, " + std::to_string(ultac) + ", '" + uploadrecord.jyDT + "', " + stringcardasn + ", " + ltos(uploadrecord.termID) + ", 217)";
	try {
		_variant_t ra;
		myconnect->Execute(_bstr_t(insertRecord.c_str()), &ra, adCmdText);
		unsigned long affectrecords = ra.lVal;
		string strmsg;
		char msg[100];
		memset(msg, 0, sizeof(msg));
		if (affectrecords == 1) 
		{
			sprintf_s(msg, 100, "{custID: %lu, �������ݿ�ɹ�!,���ѽ�%lu ��}", uploadrecord.custID, uploadrecord.opFare);
			INFO(msg);
		}
		else
		{
			sprintf_s(msg, 100, "{custID: %lu, �������ݿ�ʧ��!, ���ѽ�%lu ��}", uploadrecord.custID, uploadrecord.opFare);
			INFO(msg);
		}
	}
	catch (_com_error &e) {
		cout << e.Description() << endl;
		char msg[100];
		memset(msg, 0, sizeof(msg));
		sprintf_s(msg, 100, "{custID: %lu, �������ݿ�ʧ��!, ���ѽ�%lu ��}", uploadrecord.custID, uploadrecord.opFare);
		INFO(msg);
	}
	/*�ر����ݿⲢ�ͷ�ָ��*/
	try
	{
		myconnect->Close();//�ر����ݿ�
		myconnect.Release();//�ͷ����Ӷ���ָ��
	}
	catch (_com_error &e)
	{
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
	}
}

void InsertLogoutRecord(string certid, string &re)
{
	string stuName = getStuName(certid);
	if (stuName.compare("0") == 0)
	{
		return;
	}
	CoInitialize(NULL);
	_ConnectionPtr myconnect = NULL;
	HRESULT hr = myconnect.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
		return;
	_bstr_t strConnect = "Driver={sql server};server=202.119.108.238,1433;uid=clear_manage;pwd=123qwe!@#;database=GraduateSysNJNU;";
	//_bstr_t strConnect = "Driver={sql server};server=202.119.108.238,1433;uid=by;pwd=123Njnu_1;database=byqz;";
	myconnect->Open(strConnect, "", "", adModeUnknown);
	string  insertRecord;
	insertRecord = "insert into tblGraduators(StudentCode, Name, HWStatus, LogoutTime, SyncFlag)";
	insertRecord = insertRecord + "values('"  + certid + "', '" +  stuName + "', 0, CONVERT(varchar(100), GETDATE(), 120), 0)";
	try 
	{
		char msg[100];
		memset(msg, 0, sizeof(msg));
		_variant_t ra;
		myconnect->Execute(_bstr_t(insertRecord.c_str()), &ra, adCmdText);
		unsigned long affectrecords = ra.lVal;
		if (affectrecords == 1) {
			sprintf_s(msg, 100, "{ѧ��: %s, �������ݿ�tblGraduators�ɹ�!}", certid.c_str());
		}
		else
		{
			sprintf_s(msg, 100, "{ѧ��: %s, �������ݿ�tblGraduatorsʧ��!}", certid.c_str());
		}
		INFO(msg);
	}
	catch (_com_error &e) {
		AfxMessageBox("���ݿ��д����!");
	}
	/*�ر����ݿⲢ�ͷ�ָ��*/
	try
	{
		myconnect->Close();//�ر����ݿ�
		myconnect.Release();//�ͷ����Ӷ���ָ��
	}
	catch (_com_error &e)
	{
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
	}
}

string getStuName(string xh)
{
	string temp = "";
	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr = sqlSp.CreateInstance(_uuidof(Connection));
	if (FAILED(hr))
	{
		MessageBox(NULL, _T("ConnectionPtr����ָ��ʵ����ʧ�ܣ�����"), _T("Sql"), MB_OK);
		return "0";
	}
	try 
	{
		_bstr_t strConnect = "Driver={sql server};server=211.65.216.147,1433;uid=sa;pwd=newcapec;database=transdbcpu;";
		sqlSp->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error &e) {
		return "0";
	}
	_RecordsetPtr m_pRecordset;
	if (FAILED(m_pRecordset.CreateInstance(_uuidof(Recordset))))
	{
		MessageBox(NULL, _T("��¼������ָ��ʵ����ʧ�ܣ�"), _T("Sql"), MB_OK);
		return "0";
	}
	try 
	{
		CString strno;
		strno = xh.c_str();
		_bstr_t sql = _T("select top 10 name from base_customers where outid = '") + strno + "'";
		m_pRecordset->Open((_bstr_t)sql, (IDispatch*)sqlSp, adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error &e) {
		return "0";
	}
	try 
	{
		m_pRecordset->MoveFirst();
		while (!m_pRecordset->adoEOF)
		{
			string name = (char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("name"))->Value);
			temp = name;
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error &e) 
	{
		return "0";
	}
	//����4���ر�����Դ
	//�ر����ݿⲢ�ͷ�ָ��
	try 
	{
		m_pRecordset->Close();//�رռ�¼��               
		sqlSp->Close();//�ر����ݿ�
		m_pRecordset.Release();//�ͷż�¼������ָ��               
		sqlSp.Release();//�ͷ����Ӷ���ָ��
	}
	catch (_com_error &e) {
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
	}
	return temp;
}

string ServiceTime()
{
	BOOL falg = FALSE;
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
			_bstr_t strConnect = "Driver={sql server};server=211.65.216.147,1433;uid=sa;pwd=newcapec;database=transdbcpu;";
			sqlSp->Open(strConnect, "", "", adModeUnknown);
		}
		catch (_com_error &e) {
			cout << e.Description() << endl;
		}
		_RecordsetPtr m_pRecordset;
		if (FAILED(m_pRecordset.CreateInstance(_uuidof(Recordset))))
		{
			MessageBox(NULL, _T("��¼������ָ��ʵ����ʧ�ܣ�"), _T("Sql"), MB_OK);
			return false;
		}
		try {
			//strno.Format("%u",xh);
			_bstr_t sql = _T("select , status from base_customers");
			//sql.Format("select top 10 cardno, status from base_customers where outid ={0}",xh);
			//sql.Format(TEXT("select top 10 cardno, status from base_customers where outid = '%s'"), xh);
			m_pRecordset->Open((_bstr_t)sql, (IDispatch*)sqlSp, adOpenDynamic, adLockOptimistic, adCmdText);
		}
		catch (_com_error &e) {
			cout << e.Description() << endl;
		}
		try {
			m_pRecordset->MoveFirst();
			while (!m_pRecordset->adoEOF)
			{
				string cardno = (char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("cardno"))->Value);
				string status = (char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("status"))->Value);
				
				m_pRecordset->MoveNext();
			}
		}
		catch (_com_error &e) {
			cout << e.Description() << endl;
		}
		//����4���ر�����Դ
		//�ر����ݿⲢ�ͷ�ָ��
		try {
			m_pRecordset->Close();//�رռ�¼��               
			sqlSp->Close();//�ر����ݿ�
			m_pRecordset.Release();//�ͷż�¼������ָ��               
			sqlSp.Release();//�ͷ����Ӷ���ָ��
		}
		catch (_com_error &e) {
			cout << e.Description() << endl;
			cout << e.HelpFile() << endl;
		}
	}
}

BOOL DataSql(string xh, long cardNo)
{
	BOOL falg = FALSE;
	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr = sqlSp.CreateInstance(_uuidof(Connection));
	if (FAILED(hr))
	{
		MessageBox(NULL, _T("ConnectionPtr����ָ��ʵ����ʧ�ܣ�����"), _T("Sql"), MB_OK);
		return false;
	}else {
		try {
			_bstr_t strConnect = "Driver={sql server};server=211.65.216.147,1433;uid=sa;pwd=newcapec;database=transdbcpu;";
			sqlSp->Open(strConnect, "", "", adModeUnknown);
		}catch (_com_error &e) {
			cout << e.Description() << endl;
		}
		_RecordsetPtr m_pRecordset;
		if (FAILED(m_pRecordset.CreateInstance(_uuidof(Recordset))))
		{
			MessageBox(NULL, _T("��¼������ָ��ʵ����ʧ�ܣ�"), _T("Sql"), MB_OK);
			return false;
		}
		try {
			CString strno;
			strno = xh.c_str();
			//strno.Format("%u",xh);
			_bstr_t sql = _T("select top 10 cardno, status from base_customers where outid = '") + strno + "'";
			//sql.Format("select top 10 cardno, status from base_customers where outid ={0}",xh);
			//sql.Format(TEXT("select top 10 cardno, status from base_customers where outid = '%s'"), xh);
			m_pRecordset->Open((_bstr_t)sql, (IDispatch*)sqlSp, adOpenDynamic, adLockOptimistic, adCmdText);
		}catch (_com_error &e){
			cout << e.Description() << endl;
		}
		try {
			m_pRecordset->MoveFirst();
			while (!m_pRecordset->adoEOF)
			{
				string cardno = (char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("cardno"))->Value);
				string status = (char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("status"))->Value);
				long result;
				istringstream is(cardno);
				is >> result;
				if (result == cardNo && status.compare("1") == 0) {
					//MessageBox(NULL, "1", "cardno", MB_OK);
					falg = TRUE;
				}
				else {
					//MessageBox(NULL, "2", "cardno", MB_OK);
					falg = FALSE;
				}
				m_pRecordset->MoveNext();
			}
		}catch (_com_error &e){
			cout << e.Description() << endl;
		}
		//����4���ر�����Դ
		//�ر����ݿⲢ�ͷ�ָ��
		try {
			m_pRecordset->Close();//�رռ�¼��               
			sqlSp->Close();//�ر����ݿ�
			m_pRecordset.Release();//�ͷż�¼������ָ��               
			sqlSp.Release();//�ͷ����Ӷ���ָ��
		}catch (_com_error &e){
			cout << e.Description() << endl;
			cout << e.HelpFile() << endl;
		}
	}
	return falg;
}