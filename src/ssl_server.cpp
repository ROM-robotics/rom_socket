#include "ssl_server.h"

QString video_directory = "/home/mr_robot/data/upload/videos/";
QString audio_directory = "/home/mr_robot/data/upload/audio/";

// Embedded SSL Certificate (ဒီမှာ သင့် certificate content ထည့်ပါ)
const char* EMBEDDED_CERTIFICATE = R"(
-----BEGIN CERTIFICATE-----
MIIEBTCCAu2gAwIBAgIULI+4AvkXolMpumQu5G4/FQK4+oQwDQYJKoZIhvcNAQEL
BQAwgZExCzAJBgNVBAYTAk1NMQwwCgYDVQQIDANZR04xDDAKBgNVBAcMA1lHTjEV
MBMGA1UECgwMUk9NLVJvYm90aWNzMREwDwYDVQQLDAhSb2JvdGljczERMA8GA1UE
AwwIR2hvc3RNYW4xKTAnBgkqhkiG9w0BCQEWGnNlcnZlcjAxLnBzYTE5ODFAZ21h
aWwuY29tMB4XDTI2MDEwMjA4MTUwMFoXDTI3MDEwMjA4MTUwMFowgZExCzAJBgNV
BAYTAk1NMQwwCgYDVQQIDANZR04xDDAKBgNVBAcMA1lHTjEVMBMGA1UECgwMUk9N
LVJvYm90aWNzMREwDwYDVQQLDAhSb2JvdGljczERMA8GA1UEAwwIR2hvc3RNYW4x
KTAnBgkqhkiG9w0BCQEWGnNlcnZlcjAxLnBzYTE5ODFAZ21haWwuY29tMIIBIjAN
BgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtPZFbHPlPZn0gKeHvhFm97lkmg0x
h1Fo41rxCUbLsJuSEyXSmz0IU7QnmEtlmIBFCcGgWTCYMSVKlxRUqNn+l2ZnoRkK
UA4hp7ezs4auJ5JzvBOz4LQzLqhasq1pLCtlM2Uh69nwFlrCIYhllCtRwAX9BqOc
xrLxLH+UbdjdFaSYIHDgB8qUdl4Qk1fOpfkDiVB19++f+pOqbBssX/HB63rr7my9
CAz/+YSQpo5tfURXGK+FMy0QrM7bKNrjBTADPT5mhd8XsVrFjmZiE5QRYoIae5c+
BWo2QEZQRuSW44API8fuSzNBLyi7R7baZUwM6dGt8iuoy8SF7IUwVmrIaQIDAQAB
o1MwUTAdBgNVHQ4EFgQURssjEMz0z6C/SzzLqlndlkrGJjowHwYDVR0jBBgwFoAU
RssjEMz0z6C/SzzLqlndlkrGJjowDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0B
AQsFAAOCAQEADhkoMGDiYHjfnLOMw27qDHc7kx0rvaOPoGyWkjNHVXV4RCoBa7gZ
/+7WTSIEiNT3t/WlSr5bSoFl7BiU0qMMC9K+eus5zeB7a8JBvFd/1gGZMys8selh
DqgqOYyOiQxEOrOqUxzV9fpC7m0NePcGL9GkETm/Y6ACbk6C8bg7WKd/wh2TLaKS
wyo0/IKYDUj2xfoqxNKPREGt/OwGn82EfxC2MjHwxeoGSNP2qBY34UrQJz1wW7q+
ThYTlH/6b/hvHkVxhRPz4Yu/0o7F60s7df738ZZN7kiIPAvJquyH2rp8s6tyexRW
bzvmOOpVNw+tclNNJnmTKJafuiu6o8ZfdQ==
-----END CERTIFICATE-----
)";

