/**********************************************************
 * @file QNavigationWidget.cpp
 * @brief A completed implementation of QNavigationWidget.
 * @author Skykey
 * @date 2021-8-8
 **********************************************************/

#include "QNavigationWidget.h"
//#include <QDebug>

/**
 * @brief Construct a new QNavigationWidget::QNavigationWidget object
 * 
 * @param parent Trans parent to QWidget
 */
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

/**
 * @brief Get the QNavigationTab of the QNavigationWidget.
 * 
 * @return QNavigationTab* The QNavigationTab of the QNavigationWidget.
 */
QNavigationTab* QNavigationWidget::tabBar() const
{
	return navigationTab;
}

/**
 * @brief Add the navigation tab to the navigation widget and return the index of the tab to be added.
 * 
 * @param page The QWidget of the navigation bar. It will be showed on the stacked area of the navigation bar.
 * @param item The title of the tab to be added.
 * @param toolTip The toolTip of the tab to be added.
 * @return int The index of the tab to be added.
 */
int QNavigationWidget::addTab(QWidget* page, const QString& item, const QString& toolTip)
{
	return insertTab(-1, page, item, toolTip);
}

/**
 * @brief Insert the navigation tab to the navigation widget and return the index of the tab to be added.
 * 
 * @param index The position of the tab to be inserted.
 * @param page The QWidget of the navigation bar. It will be showed on the stacked area of the navigation bar.
 * @param item The title of the tab to be added.
 * @param toolTip The toolTip of the tab to be added.
 * @return int The index of the tab to be added.
 */
int QNavigationWidget::insertTab(const int index, QWidget* page, const QString& item, const QString& toolTip)
{
	//qDebug() << "Add Tab" << page->objectName() << item << toolTip;
	
	int ret = index;
	if(index!=-1)  
	{
		rightWidget->insertWidget(index, page);
		navigationTab->insertItem(index, item, toolTip);
	}
	else // Add
	{
		rightWidget->addWidget(page);
		navigationTab->addItem(item, toolTip);
		ret = rightWidget->count() - 1;
	}

	return ret;
}

/**
 * @brief Set the toolTip of the specified tab.
 * 
 * @param index The index of the tab.
 * @param toolTip The toolTip of the tab.
 */
void QNavigationWidget::setTabToolTip(const int index, const QString& toolTip)
{
	navigationTab->setItemToolTip(index, toolTip);
}

/**
 * @brief Set the backgroundColor of the tabbar.
 * 
 * @param color A hex code of the color. Such as #000000.
 */
void QNavigationWidget::setTabBackgroundColor(const QString& color)
{
	navigationTab->setBackgroundColor(color);
}

/**
 * @brief Set the selectedColor of the tabbar.
 * 
 * @param color A hex code of the color. Such as #000000.
 */
void QNavigationWidget::setTabSelectedColor(const QString& color)
{
	navigationTab->setSelectedColor(color);
}

/**
 * @brief Set the row height of the tabbar.
 * 
 * @param height 
 */
void QNavigationWidget::setTabRowHeight(const int height)
{
	navigationTab->setRowHeight(height);
}

/**
 * @brief Set the tab width of the tabbar.
 * 
 * @param width 
 */
void QNavigationWidget::setTabWidth(const int width)
{
	navigationTab->setWidth(width);
}

/**
 * @brief Set the title of the specified tab.
 * 
 * @param index The index of the tab.
 * @param text The titles of the tab.
 */
void QNavigationWidget::setTabText(const int index, const QString& text)
{
	navigationTab->setItemText(index, text);
}

/**
 * @brief Delete a specified tab.
 * 
 * @param index The index of the tab to be deleted.
 */
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

/**
 * @brief Get the index of the current tab.
 * 
 * @return int The index of the current tab.
 */
int QNavigationWidget::getCurrentIndex() const
{
	return currentIndex;
}

/**
 * @brief Get the current widget shown on the stacked area.
 * 
 * @return QWidget* The current widget.
 */
QWidget* QNavigationWidget::getCurrentWidget() const
{
	return currentWidget;
}

/**
 * @brief The slot function to be called when tab is clicked.
 * 
 * @param index The index of the tab clicked.
 */
void QNavigationWidget::changeTab(const int index)
{
	rightWidget->setCurrentIndex(index);
	
	currentIndex = rightWidget->currentIndex();
	currentWidget = rightWidget->currentWidget();

	// Emit signals
	emit currentTabChanged();
	emit currentIndexChanged(currentIndex);
}

/**
 * @brief Destroy the QNavigationWidget::QNavigationWidget object
 * 
 */
QNavigationWidget::~QNavigationWidget()
{
	
}
