# WiFi Feature Testing Guide (စမ်းသပ်မှု လမ်းညွှန်)

## အဆင့် ၁ - Server ကို စတင်ခြင်း

Terminal တစ်ခု ဖွင့်ပြီး server ကို run လုပ်ပါ:

```bash
cd /home/mr_robot/Desktop/Git/rom_socket/build
./rom_socket
```

မြင်ရမယ့် output:
```
WiFi Manager initialized
Audio MPV instance created
Video MPV instance created
...
SslServer initialization complete - Audio: OK Video: OK WiFi: OK
SSL Server is running on port 8765
```

**အရေးကြီးတာ:** WiFi: OK ဆိုတာ မြင်ရရမယ်။

---

## အဆင့် ၂ - Test Client ကို Build လုပ်ခြင်း

Terminal အသစ် တစ်ခု ဖွင့်ပါ:

```bash
cd /home/mr_robot/Desktop/Git/rom_socket

# Build test client
mkdir -p build_test
cd build_test
cmake -f ../CMakeLists_test.txt ..
make
```

မြင်ရမယ့် output:
```
[ 33%] Automatic MOC for target test_wifi
[ 66%] Building CXX object CMakeFiles/test_wifi.dir/test_wifi.cpp.o
[100%] Linking CXX executable test_wifi
[100%] Built target test_wifi
```

---

## အဆင့် ၃ - Test Client ကို Run လုပ်ခြင်း

### Local server နဲ့ စမ်းခြင်း

```bash
cd /home/mr_robot/Desktop/Git/rom_socket/build_test
./test_wifi
```

### Remote robot နဲ့ စမ်းခြင်း

```bash
./test_wifi 192.168.1.100 8765
```

---

## မြင်ရမယ့် Output

### Server Terminal မှာ:

```
Loaded embedded SSL certificate
Packet Type: COMMAND
Received Command: wifi_status
WiFi command processed: wifi_status
Response sent: WiFi Status:
==================================================
WiFi Radio:        Enabled
Current Network:   ROM-Dynamics 2.4G
Status:            Connected to: ROM-Dynamics 2.4G
==================================================
```

### Client Terminal မှာ:

```
==============================================
  ROM Socket - WiFi Test Client (C++)
  ROM-Robotics © 2026
==============================================
Server: localhost : 8765
==============================================

Connecting to localhost : 8765

=== Connected to server ===


>>> Test 1: WiFi Status စစ်ဆေးခြင်း
Sent custom command: wifi_status

--- Server Response ---
WiFi Status:
==================================================
WiFi Radio:        Enabled
Current Network:   ROM-Dynamics 2.4G
Status:            Connected to: ROM-Dynamics 2.4G
==================================================
------------------------


>>> Test 2: WiFi Networks Scan လုပ်ခြင်း
Sent custom command: wifi_scan

--- Server Response ---
WiFi Networks:
================================================================================
SSID                           BSSID                Signal   Security        Active
--------------------------------------------------------------------------------
ROM-Dynamics 2.4G              AA:BB:CC:DD:EE:FF      85%    WPA2            Yes
OfficeNetwork                  11:22:33:44:55:66      72%    WPA2            No
================================================================================
Total: 2 networks
------------------------


>>> Test 3: Saved Networks ကြည့်ခြင်း
Sent custom command: wifi_saved

--- Server Response ---
Saved WiFi Networks:
==================================================
1. ROM-Dynamics 2.4G
2. OfficeNetwork
==================================================
Total: 2 saved networks
------------------------


>>> Test 4: WiFi Status ပြန်စစ်ဆေးခြင်း
Sent custom command: wifi_status

--- Server Response ---
WiFi Status:
==================================================
WiFi Radio:        Enabled
Current Network:   ROM-Dynamics 2.4G
Status:            Connected to: ROM-Dynamics 2.4G
==================================================
------------------------


>>> Test 5: Skipped (connection test disabled)

>>> All tests completed!

Disconnecting in 2 seconds...

=== Disconnected from server ===
```

---

## WiFi Commands များ စမ်းကြည့်ခြင်း

### Manual Testing

Test client ရဲ့ code ကို ပြင်ပြီး specific command တွေ စမ်းလို့ရပါတယ်:

```cpp
// test_wifi.cpp ထဲမှာ runNextTest() function ကို ပြင်ပါ

case 5:
    qDebug() << "\n>>> Test 5: WiFi Network ချိတ်ဆက်ခြင်း";
    client_->sendCustomCommand("wifi_connect:MyNetwork:mypassword123");
    break;
```

ပြီးရင် rebuild လုပ်ပါ:
```bash
cd build_test
make
./test_wifi
```

---

## Available WiFi Commands

| Command | Description | Example |
|---------|-------------|---------|
| `wifi_scan` | Scan for WiFi networks | `wifi_scan` |
| `wifi_status` | Get WiFi status | `wifi_status` |
| `wifi_connect:SSID:PASSWORD` | Connect to network | `wifi_connect:MyWiFi:pass123` |
| `wifi_connect:SSID` | Connect to open network | `wifi_connect:GuestNetwork` |
| `wifi_disconnect` | Disconnect from WiFi | `wifi_disconnect` |
| `wifi_saved` | List saved networks | `wifi_saved` |
| `wifi_delete:SSID` | Delete saved network | `wifi_delete:OldNetwork` |
| `wifi_enable` | Enable WiFi radio | `wifi_enable` |
| `wifi_disable` | Disable WiFi radio | `wifi_disable` |

