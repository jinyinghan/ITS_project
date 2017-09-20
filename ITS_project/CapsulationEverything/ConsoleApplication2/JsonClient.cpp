#include <iostream>
#include <fstream> 
#include <string>
#include <cassert>
#include <iostream>

#include "frozen.h"

#include "rapidjson/document.h"  
#include "rapidjson/prettywriter.h"  
#include "rapidjson/filestream.h"  
#include "rapidjson/stringbuffer.h" 

#define psln(x) std::cout << #x " = " << (x) << std::endl

using namespace std;
using namespace rapidjson;

void test1();
void test2();
void test3();

void main()
{
	cout << "Hello litjson" << endl;

	//test1();
	test2();

	/*
	static const char *json = " { foo: 1, bar: \"changshuhang\" } ";
	struct json_token *arr, *tok;

	// Tokenize json string, fill in tokens array
	arr = parse_json2(json, strlen(json));

	// Search for parameter "bar" and print it's value
	tok = find_json_token(arr, "bar");
	printf("Value of bar is: [%.*s]\n", tok->len, tok->ptr);

	// Do not forget to free allocated tokens array
	free(arr);
	*/

	////////////////////////////////////////////////////////////////////////////////
	// Loop until user enters q or Q
	////////////////////////////////////////////////////////////////////////////////
	char c(' ');

	while (c != 'q' && c != 'Q')
	{
		cout << "Press q then enter to quit: ";
		cin >> c;
	}
}

//测试1
void test1()
{
	Document document;

	Document::AllocatorType& allocator = document.GetAllocator();
	Value contact(kArrayType);
	Value contact2(kArrayType);
	Value root(kArrayType);
	contact.PushBack("Lu//a\"", allocator).PushBack("Mio", allocator).PushBack("", allocator);
	contact2.PushBack("Lu// a", allocator).PushBack("Mio", allocator).PushBack("", allocator);
	root.PushBack(contact, allocator);
	root.PushBack(contact2, allocator);

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	root.Accept(writer);
	string reststring = buffer.GetString();
	cout << reststring.c_str() << endl;
}

//测试2
void test2()
{
	Document document;
	Document::AllocatorType& allocatorType = document.GetAllocator();
	Value root(kObjectType);

	//添加string数据
	Value FlgStatus="sample string 1";
	root.AddMember("FlgStatus", FlgStatus, allocatorType);
	//添加bool
	Value OrderNo=true;
	root.AddMember("OrderNo", OrderNo, allocatorType);
	//添加int
	Value CustomerContactID=123;
	root.AddMember("CustomerContactID", CustomerContactID, allocatorType);
	//添加double
	Value CouponType = 123.456;
	root.AddMember("CouponType", CouponType, allocatorType);
	//添加array
	Value ordersBody(kArrayType);
	for (int i = 0; i < 2; i++)
	{
		Value v(kObjectType);

		Value CustomerContactID = "sample string 1";
		v.AddMember("CustomerContactID", CustomerContactID, allocatorType);
		Value CustomerID = false;
		v.AddMember("CustomerID", CustomerID, allocatorType);
		Value Provinces = 123.45;
		v.AddMember("Provinces", Provinces, allocatorType);
		Value City = 34545;
		v.AddMember("City", City, allocatorType);

		ordersBody.PushBack(v,allocatorType);
	}
	root.AddMember("ordersBody", ordersBody, allocatorType);

	//添加object数据
	Value customercontact(kObjectType);
	Value CustomerContactID1 = "sample string 1";
	customercontact.AddMember("CustomerContactID", CustomerContactID1, allocatorType);
	Value CustomerID = false;
	customercontact.AddMember("CustomerID", CustomerID, allocatorType);
	Value Provinces = 123.45;
	customercontact.AddMember("Provinces", Provinces, allocatorType);
	Value City = 34545;
	customercontact.AddMember("City", City, allocatorType);
	root.AddMember("customercontact", customercontact, allocatorType);


	StringBuffer stringBuffer;
	Writer<StringBuffer> writer(stringBuffer);
	root.Accept(writer);
	std::string result = stringBuffer.GetString();
	cout << "result: " << result.c_str() << "..........:" << result.size() << endl;

	ofstream outfile("E://json2.json");
	outfile << result.c_str() << endl;
	outfile.close();
}

//读取解析文件
void test3()
{
	using std::string;
	using std::ifstream;

	string  stringFromStream;
	ifstream  in;
	in.open("E://json1.json", ifstream::in);
	if (!in.is_open())
		return;
	string line;
	while (getline(in, line)) {
		stringFromStream.append(line + "\n");
	}
	in.close();

	//cout << stringFromStream << endl;

	Document doc;
	doc.Parse<0>(stringFromStream.c_str());
	if (doc.HasParseError()) {
		//ParseErrorCode code = doc.GetParseError();
		psln("error");
		return;
	}

	// use values in parse result.
	Value & v = doc["FlgStatus"];
	if (v.IsString())
	{
		psln(v.GetString());
	}
	v = doc["OrderNo"];
	if (v.IsBool())
	{
		psln(v.GetBool());
	}
	v = doc["CustomerContactID"];
	if (v.IsDouble())
	{
		psln(v.GetDouble());
	}
	v = doc["CouponType"];
	if (v.IsInt())
	{
		psln(v.GetInt());
	}
	//解析array
	v = doc["ordersBody"];
	if (v.IsArray())
	{
		int len = v.Size();
		for (int i = 0; i < len; i++)
		{
			Value & value = v[i];
			if (value.IsObject())
			{
				if (value.HasMember("CustomerContactID") && value["CustomerContactID"].IsString())
				{
					psln(value["CustomerContactID"].GetString());
				}
				if (value.HasMember("CustomerID") && value["CustomerID"].IsBool())
				{
					psln(value["CustomerID"].GetBool());
				}
				if (value.HasMember("Provinces") && value["Provinces"].IsDouble())
				{
					psln(value["Provinces"].GetDouble());
				}
				if (value.HasMember("City") && value["City"].IsInt())
				{
					psln(value["City"].GetInt());
				}
			}
		}
	}
	//解析object
	v = doc["customercontact"];
	if (v.IsObject())
	{
		if (v.HasMember("CustomerContactID") && v["CustomerContactID"].IsString())
		{
			psln(v["CustomerContactID"].GetString());
		}
		if (v.HasMember("CustomerID") && v["CustomerID"].IsBool())
		{
			psln(v["CustomerID"].GetBool());
		}
		if (v.HasMember("Provinces") && v["Provinces"].IsDouble())
		{
			psln(v["Provinces"].GetDouble());
		}
		if (v.HasMember("City") && v["City"].IsInt())
		{
			psln(v["City"].GetInt());
		}
	}
}