// Embedded Private Key (ဒီမှာ သင့် private key content ထည့်ပါ)
const char* EMBEDDED_PRIVATE_KEY = R"(
-----BEGIN PRIVATE KEY-----
MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC09kVsc+U9mfSA
p4e+EWb3uWSaDTGHUWjjWvEJRsuwm5ITJdKbPQhTtCeYS2WYgEUJwaBZMJgxJUqX
FFSo2f6XZmehGQpQDiGnt7Ozhq4nknO8E7PgtDMuqFqyrWksK2UzZSHr2fAWWsIh
iGWUK1HABf0Go5zGsvEsf5Rt2N0VpJggcOAHypR2XhCTV86l+QOJUHX375/6k6ps
Gyxf8cHreuvubL0IDP/5hJCmjm19RFcYr4UzLRCsztso2uMFMAM9PmaF3xexWsWO
ZmITlBFighp7lz4FajZARlBG5JbjgA8jx+5LM0EvKLtHttplTAzp0a3yK6jLxIXs
hTBWashpAgMBAAECggEAIrP3rEytcZrMoL9/8Js1u9v5xvEwxlp+WttdzgGdnki3
QqTGNq8FoceysCoFWbF/i9duAKypAwO7wi1L7vWfNTmWNfavW5raKWe5NnxleYFE
YJUGsdjc193BRvKqcKYBylFip/Arcp4FDJkzoa6NBt4fH97QeepnBbmRpV8pRrTu
yqoN2iW1kDQNGoBD9xyCXJdeV9IDIlFWKi8qeWpqm368F62S/XJfgyAVdmEECpFc
38n2hX7k+sUMXNoj8KPiqO6v4oPOzfqCRBivzjWBS8yqG+dTYiaOSQ4z/TlUVTDa
ioEAKcM1cIYYKHG2B48CdlnhBTM4urTwZBlO+8KX4QKBgQDwNQilqaYAB+gOdXGG
LStuDsyh+adDBZqFwQZnA1SR2Lu7s84MD2+U3qVcbqK4G2XrThb0SKRhdN50JFjL
sZDjJhNlrfyosGw4GdD/0VdYXhkcummB9tE0toA1ONq9hlQI4WKgwmYOq0sDDMBV
UDRrl4umPB7YYF5f722A203CPwKBgQDA3BKBAQYdB3EC9geOjfo0AovAyAMMNOxC
lHwmy8/IzaCPwIijYmzrkDTn0xVgFajSGk3OCOVaxlG0DlDc7sHEaZhUFovg3yx4
TMNB2n2Wm4J0X4pOha1dxx2sA4BI2rQYms6t8lOmdkTa+B0rwgvbOUDUEtjfx4Pn
4dg71/b7VwKBgQC6H43Ut5BNw9KWqX/OhN97BvKeq1BkSUpDS57HYTg9Tl+hAKCu
jaNbCe29omhpGamuWzLEFCly7liUS7mWE799knpDNj5pA1LHYZGlNzNj4H262eJ4
9qOCIctT8frkEdq5itKeWCM2SJn2AgJh2KTVnXZy13DbHkjiMyZ5SvSEhwKBgGCC
wM/Fz2Vff/JXZFi2O+sjCwSiEsRdB44Z+DcB7y0xmZPWaYo5iwAm3hLU0vGOZTke
6KieUwgmDmTodRbadCTyIsSRs9YIWJyq7VtbF1Xy5EmQNgotYyB2sCaQafYLW+yk
K6FojuvSa4qYdyCarow6DnMSK21wzlWP80GfRX1pAoGAXnVnF1Y2ncu2D5YdFSGa
KJU+r14OaTUpAVLdSyhcp0gYSE2rGQuf8+Nc0SqfoehWo1tDP4Q1pZ/M/TM2WaB6
AYfQleUbAbWQNjLvpPlnxb3wecKSxxvaiccGV/u67IdCydf0ssTJvf1zb4lA7bMp
KzyBByrueDl2o25D6iWm1so=
-----END PRIVATE KEY-----
)";

