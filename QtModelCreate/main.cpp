#include "QtModelCreate.h"
#include <QtWidgets/QApplication>

QtModelCreate *w;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	w = new QtModelCreate;
	w->show();
	return a.exec();
}
