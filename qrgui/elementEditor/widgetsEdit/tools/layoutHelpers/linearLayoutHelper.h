#pragma once

#include <QtGui/QGraphicsLinearLayout>

#include "../layoutTool.h"
#include "layoutHelperBase.h"

namespace Ui
{
namespace WidgetsEdit
{

class LayoutHelperBase;
class LayoutTool;

class LinearLayoutHelper : public LayoutHelperBase
{
public:
	LinearLayoutHelper(LayoutTool *tool, Qt::Orientation const orientation);

	virtual void drawCurrentDropPosition(QPainter *painter);
	virtual void dropItem(Tool *item);

	virtual void resetLayout(QGraphicsLayout *layout);

	virtual void startChildDrag(Tool *item);
	virtual void finishChildDrag(bool success);

	virtual void generateAttachedProperty(QDomElement &element, Tool *tool);

protected:
	virtual void onToolResized(const QRectF &newGeometrry);

private:
	void insertItem(int index, Tool *item);
	int findTool(Tool *tool) const;

	LayoutTool *mTool;
	QGraphicsLinearLayout *mLayout;
	Qt::Orientation mOrientation;
	int mCurrentSell;

	Tool *mDraggedChild;
	int mDraggedChildOldSell;

};

}
}