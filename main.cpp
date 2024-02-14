
#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>

//#include "controlip.h"
#include "vmConfigs.h"
#include "ipAddr.h"
//#include "mbtcpClient.h"

int main(int argc, char *argv[])
{
    // Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.
    QApplication app(argc, argv);

    QQuickView viewer;
//    ControlIp* pCIP;
//    MbtcpClient tcpC;   //(pCIP);
    MbtcpClient mc;
    configs cs(&mc);
    vmConfigs vm(cs);
    //ControlIp controlIp;
//    pCIP = &controlIp;
    IpAddr ipAddr;

    //mbtcpClient tcpC2;

    QQmlContext *context = viewer.rootContext();
    context->setContextProperty("vmConfigs", &vm);
    context->setContextProperty("ipAddr", &ipAddr);
//    context->setContextProperty("tcpC", &tcpC);

    //context->setContextObject();

    // The following are needed to make examples run without having to install the module
    // in desktop environments.
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    viewer.engine()->addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(),
                                      QString::fromLatin1("qml")));
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    viewer.setTitle(QStringLiteral("QML Chart"));
    // /media/alex/Work/Alex-m/qtproj/qmlchart/main.qml
    viewer.setSource(QUrl("qrc:/main.qml"));
    //viewer.setSource(QUrl("../kmdelta6/main.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.show();
//    ipAddr.init();

    return app.exec();
}
