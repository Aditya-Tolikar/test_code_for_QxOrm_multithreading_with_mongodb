#ifndef DB_INTERACTOR_H
#define DB_INTERACTOR_H

#include <QFile>
#include <QTextStream>

#include <QDebug>
#include <QJsonDocument>
#include <QObject>
#include <QxOrm.h>

class db_interactor : public QObject
{
	Q_OBJECT
public:
	explicit db_interactor(QObject *parent = nullptr);
	db_interactor(QString configFilename, QObject *parent = nullptr);

signals:

	void errorNoReturn (QString errString);
	void errorReturn (QString errString);
	void initComplete();
	void dataReady (QJsonDocument response);

public slots:
	void init();
	void runQuery();

private:
	bool inited = false;
	QHash<QString, QString> config;

	qx::QxSqlDatabase *db;
};

#endif // DB_INTERACTOR_H
