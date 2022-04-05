#ifndef UPDATECONTROLLER_H
#define UPDATECONTROLLER_H

#include "fetchtimes.h"

#include <QWidget>
#include <QObject>

class UpdateController : public QObject
{
    Q_OBJECT
public:
	UpdateController();
//	~UpdateController();
	void isNewVersionAvailable();
//	void checkNewVersionNow();
    bool isChecked;
    void checkForUpdates();
private:
	HttpWindow fetchTimes;
	const QString applicationDirPath = QCoreApplication::applicationDirPath();
	bool compareTagVersion(QString tag, QString currentTag);
};

#endif // UPDATECONTROLLER_H
