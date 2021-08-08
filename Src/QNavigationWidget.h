/****************************************************************
 * @file QNavigationWidget.h
 * @brief A completed implementation of QNavigationWidget.
 ***************************************************************/


#ifndef QNAVIGATIONWIDGET_H
#define QNAVIGATIONWIDGET_H

#include "QNavigationTab.h"
#include <QWidget>
#include <QStackedWidget>
#include <QHBoxLayout>

/**
 * @brief A completed implementation of QNavigationWidget.
 */
class QNavigationWidget : public QWidget
{
	Q_OBJECT
public:
	QNavigationWidget(QWidget* parent = 0);
	~QNavigationWidget();

	QNavigationTab* tabBar() const;
	int addTab(QWidget* page, const QString& item, const QString& toolTips = 0);
	int insertTab(const int index, QWidget* page, const QString& item, const QString& toolTips = 0);
	void setTabToolTip(const int index, const QString& toolTip);
	void setTabBackgroundColor(const QString& color);
	void setTabSelectedColor(const QString& color);
	void setTabRowHeight(const int height);
	void setTabWidth(const int width);
	void setTabText(const int index, const QString& text);
	void deleteTab(const int index);
	int getCurrentIndex() const;
	QWidget* getCurrentWidget() const;

private:
	QHBoxLayout* mainLayout;
	QStackedWidget* rightWidget;  ///< Shift the right widgets (Use StackedWidget)
	QNavigationTab* navigationTab;  
	
	QWidget* currentWidget;
	int currentIndex;

private slots:

	void changeTab(const int index);  // Shift the right widgets

signals:
/**
 * @brief The signal of the tab change event.
 * 
 * @param index The index of the tab.
 */
	void currentIndexChanged(const int index);

/**
 * @brief The signal of the tab change event.
 * 
 */
	void currentTabChanged();
};

#endif