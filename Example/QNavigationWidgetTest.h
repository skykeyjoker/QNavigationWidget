#ifndef QNAVIGATIONWIDGETTEST_H
#define QNAVIGATIONWIDGETTEST_H

#include "QNavigationWidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QDebug>

class QNavigationWidgetTest : public QWidget
{
	Q_OBJECT

public:
	QNavigationWidgetTest(QWidget* parent = 0);
	~QNavigationWidgetTest();
};

#endif
