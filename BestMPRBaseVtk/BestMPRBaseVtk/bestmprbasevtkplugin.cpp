#include "bestmprbasevtk.h"
#include "bestmprbasevtkplugin.h"

#include <QtPlugin>

BestMPRBaseVtkPlugin::BestMPRBaseVtkPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void BestMPRBaseVtkPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BestMPRBaseVtkPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BestMPRBaseVtkPlugin::createWidget(QWidget *parent)
{
    return new BestMPRBaseVtk(parent);
}

QString BestMPRBaseVtkPlugin::name() const
{
    return QLatin1String("BestMPRBaseVtk");
}

QString BestMPRBaseVtkPlugin::group() const
{
    return QLatin1String("");
}

QIcon BestMPRBaseVtkPlugin::icon() const
{
    return QIcon();
}

QString BestMPRBaseVtkPlugin::toolTip() const
{
    return QLatin1String("");
}

QString BestMPRBaseVtkPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool BestMPRBaseVtkPlugin::isContainer() const
{
    return false;
}

QString BestMPRBaseVtkPlugin::domXml() const
{
    return QLatin1String("<widget class=\"BestMPRBaseVtk\" name=\"bestMPRBaseVtk\">\n</widget>\n");
}

QString BestMPRBaseVtkPlugin::includeFile() const
{
    return QLatin1String("bestmprbasevtk.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(bestmprbasevtkplugin, BestMPRBaseVtkPlugin)
#endif // QT_VERSION < 0x050000
