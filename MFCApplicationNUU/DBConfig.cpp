#include "stdafx.h"
#include "DBConfig.h"
string  result;
bool readConfigFile(string cfgfilepath, string  key, string value)
{
	//CheckDlgButton(IDC_RADIO2, 1);
	fstream cfgFile;
	cfgFile.open(cfgfilepath);//打开文件      
	if (!cfgFile.is_open())
	{
		cout << "can not open cfg file!" << endl;
		return false;
	}
	char tmp[1000];
	while (!cfgFile.eof())//循环读取每一行  
	{
		cfgFile.getline(tmp, 1000);//每行读取前1000个字符，1000个应该足够了 
		string line(tmp);
		size_t pos = line.find('=');//找到每行的“=”号位置，之前是key之后是value
		if (pos == string::npos) return false;
		string tmpKey = line.substr(0, pos);//取=号之前  
		if (key == tmpKey)
		{
			result = line.substr(pos + 1);//取=号之后
			
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
