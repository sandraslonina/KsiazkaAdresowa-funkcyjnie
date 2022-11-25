#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>


using namespace std;


string wczytajLinie() {
    string wejscie = "";
    cin.sync();
    getline (cin, wejscie);
    return wejscie;
}

char wczytajZnak() {
    string wejscie = "";
    char znak = {0};

    while (true) {
        cin.sync();
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
    }
    return znak;
}


struct InformacjeOAdresacie {
    int id = 0;
    string imie, nazwisko, numerTelefonu, email, adres;
};


vector<InformacjeOAdresacie> zaladujListeAdresatow(int liczbaAdresatow, InformacjeOAdresacie adresat) {
    string linia;
    fstream plik;
    vector<InformacjeOAdresacie> adresaci;
    char szukanyZnak = '|';

    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == true)
        {

            for (int i = 0; i < liczbaAdresatow; i++)
            {
                getline(plik,linia);

                size_t pozycja1 = linia.find(szukanyZnak);
                adresat.id = atoi((linia.substr(0,pozycja1)).c_str());

                size_t pozycja2 = linia.find(szukanyZnak, pozycja1 + 1 );
                adresat.imie = linia.substr(pozycja1 + 1,(pozycja2-pozycja1 - 1));

                size_t pozycja3 = linia.find( szukanyZnak, pozycja2 + 1 );
                adresat.nazwisko = linia.substr(pozycja2 + 1,(pozycja3-pozycja2 - 1));

                size_t pozycja4 = linia.find( szukanyZnak, pozycja3 + 1 );
                adresat.numerTelefonu = linia.substr(pozycja3 + 1,(pozycja4-pozycja3 - 1));

                size_t pozycja5 = linia.find( szukanyZnak, pozycja4 + 1 );
                adresat.email = linia.substr(pozycja4 + 1,(pozycja5-pozycja4 - 1));

                size_t pozycja6 = linia.find( szukanyZnak, pozycja5 + 1 );
                adresat.adres = linia.substr(pozycja5 + 1,(pozycja6-pozycja5 - 1));

                adresaci.push_back(adresat);
            }

    }
    plik.close();

    return adresaci;
}

int znajdzLiczbeAdresatow () {
    int liczbaAdresatow;
    int numerLinii = 0;

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good()== false)
        liczbaAdresatow = 1;

    else {
        string linia;
        while (getline(plik, linia)) {
            numerLinii++;
        }
        liczbaAdresatow = numerLinii;
    }

    plik.close();
    return liczbaAdresatow;
}

int znajdzOstatniNumerId (int liczbaAdresatow) {

    string linia;
    int ostatniNumerId = 0;

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);
    for (int i = 0; i < liczbaAdresatow; i++) {
        getline(plik,linia);

        char szukanyZnak='|';
        size_t pozycja1 = linia.find(szukanyZnak);
        ostatniNumerId = atoi((linia.substr(0,pozycja1)).c_str());
    }
    plik.close();

    return ostatniNumerId;
}

void zapiszNowegoAdresata(InformacjeOAdresacie adresat, vector<InformacjeOAdresacie>adresaci, int liczbaAdresatow) {
    string imie, nazwisko, numerTelefonu, email, adres;
    int id;

    cout << "Podaj imie: ";
    imie = wczytajLinie();

    cout << "Podaj nazwisko: ";
    nazwisko = wczytajLinie();

    cout << "Podaj numer telefonu: ";
    numerTelefonu = wczytajLinie();

    cout << "Podaj e-mail: ";
    email = wczytajLinie();

    cout << "Podaj adres: ";
    adres = wczytajLinie();

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == false)
        id = 1;

    else
        id = znajdzOstatniNumerId(liczbaAdresatow) + 1;

    plik.close();

    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    plik << id << '|' << imie << '|' << nazwisko << '|' << numerTelefonu << '|' << email << '|' << adres << '|' << endl;

    plik.close();

    cout << "Adresat " << imie <<  " " << nazwisko << " zostal dodany do ksiazki adresowej!" <<  endl;

    Sleep(2000);
}

void wykszukajAdresataPoImieniu(vector<InformacjeOAdresacie>adresaci) {
    string imie;
    string weryfikacja = "";

    cout << "Podaj szukane imie adresata: ";
    cin >> imie;

    for(unsigned int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].imie == imie) {
            weryfikacja = "Znaleziono";
            cout << endl;
            cout << "ID:" << adresaci[i].id << endl;
            cout << "Imie i nazwisko: "<< adresaci[i].imie << " "<< adresaci[i].nazwisko << endl;
            cout << "Numer telefonu: " << adresaci[i].numerTelefonu << endl;
            cout << "E-mail: " << adresaci[i].email << endl;
            cout << "Adres: " << adresaci[i].adres << endl ;
        }
    }
    cout << endl;

    if(weryfikacja == "Znaleziono") {
        cout << "Wyswietlono wszystkich adresatow o takim imieniu!" << endl;
        cout << endl;
    } else {
        cout << "Brak adresatow o takim imieniu!" << endl;
        cout << endl;
    }

    cout << "Nacisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void wyszukajAdresataPoNazwisku(vector<InformacjeOAdresacie>adresaci) {
    string nazwisko;
    string weryfikacja = "";

    cout << "Podaj szukane nazwisko adresata: ";
    cin >> nazwisko;
    for(unsigned int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].nazwisko == nazwisko) {
            weryfikacja = "Znaleziono";
            cout << endl;
            cout << "ID:" << adresaci[i].id << endl;
            cout << "Imie i nazwisko: "<< adresaci[i].imie << " "<< adresaci[i].nazwisko << endl;
            cout << "Numer telefonu: " << adresaci[i].numerTelefonu << endl;
            cout << "E-mail: " << adresaci[i].email << endl;
            cout << "Adres: " << adresaci[i].adres << endl ;
        }
    }
    cout<<endl;

    if(weryfikacja == "Znaleziono") {
        cout << "Wyswietlono wszystkich adresatow o takim nazwisku!" << endl;
        cout << endl;
    } else {
        cout << "Brak adresatow o takim nazwisku!" << endl;
        cout << endl;
    }

    cout << "Nacisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void wyswietlWszystkichAdresatow(vector<InformacjeOAdresacie> adresaci) {
    system("cls");

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == false) {
        cout << "Twoja ksiazka adresowa jest pusta!" << endl;
    }

    else {
        for(unsigned int i = 0; i < adresaci.size(); i++) {
            cout << "ID:                 " << adresaci[i].id << endl;
            cout << "Imie:               " << adresaci[i].imie << endl;
            cout << "Nazwisko:           " << adresaci[i].nazwisko << endl;
            cout << "Numer telefonu:     " << adresaci[i].numerTelefonu << endl;
            cout << "E-mail:             " << adresaci[i].email << endl;
            cout << "Adres:              " << adresaci[i].adres << endl;
            cout << endl;
        }
    }
    plik.close();

    cout << endl;

    cout << "Nacisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();

}

void usunAdresataZKsiazki (int liczbaAdresatow, vector<InformacjeOAdresacie> adresaci) {
    int id;
    char potwierdzenieWyboru;
    cout << "Podaj ID adresata, ktorego chcesz usunac z ksiazki adresowej: ";
    cin >> id;
    cout << "Czy napewno usunac adresata o numerze ID: " << id << "? (potwierdz klawiszem t) ";
    cin >> potwierdzenieWyboru;
    cout << endl;
    bool wybor = false;

    if (potwierdzenieWyboru == 't') {
        for(unsigned int i = 0; i < adresaci.size(); i++) {
            if (adresaci[i].id == id)
                wybor = true;
        }

        if (wybor == false) {
            cout << "Adresat o takim ID nie istnieje!" << endl;
        }

        else {
            fstream plik, plik2;
            string linia;

            plik.open("ksiazkaAdresowa.txt", ios::in);
            plik2.open("ksiazkaAdresowa_tymczasowa.txt", ios::out);

            for (int i = 0; i < liczbaAdresatow; i++) {
                getline(plik,linia);

                char szukanyZnak = '|';
                size_t pozycja1 = linia.find(szukanyZnak);
                int poszukiwaneId = atoi((linia.substr(0,pozycja1)).c_str());

                if (poszukiwaneId != id) {
                    plik2 << linia << endl;
                }
            }

            plik.close();
            plik2.close();

            remove("ksiazkaAdresowa.txt");
            rename( "ksiazkaAdresowa_tymczasowa.txt", "ksiazkaAdresowa.txt" );

            cout << "Adresat z ksiazki adresowej zostal usuniety! ";
        }

        cout << endl;
        cout << "Nacisnij enter aby wrocic do menu glownego.";
        getchar();
        getchar();
    }
}

