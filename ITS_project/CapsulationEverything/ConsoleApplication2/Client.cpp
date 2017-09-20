#include <iostream>

#include "CppSQLite3.h"
#include <ctime>

using namespace std;

const char * gszFile = "e:\\sqlite3\\test.db";

//测试Sqlite3的使用
void main1()
{
	cout << "hello sqlite3" << endl;

	try
	{
		int i, fld;
		time_t tmStart, tmEnd;
		CppSQLite3DB db;

		char *sql;

		cout << "SQLite Header Version: " << CppSQLite3DB::SQLiteHeaderVersion() << endl;
		cout << "SQLite Library Version: " << CppSQLite3DB::SQLiteLibraryVersion() << endl;
		cout << "SQLite Library Version Number: " << CppSQLite3DB::SQLiteLibraryVersionNumber() << endl;

		//remove(gszFile);
		db.open(gszFile);
		//插入数据
		cout << endl << "emp table exists=" << (db.tableExists("person") ? "TRUE" : "FALSE") << endl;
		// Create SQL statement
		sql = "CREATE TABLE person("  \
			"id INT PRIMARY KEY     NOT NULL," \
			"name           TEXT    NOT NULL," \
			"age            INT     NOT NULL," \
			"address        CHAR(50)," \
			"salary         REAL );";
		//db.execDML(sql);
		//cout << endl << "emp table exists=" << (db.tableExists("person") ? "TRUE" : "FALSE") << endl;
		//cout << endl << "DML tests" << endl;

		sql = "insert into person values (1, 'David Beckham',34,'china person',3455.78);"\
			"insert into person values (2, 'changshuhang',33,'china person1',3455.34);"\
			"insert into person values (3, 'houyuzhu',37,'china person2',34534);"\
			"insert into person values (4, 'chengye',356,'china person3',45.78);"\
			"insert into person values (5, 'dujianfei',38,'china person4',3655.78);";
		int nRows = db.execDML(sql);
		cout << nRows << " rows inserted" << endl;

		//update
		/*
		sql = "update person set name = 'xijinping' where id = 5 ;"\
				"update person set name = 'hujingtao' where address = 'china person2' ;";
		int nRows = db.execDML(sql);
		cout << nRows << " rows updated" << endl;
		*/

		//delete
		/*
		sql = "delete from person where id = 5 ;"\
			"delete from person where address = 'china person2' ;";
		int nRows = db.execDML(sql);
		cout << nRows << " rows updated" << endl;
		*/

		/*
		// Query data and also show results of inserts into auto-increment field
		cout << endl << "Select statement test" << endl;
		CppSQLite3Query q = db.execQuery("select * from person order by id;");

		for (fld = 0; fld < q.numFields(); fld++)
		{
			cout << q.fieldName(fld) << "(" << q.fieldDeclType(fld) << ")|";
		}
		cout << endl;

		while (!q.eof())
		{
			cout << q.fieldValue(0) << "|";
			cout << q.fieldValue(1) << "|";
			cout << q.fieldValue(2) << "|";
			cout << q.fieldValue(3) << endl;
			q.nextRow();
		}
		*/

		/*
		// Fetch table at once, and also show how to use CppSQLiteTable::setRow() method
		cout << endl << "getTable() test" << endl;
		CppSQLite3Table t = db.getTable("select * from person order by id;");

		for (fld = 0; fld < t.numFields(); fld++)
		{
			cout << t.fieldName(fld) << "|";
		}
		cout << endl;
		for (int row = 0; row < t.numRows(); row++)
		{
			t.setRow(row);
			for (int fld = 0; fld < t.numFields(); fld++)
			{
				if (!t.fieldIsNull(fld))
					cout << t.fieldValue(fld) << "|";
				else
					cout << "NULL" << "|";
			}
			cout << endl;
		}
		*/

	}
	catch (CppSQLite3Exception& e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

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