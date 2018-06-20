#include "stdafx.h"
#include "DBConfig.h"
string  result;
bool readConfigFile(string cfgfilepath, string  key, string value)
{
	//CheckDlgButton(IDC_RADIO2, 1);
	fstream cfgFile;
	cfgFile.open(cfgfilepath);//���ļ�      
	if (!cfgFile.is_open())
	{
		cout << "can not open cfg file!" << endl;
		return false;
	}
	char tmp[1000];
	while (!cfgFile.eof())//ѭ����ȡÿһ��  
	{
		cfgFile.getline(tmp, 1000);//ÿ�ж�ȡǰ1000���ַ���1000��Ӧ���㹻�� 
		string line(tmp);
		size_t pos = line.find('=');//�ҵ�ÿ�еġ�=����λ�ã�֮ǰ��key֮����value
		if (pos == string::npos) return false;
		string tmpKey = line.substr(0, pos);//ȡ=��֮ǰ  
		if (key == tmpKey)
		{
			result = line.substr(pos + 1);//ȡ=��֮��
			
			return true;
		}
	}
	return false;
}

void writeConfigFile(string cfgfilepath, string  key, string value) {
	fstream  outfile;
	outfile.open(cfgfilepath, ios::out | ios::trunc);
	if (outfile.is_open()) {
		outfile << key << "=" << value << endl;
	}
	outfile.close();
}

string readURL() {
	fstream infile;
	infile.open("url.txt", ios::in);
	char data[100];
	infile >> data;
	return data;
}
