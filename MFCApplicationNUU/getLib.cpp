#include "stdafx.h"
#include "getLib.h"
using namespace std;




void *getReader(string newnowdate, string result1, string certid, ns1__getReaderResponse *readerp) {
	LibServicePortBindingProxy proxy;
	long result;
	ns1__getReader *reader = new ns1__getReader();
	//ns1__getReaderResponse *readerp = new ns1__getReaderResponse();
	string un = "libsys";
	reader->arg0 = new string("libsys");
	reader->arg1 = new string(newnowdate);
	reader->arg2 = new string(result1);
	reader->arg3 = 1;
	reader->arg4 = new string(certid);

	result = proxy.getReader(reader, readerp);
	if (result) {
		return;
	}
	return;

}