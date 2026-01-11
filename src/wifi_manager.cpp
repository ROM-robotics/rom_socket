#include "wifi_manager.h"
#include <QDebug>
#include <QRegularExpression>
#include <QThread>

WiFiManager::WiFiManager(QObject *parent) 
    : QObject(parent)
{
    qDebug() << "WiFiManager initialized";
}

WiFiManager::~WiFiManager()
{
    qDebug() << "WiFiManager destroyed";
}

// ==================== WiFi Scanning and Information ====================

QList<WiFiNetwork> WiFiManager::scanNetworks()
{
    qDebug() << "Scanning for WiFi networks...";
    
    // Rescan networks first
    bool rescanSuccess = false;
    executeCommand("nmcli", QStringList() << "device" << "wifi" << "rescan", &rescanSuccess);
    
    if (!rescanSuccess) {
        qWarning() << "WiFi rescan failed, using cached results";
    }
    
    // Small delay to allow scan to complete
    QThread::msleep(1000);
    
    // Get network list
    bool success = false;
    QString output = executeCommand("nmcli", 
        QStringList() << "-t" << "-f" << "IN-USE,SSID,BSSID,SIGNAL,SECURITY" << "device" << "wifi" << "list",
        &success);
    
    if (!success) {
        qWarning() << "Failed to get WiFi network list";
        return QList<WiFiNetwork>();
    }
    
    return parseNetworkList(output);
}

QString WiFiManager::getCurrentConnection()
{
    bool success = false;
    QString output = executeCommand("nmcli", 
        QStringList() << "-t" << "-f" << "NAME" << "connection" << "show" << "--active",
        &success);
    
    if (!success || output.isEmpty()) {
        return "Not connected";
    }
    
    // Return first active connection (usually WiFi)
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    return lines.isEmpty() ? "Not connected" : lines.first().trimmed();
}

bool WiFiManager::isWiFiEnabled()
{
    bool success = false;
    QString output = executeCommand("nmcli", 
        QStringList() << "radio" << "wifi",
        &success);
    
    if (!success) {
        return false;
    }
    
    return output.trimmed() == "enabled";
}

QString WiFiManager::getConnectionStatus()
{
    QString status;
    
    if (!isWiFiEnabled()) {
        status = "WiFi is disabled";
    } else {
        QString connection = getCurrentConnection();
        if (connection == "Not connected") {
            status = "WiFi enabled, not connected";
        } else {
            status = "Connected to: " + connection;
        }
    }
    
    return status;
}

// ==================== Connection Management ====================

bool WiFiManager::connectToNetwork(const QString &ssid, const QString &password)
{
    qDebug() << "Attempting to connect to:" << ssid;
    
    if (ssid.isEmpty()) {
        qWarning() << "SSID cannot be empty";
        emit errorOccurred("SSID cannot be empty");
        return false;
    }
    
    QStringList args;
    args << "device" << "wifi" << "connect" << ssid;
    
    if (!password.isEmpty()) {
        args << "password" << password;
    }
    
    bool success = false;
    QString output = executeCommand("nmcli", args, &success);
    
    if (success) {
        qDebug() << "Successfully connected to:" << ssid;
        emit connectionStatusChanged("Connected to: " + ssid);
        return true;
    } else {
        qWarning() << "Failed to connect to:" << ssid << "-" << output;
        emit errorOccurred("Failed to connect: " + output);
        return false;
    }
}

bool WiFiManager::disconnectFromNetwork()
{
    qDebug() << "Disconnecting from current network...";
    
    // Get current WiFi device name
    bool success = false;
    QString output = executeCommand("nmcli", 
        QStringList() << "-t" << "-f" << "DEVICE,TYPE" << "device",
        &success);
    
    if (!success) {
        qWarning() << "Failed to get device list";
        return false;
    }
    
    // Find WiFi device
    QString wifiDevice;
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    for (const QString &line : lines) {
        if (line.contains("wifi")) {
            wifiDevice = line.split(':').first();
            break;
        }
    }
    
    if (wifiDevice.isEmpty()) {
        qWarning() << "No WiFi device found";
        return false;
    }
    
    // Disconnect the device
    output = executeCommand("nmcli", 
        QStringList() << "device" << "disconnect" << wifiDevice,
        &success);
    
    if (success) {
        qDebug() << "Successfully disconnected from network";
        emit connectionStatusChanged("Disconnected");
        return true;
    } else {
        qWarning() << "Failed to disconnect:" << output;
        return false;
    }
}

bool WiFiManager::disconnectFromNetwork(const QString &ssid)
{
    qDebug() << "Disconnecting from network:" << ssid;
    
    bool success = false;
    QString output = executeCommand("nmcli", 
        QStringList() << "connection" << "down" << ssid,
        &success);
    
    if (success) {
        qDebug() << "Successfully disconnected from:" << ssid;
        emit connectionStatusChanged("Disconnected from: " + ssid);
        return true;
    } else {
        qWarning() << "Failed to disconnect from:" << ssid << "-" << output;
        return false;
    }
}

// ==================== Saved Connections ====================

