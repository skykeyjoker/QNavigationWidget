#include "QNavigationWidgetTest.h"
#include <QDebug>

QNavigationWidgetTest::QNavigationWidgetTest(QWidget* parent) : QWidget(parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);

	QNavigationWidget* navigationWidget = new QNavigationWidget;

	QWidget* dianaPage = new QWidget;
	QWidget* infoPage = new QWidget;
	QWidget* settingPage = new QWidget;

	navigationWidget->addTab(dianaPage, "嘉然", "嘉心糖");
	navigationWidget->addTab(infoPage, "信息", "这里是信息");
	navigationWidget->addTab(new QWidget(), "new", "new");
	navigationWidget->addTab(settingPage, "设置", "这里是设置");
	navigationWidget->deleteTab(2);

	QVBoxLayout* dianaLayout = new QVBoxLayout(dianaPage);
	dianaLayout->addWidget(new QLabel("DianaPage"));
	dianaLayout->addWidget(new QCheckBox("嘉心糖"));
	dianaLayout->addWidget(new QPushButton("不可思议"));

	QVBoxLayout* infoLayout = new QVBoxLayout(infoPage);
	infoLayout->addWidget(new QLabel("InfoPage"));
	infoLayout->addWidget(new QRadioButton("Radio Button"));

	QVBoxLayout* settingLayout = new QVBoxLayout(settingPage);
	settingLayout->addWidget(new QLabel("SettingPage"));

	mainLayout->addWidget(navigationWidget);

	connect(navigationWidget, &QNavigationWidget::currentTabChanged, [=]()
	{
			qDebug() << navigationWidget->getCurrentIndex();
			qDebug() << navigationWidget->getCurrentWidget();
	});
	
	
}

QNavigationWidgetTest::~QNavigationWidgetTest()
{
	
}

