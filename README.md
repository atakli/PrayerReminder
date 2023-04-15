# PrayerReminder
Windows ve Linux'ta çalışan, bir sonraki namaz vaktine kalan süreyi gösteren uygulama.<br>
Prayer Reminder app, on Windows and Linux. It shows the remaining time to the next prayer.

Derlemek için gereken bağımlılıklar:<br>
* Qt - 6.4.1 (daha düşük bir versiyonun da çalışma ihtimali var ama ben bununla derledim)
* UpdateController kütüphanesi ve updatecontroller.h başlık dosyası
* SingleApplication kütüphanesi ve singleapplication.h başlık dosyası

TODO:<br>
* Uygulama güncellendiği sırada açıksa inno setup'taki sonlandır'a basınca sonlandırmıyor. Task Manager'dan kapatmak gerekiyor. 
* beş ve altmış dakika süreleri değiştirilebilir olsun
* enlem boylamı otomatik alacak özellik ekle
* görev çubuğuna da simge ekleme seçeneği sun
* online vakitler yokken offline'dan devam edildiği bildirilsin. şuanda da var gibi ama yanlış. json eski ise o uyarıyı veriyor. online için de.

Paketleme öncesinde yapılacaklar:
* .exe'yi bir klasöre alıp windeployqt yap.
* namazVakitFiles'ın içindeki version.txt'yi güncelle.
* inno setup'taki versiyon bilgisini güncelle ve inno setup scriptini çalıştır
