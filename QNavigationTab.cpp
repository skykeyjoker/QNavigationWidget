#include "QNavigationTab.h"
#include <QPainter>
#include <QPainterPath>
#include <QToolTip>

QNavigationTab::QNavigationTab(QWidget* parent) : QWidget(parent)
{
	currentIndex = 0;
	backgroundColor = "#E4E4E4";
	selectedColor = "#2CA7F8";
	rowHeight = 40;

	setMouseTracking(true);
	setFixedWidth(150);
}

QNavigationTab::~QNavigationTab()
{
	
}

int QNavigationTab::addItem(const QString& item, const QString& toolTips)
{
	return insertItem(-1, item, toolTips);
}

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
		else
		{
			listItems << item;
			itemToolTips << toolTips;

			ret = listItems.size() - 1;
		}
	}

	update();  // Repaint

	return ret;
}


void QNavigationTab::setBackgroundColor(const QString& color)
{
	if (!color.isEmpty())
		backgroundColor = color;

	update();  // Repaint
}

void QNavigationTab::setSelectedColor(const QString& color)
{
	if (!color.isEmpty())
		selectedColor = color;

	update();  // Repaint
}

void QNavigationTab::setWidth(const int width)
{
	setFixedWidth(width);
}

void QNavigationTab::setRowHeight(const int height)
{
	if (rowHeight)
		rowHeight = height;

	update();  // Repaint
}

void QNavigationTab::setItemToolTip(const int index, const QString& itemToolTip)
{
	if (index < listItems.size())
	{
		itemToolTips[index] = itemToolTip;
	}
}

int QNavigationTab::getCurrentIndex() const
{
	return currentIndex;
}

void QNavigationTab::setItemText(const int index, const QString& text)
{
	if (index < listItems.size())
	{
		listItems[index] = text;

		update();  // Repaint
	}
}

void QNavigationTab::deleteItem(const int index)
{
	if (index < listItems.size())
	{
		if (index == currentIndex)
		{
			currentIndex = 0;
		}
		
		listItems.removeAt(index);
		itemToolTips.removeAt(index);

		update();  // Repaint
	}
}

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

void QNavigationTab::mousePressEvent(QMouseEvent* event)
{
	if(event->y() / rowHeight < listItems.count())
	{
		currentIndex = event->y() / rowHeight;

		emit(currentItemChange(currentIndex));

		update();  // Repaint
	}
}

void QNavigationTab::mouseReleaseEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
}

void QNavigationTab::mouseMoveEvent(QMouseEvent* event)
{
	if(event->y() / rowHeight < listItems.count())
	{
		// Do something here.
		int index = event->y() / rowHeight;
		QToolTip::showText(event->globalPos(), itemToolTips.at(index));
	}
}




