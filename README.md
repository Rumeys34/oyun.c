-> SDL/SDL2 ile Uzay Temalı Savaş Oyunu <-

Bu proje,Kocaeli Üniversitesi Yazılım Mühendisliği 1. Sınıf Programlama II
dersi kapsamında geliştirilmiş, C dili ve SDL/SDL2  kütüphanesi kullanılarak yaptığım Space Invaders'e benzeyen bir uzay savaşı oyunudur.

 -> Oyun Özellikleri ve Mekanikler

* Dinamik Seviye Sistemi: Her düşman dalgası tamamen temizlendiğinde seviye atlanır. Seviye arttıkça düşmanların hareket hızları ve düşman sayısı belli bir oranda artar.
* Ortak Bellek Kullanımı:Grafik resimleri belleğe döngüler içinde yüzlerce kez değil, açılışta yalnızca 1 kez yüklenir. Tüm mermiler ve aktörler bu resimleri pointer'lar aracılığıyla ortaklaşa kullanır.Bunun sayesinde hafıza şişmesinin önün geçilir.
* Barikat Dinamikleri:Oyuncu gemisinin önünde konumlandırılmış 4 adet koruyucu bariyer bulunur. Bu bariyerler düşman mermilerinden hasar aldıkça can sayısını azalır.Üç renk bariyer vardır.Bunlardan bordo olanın bir,mor olanın iki,mavi olanın üç canı vardır.
* Ekran Durumu Yönetimi: Oyun; giriş Ekranı, nasıl oynanır (How to Play) ekranı,oyun ekranı ve skoru gösteren çıkış ekranı olmak üzere 4 enum durumu ile yönetilir.

-> Kontroller ve Oynanış

* Sol Ok Tuşu:Oyuncu gemisini sola hareket ettirir.
* Sağ Ok Tuşu:Oyuncu gemisini sağa hareket ettirir.
* Space Tuşu:Oyuncu gemisinin mermisini ateşler.

Oyunun Amacı:Başlangıçta 5 olan can hakları tükenmeden önce düşman gemilerini yok ederek en yüksek skora ulaşmaktır. Her 5 seviyede bir gemi +1 ekstra can hakkı kazanır ve her yok ettiğimiz gemi 10 puandır.

-> Kurulum ve Bağımlılıklar

Projenin derlenebilmesi ve çalışabilmesi için bilgisayarınızda SDL2 kütüphanelerinin yüklü olması gerekmektedir.

->Derleme ve Çalıştırma
Proje dosyasında bulunan Makefile yardımıyla oyunu doğrudan terminalden derleyebilirsiniz. 
* make clean: Varsa eski nesne dosyalarını temizlemek için ilk yazılır.
* make:Projeyi derlemek için yazılır.
* make run/./uzay_oyunu:Oyunu başlatmak için yazılır.

-> Akademik Bilgiler 
* Öğrenci: Rümeysa Ertekin
* Öğrenci Numarası: 240229083
* Üniversite: Kocaeli Üniversitesi
* Bölüm: Yazılım Mühendisliği 
* Ders: Programlama II