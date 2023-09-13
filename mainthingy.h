#ifndef MAINTHINGY_H
#define MAINTHINGY_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>

#include "db_interactor.h"

class mainThingy : public QObject
{
	Q_OBJECT

	QThread aFewThreads[2];
public:
	explicit mainThingy(QObject *parent = nullptr);

signals:
	void init1 ();
	void init2 ();

	void runQr1 ();
	void runQr2 ();

private slots:
	void dataFrom1 (QJsonDocument response);
	void dataFrom2 (QJsonDocument response);

	void showErrReturn (QString err, int thread);

private:
	db_interactor *di1, *di2;

	void f_init1();
	void f_init2();

	void f_rq1();
	void f_rq2();

	void interface();

	bool user_time = true;
	QTimer ui_timer;
};

#endif // MAINTHINGY_H
