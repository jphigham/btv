#include <QApplication>

#include "Node.h"
#include "TreeWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    QStringList args = QApplication::arguments();

    TreeWindow w;
	w.show();
    if (args.length() > 1)
        w.loadFile(args[1]);
#if 0
    else
        w.loadFile("test.json");
#endif

	return app.exec();
}
