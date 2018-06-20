#if !defined CHANGEEXPORT_H
#define CHANGEEXPORT_H


#pragma pack( push)
#pragma pack(1)

typedef struct tagCustomerInfo
{
	long CardClass;		//卡类型：4-M1卡，8-CPU卡
	long CustomerID;	//账号序号
	long CardNO;		//卡号
	long CardSN;		//个人持卡序号
	long Status;		//卡状态 F1H=正常 F3H=挂失
	long SubType;		//卡类别
	long Ze;			//总额	单位：分
	long Ye;			//自费余额	单位：分
	long OpCount;		//自费消费计数
	long SubYe;			//个人补助余额	单位：分
	long SubCount;		//个人补助消费计数
	char CardASN[24];	//卡应用序列号
	char xh[24];		//学(工)号
}CUSTOMERINFO;

typedef struct tagDownInfo
{
	char bm[200];	//部门名称
	char xh[60];	//学号
	char name[40];	//姓名
	long sex;		//性别 (1男,0女)
	long customerid;//帐号
	long cardno; 	//卡号
	long cardsn; 	//持卡序号
	long status; 	//客户状态
}DOWNINFO;

typedef struct tagDownDepInfo
{
	char DPCODE1[6];	//一级部门
	char DPCODE2[6];	//二级部门
	char DPCODE3[8];	//三级部门
	char DPCODE4[8];	//四级部门
	char DPNAME1[60];	//一级部门
	char DPNAME2[60];	//二级部门
	char DPNAME3[60];	//三级部门
	char DPNAME4[60];	//四级部门
}DOWNDEPINFO;

typedef struct tagUpLoadInfo
{
	long termID;	//终端机ID	
	long custID;	//帐号
	long cardNO;	//卡号
	long cardSn;	//卡序号
	long cardClass;	//卡类型：4-M1卡，8-CPU卡
	char cardASN[24];//卡应用序列号
	long sumFare;	//总额 （单位：分）
	long mngFare;	//管理费 （单位：分）
	long objNo;		//钱包类型：0-主钱包，1-补助钱包
	long opFare;	//扣款金额 （单位：分） 
	long oddFare;	//余额 （单位：分）
	long opCount;	//消费计数
	char jyDT[24];	//扣款时间
	__int64 psamID;	//PSAM卡号
	long psamJyNo;	//PSAM卡脱机交易序号
	long tac;		//交易验证码
	long rtn;       //返回标志.OUT
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