SslServer::SslServer(QObject *parent) : QTcpServer(parent) 
{
    qDebug() << "Initializing SslServer...";
    
    // Initialize WiFi configurator
    m_wifiConfig = new WiFiConfigurator(this);
    qDebug() << "WiFi configurator initialized";
    
    // Initialize audio mpv player
    audioMpv_ = mpv_create();
    if (!audioMpv_) {
        qCritical() << "Failed to create audio MPV instance";
    } else {
        qDebug() << "Audio MPV instance created";
        
        mpv_set_option_string(audioMpv_, "vo", "null");
        mpv_set_option_string(audioMpv_, "video", "no");
        mpv_set_option_string(audioMpv_, "audio-display", "no");
        mpv_set_option_string(audioMpv_, "force-window", "no");
        mpv_set_option_string(audioMpv_, "ytdl", "no");
        mpv_set_option_string(audioMpv_, "terminal", "no");
        mpv_set_option_string(audioMpv_, "input-terminal", "no");
        mpv_set_option_string(audioMpv_, "volume", "70");
        
        int result = mpv_initialize(audioMpv_);
        if (result < 0) {
            qCritical() << "Failed to initialize audio MPV:" << mpv_error_string(result);
            mpv_terminate_destroy(audioMpv_);
            audioMpv_ = nullptr;
        } else {
            qDebug() << "Audio MPV player initialized successfully";
        }
    }
    
    // Initialize video mpv player
    videoMpv_ = mpv_create();
    if (!videoMpv_) {
        qCritical() << "Failed to create video MPV instance";
    } else {
        qDebug() << "Video MPV instance created";
        
        mpv_set_option_string(videoMpv_, "terminal", "no");
        mpv_set_option_string(videoMpv_, "input-terminal", "no");
        mpv_set_option_string(videoMpv_, "input-default-bindings", "no");
        mpv_set_option_string(videoMpv_, "vo", "drm,gpu,null");
        mpv_set_option_string(videoMpv_, "volume", "70");
        
        int result = mpv_initialize(videoMpv_);
        if (result < 0) {
            qCritical() << "Failed to initialize video MPV:" << mpv_error_string(result);
            mpv_terminate_destroy(videoMpv_);
            videoMpv_ = nullptr;
        } else {
            qDebug() << "Video MPV player initialized successfully";
        }
    }
    
    qDebug() << "SslServer initialization complete - Audio:" << (audioMpv_ ? "OK" : "FAILED") 
             << "Video:" << (videoMpv_ ? "OK" : "FAILED");
}

SslServer::~SslServer()
{
    // Clean up audio mpv player
    if (audioMpv_) {
        mpv_terminate_destroy(audioMpv_);
        audioMpv_ = nullptr;
        qDebug() << "Audio MPV player destroyed";
    }
    
    // Clean up video mpv player
    if (videoMpv_) {
        mpv_terminate_destroy(videoMpv_);
        videoMpv_ = nullptr;
        qDebug() << "Video MPV player destroyed";
    }
}

void SslServer::incomingConnection(qintptr socketDescriptor) 
{
    QSslSocket *socket = new QSslSocket(this);

    if (socket->setSocketDescriptor(socketDescriptor)) 
    {
        // Embedded certificate နဲ့ key ကို load လုပ်ခြင်း
        QSslCertificate certificate(QByteArray(EMBEDDED_CERTIFICATE), QSsl::Pem);
        QSslKey privateKey(QByteArray(EMBEDDED_PRIVATE_KEY), QSsl::Rsa, QSsl::Pem);
        
        if (certificate.isNull()) {
            qCritical() << "Failed to load embedded certificate";
        } else if (privateKey.isNull()) {
            qCritical() << "Failed to load embedded private key";
        } else {
            socket->setLocalCertificate(certificate);
            socket->setPrivateKey(privateKey);
            qDebug() << "Loaded embedded SSL certificate";
        }
        
        socket->setProtocol(QSsl::TlsV1_2OrLater);

        // Encryption စတင်ခြင်း
        socket->startServerEncryption();

        connect(socket, &QSslSocket::readyRead, [this, socket]() 
        {
            // Get or create buffer for this socket
            QByteArray &buffer = socketBuffers[socket];
            quint32 &expectedSize = socketExpectedSizes[socket];
            
            // Append incoming data to buffer
            buffer.append(socket->readAll());
            
            // Process all complete packets
            processPackets(socket, buffer, expectedSize);
        });
        
        connect(socket, &QSslSocket::disconnected, [this, socket]() 
        {
            // Clean up buffers when socket disconnects
            socketBuffers.remove(socket);
            socketExpectedSizes.remove(socket);
            socket->deleteLater();
        });
    } 
    else 
    {
        delete socket;
    }
}