QStringList WiFiManager::getSavedConnections()
{
    bool success = false;
    QString output = executeCommand("nmcli", 
        QStringList() << "-t" << "-f" << "NAME,TYPE" << "connection" << "show",
        &success);
    
    if (!success) {
        return QStringList();
    }
    
    QStringList savedConnections;
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    
    for (const QString &line : lines) {
        QStringList parts = line.split(':');
        if (parts.size() >= 2 && parts[1] == "802-11-wireless") {
            savedConnections << parts[0];
        }
    }
    
    return savedConnections;
}

bool WiFiManager::deleteSavedConnection(const QString &ssid)
{
    qDebug() << "Deleting saved connection:" << ssid;
    
    bool success = false;
    QString output = executeCommand("nmcli", 
        QStringList() << "connection" << "delete" << ssid,
        &success);
    
    if (success) {
        qDebug() << "Successfully deleted connection:" << ssid;
        return true;
    } else {
        qWarning() << "Failed to delete connection:" << ssid << "-" << output;
        return false;
    }
}

// ==================== WiFi Radio Control ====================

bool WiFiManager::enableWiFi()
{
    qDebug() << "Enabling WiFi...";
    
    bool success = false;
    executeCommand("nmcli", QStringList() << "radio" << "wifi" << "on", &success);
    
    if (success) {
        qDebug() << "WiFi enabled successfully";
        return true;
    } else {
        qWarning() << "Failed to enable WiFi";
        return false;
    }
}

bool WiFiManager::disableWiFi()
{
    qDebug() << "Disabling WiFi...";
    
    bool success = false;
    executeCommand("nmcli", QStringList() << "radio" << "wifi" << "off", &success);
    
    if (success) {
        qDebug() << "WiFi disabled successfully";
        return true;
    } else {
        qWarning() << "Failed to disable WiFi";
        return false;
    }
}

// ==================== Configuration ====================

bool WiFiManager::setAutoConnect(const QString &ssid, bool autoConnect)
{
    qDebug() << "Setting auto-connect for" << ssid << "to:" << autoConnect;
    
    QString value = autoConnect ? "yes" : "no";
    
    bool success = false;
    executeCommand("nmcli", 
        QStringList() << "connection" << "modify" << ssid << "connection.autoconnect" << value,
        &success);
    
    if (success) {
        qDebug() << "Auto-connect setting updated for:" << ssid;
        return true;
    } else {
        qWarning() << "Failed to update auto-connect setting for:" << ssid;
        return false;
    }
}

// ==================== Detailed Information ====================

QString WiFiManager::getNetworkDetails(const QString &ssid)
{
    bool success = false;
    QString output = executeCommand("nmcli", 
        QStringList() << "connection" << "show" << ssid,
        &success);
    
    if (!success) {
        return "Network not found or not saved";
    }
    
    return output;
}

// ==================== Helper Methods ====================

QString WiFiManager::executeCommand(const QString &command, const QStringList &arguments, bool *success)
{
    QProcess process;
    process.setProgram(command);
    process.setArguments(arguments);
    
    qDebug() << "Executing:" << command << arguments.join(" ");
    
    process.start();
    
    if (!process.waitForStarted(COMMAND_TIMEOUT)) {
        qCritical() << "Failed to start command:" << command;
        if (success) *success = false;
        return QString();
    }
    
    if (!process.waitForFinished(COMMAND_TIMEOUT)) {
        qCritical() << "Command timeout:" << command;
        process.kill();
        if (success) *success = false;
        return QString();
    }
    
    int exitCode = process.exitCode();
    QString output = QString::fromUtf8(process.readAllStandardOutput());
    QString errorOutput = QString::fromUtf8(process.readAllStandardError());
    
    if (exitCode != 0) {
        qWarning() << "Command failed with exit code:" << exitCode;
        qWarning() << "Error output:" << errorOutput;
        if (success) *success = false;
        return errorOutput.isEmpty() ? output : errorOutput;
    }
    
    if (success) *success = true;
    return output.trimmed();
}

QList<WiFiNetwork> WiFiManager::parseNetworkList(const QString &output)
{
    QList<WiFiNetwork> networks;
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    
    for (const QString &line : lines) {
        QStringList fields = line.split(':');
        
        if (fields.size() < 5) {
            continue; // Skip malformed lines
        }
        
        WiFiNetwork network;
        network.inUse = (fields[0] == "*");
        network.ssid = fields[1].trimmed();
        network.bssid = fields[2].trimmed();
        network.signal = parseSignalStrength(fields[3].trimmed());
        network.security = fields[4].trimmed();
        
        // Skip empty SSIDs (hidden networks)
        if (network.ssid.isEmpty()) {
            continue;
        }
        
        networks.append(network);
    }
    
    qDebug() << "Found" << networks.size() << "WiFi networks";
    return networks;
}

int WiFiManager::parseSignalStrength(const QString &signalStr)
{
    bool ok = false;
    int signal = signalStr.toInt(&ok);
    
    if (!ok || signal < 0 || signal > 100) {
        return 0;
    }
    
    return signal;
}
