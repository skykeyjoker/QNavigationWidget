#include "QNavigationWidgetTest.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QNavigationWidgetTest widget;
	widget.show();
	
	return app.exec();
}
