#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// saat classi 00:00 - 23:59 formatinda
class Saat {
private:
    int saat;
    int dakika;

public:
    Saat(int saat, int dakika) {
        this->saat = saat;
        this->dakika = dakika;
    }

    Saat() {
        this->saat = 0;
        this->dakika = 0;
    }

    void setSaat(int saat) {
        this->saat = saat;
    }

    void setDakika(int dakika) {
        this->dakika += dakika;
        if (this->dakika >= 60) {
            this->saat += this->dakika / 60;
            this->dakika = this->dakika % 60;
        }
    }

    int getSaat() {
        return saat;
    }

    int getDakika() {
        return dakika;
    }

    void addDakika(int dakika) { //
        this->dakika += dakika;
        if (this->dakika >= 60) {
            this->saat += this->dakika / 60;
            this->dakika = this->dakika % 60;
        }
    }
};

int saatKarsilastir(Saat saat1, Saat saat2) {
    if (saat1.getSaat() > saat2.getSaat()) {
        return 1;
    } else if (saat1.getSaat() < saat2.getSaat()) {
        return -1;
    } else {
        if (saat1.getDakika() > saat2.getDakika()) {
            return 1;
        } else if (saat1.getDakika() < saat2.getDakika()) {
            return -1;
        } else {
            return 0;
        }
    }
}

int saatFarkiGetir(Saat saat1, Saat saat2) {
    int saatFarki = 0;
    if (saat1.getSaat() > saat2.getSaat()) {
        saatFarki += (saat1.getSaat() - saat2.getSaat()) * 60;
    } else if (saat1.getSaat() < saat2.getSaat()) {
        saatFarki += (saat2.getSaat() - saat1.getSaat()) * 60;
    }
    if (saat1.getDakika() > saat2.getDakika()) {
        saatFarki += saat1.getDakika() - saat2.getDakika();
    } else if (saat1.getDakika() < saat2.getDakika()) {
        saatFarki += saat2.getDakika() - saat1.getDakika();
    }
    return saatFarki;
}

// arizaNo enum
enum ArizaNo {
    Kaporta = 1,
    Elektrik = 2,
    Mekanik = 3,
};

// arac classi
class Arac {
private:
    int aracNo;
    ArizaNo arizaNo;
    Saat atolyeGelisSaati;
    Saat istasyonGelisSaati;
    Saat teslimSaati;
    int tamirSuresi;
    int kalanTamirSuresi;
    string aracPlaka;
    bool tamirEdilmeDurumu = false;
public:
    Arac(int aracNo, ArizaNo arizaNo, Saat atolyeGelisSaati, Saat istasyonGelisSaati, Saat teslimSaati,
         int tamirSuresi, string aracPlaka) {
        this->aracNo = aracNo;
        this->arizaNo = arizaNo;
        this->atolyeGelisSaati = atolyeGelisSaati;
        this->istasyonGelisSaati = istasyonGelisSaati;
        this->teslimSaati = teslimSaati;
        this->tamirSuresi = tamirSuresi;
        this->kalanTamirSuresi = tamirSuresi;
        this->aracPlaka = aracPlaka;
    }

    int getAracNo() {
        return aracNo;
    }

    ArizaNo getArizaNo() {
        return arizaNo;
    }

    Saat getAtolyeGelisSaati() {
        return atolyeGelisSaati;
    }

    Saat getIstasyonGelisSaati() {
        return istasyonGelisSaati;
    }

    Saat getTeslimSaati() {
        return teslimSaati;
    }

    int getTamirSuresi() {
        return tamirSuresi;
    }

    string getAracPlaka() {
        return aracPlaka;
    }

    void setAracNo(int aracNo) {
        Arac::aracNo = aracNo;
    }

    void setArizaNo(ArizaNo arizaNo) {
        Arac::arizaNo = arizaNo;
    }

    void setAtolyeGelisSaati(const Saat &atolyeGelisSaati) {
        Arac::atolyeGelisSaati = atolyeGelisSaati;
    }

    void setIstasyonGelisSaati(const Saat &istasyonGelisSaati) {
        Arac::istasyonGelisSaati = istasyonGelisSaati;
    }

    void setTeslimSaati(const Saat &teslimSaati) {
        Arac::teslimSaati = teslimSaati;
    }

    void setTamirSuresi(int tamirSuresi) {
        Arac::tamirSuresi = tamirSuresi;
    }

    void setAracPlaka(const string &aracPlaka) {
        Arac::aracPlaka = aracPlaka;
    }


