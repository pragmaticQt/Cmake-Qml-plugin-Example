#ifndef QATERIAL_PLUGIN_H
#define QATERIAL_PLUGIN_H

#include <QQmlExtensionPlugin>

/**
 * @brief The QaterialPlugin class.
 */

class QaterialPlugin: public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Qaterial/1.0")
public:

    /**
     * @brief registerTypes Overrided function that should register all
     * C++ classes exported by this plugin.
     * @param uri           Plugin uri.
     */
    void registerTypes(const char* uri) override;
};

#endif // QATERIAL_PLUGIN_H
