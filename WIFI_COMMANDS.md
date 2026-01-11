# WiFi Configuration Commands

This document describes all WiFi-related commands available in the ROM Socket server.

## Overview

The WiFi management system uses NetworkManager (`nmcli`) to control WiFi connections on the robot. All commands are sent through the SSL socket connection with the `COMMAND` packet type.

## Prerequisites

- NetworkManager must be installed and running on the system
- User must have appropriate permissions to manage network connections (may require sudo/root for some operations)
- WiFi hardware must be present and functional

## Command Format

All WiFi commands follow this format:
```
Packet Type: COMMAND
Command Format: wifi_<action>[:parameters]
```

---

## Available Commands

### 1. **Scan WiFi Networks**
```
Command: wifi_scan
```

**Description:** Scans for available WiFi networks in range and returns a formatted list.

**Response Format:**
```
WiFi Networks:
================================================================================
SSID                           BSSID                Signal   Security        Active
--------------------------------------------------------------------------------
MyHomeWiFi                     AA:BB:CC:DD:EE:FF      85%    WPA2            Yes
OfficeNetwork                  11:22:33:44:55:66      72%    WPA2-Enterprise No
GuestNetwork                   99:88:77:66:55:44      45%    Open            No
================================================================================
Total: 3 networks
```

**Example Usage (Client):**
```cpp
client.sendCustomCommand("wifi_scan");
```

---

### 2. **Get WiFi Status**
```
Command: wifi_status
```

**Description:** Returns current WiFi connection status including radio state and connected network.

**Response Format:**
```
WiFi Status:
==================================================
WiFi Radio:        Enabled
Current Network:   MyHomeWiFi
Status:            Connected to: MyHomeWiFi
==================================================
```

**Example Usage:**
```cpp
client.sendCustomCommand("wifi_status");
```

---

### 3. **Connect to WiFi Network**
```
Command: wifi_connect:SSID:PASSWORD
Command: wifi_connect:SSID          (for open networks)
```

**Description:** Connects to a specified WiFi network with optional password.

**Parameters:**
- `SSID`: Network name (required)
- `PASSWORD`: Network password (optional, for secured networks)

**Response:**
- Success: `"Successfully connected to: <SSID>"`
- Failure: `"Failed to connect to: <SSID>"`

**Example Usage:**
```cpp
// Connect to secured network
client.sendCustomCommand("wifi_connect:MyHomeWiFi:mypassword123");

// Connect to open network
client.sendCustomCommand("wifi_connect:GuestNetwork");
```

**Notes:**
- Password should not contain colon (`:`) characters
- Connection is saved automatically for future use
- Auto-connect is enabled by default

---

### 4. **Disconnect from WiFi**
```
Command: wifi_disconnect
```

**Description:** Disconnects from the currently connected WiFi network.

**Response:**
- Success: `"Successfully disconnected from WiFi"`
- Failure: `"Failed to disconnect from WiFi"`

**Example Usage:**
```cpp
client.sendCustomCommand("wifi_disconnect");
```

---

### 5. **List Saved Networks**
```
Command: wifi_saved
```

**Description:** Lists all saved (previously connected) WiFi networks.

**Response Format:**
```
Saved WiFi Networks:
==================================================
1. MyHomeWiFi
2. OfficeNetwork
3. CafeWiFi
==================================================
Total: 3 saved networks
```

**Example Usage:**
```cpp
client.sendCustomCommand("wifi_saved");
```

---

### 6. **Delete Saved Network**
```
Command: wifi_delete:SSID
```

**Description:** Removes a saved WiFi network connection profile.

**Parameters:**
- `SSID`: Name of the saved network to delete

**Response:**
- Success: `"Successfully deleted saved connection: <SSID>"`
- Failure: `"Failed to delete connection: <SSID>"`

**Example Usage:**
```cpp
client.sendCustomCommand("wifi_delete:OldNetwork");
```

**Notes:**
- This does not disconnect if currently connected
- The network can be reconnected later, but will require password again

---

### 7. **Enable WiFi Radio**
```
Command: wifi_enable
```

**Description:** Turns on the WiFi radio hardware.

**Response:**
- Success: `"WiFi radio enabled successfully"`
- Failure: `"Failed to enable WiFi radio"`

**Example Usage:**
```cpp
client.sendCustomCommand("wifi_enable");
```

---

### 8. **Disable WiFi Radio**
```
Command: wifi_disable
```

**Description:** Turns off the WiFi radio hardware (disconnects from any network).

