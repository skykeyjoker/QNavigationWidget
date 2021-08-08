#include "QNavigationWidget.h"
//#include <QDebug>

QNavigationWidget::QNavigationWidget(QWidget* parent) : QWidget(parent)
{
	currentWidget = nullptr;
	mainLayout = new QHBoxLayout(this);
	rightWidget = new QStackedWidget;
	navigationTab = new QNavigationTab;
	currentIndex = 0;

	rightWidget->setFixedWidth(width() - navigationTab->width());
	rightWidget->setLineWidth(0);
	rightWidget->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred, QSizePolicy::TabWidget));
	
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->addWidget(navigationTab);
	mainLayout->addWidget(rightWidget);

	connect(navigationTab, &QNavigationTab::currentItemChange, [=](const int current)
	{
			changeTab(current);
	});
}

QNavigationTab* QNavigationWidget::tabBar() const
{
	return navigationTab;
}

int QNavigationWidget::addTab(QWidget* page, const QString& item, const QString& toolTip)
{
	return insertTab(-1, page, item, toolTip);
}

int QNavigationWidget::insertTab(const int index, QWidget* page, const QString& item, const QString& toolTip)
{
	//qDebug() << "Add Tab" << page->objectName() << item << toolTip;
	
	int ret = index;
	if(index!=-1)
	{
		rightWidget->insertWidget(index, page);
		navigationTab->insertItem(index, item, toolTip);
	}
	else
	{
		rightWidget->addWidget(page);
		navigationTab->addItem(item, toolTip);
		ret = rightWidget->count() - 1;
	}

	return ret;
}


void QNavigationWidget::setTabToolTip(const int index, const QString& toolTip)
{
	navigationTab->setItemToolTip(index, toolTip);
}

void QNavigationWidget::setTabBackgroundColor(const QString& color)
{
	navigationTab->setBackgroundColor(color);
}

void QNavigationWidget::setTabSelectedColor(const QString& color)
{
	navigationTab->setSelectedColor(color);
}

void QNavigationWidget::setTabRowHeight(const int height)
{
	navigationTab->setRowHeight(height);
}

void QNavigationWidget::setTabWidth(const int width)
{
	navigationTab->setWidth(width);
}

void QNavigationWidget::setTabText(const int index, const QString& text)
{
	navigationTab->setItemText(index, text);
}

void QNavigationWidget::deleteTab(const int index)
{
	if (index < rightWidget->count())
	{
		if (currentIndex == index)
		{
			currentIndex = 0;
		}
	
		navigationTab->deleteItem(index);
		QWidget* deleteWidget = rightWidget->widget(index);
		rightWidget->removeWidget(rightWidget->widget(index));
		deleteWidget->deleteLater();
	}
}

int QNavigationWidget::getCurrentIndex() const
{
	return currentIndex;
}

QWidget* QNavigationWidget::getCurrentWidget() const
{
	return currentWidget;
}

void QNavigationWidget::changeTab(const int index)
{
	rightWidget->setCurrentIndex(index);
	
	currentIndex = rightWidget->currentIndex();
	currentWidget = rightWidget->currentWidget();

	// Emit signals
	emit currentTabChanged();
	emit currentIndexChanged(currentIndex);
}

QNavigationWidget::~QNavigationWidget()
{
	
}
