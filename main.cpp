#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
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

int wczytajLiczbeCalkowita() {
    string wejscie = "";
    int liczba = 0;

    while (true) {
        cin.sync();
        getline(cin, wejscie);

        stringstream myStream(wejscie);

        if (myStream >> liczba)
            break;

        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }

    return liczba;
}

struct InformacjeOUzytkowniku {
    int idUzytkownika = 0;
    string login, haslo;
};

struct InformacjeOAdresacie {
    int id, idUzytkownika = 0;
    string imie, nazwisko, numerTelefonu, email, adres;
};

vector <InformacjeOUzytkowniku> zaladujListeUzytkownikow (int liczbaUzytkownikow, InformacjeOUzytkowniku uzytkownik) {
    string linia;
    vector<InformacjeOUzytkowniku> uzytkownicy;
    char szukanyZnak = '|';


    fstream plik;
    plik.open("listaUzytkownikow.txt", ios::in);

    if(plik.good() == true) {

        for (int i = 0; i < liczbaUzytkownikow; i++) {
            getline(plik,linia);

            size_t pozycja1 = linia.find(szukanyZnak);
            uzytkownik.idUzytkownika = atoi((linia.substr(0, pozycja1)).c_str());

            size_t pozycja2 = linia.find(szukanyZnak, pozycja1 + 1 );
            uzytkownik.login = linia.substr(pozycja1 + 1,(pozycja2-pozycja1 - 1));

            size_t pozycja3 = linia.find( szukanyZnak, pozycja2 + 1 );
            uzytkownik.haslo = linia.substr(pozycja2 + 1,(pozycja3-pozycja2 - 1));

            uzytkownicy.push_back(uzytkownik);
        }
    }

    plik.close();

    return uzytkownicy;

}

vector<InformacjeOAdresacie> zaladujListeAdresatow(int liczbaAdresatow, InformacjeOAdresacie adresat, int idZalogowanegoUzytkownika) {
    string linia;
    vector<InformacjeOAdresacie> adresaci;
    char szukanyZnak = '|';
    
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == true) {
        while (!plik.eof()) {

            for (int i = 0; i < liczbaAdresatow; i++) {
                getline(plik,linia);

                size_t pozycja1 = linia.find(szukanyZnak);
                adresat.id = atoi((linia.substr(0,pozycja1)).c_str());

                size_t pozycja2 = linia.find(szukanyZnak, pozycja1 + 1 );
                adresat.idUzytkownika = atoi((linia.substr(pozycja1 + 1,(pozycja2-pozycja1 - 1))).c_str());

                size_t pozycja3 = linia.find( szukanyZnak, pozycja2 + 1 );
                adresat.imie = linia.substr(pozycja2 + 1,(pozycja3-pozycja2 - 1));

                size_t pozycja4 = linia.find( szukanyZnak, pozycja3 + 1 );
                adresat.nazwisko = linia.substr(pozycja3 + 1,(pozycja4-pozycja3 - 1));

                size_t pozycja5 = linia.find( szukanyZnak, pozycja4 + 1 );
                adresat.numerTelefonu = linia.substr(pozycja4 + 1,(pozycja5-pozycja4 - 1));

                size_t pozycja6 = linia.find( szukanyZnak, pozycja5 + 1 );
                adresat.email = linia.substr(pozycja5 + 1,(pozycja6-pozycja5 - 1));

                size_t pozycja7 = linia.find( szukanyZnak, pozycja6 + 1 );
                adresat.adres = linia.substr(pozycja6 + 1,(pozycja7-pozycja6 - 1));


                if (adresat.idUzytkownika == idZalogowanegoUzytkownika) {
                    adresaci.push_back(adresat);
                }
            }
        }
    }

    plik.close();

    return adresaci;
}