    bool tamirEdildimi() {
        return tamirEdilmeDurumu;
    }

    void tamirEt() {
        tamirEdilmeDurumu = true;
    }

    int getKalanTamirSuresi() const {
        return kalanTamirSuresi;
    }

    void setKalanTamirSuresi(int kalanTamirSuresi) {
        Arac::kalanTamirSuresi = kalanTamirSuresi;
    }
};

// evet diye biliyom Json ve Serliazed Name diye bişey var ordan ayarlıyon ObjectMapperda öyle yapıyorduk

// stack ve kuyruk yapısı
class Node {
public:
    Arac *veri;
    Node *sonraki;

    Node(Arac *veri) {
        this->veri = veri;
        this->sonraki = NULL;
    }
};

class Yigin {
public:
    Node *ust;

    Yigin() {
        this->ust = NULL;
    }

    void push(Arac *arac) {
        Node *node = new Node(arac);
        node->sonraki = ust;
        ust = node;
    }

    Arac *cikar() {
        if (ust == NULL) {
            return NULL;
        }

        Arac *arac = ust->veri;
        Node *temp = ust;
        ust = ust->sonraki;
        delete temp;

        return arac;
    }

    bool bosMu() {
        return ust == NULL;
    }
};

class Kuyruk {
public:
    Node *on;
    Node *arka;

    Kuyruk() {
        this->on = NULL;
        this->arka = NULL;
    }

    void ekle(Arac *arac) {
        Node *node = new Node(arac);

        if (bosMu()) {
            on = node;
            arka = node;
        } else {
            arka->sonraki = node;
            arka = node;
        }
    }

    Arac *cikar() {
        if (bosMu()) {
            return NULL;
        }

        Arac *arac = on->veri;
        Node *temp = on;

        if (on == arka) {
            on = NULL;
            arka = NULL;
        } else {
            on = on->sonraki;
        }

        delete temp;
        return arac;
    }

    bool bosMu() {
        return on == NULL;
    }
};

// eeee açsana bi varsa
Kuyruk TAMIR_EDILEN_ARACLAR = Kuyruk();


class Atolye {
private:
    string ad;
    Yigin *tamirdekiAraclar;
    Kuyruk *tamirEdilecekAraclar;
    int kapasite = 3;
    int doluluk = 0;
    Saat saat = Saat(8, 0);
public:
    Atolye(string ad, Kuyruk *tamirEdilecekAraclar) {
        this->tamirdekiAraclar = new Yigin();
        this->tamirEdilecekAraclar = tamirEdilecekAraclar;
        this->ad = ad;
    }

    void tamireBasla() {

        while (!tamirEdilecekAraclar->bosMu()) {
            Arac *tamirEdilecekArac = tamirEdilecekAraclar->cikar();
            if (doluluk == 3) {
                Arac *tamirEdilenArac1 = tamirdekiAraclar->cikar();
                tamirEdilenArac1->tamirEt();
                saat.setDakika(saat.getDakika() + tamirEdilenArac1->getTamirSuresi());
                tamirEdilenArac1->setTeslimSaati(saat);
                TAMIR_EDILEN_ARACLAR.ekle(tamirEdilenArac1);
                doluluk--;
                tumAraclarinTamirSureleriniAyarla(tamirEdilenArac1->getTamirSuresi());
                if (tamirdekiAraclar->ust->sonraki->veri->tamirEdildimi()) {
                    Arac *tamirEdilenArac2 = tamirdekiAraclar->cikar();
                    tamirEdilenArac2->tamirEt();
                    saat.setDakika(tamirEdilenArac2->getKalanTamirSuresi());
                    tamirEdilenArac2->setTeslimSaati(saat);
                    tamirEdilenArac2->setKalanTamirSuresi(0);
                    TAMIR_EDILEN_ARACLAR.ekle(tamirEdilenArac2);
                    doluluk--;
                    Arac *tamirEdilenArac3 = tamirdekiAraclar->cikar();
                    tamirEdilenArac3->setTeslimSaati(saat);
                    tamirEdilenArac3->setKalanTamirSuresi(0);
                    TAMIR_EDILEN_ARACLAR.ekle(tamirEdilenArac3);
                    doluluk--;
                    tamirdekiAraclar->push(tamirEdilecekArac);
                    doluluk++;
                } else {
                    tamirdekiAraclar->push(tamirEdilecekArac);
                    doluluk++;
                }


            } else {
                // if atolye gelis saati saaten ileriyse onu ayarla
                if (saatKarsilastir(saat, tamirEdilecekArac->getAtolyeGelisSaati()) == -1) {
                    int fark = saatFarkiGetir(saat, tamirEdilecekArac->getAtolyeGelisSaati());
                    saat.setDakika(saat.getDakika() + fark);
                    tumAraclarinTamirSureleriniAyarla(fark);
                }
                tamirdekiAraclar->push(tamirEdilecekArac);
                doluluk++;
            }

        }
    }

