#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QFileInfo>
#include <QByteArray>

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = 0);
    Q_INVOKABLE void download(QString url);
    int getValue() const { return m_value; }
    int getMaximumValue() const { return m_maximumValue; }
    Q_INVOKABLE bool getDownloadStatus() const { return startDownload; }
    Q_PROPERTY(int value READ getValue NOTIFY valueChanged)
    Q_PROPERTY(int maximumValue READ getMaximumValue NOTIFY maximumValueChanged)

signals:
    void valueChanged();
    void maximumValueChanged();

public slots:
    void replyFinished();
    void onDownloadProgress(qint64, qint64);
    void onReadyRead();

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString fileName;
    qint64 m_value;
    qint64 m_maximumValue;
    bool startDownload = false;
    QFile *file;
};

#endif // DATA_H