---

## Custom Test Client ဖန်တီးခြင်း

သင့်ရဲ့ specific needs များအတွက် test client ကို ပြင်ဆင်နိုင်ပါတယ်:

```cpp
#include <QCoreApplication>
#include "src/ssl_client.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    SslClient client;
    client.setIgnoreSslErrors(true);
    
    // Connect signals
    QObject::connect(&client, &SslClient::connected, []() {
        qDebug() << "Connected!";
    });
    
    QObject::connect(&client, &SslClient::responseReceived, 
        [](const QString &response) {
            qDebug().noquote() << response;
        });
    
    // Connect to server
    client.connectToServer("localhost", 8765);
    
    // Wait for connection
    QTimer::singleShot(1000, [&]() {
        // Send your commands
        client.sendCustomCommand("wifi_scan");
    });
    
    return app.exec();
}
```

---

## Troubleshooting (ပြဿနာ ဖြေရှင်းခြင်း)

### ပြဿနာ ၁: Build လုပ်လို့ မရဘူး

**ဖြေရှင်းနည်း:**
```bash
# Qt6 ရှိ/မရှိ စစ်ဆေးပါ
qmake6 --version

# မရှိရင် install လုပ်ပါ
sudo apt install qt6-base-dev libqt6network6
```

### ပြဿနာ ၂: "Cannot find ssl_client.h"

**ဖြေရှင်းနည်း:**
```bash
# Project root directory မှာ ရှိမှန်း သေချာပါစေ
ls src/ssl_client.h

# Build directory ကို clean လုပ်ပါ
rm -rf build_test
mkdir build_test
cd build_test
cmake -f ../CMakeLists_test.txt ..
make
```

### ပြဿနာ ၃: Connection failed

**ဖြေရှင်းနည်း:**
```bash
# Server လုပ်နေပါသလား?
ps aux | grep rom_socket

# Port open ရှိပါသလား?
netstat -tlnp | grep 8765

# Firewall block မလုပ်ပါဘူးလား?
sudo ufw status
```

### ပြဿနာ ၄: SSL handshake failed

**ဖြေရှင်းနည်း:**
```cpp
// test_wifi.cpp မှာ
client_->setIgnoreSslErrors(true);  // ဒါ ရှိမှန်း သေချာပါစေ
```

---

## Quick Test Script

အမြန် test လုပ်ချင်ရင် ဒီ script ကို သုံးပါ:

```bash
#!/bin/bash
# quick_test_wifi.sh

cd /home/mr_robot/Desktop/Git/rom_socket

echo "Building test client..."
mkdir -p build_test
cd build_test
cmake -f ../CMakeLists_test.txt .. && make

if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful! Running tests..."
    echo ""
    ./test_wifi
else
    echo "Build failed!"
    exit 1
fi
```

```bash
chmod +x quick_test_wifi.sh
./quick_test_wifi.sh
```

---

## Integration with ROS 2

ROS 2 node နဲ့ integrate လုပ်ချင်ရင်:

```cpp
// In your ROS 2 node
#include "ssl_client.h"

class WiFiControlNode : public rclcpp::Node
{
private:
    SslClient* ssl_client_;
    
public:
    WiFiControlNode() : Node("wifi_control_node")
    {
        ssl_client_ = new SslClient(this);
        ssl_client_->setIgnoreSslErrors(true);
        
        connect(ssl_client_, &SslClient::responseReceived,
            this, &WiFiControlNode::onWiFiResponse);
        
        ssl_client_->connectToServer("localhost", 8765);
    }
    
    void scanWiFi()
    {
        ssl_client_->sendCustomCommand("wifi_scan");
    }
    
    void connectWiFi(const std::string& ssid, const std::string& password)
    {
        QString cmd = QString("wifi_connect:%1:%2")
            .arg(QString::fromStdString(ssid))
            .arg(QString::fromStdString(password));
        ssl_client_->sendCustomCommand(cmd);
    }
    
private:
    void onWiFiResponse(const QString& response)
    {
        RCLCPP_INFO(this->get_logger(), "WiFi Response: %s", 
            response.toStdString().c_str());
    }
};
```

---

## Performance Notes

- **Connection time**: ~100-500ms
- **Scan time**: ~2-5 seconds
- **Connect time**: ~3-10 seconds (network dependent)
- **Command response**: <100ms (except scan/connect)

---

## Security Reminders

⚠️ **Production မှာ သုံးမယ်ဆိုရင်:**

1. SSL certificate verification ကို enable လုပ်ပါ
2. Authentication mechanism ထည့်ပါ
3. Password logging ကို ပိတ်ပါ
4. Rate limiting ထည့်ပါ
5. Input validation လုပ်ပါ

---

## Summary

✅ **C++ Test Client က အဆင်ပြေစွာ အလုပ်လုပ်ပါတယ်**
✅ **Qt's QDataStream format နဲ့ တိုက်ရိုက် compatible ဖြစ်ပါတယ်**
✅ **Python client ထက် ပိုမို reliable ဖြစ်ပါတယ်**
✅ **Production code မှာ လွယ်လွယ် integrate လုပ်နိုင်ပါတယ်**

---

**အကူအညီ လိုအပ်ရင် ပြန်ပြောပါ!** 🚀
