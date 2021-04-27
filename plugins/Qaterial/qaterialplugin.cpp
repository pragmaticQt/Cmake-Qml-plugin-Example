#include "qaterialplugin.h"
#include "IconDescription.hpp"

#include <QtQml/QtQml>

void QaterialPlugin::registerTypes(const char* uri) {
    // Register our 'MyQuickItem' in qml engine
    qmlRegisterType<qaterial::IconDescription>(uri, 1, 0, "IconDescription");
}
