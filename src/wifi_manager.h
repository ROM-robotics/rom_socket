#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QMap>

/**
 * @brief WiFi network information structure
 */
struct WiFiNetwork {
    QString ssid;           // Network name
    QString bssid;          // MAC address
    int signal;             // Signal strength (0-100)
    QString security;       // Security type (WPA2, WPA3, Open, etc.)
    bool inUse;             // Currently connected to this network
    
    QString toString() const {
        return QString("SSID: %1, Signal: %2%, Security: %3, Active: %4")
            .arg(ssid)
            .arg(signal)
            .arg(security)
            .arg(inUse ? "Yes" : "No");
    }
};

/**
 * @brief WiFi Manager class for managing WiFi connections
 * 
 * This class provides WiFi management functionality using NetworkManager (nmcli)
 * Thread-safe operations with synchronous command execution
 */
class WiFiManager : public QObject
{
    Q_OBJECT

public:
    explicit WiFiManager(QObject *parent = nullptr);
    ~WiFiManager();

    // WiFi scanning and information
    QList<WiFiNetwork> scanNetworks();
    QString getCurrentConnection();
    bool isWiFiEnabled();
    QString getConnectionStatus();
    
    // Connection management
    bool connectToNetwork(const QString &ssid, const QString &password);
    bool disconnectFromNetwork();
    bool disconnectFromNetwork(const QString &ssid);
    
    // Saved connections
    QStringList getSavedConnections();
    bool deleteSavedConnection(const QString &ssid);
    
    // WiFi radio control
    bool enableWiFi();
    bool disableWiFi();
    
    // Configuration
    bool setAutoConnect(const QString &ssid, bool autoConnect);
    
    // Get detailed info
    QString getNetworkDetails(const QString &ssid);

signals:
    void scanCompleted(const QList<WiFiNetwork> &networks);
    void connectionStatusChanged(const QString &status);
    void errorOccurred(const QString &error);

private:
    // Helper methods
    QString executeCommand(const QString &command, const QStringList &arguments, bool *success = nullptr);
    QList<WiFiNetwork> parseNetworkList(const QString &output);
    int parseSignalStrength(const QString &signalStr);
    
    // Command timeout (ms)
    static const int COMMAND_TIMEOUT = 10000;
};

#endif // WIFI_MANAGER_H
