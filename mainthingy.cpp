#include "mainthingy.h"

#include <iostream>
#include <string>

mainThingy::mainThingy(QObject *parent)
	: QObject{parent}
{
	di1 = new db_interactor(QStringLiteral(":/conf1.ini"));
	di2 = new db_interactor(QStringLiteral(":/conf2.ini"));
	di1->moveToThread(&aFewThreads[0]);
	di2->moveToThread(&aFewThreads[1]);
	aFewThreads[0].start();
	aFewThreads[1].start();

	connect(this, &mainThingy::init1, di1, &db_interactor::init);
	connect(di1, &db_interactor::initComplete, this, [this]()
	{
		qDebug () << "DB Interactor 1 Init Complete";
		user_time = true;
	});
	connect(di2, &db_interactor::initComplete, this, [this]()
	{
		qDebug () << "DB Interactor 2 Init Complete";
		user_time = true;
	});
	connect(this, &mainThingy::init2, di2, &db_interactor::init);
	connect(this, &mainThingy::runQr1, di1, &db_interactor::runQuery);
	connect(this, &mainThingy::runQr2, di2, &db_interactor::runQuery);
	connect(di1, &db_interactor::dataReady, this, &mainThingy::dataFrom1);
	connect(di2, &db_interactor::dataReady, this, &mainThingy::dataFrom2);

	connect(di1, &db_interactor::errorReturn, this, [this] (QString eS)
	{
		showErrReturn(eS, 1);
	});
	connect(di2, &db_interactor::errorReturn, this, [this] (QString eS)
	{
		showErrReturn(eS, 2);
	});

	interface();

	connect(&ui_timer, &QTimer::timeout, this, [this] ()
	{
		if (this->user_time)
		{
			interface();
		}
	});
	ui_timer.start(2000);
}

void mainThingy::dataFrom1(QJsonDocument response)
{
	qDebug () << response;
	user_time = true;
}

void mainThingy::dataFrom2(QJsonDocument response)
{
	qDebug () << response;
	user_time = true;
}

void mainThingy::showErrReturn(QString err, int thread)
{
	std::cout << "Error in " << thread << ": " << err.toStdString() << std::endl;
	qDebug () << "Err " << 1 << err;
	user_time = true;
}

void mainThingy::f_init1()
{
	qDebug () << "void mainThingy::f_init1()";
	emit init1();
}

void mainThingy::f_init2()
{
	qDebug () << "void mainThingy::f_init2()";
	emit init2();
}

void mainThingy::f_rq1()
{
	qDebug () << "void mainThingy::f_rq1()";
	emit runQr1();
}

void mainThingy::f_rq2()
{
	qDebug () << "void mainThingy::f_rq2()";
	emit runQr2();
}

void mainThingy::interface()
{
	qDebug () << "void mainThingy::interface()";
	std::cout << "Ready for command" << std::endl;
	std::string usrResp;
	std::cin >> usrResp;
	QString uR = QString::fromStdString(usrResp);
	if (uR == "i1")
	{
		f_init1();
		user_time = false;
	}
	else if (uR == "i2")
	{
		f_init2();
		user_time = false;
	}
	else if (uR == "q1")
	{
		f_rq1();
		user_time = false;
	}
	else if (uR == "q2")
	{
		f_rq2();
		user_time = false;
	}
	else if (uR == "quit")
	{
		exit (0);
	}
	else
	{
		std::cout << "?" << std::endl;
		qDebug () << "??";
	}
}