**Response:**
- Success: `"WiFi radio disabled successfully"`
- Failure: `"Failed to disable WiFi radio"`

**Example Usage:**
```cpp
client.sendCustomCommand("wifi_disable");
```

**Warning:** This will disconnect from all networks and disable WiFi completely.

---

## Error Handling

### Common Error Messages

1. **"Error: WiFi Manager not initialized"**
   - The WiFi management system failed to start
   - Check if NetworkManager is installed

2. **"No networks found or WiFi is disabled"**
   - WiFi radio might be disabled
   - No networks in range
   - WiFi hardware issue

3. **"Error: Invalid format"**
   - Command syntax is incorrect
   - Check parameter format

4. **"Unknown WiFi command"**
   - Command not recognized
   - Check spelling and format

### Troubleshooting

**WiFi commands not working:**
```bash
# Check if NetworkManager is running
sudo systemctl status NetworkManager

# Check WiFi device status
nmcli device status

# Check if WiFi is enabled
nmcli radio wifi
```

**Permission issues:**
- Some commands may require root/sudo privileges
- Consider adding user to `netdev` group: `sudo usermod -aG netdev $USER`

---

## Implementation Details

### Architecture

```
SslServer
    └── WiFiManager
            └── QProcess (executes nmcli commands)
```

### Thread Safety

- All WiFi operations are synchronous
- Commands execute within the server's event loop
- QProcess operations have a 10-second timeout

### Files

- `src/wifi_manager.h` - WiFiManager class declaration
- `src/wifi_manager.cpp` - WiFiManager implementation
- `src/ssl_server.h` - Server with WiFi command handling
- `src/ssl_server.cpp` - WiFi command routing and formatting

---

## Example Client Session

```cpp
#include "ssl_client.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    SslClient client;
    
    // Connect response handler
    QObject::connect(&client, &SslClient::responseReceived, 
        [](const QString &response) {
            qDebug() << "Server response:" << response;
        });
    
    // Connect to server
    client.setIgnoreSslErrors(true);
    client.connectToServer("192.168.1.100", 8765);
    
    // Wait for connection...
    QObject::connect(&client, &SslClient::connected, [&]() {
        // Check current status
        client.sendCustomCommand("wifi_status");
        
        // Scan for networks
        QTimer::singleShot(2000, [&]() {
            client.sendCustomCommand("wifi_scan");
        });
        
        // Connect to network
        QTimer::singleShot(4000, [&]() {
            client.sendCustomCommand("wifi_connect:MyHomeWiFi:password123");
        });
    });
    
    return app.exec();
}
```

---

## Security Considerations

1. **Password Transmission:** Passwords are sent over SSL/TLS encrypted connection
2. **Saved Credentials:** NetworkManager stores passwords encrypted on the system
3. **Access Control:** Consider implementing authentication before allowing WiFi changes
4. **Logging:** WiFi passwords are logged by Qt's debug output - disable in production

---

## Future Enhancements

Potential features for future versions:

- [ ] WiFi network priority management
- [ ] Hidden network connection support
- [ ] Advanced security settings (WPA3, Enterprise)
- [ ] Network speed test
- [ ] WiFi hotspot/AP mode
- [ ] Multiple adapter support
- [ ] Connection quality monitoring
- [ ] Automatic reconnection on disconnect

---

## Testing

### Manual Testing

```bash
# Build and run server
cd build
cmake .. && make
./rom_socket

# In another terminal, use netcat or custom client to send commands
```

### Test Commands Sequence

1. `wifi_status` - Check initial state
2. `wifi_scan` - Verify network detection
3. `wifi_saved` - Check existing connections
4. `wifi_connect:TestNetwork:password` - Test connection
5. `wifi_status` - Verify connection
6. `wifi_disconnect` - Test disconnection
7. `wifi_delete:TestNetwork` - Clean up test connection

---

## API Integration Example

For ROS 2 integration:

```cpp
// In your ROS 2 node
void WiFiControlNode::changeNetwork(const std::string& ssid, const std::string& password)
{
    std::string command = "wifi_connect:" + ssid + ":" + password;
    ssl_client_->sendCustomCommand(QString::fromStdString(command));
}

void WiFiControlNode::onResponseReceived(const QString& response)
{
    // Publish response to ROS 2 topic
    std_msgs::msg::String msg;
    msg.data = response.toStdString();
    wifi_status_publisher_->publish(msg);
}
```

---

## License

This WiFi management system is part of the ROM Socket project.
Copyright © 2026 ROM-Robotics
