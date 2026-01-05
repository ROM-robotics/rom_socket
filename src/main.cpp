#include <QCoreApplication>
#include "ssl_server.h"
#include <locale.h>

int main(int argc, char *argv[])
{
    // Set C locale for MPV (required by libmpv)
    setlocale(LC_NUMERIC, "C");
    
    QCoreApplication app(argc, argv);
    
    // QCoreApplication may change locale, so set it again
    setlocale(LC_NUMERIC, "C");

    SslServer server;
    
    if (!server.listen(QHostAddress::Any, 8765)) {
        qCritical() << "Server could not start!";
        return 1;
    }

    qDebug() << "SSL Server is running on port 8765";

    return app.exec();
}
