/****************************************************************
 * @file QNavigationWidget.h
 * @brief A implementation of tabbar.
 ****************************************************************/

#ifndef QNAVIGATIONTAB_H
#define QNAVIGATIONTAB_H

#include <QWidget>
#include <QMouseEvent>

/**
 * @brief A implementation of tabbar.
 */
class QNavigationTab : public QWidget
{
	Q_OBJECT
public:
	QNavigationTab(QWidget* parent = 0);
	~QNavigationTab();

	int addItem(const QString& item, const QString& toolTips = 0);
	int insertItem(const int index, const QString& item, const QString& toolTips = 0);
	void setItemToolTip(const int index, const QString& toolTip);
	void setBackgroundColor(const QString& color);
	void setSelectedColor(const QString& color);
	void setRowHeight(const int height);
	void setWidth(const int width);
	void setItemText(const int index, const QString& text);
	void deleteItem(const int index);
	int getCurrentIndex() const;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	QList<QString> listItems;
	QList<QString> itemToolTips;
	QString backgroundColor;
	QString selectedColor;
	int rowHeight;
	int currentIndex;

signals:
	/**
	 * @brief The signal of item selection change.
	 * 
	 * @param index The index of the current item.
	 */
	void currentItemChange(const int index);
};


#endif
