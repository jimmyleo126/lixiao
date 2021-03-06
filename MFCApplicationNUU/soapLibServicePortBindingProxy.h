/* soapLibServicePortBindingProxy.h
   Generated by gSOAP 2.7.16 from LibServicePort.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapLibServicePortBindingProxy_H
#define soapLibServicePortBindingProxy_H
#include "soapH.h"

class SOAP_CMAC LibServicePortBindingProxy : public soap
{ public:
	/// Endpoint URL of service 'LibServicePortBindingProxy' (change as needed)
	const char *soap_endpoint;
	/// Constructor
	LibServicePortBindingProxy();
	/// Constructor with copy of another engine state
	LibServicePortBindingProxy(const struct soap&);
	/// Constructor with engine input+output mode control
	LibServicePortBindingProxy(soap_mode iomode);
	/// Constructor with engine input and output mode control
	LibServicePortBindingProxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~LibServicePortBindingProxy();
	/// Initializer used by constructors
	virtual	void LibServicePortBindingProxy_init(soap_mode imode, soap_mode omode);
	/// Delete all deserialized data (uses soap_destroy and soap_end)
	virtual	void destroy();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Force close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
	virtual	void soap_stream_fault(std::ostream&);
	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif

	/// Web service operation 'getReader' (returns error code or SOAP_OK)
	virtual	int getReader(ns1__getReader *ns1__getReader_, ns1__getReaderResponse *ns1__getReaderResponse_);

	/// Web service operation 'getItems' (returns error code or SOAP_OK)
	virtual	int getItems(ns1__getItems *ns1__getItems_, ns1__getItemsResponse *ns1__getItemsResponse_);

	/// Web service operation 'getBook' (returns error code or SOAP_OK)
	virtual	int getBook(ns1__getBook *ns1__getBook_, ns1__getBookResponse *ns1__getBookResponse_);

	/// Web service operation 'getCircs' (returns error code or SOAP_OK)
	virtual	int getCircs(ns1__getCircs *ns1__getCircs_, ns1__getCircsResponse *ns1__getCircsResponse_);

	/// Web service operation 'getViolations' (returns error code or SOAP_OK)
	virtual	int getViolations(ns1__getViolations *ns1__getViolations_, ns1__getViolationsResponse *ns1__getViolationsResponse_);

	/// Web service operation 'getDebts' (returns error code or SOAP_OK)
	virtual	int getDebts(ns1__getDebts *ns1__getDebts_, ns1__getDebtsResponse *ns1__getDebtsResponse_);

	/// Web service operation 'getPregArrivals' (returns error code or SOAP_OK)
	virtual	int getPregArrivals(ns1__getPregArrivals *ns1__getPregArrivals_, ns1__getPregArrivalsResponse *ns1__getPregArrivalsResponse_);

	/// Web service operation 'getRelegateArrivals' (returns error code or SOAP_OK)
	virtual	int getRelegateArrivals(ns1__getRelegateArrivals *ns1__getRelegateArrivals_, ns1__getRelegateArrivalsResponse *ns1__getRelegateArrivalsResponse_);

	/// Web service operation 'getPregs' (returns error code or SOAP_OK)
	virtual	int getPregs(ns1__getPregs *ns1__getPregs_, ns1__getPregsResponse *ns1__getPregsResponse_);

	/// Web service operation 'getRelegates' (returns error code or SOAP_OK)
	virtual	int getRelegates(ns1__getRelegates *ns1__getRelegates_, ns1__getRelegatesResponse *ns1__getRelegatesResponse_);

	/// Web service operation 'getAccounts' (returns error code or SOAP_OK)
	virtual	int getAccounts(ns1__getAccounts *ns1__getAccounts_, ns1__getAccountsResponse *ns1__getAccountsResponse_);

	/// Web service operation 'getLostPays' (returns error code or SOAP_OK)
	virtual	int getLostPays(ns1__getLostPays *ns1__getLostPays_, ns1__getLostPaysResponse *ns1__getLostPaysResponse_);

	/// Web service operation 'exceedFine' (returns error code or SOAP_OK)
	virtual	int exceedFine(ns1__exceedFine *ns1__exceedFine_, ns1__exceedFineResponse *ns1__exceedFineResponse_);

	/// Web service operation 'certLoss' (returns error code or SOAP_OK)
	virtual	int certLoss(ns1__certLoss *ns1__certLoss_, ns1__certLossResponse *ns1__certLossResponse_);

	/// Web service operation 'logout' (returns error code or SOAP_OK)
	virtual	int logout(ns1__logout *ns1__logout_, ns1__logoutResponse *ns1__logoutResponse_);

	/// Web service operation 'getLendHist' (returns error code or SOAP_OK)
	virtual	int getLendHist(ns1__getLendHist *ns1__getLendHist_, ns1__getLendHistResponse *ns1__getLendHistResponse_);

	/// Web service operation 'getMarc' (returns error code or SOAP_OK)
	virtual	int getMarc(ns1__getMarc *ns1__getMarc_, ns1__getMarcResponse *ns1__getMarcResponse_);

	/// Web service operation 'checkReader' (returns error code or SOAP_OK)
	virtual	int checkReader(ns1__checkReader *ns1__checkReader_, ns1__checkReaderResponse *ns1__checkReaderResponse_);

	/// Web service operation 'voltFine' (returns error code or SOAP_OK)
	virtual	int voltFine(ns1__voltFine *ns1__voltFine_, ns1__voltFineResponse *ns1__voltFineResponse_);

	/// Web service operation 'getViolations1' (returns error code or SOAP_OK)
	virtual	int getViolations1(ns1__getViolations1 *ns1__getViolations1_, ns1__getViolations1Response *ns1__getViolations1Response_);

	/// Web service operation 'exceedFine1' (returns error code or SOAP_OK)
	virtual	int exceedFine1(ns1__exceedFine1 *ns1__exceedFine1_, ns1__exceedFine1Response *ns1__exceedFine1Response_);

	/// Web service operation 'registerReader' (returns error code or SOAP_OK)
	virtual	int registerReader(ns1__registerReader *ns1__registerReader_, ns1__registerReaderResponse *ns1__registerReaderResponse_);

	/// Web service operation 'getRedrTypes' (returns error code or SOAP_OK)
	virtual	int getRedrTypes(ns1__getRedrTypes *ns1__getRedrTypes_, ns1__getRedrTypesResponse *ns1__getRedrTypesResponse_);

	/// Web service operation 'getDeps' (returns error code or SOAP_OK)
	virtual	int getDeps(ns1__getDeps *ns1__getDeps_, ns1__getDepsResponse *ns1__getDepsResponse_);

	/// Web service operation 'getAccounts1' (returns error code or SOAP_OK)
	virtual	int getAccounts1(ns1__getAccounts1 *ns1__getAccounts1_, ns1__getAccounts1Response *ns1__getAccounts1Response_);
};
#endif
