#include "updatecontroller.h"

#include <QJsonDocument>
#include <QMessageBox>
#include <QFile>

UpdateController::UpdateController()	{}
//UpdateController::~UpdateController()	{}
QString dosyayiAc(QString fileName, QIODevice::OpenModeFlag flag=QIODevice::ReadOnly)
{
	QFile file(fileName);
	if (!file.open(flag | QIODevice::Text))
		return "";							// TODO: buraya girerse ne olcak?
	QString text = file.readAll();
	file.close();
	return text;
}
bool UpdateController::compareTagVersion(QString tag, QString currentTag)
{
	QString tag1 = tag.split("-").at(0).mid(1);

	uint8_t ilkTagCurrent = currentTag.split(".").first().toUInt();
	uint8_t ortaTagCurrent = currentTag.split(".").at(1).toUInt();
	uint8_t sonTagCurrent = currentTag.split(".").last().toUInt();

	uint8_t ilkTag = tag1.split(".").first().toUInt();
	uint8_t ortaTag = tag1.split(".").at(1).toUInt();
	uint8_t sonTag = tag1.split(".").last().toUInt();

	if(ilkTag < ilkTagCurrent)
		return false;
	else if(ilkTag > ilkTagCurrent)
		return true;
	else
	{
		if(ortaTag < ortaTagCurrent)
			return false;
		else if(ortaTag > ortaTagCurrent)
			return true;
		else
		{
			if(sonTag > sonTagCurrent)
				return true;
			else
				return false;
		}
	}
	return false;
}

void UpdateController::isNewVersionAvailable()
{
	QString apiPath = applicationDirPath + "/api.json";
	QString newUrl = "https://api.github.com/repos/atakli/PrayerReminder-Desktop/releases/latest";
	fetchTimes.downloadSynchronous(apiPath, newUrl);

	QString saveData = dosyayiAc(apiPath);
	QString currentTag = dosyayiAc(applicationDirPath + "/namazVakitFiles/version.txt");

//	QJsonDocument loadDoc = QJsonDocument::fromVariant(saveData);
	QJsonDocument loadDoc = QJsonDocument::fromJson(QByteArray::fromStdString(saveData.toStdString()));

	uint8_t index = 0;
	QJsonValue next;
	while(!next.isUndefined())
	{
//		next = loadDoc[index];
//		QString tag = next["tag_name"].toString();
		QString tag = loadDoc["tag_name"].toString();
		if(compareTagVersion(tag, currentTag))
		{
//			if (QMessageBox::question(this, tr("Yeni sürüm bulundu"), tr("İndirilelim mi?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::No)
//			{
//				return;
//			}
//			fetchTimes.downloadSynchronous("", "https://github.com/atakli/PrayerReminder-Desktop/releases/latest/download/PrayerReminder.zip");
			fetchTimes.downloadSynchronous("", loadDoc["assets"][0]["browser_download_url"].toString()); // ismi PrayerReminder.zip'dan başka bişey olursa diye
			break;
		}
		++index;
	}
}