int znajdzLiczbeUzytkownikow() {
    int liczbaUzytkownikow;
    int numerLinii = 0;

    fstream plik;
    plik.open("listaUzytkownikow.txt", ios::in);

    if(plik.good()== false)
        liczbaUzytkownikow = 0;

    else {
        string linia;

        while (getline(plik, linia)) {
            numerLinii++;
        }

        liczbaUzytkownikow = numerLinii;
    }

    plik.close();
    return liczbaUzytkownikow;
}


int znajdzLiczbeAdresatow () {
    int liczbaAdresatow;
    int numerLinii = 0;

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good()== false)
        liczbaAdresatow = 0;

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

        char szukanyZnak = '|';
        size_t pozycja1 = linia.find(szukanyZnak);
        ostatniNumerId = atoi((linia.substr(0,pozycja1)).c_str());
    }

    plik.close();

    return ostatniNumerId;
}

void zapiszNowegoAdresata(InformacjeOAdresacie adresat, vector<InformacjeOAdresacie>adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika) {
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

    plik << id << '|' << idZalogowanegoUzytkownika << '|' << imie << '|' << nazwisko << '|' << numerTelefonu << '|' << email << '|' << adres << '|' << endl;

    plik.close();

    cout << endl;
    cout << "Adresat " << imie <<  " " << nazwisko << " zostal dodany do ksiazki adresowej!" <<  endl;

    cout << endl;
    cout << "Nacisnij enter aby wrocic do menu glownego.";
    getchar();
    return;
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
    }

    else {
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
    }

    else {
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
    return;
}

void usunAdresataZKsiazki (int liczbaAdresatow, vector<InformacjeOAdresacie> adresaci) {
    int id;
    char potwierdzenieWyboru;
    cout << "Podaj ID adresata, ktorego chcesz usunac z ksiazki adresowej: ";
    id = wczytajLiczbeCalkowita();
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
            }

            else {
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
    return;
}

void rejestracjaUzytkownika (int liczbaUzytkownikow, vector<InformacjeOUzytkowniku> uzytkownicy) {
    int idUzytkownika;
    string login, haslo;
    cout << "Podaj nowy login: ";
    login = wczytajLinie();

    int i = 0;

    while (i < liczbaUzytkownikow) {
        if (uzytkownicy[i].login == login) {
            cout << "Uzytkownik o takim loginie istnieje. Wpisz inna nazwe uzytkownika: ";
            login = wczytajLinie();
            i = 0;
        }

        else {
            i++;
        }
    }

    cout << "Podaj haslo: ";
    haslo = wczytajLinie();

    fstream plik;
    plik.open("listaUzytkownikow.txt", ios::in);

    if(plik.good() == false)
        idUzytkownika = 1;

    else
        idUzytkownika = uzytkownicy[liczbaUzytkownikow-1].idUzytkownika + 1;

    plik.close();

    plik.open("listaUzytkownikow.txt", ios::out | ios::app);
    plik << idUzytkownika << '|' << login << '|' << haslo << '|' << endl;
    plik.close();

    cout << "Konto zostalo zalozone!";
    Sleep(1000);
}



int logowanie (int liczbaUzytkownikow, vector <InformacjeOUzytkowniku> uzytkownicy) {
    string login, haslo;

    cout << "Podaj login: ";
    login = wczytajLinie();

    int i = 0;

    while (i < liczbaUzytkownikow) {
        if (uzytkownicy[i].login == login) {
            for (int proby = 0; proby < 3; proby++) {
                cout << endl << "Login poprawny. Podaj haslo. Pozostalo: " << 3 - proby << " proby" << endl;;
                haslo = wczytajLinie();

                if (uzytkownicy[i].haslo == haslo) {
                    cout << endl << "Zalogowales sie do ksiazki adresowej!" << endl;
                    Sleep (1000);
                    return uzytkownicy[i].idUzytkownika;
                }

                else {
                    cout << "Wprowadzono bledne haslo!" << endl;
                }

            }

            cout << "Podales 3 razy bledne haslo. Twoje konto pozostanie zablokowane. Poczekaj 3 sekundy przed kolejna proba logowania!" << endl;
            Sleep (3000);
            return 0;
        }

        i++;

    }

    cout << "Nie ma uzytkownika z takim loginem!" << endl;
    Sleep (1500);
    return 0;

}

