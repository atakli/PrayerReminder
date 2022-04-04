#ifndef WINDOW_H
#define WINDOW_H

#include <QCoreApplication>
#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QElapsedTimer>
#include <QDialog>
#include <QWidget>

#include "updatecontroller.h"
#include "fetchtimes.h"

#include <memory>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT
public:
	Window(QWidget* parent=0);

private slots:
	void downloadEvkat();
    void bolgeSec();
    void fillCities(int ulkeIndex);
	void fillTown(int sehirIndex);
	void executeIlceKodu(int ilceIndex);
public slots:
	void showMessage();

	void showTime();
signals:
    void son5Dk();
    void sehirSec(QString sehirKodu);
private:
	const QString applicationDirPath = QCoreApplication::applicationDirPath();
	QString ulkeFile, sehirFile, ilceFile;
	QString ulkeKodu, sehirKodu, ilceKodu;
	void controlOnlineEvkatFileExistOtherwiseRequestDownload();
	UpdateController update;
    bool compareTagVersion(QString tag, QString currentTag);
	HttpWindow fetchTimes;	// TODO: önceki hali gibi olup da signal slot ile filan HttpWindow'dan Window'a sinyal gönderip indirme işlemi bitmeden fetchTimes objesinin ömrünü doldurmasını
	std::shared_ptr<Ui::Window> ui;	// men edebilirim
	bool kalanVakitBesOldu = false;
	void executeFileNames();
	void ilkBolgeSecimi();
	void setIcon(uint8_t number);    // önceden slot'tu
    void createActions();
    void createTrayIcon();

    QElapsedTimer timer;

    QAction *quitAction;
	QAction *sehirSecimiAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif
