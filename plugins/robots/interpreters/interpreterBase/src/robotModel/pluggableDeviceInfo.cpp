#include <interpreterBase/robotModel/pluggableDeviceInfo.h>

#include <QtCore/QStringList>

#include <qrkernel/exception/exception.h>

using namespace interpreterBase::robotModel;

QMap<QString, PluggableDeviceInfo> PluggableDeviceInfo::mCreatedInfos = QMap<QString, PluggableDeviceInfo>();

PluggableDeviceInfo::PluggableDeviceInfo()
	: mDeviceType(nullptr)
{
}

PluggableDeviceInfo::PluggableDeviceInfo(QMetaObject const *deviceType, QString const &friendlyName)
	: mDeviceType(deviceType)
	, mFriendlyName(friendlyName)
{
}

bool PluggableDeviceInfo::isA(PluggableDeviceInfo const &parent) const
{
	QMetaObject const *currentParent = mDeviceType;
	while (currentParent && QString(parent.mDeviceType->className()) != QString(currentParent->className())) {
		currentParent = currentParent->superClass();
	}

	return currentParent != nullptr;
}

QString PluggableDeviceInfo::friendlyName() const
{
	return mFriendlyName;
}

bool PluggableDeviceInfo::isNull() const
{
	return mDeviceType == nullptr;
}

QString PluggableDeviceInfo::toString() const
{
	return QString(mDeviceType ? mDeviceType->className() : QString());
}

PluggableDeviceInfo PluggableDeviceInfo::fromString(QString const &string)
{
	if (string.isEmpty()) {
		return PluggableDeviceInfo();
	}

	if (!mCreatedInfos.contains(string)) {
		throw qReal::Exception(QString("QMetaObject for %1 not found").arg(string));
	}

	return mCreatedInfos[string];
}