void zmianaHasla (int liczbaUzytkownikow, vector<InformacjeOUzytkowniku> uzytkownicy, int idZalogowanegoUzytkownika) {
    fstream plik;
    string haslo;
    cout << "Podaj nowe haslo: ";
    haslo = wczytajLinie();

    for (int i = 0; i < liczbaUzytkownikow; i++) {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione"<<endl;
            Sleep (2000);
        }
    }

    plik.open("listaUzytkownikow.txt", ios::out);

    for(int i = 0; i < liczbaUzytkownikow; i++) {
        plik << uzytkownicy[i].idUzytkownika << '|' << uzytkownicy[i].login << '|' << uzytkownicy[i].haslo << '|' << endl;
    }

    plik.close();
}

int main() {
    InformacjeOAdresacie adresat;
    InformacjeOUzytkowniku uzytkownik;

    int liczbaAdresatow = znajdzLiczbeAdresatow();
    int liczbaUzytkownikow = znajdzLiczbeUzytkownikow();


    vector<InformacjeOAdresacie> adresaci;
    vector<InformacjeOUzytkowniku> uzytkownicy = zaladujListeUzytkownikow (liczbaUzytkownikow, uzytkownik);

    char wyborZMenuLogowania;
    char wyborZMenuGlownego;

    int idZalogowanegoUzytkownika = 0;

    while(true) {
        if (idZalogowanegoUzytkownika == 0) {
            system ("cls");
            cout << ">>> MENU LOGOWANIE <<<" << endl;
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "3. Zamknij program" << endl;
            cout << endl;
            cout << "Twoj wybor: " << endl;

            wyborZMenuLogowania = wczytajZnak();

            switch (wyborZMenuLogowania) {
            case '1':
                idZalogowanegoUzytkownika = logowanie(liczbaUzytkownikow, uzytkownicy);
                break;

            case '2':

                rejestracjaUzytkownika(liczbaUzytkownikow, uzytkownicy);
                liczbaUzytkownikow = znajdzLiczbeUzytkownikow();
                uzytkownicy = zaladujListeUzytkownikow (liczbaUzytkownikow, uzytkownik);
                break;

            case '3':
                exit(0);
                break;

            default:
                cout << endl << "Nie ma takiej opcji w menu logowania. Dokonaj wyboru jeszcze raz!" << endl << endl;
                system ("pause");
                break;
            }
        }

        else {
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
            cout << "----------------------------" << endl;
            cout << "7. Zmiana hasla" << endl;
            cout << "8. Wyloguj sie" << endl;
            cout << "----------------------------" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << endl;
            cout << "Wybierz opcje z menu glownego: ";

            wyborZMenuGlownego = wczytajZnak();
            cout << endl;

            liczbaAdresatow = znajdzLiczbeAdresatow();
            adresaci = zaladujListeAdresatow(liczbaAdresatow, adresat, idZalogowanegoUzytkownika);

            switch (wyborZMenuGlownego) {
            case '1':
                zapiszNowegoAdresata(adresat, adresaci, liczbaAdresatow, idZalogowanegoUzytkownika);
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

            case '7':
                zmianaHasla (liczbaUzytkownikow, uzytkownicy, idZalogowanegoUzytkownika);
                uzytkownicy = zaladujListeUzytkownikow(liczbaUzytkownikow, uzytkownik);
                break;

            case '8':
                idZalogowanegoUzytkownika = 0;
                break;

            case '9':
                exit(0);

            default:
                cout << endl << "Nie ma takiej opcji w menu glownym. Dokonaj wyboru jeszcze raz" << endl << endl;
                system ("pause");
                break;
            }
        }
    }

    return 0;
}
