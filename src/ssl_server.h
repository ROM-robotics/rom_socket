#include <QTcpServer>
#include <QSslSocket>
#include <QSslKey>
#include <QSslCertificate>
#include <QDir>
#include <QFileInfo>
#include <QDataStream>
#include <QMap>
#include <QMediaPlayer>
#include <QAudioOutput>

class SslServer : public QTcpServer 
{
    Q_OBJECT
public:
    explicit SslServer(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor) override; // Connection လက်ခံဖို့ override လုပ်ခြင်း

private:
    QString getVideoList();
    QString getAudioList();
    QString llmResponse(const QString &query);
    void sendResponse(QSslSocket *socket, const QString &response);
    bool saveUploadedFile(const QString &directory, const QString &filename, const QByteArray &fileData);
    void processPackets(QSslSocket *socket, QByteArray &buffer, quint32 &expectedSize);
    
    // Media playback
    void playAudio(const QString &filename);
    void playVideo(const QString &filename);
    void toggleAudioPlayback();
    void toggleVideoPlayback();
    
    // Track buffers per socket
    QMap<QSslSocket*, QByteArray> socketBuffers;
    QMap<QSslSocket*, quint32> socketExpectedSizes;
    
    // Media players
    QMediaPlayer* audioPlayer_ = nullptr;
    QAudioOutput* audioOutput_ = nullptr;
    QMediaPlayer* videoPlayer_ = nullptr;
    QAudioOutput* videoOutput_ = nullptr;
    QString currentAudioFile_;
    QString currentVideoFile_;
};