    void tumAraclarinTamirSureleriniAyarla(int dakika) {
        Yigin temp = *tamirdekiAraclar;
        while (temp.ust != NULL) {
            Arac *arac = temp.ust->veri;
            arac->setKalanTamirSuresi(arac->getTamirSuresi() - dakika);
            if (arac->getKalanTamirSuresi() < 0) {
                arac->setKalanTamirSuresi(0);
                arac->tamirEt();
            }
            temp.ust = temp.ust->sonraki;
        }
    }

};


// Dosya konumu Dikat ********************************************************************************
Kuyruk dosyaOku() {
    ifstream dosya("C:/Users/yasin/Downloads/arac.txt");
    if (!dosya.is_open()) {
        cerr << "Dosya acilamadi" << endl;
    }
    string satir;
    Kuyruk araclar = Kuyruk();
    while (getline(dosya, satir)) {
        stringstream ss(satir);
        string token;
        int aracNo, tamirSuresiDakika, tamirSuresi;
        ArizaNo arizaNo;
        Saat atolyeGelisSaati, istasyonGelisSaati, teslimSaati;
        string aracPlaka;

        getline(ss, token, '-');
        aracNo = stoi(token);

        getline(ss, token, '-');
        arizaNo = static_cast<ArizaNo>(stoi(token));

        getline(ss, token, '-');
        string saatFromText = token;
        int saat = stoi(saatFromText.substr(0, saatFromText.find(':')));
        int dakika = stoi(saatFromText.substr(saatFromText.find(':') + 1));
        atolyeGelisSaati.setSaat(saat);
        atolyeGelisSaati.setDakika(dakika);

        getline(ss, token, '-');
        tamirSuresi = stoi(token);

        getline(ss, token, '-');
        aracPlaka = token;

        Arac *arac = new Arac(aracNo, arizaNo, atolyeGelisSaati, istasyonGelisSaati, teslimSaati, tamirSuresi,
                              aracPlaka);
        araclar.ekle(arac);
    }
    dosya.close();
    return araclar;
}


int main() {
    Kuyruk araclar = dosyaOku();
    Kuyruk kaportaHasarliAraclar = Kuyruk();
    Kuyruk elektrikHasarliAraclar = Kuyruk();
    Kuyruk mekanikHasarliAraclar = Kuyruk();

    while (!araclar.bosMu()) {
        Arac *arac = araclar.cikar();
        switch (arac->getArizaNo()) {
            case Kaporta:
                kaportaHasarliAraclar.ekle(arac);
                break;
            case Elektrik:
                elektrikHasarliAraclar.ekle(arac);
                break;
            case Mekanik:
                mekanikHasarliAraclar.ekle(arac);
                break;
        }
    }
    Atolye *kaportaAtolyesi = new Atolye("Kaporta Atolyesi", &kaportaHasarliAraclar);
    Atolye *elektrikAtolyesi = new Atolye("Elektrik Atolyesi", &elektrikHasarliAraclar);
    Atolye *mekanikAtolyesi = new Atolye("Mekanik Atolyesi", &mekanikHasarliAraclar);

    kaportaAtolyesi->tamireBasla();
    elektrikAtolyesi->tamireBasla();
    mekanikAtolyesi->tamireBasla();
    // Dosya konumu Dikat ********************************************************************************
    ofstream file("C:/Users/yasin/Downloads/sonuc.txt");
    while (!TAMIR_EDILEN_ARACLAR.bosMu()) {
        if (file.is_open()) {
            Arac *arac = TAMIR_EDILEN_ARACLAR.cikar();
            // her aracı satır satır yazdır
            // clear /n from plaka
            string plaka = arac->getAracPlaka().substr(0, arac->getAracPlaka().find('\r'));
            file << arac->getAracNo() << "-" << arac->getArizaNo() << "-" << plaka << "-"
                 << arac->getAtolyeGelisSaati().getSaat() << ":" << arac->getAtolyeGelisSaati().getDakika() << "-"
                 << arac->getTamirSuresi() << "-" << arac->getTeslimSaati().getSaat() << ":"
                 << arac->getTeslimSaati().getDakika() << endl;
        }
    }
    file.close();
    return 0;
}










