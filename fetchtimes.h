#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QNetworkAccessManager>
#include <QProgressDialog>
#include <QUrl>

QT_BEGIN_NAMESPACE
class QFile;
class QSslError;
class QNetworkReply;
QT_END_NAMESPACE

class HttpWindow : public QDialog
{
    Q_OBJECT
public:
    explicit HttpWindow(QWidget *parent = nullptr);
	~HttpWindow();
    void startRequest(const QUrl &requestedUrl);
	void downloadFile(const QString fileName, const QString urlSpec);
	void downloadSynchronous(QString fileName, QString urlSpec);
private slots:
	void httpFinished();
	void httpReadyRead();
#if QT_CONFIG(ssl)
	void sslErrors(const QList<QSslError> &errors);
#endif

private:
    std::unique_ptr<QFile> openFileForWrite(const QString &fileName);

	QNetworkAccessManager qnam;
	std::unique_ptr<QNetworkReply> reply;
//    QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reply;
    std::unique_ptr<QFile> file;
};

#endif
