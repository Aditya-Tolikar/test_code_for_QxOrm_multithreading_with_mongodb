#include "db_interactor.h"

db_interactor::db_interactor(QObject *parent)
	: QObject{parent}
{

}

db_interactor::db_interactor(QString configFileName, QObject *parent) : QObject{parent}
{
	if (!configFileName.isEmpty())
	{
		QFile cf(configFileName);
		if (!cf.open(QFile::ReadOnly))
		{
			qDebug () << "Error : Unable to open file: " << cf.fileName();
		}
		QTextStream ts (&cf);
		while (!ts.atEnd())
		{
			QString aLine = ts.readLine();
			config.insert(aLine.split('=').at(0).trimmed(), aLine.split('=').at(1).trimmed());
		}
		qDebug () << "CONFIG: " << config;
	}
	else
	{
		qDebug () << "Config File Name EMPTY: " << configFileName;
	}
}

void db_interactor::init()
{
	db = qx::QxSqlDatabase::getSingleton();
	qDebug () << "Database Pointer" << db;
	db->setDriverName("QXMONGODB");
	db->setHostName("localhost");
	if (config.contains("DB"))
	{
		qDebug () << "Setting DB : " << config["DB"];
		db->setDatabaseName(config["DB"]);
	}
	else
	{
		qDebug () << "_________CONFIG DOES NOT CONTAIN \"DB\"_________________";
		db->setDatabaseName("new_db");
	}
	qDebug () << "____________Initialising DB____________";
	qDebug () << db->getDatabase();
	inited = true;
	emit initComplete();
}

void db_interactor::runQuery()
{
	if (inited)
	{
		qx_query nq ("{\"insert\" : \"ootpataang\" , \"documents\" : [{\"a\" : 213}, {\"bc\" : \"lsdhoufbg\"}, {\"def\" : 23.42}]}");
		QSqlError err = qx::dao::call_query(nq);

		if (err.isValid())
		{
			qDebug () << "Error writing to db : " << err.driverText();

			emit errorReturn("Error writing to db : " + err.driverText());
		}
		else
		{
			emit errorNoReturn("Written to DB");

			qx_query bq ("cursor" , "{\"find\" : \"ootpataang\"}");
			err = qx::dao::call_query(bq);
			if (err.isValid())
			{
				qDebug () << "Error writing to db : " << err.driverText();

				emit errorReturn("Error writing to db : " + err.driverText());
			}
			else
			{
				emit dataReady(QJsonDocument::fromJson(bq.response().toString().toUtf8()));
			}
		}
		return;
	}
	errorReturn ("Not Initialised yet");
}
