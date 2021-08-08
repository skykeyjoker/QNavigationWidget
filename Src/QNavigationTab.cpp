/****************************************************************
 * @file QNavigationTab.cpp
 * @brief A implementation of tabbar.
 * @author Skykey
 * @date 2021-8-8
 ****************************************************************/

#include "QNavigationTab.h"
#include <QPainter>
#include <QPainterPath>
#include <QToolTip>

/**
 * @brief Construct a new QNavigationTab::QNavigationTab object
 * 
 * @param parent trans parent to QWidget
 */
QNavigationTab::QNavigationTab(QWidget* parent) : QWidget(parent)
{
	currentIndex = 0;
	backgroundColor = "#E4E4E4";
	selectedColor = "#2CA7F8";
	rowHeight = 40;

	setMouseTracking(true);
	setFixedWidth(150);
}

/**
 * @brief Destroy the QNavigationTab::QNavigationTab object
 * 
 */
QNavigationTab::~QNavigationTab()
{
	
}

/**
 * @brief Add items to the navigation.
 * 
 * @param item The title of the item to be added.
 * @param toolTips The toolTip of the item to be added.
 * @return int Return the index of the item to be added.
 */
int QNavigationTab::addItem(const QString& item, const QString& toolTips)
{
	return insertItem(-1, item, toolTips);
}

/**
 * @brief Insert items to the navigation at the specified position.
 * 
 * @param index Give the index of the item to be inserted.
 * @param item The title of the item to be added.
 * @param toolTips The toolTip of the item to be added.
 * @return int Return the index of the item to be added.
 */
int QNavigationTab::insertItem(const int index, const QString& item, const QString& toolTips)
{
	int ret = index;
	if(!item.isEmpty())
	{
		if (index != -1)  
		{
			listItems.insert(index, item);
			itemToolTips.insert(index, toolTips);
		}
		else // Add
		{
			listItems << item;
			itemToolTips << toolTips;

			ret = listItems.size() - 1;
		}
	}

	update();  // Repaint

	return ret;
}

/**
 * @brief Set the background color of the navigation bar.
 * 
 * @param color A hex code of the color. Such as #000000.
 */
void QNavigationTab::setBackgroundColor(const QString& color)
{
	if (!color.isEmpty())
		backgroundColor = color;

	update();  // Repaint
}

/**
 * @brief Set the selectedColor of the navigation bar.
 * 
 * @param color A hex code of the color. Such as #000000.
 */
void QNavigationTab::setSelectedColor(const QString& color)
{
	if (!color.isEmpty())
		selectedColor = color;

	update();  // Repaint
}

/**
 * @brief Set the width of the items in the navigation bar.
 * 
 * @param width 
 */
void QNavigationTab::setWidth(const int width)
{
	setFixedWidth(width);
}

/**
 * @brief Set the height of the items in the navigation bar.
 * 
 * @param height 
 */
void QNavigationTab::setRowHeight(const int height)
{
	if (rowHeight)
		rowHeight = height;

	update();  // Repaint
}

/**
 * @brief Set the toolTip of the specified item in the navigation bar.
 * 
 * @param index The index of the specified item.
 * @param itemToolTip The toolTip of the specified item.
 */
void QNavigationTab::setItemToolTip(const int index, const QString& itemToolTip)
{
	if (index < listItems.size())
	{
		itemToolTips[index] = itemToolTip;
	}
}

/**
 * @brief Get the index of the current item.
 * 
 * @return int The inex of the current item.
 */
int QNavigationTab::getCurrentIndex() const
{
	return currentIndex;
}

/**
 * @brief Set the title of the specified item in the navigation bar.
 * 
 * @param index The index of the specified item.
 * @param text The title of the specified item.
 */
void QNavigationTab::setItemText(const int index, const QString& text)
{
	if (index < listItems.size())
	{
		listItems[index] = text;

		update();  // Repaint
	}
}

/**
 * @brief Delete a specified item in the navigation bar.
 * 
 * @param index The index of the specified item.
 */
void QNavigationTab::deleteItem(const int index)
{
	if (index < listItems.size())
	{
		// If the item to be deleted is current item
		if (index == currentIndex)
		{
			currentIndex = 0;  // Reset the currentIndex
		}
		
		listItems.removeAt(index);
		itemToolTips.removeAt(index);

		update();  // Repaint
	}
}

/**
 * @brief Main implementation. Draw the navigation bar.
 * 
 * @param event 
 */
void QNavigationTab::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);  // Antialiasing

	// Draw background
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(backgroundColor));
	painter.drawRect(rect());

	// Draw items
	int count = 0;
	for (const QString& item : listItems)
	{
		QPainterPath itemPath;
		// QRect(int x, int y, int width, int height)
		// Constructs a rectangle with (x, y) as its top-left corner and the given width and height.
		itemPath.addRect(QRect(0, count * rowHeight, width(), rowHeight));

		if(count == currentIndex)
		{
			painter.setPen(QColor("#FFFFFF"));
			painter.fillPath(itemPath, QColor(selectedColor));
		}
		else
		{
			painter.setPen(QColor("#202020"));
			painter.fillPath(itemPath, QColor(backgroundColor));
		}

		// Draw text
		painter.drawText(QRect(0, count*rowHeight, width(), rowHeight), 
			Qt::AlignVCenter | Qt::AlignHCenter, 
			item);
		
		++count;
	}
}

/**
 * @brief Change Item
 * 
 * @param event 
 */
void QNavigationTab::mousePressEvent(QMouseEvent* event)
{
	// Get the cursor position
	if(event->y() / rowHeight < listItems.count())
	{
		currentIndex = event->y() / rowHeight;

		emit(currentItemChange(currentIndex));

		update();  // Repaint
	}
}

/**
 * @brief 
 * 
 * @param event 
 */
void QNavigationTab::mouseReleaseEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
}

/**
 * @brief Show toolTips.
 * 
 * @param event 
 */
void QNavigationTab::mouseMoveEvent(QMouseEvent* event)
{
	if(event->y() / rowHeight < listItems.count())
	{
		// Do something here.
		int index = event->y() / rowHeight;
		QToolTip::showText(event->globalPos(), itemToolTips.at(index));
	}
}




