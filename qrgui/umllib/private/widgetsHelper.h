#pragma once

#include <QtCore/QMap>
#include <QtGui/QPixmap>

#include "../nodeElement.h"
#include "../../editorPluginInterface/widgetsHelperInterface.h"
#include "../../editorPluginInterface/sdfRendererInterface.h"
#include "../../editorPluginInterface/propertyEditorInterface.h"


class WidgetsHelper : public WidgetsHelperInterface
{
public:
	explicit WidgetsHelper(NodeElement *element = 0);
	virtual ~WidgetsHelper();

	QWidget *widget() const;
	virtual bool initWidget(QString const &filename);
	QMap<QString, PropertyEditorInterface *> propertyEditors() const;

private:
	void initPropertyEditors();
	void initPropertyEditors(QWidget *widget);

	NodeElement *mElement;
	QWidget *mWidget;
	QMap<QString, PropertyEditorInterface *> mPropertyEditors;
};

class WtfIconEngineV2: public SdfIconEngineV2Interface
{
public:
	WtfIconEngineV2(QString const &fileName);
	virtual void paint(QPainter *painter, QRect const &rect, QIcon::Mode mode, QIcon::State state);

private:
	QPixmap mPixmap;
};

class WtfIconLoader
{
public:
	static WtfIconLoader *instance();
	/// Returns a pixmap of widget in specified wtf-file
	QPixmap pixmapOf(QString const &fileName);

private:
	WtfIconLoader();
	~WtfIconLoader();

	WidgetsHelper *mHelper;
	QMap<QString, QPixmap> mLoadedIcons;
};
