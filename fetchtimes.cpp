#include "fetchtimes.h"

#include <QtWidgets>
#include <QtNetwork>
#include <QtGlobal>

#include <algorithm>

HttpWindow::HttpWindow(QWidget *parent) : QDialog(parent)
{
	isNewVersionExists();
}
HttpWindow::~HttpWindow() = default;	// TODO: bu nasıl bir saçmalıktır: default'u niye burda yazmışım, class definition'da yazayım diye oraya alıp burayı tamamen kaldırınca hata verdi.

void HttpWindow::startRequest(const QUrl &requestedUrl)
{
	url = requestedUrl;
	QNetworkRequest req = QNetworkRequest(url);
//#if QT_VERSION < QT_VERSION_CHECK(5,15,3)
#if QT_VERSION < 393729                                                 // TODO: düzeltmem gerekli burayı. generic değil. sadece bana uygun
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
#endif
//	req.setHeader(QNetworkRequest::LocationHeader, "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:98.0) Gecko/20100101 Firefox/98.0");

	reply.reset(qnam.get(req));
	connect(reply.get(), &QIODevice::readyRead, this, &HttpWindow::httpReadyRead);
	connect(reply.get(), &QNetworkReply::finished, this, &HttpWindow::httpFinished);
#if QT_CONFIG(ssl)
	connect(reply.get(), &QNetworkReply::sslErrors, this, &HttpWindow::sslErrors);
#endif
}

bool HttpWindow::isNewVersionExists()
{
	QUrl url1 = QUrl("https://github.com/atakli/PrayerReminder-Desktop/releases/download/v1.0.0-beta/PrayerReminder.zip");
	QNetworkRequest req = QNetworkRequest(url1);
//	req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

	reply1.reset(qnam1.get(req));
	connect(reply1.get(), &QNetworkReply::finished, this, &HttpWindow::httpFinished1);
	return true;
}
void HttpWindow::httpFinished1()
{
	qDebug() << reply1->error();
}

void HttpWindow::downloadFile(QString fileName, QString urlSpec)
{
    QString directory = "";
    if(fileName == "")
    {
        directory = QFileDialog::getExistingDirectory(this, tr("Yeni sürümü indireceğiniz klasörü seçin"));
        fileName = directory + "/PrayerReminder.zip";
    }

	/*const*/ QUrl newUrl = QUrl::fromUserInput(urlSpec);

//	if (QFile::exists(fileName))
//	{
//        if (QMessageBox::question(this, tr("Overwrite Existing File"), tr("There already exists a file called %1%2. Overwrite?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::No)
//		{
//			return;
//		}
////		QFile::remove(fileName);
//	}
	file = openFileForWrite(fileName);
	if (!file)
	{
		return;
	}
	startRequest(newUrl);	// schedule the request
}

std::unique_ptr<QFile> HttpWindow::openFileForWrite(const QString &fileName)
{
	std::unique_ptr<QFile> file = std::make_unique<QFile>(fileName);
	if (!file->open(QIODevice::WriteOnly))
	{
		QMessageBox::information(this, tr("Error"), tr("Unable to save the file %1: %2.").arg(QDir::toNativeSeparators(fileName), file->errorString()));
		return nullptr;
	}
	return file;
}

void HttpWindow::httpFinished()
{
	QFileInfo fi;
	if (file)
	{
		fi.setFile(file->fileName());
		file->close();
		file.reset();
	}

//	if (httpRequestAborted) {
//        reply->deleteLater();
//        reply = nullptr;
//        return;
//    }

//    if (reply->error()) {
//        QFile::remove(fi.absoluteFilePath());
//        reply->deleteLater();
//        reply = nullptr;
//        return;
//    }

//	const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

//	reply->deleteLater();
//	reply = nullptr;

//	if (!redirectionTarget.isNull())
//	{
//		qDebug() << "redirect";
//		const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
//		file = openFileForWrite(fi.absoluteFilePath());
//		if (!file)
//		{
//			return;
//		}
//		startRequest(redirectedUrl);
//		return;
//	}

	/*QNetworkReply::NetworkError error = reply->error();				// QNetworkReply::ContentNotFoundError
//	reply.reset();
	if (error != QNetworkReply::NoError)
	{
		QFile::remove(fi.absoluteFilePath());
		return;
	}*/
}

void HttpWindow::httpReadyRead()
{
    // This slot gets called every time the QNetworkReply has new data. We read all of its new data and write it into the file. That way we use less RAM than when reading it at the finished() signal of the QNetworkReply
	if (file)
		file->write(reply->readAll());
}

#if QT_CONFIG(ssl)
void HttpWindow::sslErrors(const QList<QSslError> &errors)
{
	QString errorString;
	for (const QSslError &error : errors)
	{
		if (!errorString.isEmpty())
			errorString += '\n';
		errorString += error.errorString();
	}

	if (QMessageBox::warning(this, tr("SSL Errors"), tr("One or more SSL errors has occurred:\n%1").arg(errorString), QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore)
	{
		reply->ignoreSslErrors();
	}
}
#endif
