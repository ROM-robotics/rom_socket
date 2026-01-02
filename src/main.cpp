#include <QCoreApplication>
#include "ssl_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    SslServer server;
    
    if (!server.listen(QHostAddress::Any, 8765)) {
        qCritical() << "Server could not start!";
        return 1;
    }

    qDebug() << "SSL Server is running on port 8765";

    return app.exec();
}
