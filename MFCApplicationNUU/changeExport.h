#if !defined CHANGEEXPORT_H
#define CHANGEEXPORT_H


#pragma pack( push)
#pragma pack(1)

typedef struct tagCustomerInfo
{
	long CardClass;		//�����ͣ�4-M1����8-CPU��
	long CustomerID;	//�˺����
	long CardNO;		//����
	long CardSN;		//���˳ֿ����
	long Status;		//��״̬ F1H=���� F3H=��ʧ
	long SubType;		//�����
	long Ze;			//�ܶ�	��λ����
	long Ye;			//�Է����	��λ����
	long OpCount;		//�Է����Ѽ���
	long SubYe;			//���˲������	��λ����
	long SubCount;		//���˲������Ѽ���
	char CardASN[24];	//��Ӧ�����к�
	char xh[24];		//ѧ(��)��
}CUSTOMERINFO;

typedef struct tagDownInfo
{
	char bm[200];	//��������
	char xh[60];	//ѧ��
	char name[40];	//����
	long sex;		//�Ա� (1��,0Ů)
	long customerid;//�ʺ�
	long cardno; 	//����
	long cardsn; 	//�ֿ����
	long status; 	//�ͻ�״̬
}DOWNINFO;

typedef struct tagDownDepInfo
{
	char DPCODE1[6];	//һ������
	char DPCODE2[6];	//��������
	char DPCODE3[8];	//��������
	char DPCODE4[8];	//�ļ�����
	char DPNAME1[60];	//һ������
	char DPNAME2[60];	//��������
	char DPNAME3[60];	//��������
	char DPNAME4[60];	//�ļ�����
}DOWNDEPINFO;

typedef struct tagUpLoadInfo
{
	long termID;	//�ն˻�ID	
	long custID;	//�ʺ�
	long cardNO;	//����
	long cardSn;	//�����
	long cardClass;	//�����ͣ�4-M1����8-CPU��
	char cardASN[24];//��Ӧ�����к�
	long sumFare;	//�ܶ� ����λ���֣�
	long mngFare;	//����� ����λ���֣�
	long objNo;		//Ǯ�����ͣ�0-��Ǯ����1-����Ǯ��
	long opFare;	//�ۿ��� ����λ���֣� 
	long oddFare;	//��� ����λ���֣�
	long opCount;	//���Ѽ���
	char jyDT[24];	//�ۿ�ʱ��
	__int64 psamID;	//PSAM����
	long psamJyNo;	//PSAM���ѻ��������
	long tac;		//������֤��
	long rtn;       //���ر�־.OUT
}UPLOADINFO;


#pragma pack( pop )



long OpenCom();
void CloseCom();

long CapNBQueryCard(long *uid);
long CapGetNBCardInfo(CUSTOMERINFO *fvst);
long CapSetNBCardInfo(long CustomerID, long opFare, long objNo, LPSTR jyDT, __int64 *psamID, long *psamJyNo, long *tac);


long CapDBConnect(LPCTSTR lpSID);
void CapDBDiscon();

long CapDownBlacklistCount();
long CapDownBlacklist(long *pList);

long CapGetDepCount();
long CapGetDepList(DOWNDEPINFO *pINFO);

long CapDownCustomerInfo(long CustomerID, DOWNINFO *downInfo);
long CapGetCustomerByNum(long CustomerID, long num, DOWNINFO *pINFO);
long CapGetCustomerCount();
long CapGetCustomerList(DOWNINFO *pINFO);

long CapUpload(UPLOADINFO *uploadInfo, LPSTR msg);

bool initDLL(void);
void UinitDLL(void);

#endif
#pragma once
