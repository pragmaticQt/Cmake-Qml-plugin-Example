#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "Qaterial/Logger.hpp"
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Create a stdout sink
    const auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    // Redirect qaterial to stdout
    qaterial::Logger::registerSink(stdoutSink);
    qaterial::Logger::registerSingleton("Qaterial.Logger");
    stdoutSink->set_level(spdlog::level::debug);
    qaterial::Logger::QATERIAL->set_level(spdlog::level::debug);

    // Add import search path
    engine.addImportPath("plugins");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