QString SslServer::getVideoList()
{
    QDir videoDir(video_directory);
    
    if (!videoDir.exists()) {
        return "Error: Video directory does not exist";
    }
    
    // Video file extensions
    QStringList filters;
    filters << "*.mp4" << "*.avi" << "*.mkv" << "*.mov" << "*.wmv" << "*.flv" << "*.webm";
    videoDir.setNameFilters(filters);
    
    QStringList videoFiles = videoDir.entryList(QDir::Files);
    
    if (videoFiles.isEmpty()) {
        return "No video files found";
    }
    
    return videoFiles.join(",");
}

QString SslServer::getAudioList()
{
    QDir audioDir(audio_directory);
    
    if (!audioDir.exists()) {
        return "Error: Audio directory does not exist";
    }
    
    // Audio file extensions
    QStringList filters;
    filters << "*.mp3" << "*.wav" << "*.flac" << "*.aac" << "*.ogg" << "*.m4a" << "*.wma";
    audioDir.setNameFilters(filters);
    
    QStringList audioFiles = audioDir.entryList(QDir::Files);
    
    if (audioFiles.isEmpty()) {
        return "No audio files found";
    }
    
    return audioFiles.join(",");
}

QString SslServer::llmResponse(const QString &query)
{
    // TODO: LLM integration ဒီနေရာမှာ လုပ်ရမယ်
    // ဥပမာ: OpenAI API, Ollama, သို့မဟုတ် အခြား LLM service ကို ခေါ်ရမယ်
    
    qDebug() << "LLM query received:" << query;
    
    // Placeholder response
    return "LLM response not implemented yet. Query was: " + query;
}

void SslServer::sendResponse(QSslSocket *socket, const QString &response)
{
    if (!socket || !socket->isOpen()) {
        qWarning() << "Cannot send response: socket is not open";
        return;
    }
    
    // Build packet in memory first
    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_0);
    stream << QString("RESPONSE") << response.toUtf8();
    
    // Send packet size first, then packet data
    QDataStream out(socket);
    out.setVersion(QDataStream::Qt_6_0);
    out << quint32(packet.size());
    socket->write(packet);
    socket->flush();
    
    qDebug() << "Response sent:" << response.left(100) << "..."; // First 100 chars
}

bool SslServer::saveUploadedFile(const QString &directory, const QString &filename, const QByteArray &fileData)
{
    // Directory ရှိမရှိ စစ်ဆေးပြီး မရှိရင် ဖန်တီးပါမယ်
    QDir dir(directory);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qCritical() << "Failed to create directory:" << directory;
            return false;
        }
        qDebug() << "Created directory:" << directory;
    }
    
    // Full file path
    QString filePath = directory + "/" + filename;
    
    // File save လုပ်ခြင်း
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    qint64 bytesWritten = file.write(fileData);
    file.close();
    
    if (bytesWritten != fileData.size()) {
        qCritical() << "File write incomplete:" << bytesWritten << "of" << fileData.size();
        return false;
    }
    
    qDebug() << "File saved successfully:" << filePath << "(" << bytesWritten << "bytes)";
    return true;
}

