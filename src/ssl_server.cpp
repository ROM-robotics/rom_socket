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
    // Initialize audio player
    audioPlayer_ = new QMediaPlayer(this);
    audioOutput_ = new QAudioOutput(this);
    audioPlayer_->setAudioOutput(audioOutput_);
    audioOutput_->setVolume(0.7); // 70% volume
    
    // Initialize video player
    videoPlayer_ = new QMediaPlayer(this);
    videoOutput_ = new QAudioOutput(this);
    videoPlayer_->setAudioOutput(videoOutput_);
    videoOutput_->setVolume(0.7); // 70% volume
    
    // Connect signals for debugging
    connect(audioPlayer_, &QMediaPlayer::playbackStateChanged, this, [](QMediaPlayer::PlaybackState state) {
        qDebug() << "Audio playback state:" << state;
    });
    
    connect(videoPlayer_, &QMediaPlayer::playbackStateChanged, this, [](QMediaPlayer::PlaybackState state) {
        qDebug() << "Video playback state:" << state;
    });
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
            } else if (command == "llm_response") {
                response = llmResponse(command);
                qDebug() << "Sending LLM response to client";
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
    if (!audioPlayer_) return;
    
    QString filePath = audio_directory + filename;
    QFileInfo fileInfo(filePath);
    
    if (!fileInfo.exists()) {
        qWarning() << "Audio file does not exist:" << filePath;
        return;
    }
    
    currentAudioFile_ = filename;
    audioPlayer_->setSource(QUrl::fromLocalFile(filePath));
    audioPlayer_->play();
    
    qDebug() << "Playing audio file:" << filePath;
}

void SslServer::playVideo(const QString &filename)
{
    if (!videoPlayer_) return;
    
    QString filePath = video_directory + filename;
    QFileInfo fileInfo(filePath);
    
    if (!fileInfo.exists()) {
        qWarning() << "Video file does not exist:" << filePath;
        return;
    }
    
    currentVideoFile_ = filename;
    videoPlayer_->setSource(QUrl::fromLocalFile(filePath));
    videoPlayer_->play();
    
    qDebug() << "Playing video file:" << filePath;
}

void SslServer::toggleAudioPlayback()
{
    if (!audioPlayer_) return;
    
    QMediaPlayer::PlaybackState state = audioPlayer_->playbackState();
    
    if (state == QMediaPlayer::PlayingState) {
        audioPlayer_->pause();
        qDebug() << "Audio paused";
    } else if (state == QMediaPlayer::PausedState) {
        audioPlayer_->play();
        qDebug() << "Audio resumed";
    } else {
        // If stopped, replay current file
        if (!currentAudioFile_.isEmpty()) {
            playAudio(currentAudioFile_);
        } else {
            qWarning() << "No audio file to play";
        }
    }
}

void SslServer::toggleVideoPlayback()
{
    if (!videoPlayer_) return;
    
    QMediaPlayer::PlaybackState state = videoPlayer_->playbackState();
    
    if (state == QMediaPlayer::PlayingState) {
        videoPlayer_->pause();
        qDebug() << "Video paused";
    } else if (state == QMediaPlayer::PausedState) {
        videoPlayer_->play();
        qDebug() << "Video resumed";
    } else {
        // If stopped, replay current file
        if (!currentVideoFile_.isEmpty()) {
            playVideo(currentVideoFile_);
        } else {
            qWarning() << "No video file to play";
        }
    }
}