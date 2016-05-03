#include <iostream>
#include <string>
#include <list>

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "Http.h"
#include "HttpChunked.h"


using namespace CppUnit;
using namespace std;

class HTTPTest : public CppUnit::TestFixture{

	CPPUNIT_TEST_SUITE(HTTPTest);
	CPPUNIT_TEST(simpleGet);
	CPPUNIT_TEST(simplePOST);
	CPPUNIT_TEST(ReadHeaders);
	CPPUNIT_TEST(GetWithHeaders);
	CPPUNIT_TEST(GetChunked);
	CPPUNIT_TEST(MapToQuery);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);

private:
	void simpleGet(void);
	void simplePOST(void);
	void ReadHeaders(void);
	void GetWithHeaders(void);
	void GetChunked(void);
	void MapToQuery(void);

};


void HTTPTest::setUp(void){
}
void HTTPTest::tearDown(void){
}


void HTTPTest::simpleGet(void){
	string resp = Http::get("https://httpbin.org/get");
	cout<<'\n'<<resp<<'\n';
	CPPUNIT_ASSERT(!resp.empty());
}


void HTTPTest::simplePOST(void){
	string resp = Http::post("https://httpbin.org/post", {{"foo","oof"}, {"nain", "nian"}});
	cout<<'\n'<<resp<<'\n';
	CPPUNIT_ASSERT(!resp.empty());
}

void HTTPTest::MapToQuery(void){
	map<string, string> params;
	params["foo"]="oof";
	params["nain"]="nian";
	CPPUNIT_ASSERT(Http::mapToURL(params)=="foo=oof&nain=nian");
}

void HTTPTest::ReadHeaders(void){
	string headers;
	string resp = Http::get("https://httpbin.org/get", {}, &headers);
	cout<<'\n'<<headers<<'\n';
	CPPUNIT_ASSERT(!headers.empty());
}


void HTTPTest::GetWithHeaders(void){
	map<string, string> headerMap;
	string header;
	headerMap["Authorization"] = "Bearer hashed";
	string resp = Http::get("https://httpbin.org/headers", headerMap, &header);
	cout<<'\n'<<resp<<'\n';
	CPPUNIT_ASSERT(!header.empty());
}

void HTTPTest::GetChunked(void){
	Http::HttpChunked request{
		[](string data){
		}
	};

	map<string, string> headerMap;
	request.start("https://httpbin.org/stream/20");
	CPPUNIT_ASSERT(true);
}

CPPUNIT_TEST_SUITE_REGISTRATION( HTTPTest );
int main(int argc, char* argv[])
{
	CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
	CPPUNIT_NS::TestResultCollector collectedresults;
	testresult.addListener (&collectedresults);

    // register listener for per-test progress output
	CPPUNIT_NS::BriefTestProgressListener progress;
	testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
	CPPUNIT_NS::TestRunner testrunner;
	testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
	testrunner.run(testresult);

    // output results in compiler-format
	CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
	compileroutputter.write ();

	ofstream xmlFileOut("Http.test.xml");

	XmlOutputter xmlOut(&collectedresults, xmlFileOut);
	xmlOut.write();

    // return 0 if tests were successful
	return collectedresults.wasSuccessful() ? 0 : 1;
}