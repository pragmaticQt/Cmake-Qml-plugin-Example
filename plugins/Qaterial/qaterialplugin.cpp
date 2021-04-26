#include "qaterialplugin.h"
#include "IconDescription.hpp"

#include <QtQml/QtQml>


using namespace qaterial;
void QaterialPlugin::registerTypes(const char* uri) {
    // Register our 'MyQuickItem' in qml engine
    qmlRegisterType<IconDescription>(uri, 1, 0, "IconDescription");
}
