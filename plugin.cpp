#include "plugin.hpp"
#include "valuemapper.hpp"
#include "logvaluemapper.hpp"
#include "scalemap.hpp"
#include "linearscale.hpp"
#include "curve.hpp"
#include <QtDeclarative/qdeclarative.h>

void PlotComponentsPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<ValueMapper>(uri, 1, 0, "ValueMapper");
    qmlRegisterType<LogValueMapper>(uri, 1, 0, "LogValueMapper");
    qmlRegisterType<ScaleMap>(uri, 1, 0, "ScaleMap");
    qmlRegisterType<LinearScale>(uri, 1, 0, "LinearScale");
    qmlRegisterType<Curve>(uri, 1, 0, "Curve");
}

Q_EXPORT_PLUGIN2(plotcomponentsplugin, PlotComponentsPlugin)
