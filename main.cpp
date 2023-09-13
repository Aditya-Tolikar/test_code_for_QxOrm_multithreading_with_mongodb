#include <QCoreApplication>
#include <QxOrm.h>

#include "mainthingy.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	mainThingy mt;

	return a.exec();
}