void edytujAdresata (int liczbaAdresatow, vector<InformacjeOAdresacie> adresaci) {
    int id;
    char wyborZMenuEdycji;
    string nowaDana;
    string poprawnosc = "";

    cout << "Podaj numer ID adresata, ktorego chcesz edytowac: ";
    cin >> id;

    for(unsigned int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].id == id) {
            poprawnosc = "ID poprawne";
        }
    }

    if (poprawnosc == "ID poprawne") {
        cout << endl;
        cout << ">>MENU EDYCJA - ktora dana chcesz edytowac? <<" << endl;
        cout << "1 - Imie" << endl;
        cout << "2 - Nazwisko" << endl;
        cout << "3 - Numer telefonu" << endl;
        cout << "4 - E-mail" << endl;
        cout << "5 - Adres" << endl;
        cout << "6 - Powrot do menu glownego" << endl;
        cout << endl;
        cout << "Twoj wybor: ";

        wyborZMenuEdycji = wczytajZnak();

        switch (wyborZMenuEdycji) {
        case '1':
            for(unsigned int i = 0; i < adresaci.size(); i++) {
                if(adresaci[i].id == id) {
                    cout << "Aktualne imie adresata: " << adresaci[i].imie <<endl;
                    cout << "Nowe imie adresata: " ;
                    nowaDana = wczytajLinie();
                    adresaci[i].imie = nowaDana;
                    cout << endl << "Imie zostalo zmienione!"<< endl;
                }
            }
            break;

        case '2':
            for(unsigned int i = 0; i < adresaci.size(); i++) {
                if(adresaci[i].id == id) {
                    cout << "Aktualne nazwisko adresata: " << adresaci[i].nazwisko <<endl;
                    cout << "Nowe nazwisko adresata: " ;
                   nowaDana = wczytajLinie();
                    adresaci[i].nazwisko = nowaDana;
                    cout << endl << "Nazwisko zostalo zmienione!"<< endl;
                }
            }
            break;

        case '3':
            for(unsigned int i = 0; i < adresaci.size(); i++) {
                if(adresaci[i].id == id) {
                    cout << "Aktualny numer telefonu adresata: " << adresaci[i].numerTelefonu <<endl;
                    cout << "Nowy numer telefonu adresata: " ;
                    nowaDana = wczytajLinie();
                    adresaci[i].numerTelefonu = nowaDana;
                    cout << endl << "Numer telefonu zostal zmieniony!"<< endl;
                }
            }
            break;

        case '4':
            for(unsigned int i = 0; i < adresaci.size(); i++) {
                if(adresaci[i].id == id) {
                    cout << "Aktualny email adresata: " << adresaci[i].email <<endl;
                    cout << "Nowy email adresata: " ;
                    cin >> nowaDana;
                    adresaci[i].email = nowaDana;
                    cout << endl << "Email zostal zmieniony!"<< endl;
                }
            }
            break;

        case '5':
            for(unsigned int i = 0; i < adresaci.size(); i++) {
                if(adresaci[i].id == id) {
                    cout << "Aktualny adres adresata: " << adresaci[i].adres <<endl;
                    cout << "Aktualny adres adresata: " ;
                    cin.sync();
                    getline(cin, nowaDana);
                    adresaci[i].adres = nowaDana;
                    cout << endl << "Adres zostal zmieniony!"<< endl;
                }
            }
            break;

        case '6':
            return;

        }

        fstream plik, plik2;
        string linia;

        plik.open("ksiazkaAdresowa.txt", ios::in);
        plik2.open("ksiazkaAdresowa_tymczasowa.txt", ios::out);

        for (int i=0; i < liczbaAdresatow; i++) {
            getline(plik,linia);

            char szukanyZnak = '|';
            size_t pozycja1 = linia.find(szukanyZnak);
            int poszukiwaneId = atoi((linia.substr(0,pozycja1)).c_str());

            if (poszukiwaneId == id) {
                for(unsigned int zmienionaPozycja = 0; zmienionaPozycja < adresaci.size(); zmienionaPozycja++) {
                    if(adresaci[zmienionaPozycja].id == id) {
                        plik2 << adresaci[zmienionaPozycja].id << '|' << adresaci[zmienionaPozycja].imie << '|' << adresaci[zmienionaPozycja].nazwisko << '|' << adresaci[zmienionaPozycja].numerTelefonu << '|' << adresaci[zmienionaPozycja].email << '|' << adresaci[zmienionaPozycja].adres << '|' << endl;
                    }
                }
            } else {
                plik2 << linia << endl;
            }
        }

        plik.close();
        plik2.close();

        remove("ksiazkaAdresowa.txt");
        rename( "ksiazkaAdresowa_tymczasowa.txt", "ksiazkaAdresowa.txt" );
    }

    else {
        cout << "Adresat o podanym ID nie istnieje!" << endl;
    }

    cout << endl;
    cout << "Nacisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}


int main() {
    InformacjeOAdresacie adresat;

    int liczbaAdresatow = znajdzLiczbeAdresatow();

    vector<InformacjeOAdresacie> adresaci;

    char wyborZMenuGlownego;


    while(true)

    {
        system("cls");
        cout << ">>>KSIAZKA ADRESOWA<<<" << endl;
        cout << endl;
        cout << ">>MENU GLOWNE - dostepne opcje:<<" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj adresata po imieniu" << endl;
        cout << "3. Wyszukaj adresata po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << endl;
        cout << "Wybierz opcje menu glownego: ";

        wyborZMenuGlownego = wczytajZnak();
        cout << endl;

        liczbaAdresatow = znajdzLiczbeAdresatow();
        adresaci = zaladujListeAdresatow(liczbaAdresatow, adresat);

        switch (wyborZMenuGlownego) {
        case '1':
            zapiszNowegoAdresata(adresat, adresaci, liczbaAdresatow);
            break;
        case '2':
            wykszukajAdresataPoImieniu(adresaci);
            break;
        case '3':
            wyszukajAdresataPoNazwisku(adresaci);
            break;
        case '4':
            wyswietlWszystkichAdresatow(adresaci);
            break;
        case '5':
            usunAdresataZKsiazki(liczbaAdresatow, adresaci);
            liczbaAdresatow = znajdzLiczbeAdresatow();
            break;
        case '6':
            edytujAdresata(liczbaAdresatow, adresaci);
            break;
        case '9':
            exit(0);
        }
    }

    return 0;
}