void SslServer::processPackets(QSslSocket *socket, QByteArray &buffer, quint32 &expectedSize)
{
    while (true) {
        // If we don't know the packet size yet, try to read it
        if (expectedSize == 0) {
            if (buffer.size() < (int)sizeof(quint32)) {
                return; // Need more data for size header
            }
            
            // Read packet size from buffer
            QDataStream sizeStream(buffer);
            sizeStream.setVersion(QDataStream::Qt_6_0);
            sizeStream >> expectedSize;
            
            // Remove size header from buffer
            buffer.remove(0, sizeof(quint32));
        }
        
        // Check if we have the complete packet
        if (buffer.size() < (int)expectedSize) {
            return; // Need more data for complete packet
        }
        
        // Extract one complete packet
        QByteArray packet = buffer.left(expectedSize);
        buffer.remove(0, expectedSize);
        expectedSize = 0; // Reset for next packet
        
        // Parse the packet
        QDataStream stream(&packet, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_6_0);
        
        QString type;
        stream >> type;
        
        qDebug() << "Packet Type:" << type;

        if (type == "COMMAND") 
        {
            // Command packets: type + command string
            QByteArray data;
            stream >> data;
            QString command = QString::fromUtf8(data);
            qDebug() << "Received Command:" << command;
            
            QString response;
            if (command == "show_video") {
                response = getVideoList();
                qDebug() << "Sending video list to client";
            } else if (command == "show_audio") {
                response = getAudioList();
                qDebug() << "Sending audio list to client";
            } else if (command.startsWith("play_video:")) {
                QString videoName = command.mid(11); // Remove "play_video:" prefix
                qDebug() << "Play video requested:" << videoName;
                playVideo(videoName);
                response = "Playing video: " + videoName;
            } else if (command.startsWith("play_audio:")) {
                QString audioName = command.mid(11); // Remove "play_audio:" prefix
                qDebug() << "Play audio requested:" << audioName;
                playAudio(audioName);
                response = "Playing audio: " + audioName;
            } else if (command == "toggle_video") {
                qDebug() << "Toggle video play/pause requested";
                toggleVideoPlayback();
                response = "Video playback toggled";
            } else if (command == "toggle_audio") {
                qDebug() << "Toggle audio play/pause requested";
                toggleAudioPlayback();
                response = "Audio playback toggled";
            } else if (command.startsWith("set_audio_volume:")) {
                int volume = command.mid(17).toInt(); // Remove "set_audio_volume:" prefix
                qDebug() << "Set audio volume requested:" << volume;
                setAudioVolume(volume);
                response = "Audio volume set to: " + QString::number(volume);
            } else if (command.startsWith("set_video_volume:")) {
                int volume = command.mid(17).toInt(); // Remove "set_video_volume:" prefix
                qDebug() << "Set video volume requested:" << volume;
                setVideoVolume(volume);
                response = "Video volume set to: " + QString::number(volume);
            } else if (command == "get_audio_volume") {
                int volume = getAudioVolume();
                qDebug() << "Get audio volume requested";
                response = "Audio volume: " + QString::number(volume);
            } else if (command == "get_video_volume") {
                int volume = getVideoVolume();
                qDebug() << "Get video volume requested";
                response = "Video volume: " + QString::number(volume);
            } else if (command == "llm_response") {
                response = llmResponse(command);
                qDebug() << "Sending LLM response to client";
            } else if (command == "SEARCH_WIFI") {
                response = handleSearchWiFi();
                qDebug() << "Sending WiFi search results to client";
            } else if (command.startsWith("CONNECT_WIFI:")) {
                QString params = command.mid(13); // Remove "CONNECT_WIFI:" prefix
                QStringList parts = params.split(":");
                if (parts.size() >= 1) {
                    QString ssid = parts[0];
                    QString password = parts.size() > 1 ? parts[1] : "";
                    response = handleConnectWiFi(ssid, password);
                } else {
                    response = "ERROR:Invalid CONNECT_WIFI format";
                }
                qDebug() << "Sending WiFi connect response to client";
            } else if (command == "DISCONNECT_WIFI") {
                response = handleDisconnectWiFi();
                qDebug() << "Sending WiFi disconnect response to client";
            } else if (command == "CURRENT_WIFI") {
                response = handleCurrentWiFi();
                qDebug() << "Sending current WiFi info to client";
            } else {
                response = "Unknown command: " + command;
                qDebug() << "Unknown command received";
            }
            
            sendResponse(socket, response);
            
        } 
        else if (type == "UPLOAD_VIDEO") 
        {
            // Video upload packets: type + filename + file data
            QString filename;
            QByteArray fileData;
            stream >> filename >> fileData;
            
            qDebug() << "Uploading video:" << filename << "Size:" << fileData.size();
            
            bool success = saveUploadedFile(video_directory, filename, fileData);
            QString response = success ? 
                "Video uploaded successfully: " + filename : 
                "Failed to upload video: " + filename;
                
            sendResponse(socket, response);
            
        } 
        else if (type == "UPLOAD_AUDIO") 
        {
            // Audio upload packets: type + filename + file data
            QString filename;
            QByteArray fileData;
            stream >> filename >> fileData;
            
            qDebug() << "Uploading audio:" << filename << "Size:" << fileData.size();
            
            bool success = saveUploadedFile(audio_directory, filename, fileData);
            QString response = success ? 
                "Audio uploaded successfully: " + filename : 
                "Failed to upload audio: " + filename;
                
            sendResponse(socket, response);
            
        } else {
            qDebug() << "Unknown packet type:" << type;
        }
    }
}

