#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QElapsedTimer>
#include <QMessageBox>
#include <QDialog>
#include <QWidget>

#include "prayertimesparser.h"
#include "updatecontroller.h"
//#include "fetchtimes.h"

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
    void showMessage();
    void showTime();
signals:
    void son5Dk();
    void sehirSec(QString sehirKodu);
private:
    const char* appName = "Namaz Vakti Hatırlatıcı";
	QString ulkeFile, sehirFile, ilceFile;
	QString ulkeKodu, sehirKodu, ilceKodu;
	PrayerTimesParser ptp;
    UpdateController update;
    bool compareTagVersion(QString tag, QString currentTag);
//    HttpWindow fetchTimes;	// TODO: önceki hali gibi olup da signal slot ile filan HttpWindow'dan Window'a sinyal gönderip indirme işlemi bitmeden fetchTimes objesinin ömrünü doldurmasını men edebilirim
    std::shared_ptr<Ui::Window> ui;
    bool kalanVakitBesOldu = false;
	void executeFileNames();
	void ilkBolgeSecimi();
	void setIcon(uint8_t number);    // önceden slot'tu
    void createActions();
    void createTrayIcon();

    QElapsedTimer timer;

	QAction *emailAction;
	QAction *quitAction;
	QAction *updateAction;
	QAction *sehirSecimiAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif
