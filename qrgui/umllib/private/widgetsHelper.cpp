#include "widgetsHelper.h"
#include "../nodeElement.h"
#include "../../elementEditor/widgetsEdit/widgetsEditor.h"
#include "../../../qrutils/xmlUtils.h"

WidgetsHelper::WidgetsHelper(NodeElement *element)
	: mElement(element), mWidget(NULL)
{
}

WidgetsHelper::~WidgetsHelper()
{
}

bool WidgetsHelper::initWidget(QString const &filename)
{
	QDomDocument const document = utils::xmlUtils::loadDocument(filename);
	if (document.isNull()) {
		return false;
	}
	mWidget = qReal::widgetsEdit::WidgetsEditor::deserializeWidget(document);
	if (!mWidget) {
		return false;
	}
	if (mElement) {
		initPropertyEditors();
		mElement->setWidget(mWidget);
	}
	return true;
}

QMap<QString, PropertyEditorInterface *> WidgetsHelper::propertyEditors() const
{
	return mPropertyEditors;
}

void WidgetsHelper::initPropertyEditors()
{
	mPropertyEditors.clear();
	if (mWidget) {
		initPropertyEditors(mWidget);
	}
}

void WidgetsHelper::initPropertyEditors(QWidget *widget)
{
	PropertyEditorInterface *iface =
			dynamic_cast<PropertyEditorInterface *>(widget);

	if (iface && !iface->binding().isEmpty()) {
		mPropertyEditors.insertMulti(iface->binding(), iface);
	}
	foreach (QObject *object, widget->children()) {
		QWidget *child = dynamic_cast<QWidget *>(object);
		if (child) {
			initPropertyEditors(child);
		}
	}
}

QWidget *WidgetsHelper::widget() const
{
	return mWidget;
}

WtfIconLoader::WtfIconLoader()
	: mHelper(new WidgetsHelper)
{
}

WtfIconLoader::~WtfIconLoader()
{
	delete mHelper;
}

WtfIconLoader *WtfIconLoader::instance()
{
	static WtfIconLoader instance;
	return &instance;
}

QPixmap WtfIconLoader::pixmapOf(const QString &fileName)
{
	if (!mLoadedIcons.contains(fileName)) {
		QPixmap pixmap;
		if (mHelper->initWidget(fileName)) {
			pixmap = QPixmap::grabWidget(mHelper->widget());
		}
		mLoadedIcons.insert(fileName, pixmap);
	}
	return mLoadedIcons[fileName];
}

WtfIconEngineV2::WtfIconEngineV2(const QString &fileName)
	: mPixmap(WtfIconLoader::instance()->pixmapOf(fileName))
{
}

void WtfIconEngineV2::paint(QPainter *painter, QRect const &rect
		, QIcon::Mode mode, QIcon::State state)
{
	// TODO: remove copy-past from SdfIconEngineV2
	Q_UNUSED(mode)
	Q_UNUSED(state)
	painter->eraseRect(rect);
	int const rh = rect.height();
	int const rw = rect.width();

	int const ph = mPixmap.height();
	int const pw = mPixmap.width();
	if (pw == 0 || ph == 0) { // SUDDENLY!!11
		return;
	}
	// Take picture aspect into account;
	QRect resRect = rect;
	if (rh * pw < ph * rw) {
		resRect.setLeft(rect.left() + (rw-rh*pw/ph)/2);
		resRect.setRight(rect.right() - (rw-rh*pw/ph)/2);
	}
	if (rh * pw > ph * rw) {
		resRect.setTop(rect.top() + (rh-rw*ph/pw)/2);
		resRect.setBottom(rect.bottom() - (rh-rw*ph/pw)/2);
	}
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->drawPixmap(resRect, mPixmap);
}