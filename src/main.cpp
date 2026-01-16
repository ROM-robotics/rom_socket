#include <QCoreApplication>
#include "ssl_server.h"
#include "wifi_tcp_server.h"
#include <locale.h>

int main(int argc, char *argv[])
{
    // Set C locale for MPV (required by libmpv)
    setlocale(LC_NUMERIC, "C");
    
    QCoreApplication app(argc, argv);
    
    // QCoreApplication may change locale, so set it again
    setlocale(LC_NUMERIC, "C");

    // Start SSL Server on port 8765 (any interface)
    SslServer server;
    
    if (!server.listen(QHostAddress::Any, 8765)) {
        qCritical() << "SSL Server could not start!";
        return 1;
    }

    qDebug() << "SSL Server is running on port 8765";

    // Start WiFi TCP Server on 10.0.0.1:7358 (no SSL)
    WiFiTcpServer wifiServer;
    
    if (!wifiServer.listen(QHostAddress("10.0.0.1"), 7358)) {
        qCritical() << "WiFi TCP Server could not start!";
        qCritical() << "Error:" << wifiServer.errorString();
        return 1;
    }

    qDebug() << "WiFi TCP Server is running on 10.0.0.1:7358 (no SSL)";

    return app.exec();
}
