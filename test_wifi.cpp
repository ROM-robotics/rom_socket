#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include "src/ssl_client.h"

/**
 * @brief ROM Socket WiFi Test Client (C++)
 * 
 * Usage:
 *   ./test_wifi [host] [port]
 *   ./test_wifi localhost 8765
 *   ./test_wifi 192.168.1.100 8765
 */

class WiFiTestClient : public QObject
{
    Q_OBJECT

public:
    WiFiTestClient(const QString &host, quint16 port, QObject *parent = nullptr)
        : QObject(parent)
        , client_(new SslClient(this))
        , host_(host)
        , port_(port)
        , testStep_(0)
    {
        // Connect signals
        connect(client_, &SslClient::connected, this, &WiFiTestClient::onConnected);
        connect(client_, &SslClient::disconnected, this, &WiFiTestClient::onDisconnected);
        connect(client_, &SslClient::responseReceived, this, &WiFiTestClient::onResponse);
        connect(client_, &SslClient::connectionError, this, &WiFiTestClient::onError);
        
        // Ignore self-signed certificate errors for testing
        client_->setIgnoreSslErrors(true);
    }

    void start()
    {
        qDebug() << "Connecting to" << host_ << ":" << port_;
        client_->connectToServer(host_, port_);
    }

private slots:
    void onConnected()
    {
        qDebug() << "\n=== Connected to server ===\n";
        
        // Start test sequence
        testStep_ = 0;
        runNextTest();
    }

    void onDisconnected()
    {
        qDebug() << "\n=== Disconnected from server ===\n";
        QCoreApplication::quit();
    }

    void onResponse(const QString &response)
    {
        qDebug().noquote() << "\n--- Server Response ---";
        qDebug().noquote() << response;
        qDebug() << "------------------------\n";
        
        // Continue to next test after 2 seconds
        QTimer::singleShot(2000, this, &WiFiTestClient::runNextTest);
    }

    void onError(const QString &error)
    {
        qCritical() << "Error:" << error;
        QCoreApplication::quit();
    }

    void runNextTest()
    {
        testStep_++;
        
        switch (testStep_) {
            case 1:
                qDebug() << "\n>>> Test 1: WiFi Status စစ်ဆေးခြင်း";
                client_->sendCustomCommand("wifi_status");
                break;
                
            case 2:
                qDebug() << "\n>>> Test 2: WiFi Networks Scan လုပ်ခြင်း";
                client_->sendCustomCommand("wifi_scan");
                break;
                
            case 3:
                qDebug() << "\n>>> Test 3: Saved Networks ကြည့်ခြင်း";
                client_->sendCustomCommand("wifi_saved");
                break;
                
            case 4:
                qDebug() << "\n>>> Test 4: WiFi Status ပြန်စစ်ဆေးခြင်း";
                client_->sendCustomCommand("wifi_status");
                break;
                
            case 5:
                // Optional: Uncomment to test connection
                // WARNING: This will change your WiFi connection!
                /*
                qDebug() << "\n>>> Test 5: WiFi Network ချိတ်ဆက်ခြင်း";
                client_->sendCustomCommand("wifi_connect:YourSSID:YourPassword");
                break;
                */
                
                // Skip connection test
                qDebug() << "\n>>> Test 5: Skipped (connection test disabled)";
                QTimer::singleShot(100, this, &WiFiTestClient::runNextTest);
                break;
                
            case 6:
                qDebug() << "\n>>> All tests completed!";
                qDebug() << "\nDisconnecting in 2 seconds...";
                QTimer::singleShot(2000, [this]() {
                    client_->disconnectFromServer();
                });
                break;
                
            default:
                qDebug() << "\n>>> Test sequence complete";
                break;
        }
    }

private:
    SslClient *client_;
    QString host_;
    quint16 port_;
    int testStep_;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Parse command line arguments
    QString host = "localhost";
    quint16 port = 8765;

    if (argc >= 2) {
        host = argv[1];
    }
    if (argc >= 3) {
        bool ok;
        quint16 p = QString(argv[2]).toUShort(&ok);
        if (ok) {
            port = p;
        }
    }

    qDebug() << "==============================================";
    qDebug() << "  ROM Socket - WiFi Test Client (C++)";
    qDebug() << "  ROM-Robotics © 2026";
    qDebug() << "==============================================";
    qDebug() << "Server:" << host << ":" << port;
    qDebug() << "==============================================\n";

    WiFiTestClient testClient(host, port);
    testClient.start();

    return app.exec();
}

#include "test_wifi.moc"
