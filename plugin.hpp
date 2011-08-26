#ifndef SG_PLOT_PLUGIN_H
#define SG_PLOT_PLUGIN_H

#include <QtDeclarative/QDeclarativeExtensionPlugin>

class PlotComponentsPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT

public:
    void registerTypes(const char *uri);
};

#endif // SG_PLOT_PLUGIN_H