void SslServer::playAudio(const QString &filename)
{
    if (!audioMpv_) {
        qWarning() << "Audio MPV player not initialized";
        return;
    }
    
    QString filePath = audio_directory + filename;
    QFileInfo fileInfo(filePath);
    
    if (!fileInfo.exists()) {
        qWarning() << "Audio file does not exist:" << filePath;
        return;
    }
    
    currentAudioFile_ = filename;
    
    // Store file path in a persistent QByteArray
    QByteArray pathData = filePath.toUtf8();
    const char* cmd[] = {"loadfile", pathData.constData(), NULL};
    
    int result = mpv_command_async(audioMpv_, 0, cmd);
    if (result < 0) {
        qCritical() << "Failed to play audio:" << mpv_error_string(result);
    } else {
        qDebug() << "Playing audio file:" << filePath;
    }
}

void SslServer::playVideo(const QString &filename)
{
    if (!videoMpv_) {
        qWarning() << "Video MPV player not initialized";
        return;
    }
    
    QString filePath = video_directory + filename;
    QFileInfo fileInfo(filePath);
    
    if (!fileInfo.exists()) {
        qWarning() << "Video file does not exist:" << filePath;
        return;
    }
    
    currentVideoFile_ = filename;
    
    // Store file path in a persistent QByteArray
    QByteArray pathData = filePath.toUtf8();
    const char* cmd[] = {"loadfile", pathData.constData(), NULL};
    
    int result = mpv_command_async(videoMpv_, 0, cmd);
    if (result < 0) {
        qCritical() << "Failed to play video:" << mpv_error_string(result);
    } else {
        qDebug() << "Playing video file:" << filePath;
    }
}

void SslServer::toggleAudioPlayback()
{
    if (!audioMpv_) return;
    
    // Get pause state
    int pause = 0;
    mpv_get_property(audioMpv_, "pause", MPV_FORMAT_FLAG, &pause);
    
    // Toggle pause
    pause = !pause;
    mpv_set_property(audioMpv_, "pause", MPV_FORMAT_FLAG, &pause);
    
    qDebug() << (pause ? "Audio paused" : "Audio resumed");
}

