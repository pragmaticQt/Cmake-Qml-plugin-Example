#include "qaterialplugin.h"
#include "Qaterial/IconDescription.hpp"

#include <QtQml/QtQml>

void QaterialPlugin::registerTypes(const char* uri) {

    Q_ASSERT(uri == QLatin1String("Qaterial"));

    qaterial::IconDescription::registerToQml();
}
