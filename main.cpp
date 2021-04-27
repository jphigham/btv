#include <QApplication>

#include "Node.h"
#include "TreeWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    QStringList args = QApplication::arguments();

    TreeWindow w;
	w.show();
	return app.exec();
}