void SslServer::toggleVideoPlayback()
{
    if (!videoMpv_) return;
    
    // Get pause state
    int pause = 0;
    mpv_get_property(videoMpv_, "pause", MPV_FORMAT_FLAG, &pause);
    
    // Toggle pause
    pause = !pause;
    mpv_set_property(videoMpv_, "pause", MPV_FORMAT_FLAG, &pause);
    
    qDebug() << (pause ? "Video paused" : "Video resumed");
}

void SslServer::setAudioVolume(int volume)
{
    if (!audioMpv_) return;
    
    // Clamp volume between 0 and 100
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;
    
    int64_t vol = volume;
    mpv_set_property(audioMpv_, "volume", MPV_FORMAT_INT64, &vol);
    
    qDebug() << "Audio volume set to:" << volume;
}

void SslServer::setVideoVolume(int volume)
{
    if (!videoMpv_) return;
    
    // Clamp volume between 0 and 100
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;
    
    int64_t vol = volume;
    mpv_set_property(videoMpv_, "volume", MPV_FORMAT_INT64, &vol);
    
    qDebug() << "Video volume set to:" << volume;
}

int SslServer::getAudioVolume()
{
    if (!audioMpv_) return 0;
    
    int64_t volume = 0;
    mpv_get_property(audioMpv_, "volume", MPV_FORMAT_INT64, &volume);
    
    return static_cast<int>(volume);
}

int SslServer::getVideoVolume()
{
    if (!videoMpv_) return 0;
    
    int64_t volume = 0;
    mpv_get_property(videoMpv_, "volume", MPV_FORMAT_INT64, &volume);
    
    return static_cast<int>(volume);
}

QString SslServer::handleSearchWiFi()
{
    qDebug() << "Searching for WiFi networks...";
    QList<WiFiConfigurator::NetworkInfo> networks = m_wifiConfig->searchWiFi();
    
    if (networks.isEmpty()) {
        QString error = m_wifiConfig->getLastError();
        if (!error.isEmpty()) {
            return "ERROR:" + error;
        }
        return "WIFI_LIST:";
    }
    
    // Format: WIFI_LIST:ssid1:signal1:security1:connected,ssid2:signal2:security2:connected,...
    QStringList networkList;
    for (const auto &network : networks) {
        QString networkStr = QString("%1:%2:%3:%4")
            .arg(network.ssid)
            .arg(network.signal)
            .arg(network.security)
            .arg(network.isConnected ? "yes" : "no");
        networkList.append(networkStr);
    }
    
    return "WIFI_LIST:" + networkList.join(",");
}

QString SslServer::handleConnectWiFi(const QString &ssid, const QString &password)
{
    qDebug() << "Connecting to WiFi:" << ssid;
    bool success = m_wifiConfig->connectWiFi(ssid, password);
    
    if (success) {
        return "CONNECT_OK:" + ssid;
    } else {
        QString error = m_wifiConfig->getLastError();
        return "ERROR:" + (error.isEmpty() ? "Connection failed" : error);
    }
}

QString SslServer::handleDisconnectWiFi()
{
    qDebug() << "Disconnecting WiFi...";
    bool success = m_wifiConfig->disconnectWiFi();
    
    if (success) {
        return "DISCONNECT_OK";
    } else {
        QString error = m_wifiConfig->getLastError();
        return "ERROR:" + (error.isEmpty() ? "Disconnection failed" : error);
    }
}

QString SslServer::handleCurrentWiFi()
{
    qDebug() << "Getting current WiFi info...";
    QString ssid = m_wifiConfig->getCurrentSSID();
    QString ip = m_wifiConfig->getCurrentIP();
    
    if (ssid.isEmpty()) {
        return "CURRENT_WIFI:Not connected::";
    }
    
    // Format: CURRENT_WIFI:ssid:ip
    return QString("CURRENT_WIFI:%1:%2").arg(ssid).arg(ip);
}
