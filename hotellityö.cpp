//Aleksi Niemi
//Hotelli harjoitustyö, 3-4p


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

using namespace std;

const int MIN_HUONEET = 40;
const int MAX_HUONEET = 300;
const int YHDEN_HENGEN_HINTA = 100;
const int KAHDEN_HENGEN_HINTA = 150;


    void tulostaMenu();
    int tarkistaSyote();
    void varaaHuone(vector<bool>& huoneet, int huonenumero);
    bool tarkistaVarattu(const vector<bool>& huoneet, int huonenumero);
    int laskeLasku(int yot, int hinta, int alennus);
    int arvoAlennus();
    void naytaVaraustilanne(const vector<bool>& YhdenHengenHuoneet, const vector<bool>& KahdenHengenHuoneet);

int main() {
    srand(static_cast<unsigned>(time(0))); // Satunnaisluvut

    // Huoneiden määrän arpominen
        int huoneidenMaara = (MIN_HUONEET + rand() % ((MAX_HUONEET - MIN_HUONEET + 1) / 2)) * 2;

    // Huoneiden jako
        int YhdenHengenMaara = huoneidenMaara / 2;
        int KahdenHengenMaara = huoneidenMaara / 2;
    vector<bool> YhdenHengenHuoneet(YhdenHengenMaara, false);
    vector<bool> KahdenHengenHuoneet(KahdenHengenMaara, false);

        cout << "Tervetuloa varaamaan hotellihuoneita!" << endl;
        cout << "Hotellissamme on " << YhdenHengenMaara << " yhden hengen huonetta ja "
            << KahdenHengenMaara << " kahden hengen huonetta." << endl;

    int valinta;
    do {
        tulostaMenu();
        valinta = tarkistaSyote();

        switch (valinta) {
        case 1: {
            // Huone varaus
            cout << "Valitse huonetyyppi (1 = yhden hengen, 2 = kahden hengen): ";
            int huonetyyppi = tarkistaSyote();

            if (huonetyyppi == 1 || huonetyyppi == 2) {
                vector<bool>& huoneet = (huonetyyppi == 1) ? YhdenHengenHuoneet : KahdenHengenHuoneet;
                int huoneidenMaara = huoneet.size();

                cout << "Anna huonenumero (1-" << huoneidenMaara << "): ";
                int huonenumero = tarkistaSyote();

                if (huonenumero < 1 || huonenumero > huoneidenMaara) {
                    cout << "Virhe: Huonenumero ei ole välillä 1-" << huoneidenMaara << ".\n";
                    break;
                }

                if (tarkistaVarattu(huoneet, huonenumero)) {
                    cout << "Huone " << huonenumero << " on jo varattu. Kokeile toista huonetta.\n";
                }
                else {
                    cout << "Syötä öiden määrä: ";
                    int yot = tarkistaSyote();

                    if (yot <= 0) {
                        cout << "Öiden määrän ei voi olla negatiivinen.\n";
                    }
                    else {
                        int alennus = arvoAlennus();
                        int hinta = (huonetyyppi == 1) ? YHDEN_HENGEN_HINTA : KAHDEN_HENGEN_HINTA;

                        varaaHuone(huoneet, huonenumero);
                        int loppusumma = laskeLasku(yot, hinta, alennus);

                        cout << "Huone " << huonenumero << " varattu " << yot << " yöksi.\n"
                            << "Loppusumma on " << loppusumma << " euroa (alennus " << alennus << "%).\n";
                    }
                }
            }
            else {
                cout << "Kyseistä huonetyyppiä ei ole. Valitse joko 1 tai 2.\n";
            }
            break;
        }
        case 2:
            // Varaustilanne
            naytaVaraustilanne(YhdenHengenHuoneet, KahdenHengenHuoneet);
            break;
        case 3:
            // Poistuminen
            cout << "Kiitos käynnistä!\n";
            break;
        default:
            cout << "Virheellinen valinta, Yritä uudelleen.\n";
        }
    } while (valinta != 3);

    return 0;
}

void tulostaMenu() {
    cout << "\nValikko:\n";
     cout << "1. Varaa huone\n";
      cout << "2. Näytä huoneiden varaustilanne\n";
       cout << "3. Lopeta\n";
        cout << "Valintasi: ";
}

int tarkistaSyote() {
    int luku;
    while (!(cin >> luku)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Virheellinen syöte. Anna numero: ";
    }
    return luku;
}

    void varaaHuone(vector<bool>& huoneet, int huonenumero) {
        huoneet[huonenumero - 1] = true;
}

bool tarkistaVarattu(const vector<bool>& huoneet, int huonenumero) {
    return huoneet[huonenumero - 1];
}

    int laskeLasku(int yot, int hinta, int alennus) {
        double lopullinenHinta = yot * hinta * (1 - alennus / 100.0);
        return static_cast<int>(lopullinenHinta);
}

int arvoAlennus() {
    int alennukset[] = { 0, 10, 20 };
    return alennukset[rand() % 3];
}

    void naytaVaraustilanne(const vector<bool>& yhdenHengenHuoneet, const vector<bool>& kahdenHengenHuoneet) {
        cout << "Yhden hengen huoneet:\n";
        for (size_t i = 0; i < yhdenHengenHuoneet.size(); ++i) {
        cout << "Huone " << (i + 1) << ": " << (yhdenHengenHuoneet[i] ? "Varattu" : "Vapaa") << endl;
    }
    cout << "\nKahden hengen huoneet:\n";
    for (size_t i = 0; i < kahdenHengenHuoneet.size(); ++i) {
    cout << "Huone " << (i + 1) << ": " << (kahdenHengenHuoneet[i] ? "Varattu" : "Vapaa") << endl;
    }
}
