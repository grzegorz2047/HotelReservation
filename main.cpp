#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "fileio.h"
#include "stringutils.h"
#include "User.h"
#include "Offer.h"
#include <map>
#include <iomanip>
#include <regex>

    //std::vector<User> users;
std::vector<std::string> userData;
std::map<std::string, User> users;
std::vector<std::string> offerData;
std::vector<Offer> offers;
std::string loggedInUsername;

struct Filter {
    std::string hotelName;
    int freeNum;
    float price;
    std::string startDate;
    std::string endDate;
};


enum PROGRAM_STATE{
    EXIT_SOFT = 0,
    TO_LOGIN_PAGE = 1,
    BACK_TO_MAIN_MENU = 2,
    TO_CLIENT_INTERFACE = 3,
    TO_OWNER_INTERFACE = 4,
    SHOW_HELP = 5
};
    void clear_screen(){
        system("cls||clear");
    }
    int showStartMenu(){
        std::string char_input;
        int input = 0;
        do{
            std::cout<< "Wybierz zadanie (nr), ktore chcesz wykonac: "<<std::endl;
            std::cout << "1. Zaloguj sie" << std::endl;
            std::cout << "2. Stworz uzytkownika" << std::endl;
            std::cout << "3. Usun uzytkownika" << std::endl;
            std::cout << "4. Wyswietl pomoc"<< std::endl;
            std::cout << "5. Zakoncz dzialanie programu"<< std::endl;

            std::cin >> char_input;
            input = atoi(char_input.c_str());
            if(input == 0){
                clear_screen();
                std::cout<< "Podany znak nie jest cyfra lub wpisales zla opcje! Sprobuj ponownie!"<<std::endl;
            }else{
                if(char_input != "1" && char_input != "2" && char_input != "3" && char_input != "4" && char_input != "5" && char_input != "6"){
                    clear_screen();
                    std::cout<< "Wybrales zla opcje! Sprobuj ponownie!"<<std::endl;
                    input = 0;
                }
            }
        }while(input == 0);
        return input;
    }

    showOffersUsingFilters(){
        Filter filter;
        std::cout << "Podaj nazwe szukanego hotelu! W innym przypadku wpisz brak." << std::endl;
        std::cin >> filter.hotelName;
        std::cout << "Podaj ilosc miejsc! W innym przypadku wpisz brak." << std::endl;
        std::string val;
        std::cin >> val;
        filter.freeNum = atoi(val.c_str());
        if(filter.freeNum == 0){
            filter.freeNum = 0;
        }
        std::cout << "Podaj podaj cene! W innym przypadku wpisz brak." << std::endl;
                std::cin >> val;
        filter.price = atof(val.c_str());
        if(filter.price == 0){
            filter.price = 0;
        }
        //std::cout << "Podaj startowa date! Np. \"20-12-2016\" (bez cudzys³owia). W innym przypadku wpisz brak." << std::endl;
        //std::cout << "Podaj koncowa date! Np. \"20-12-2016\" (bez cudzys³owia). W innym przypadku wpisz brak." << std::endl;
        clear_screen();
        std::cout << "Dostepne oferty: " << std::endl;
        std::cout <<'|' << std::setw(8) << "Id oferty" << '|' << std::setw(20) << "Nazwa hotelu" << '|' << std::setw(20) << "Rezerwujacy" << '|' << std::setw(20) << "cena" << '|' << std::setw(20) << "liczba miejsc" << '|'  << std::setw(20) << "stan"<< '|' << std::endl;
        for(int i = 0; i < offers.size(); i++) {
            Offer offer = offers[i];
            if((offer.getHotelName() == filter.hotelName) && filter.hotelName != "brak"){
                std::cout <<'|' << std::setw(8) << (i) << "." << '|' << std::setw(20) << offer.getHotelName() << '|' << std::setw(20) << offer.getWhoReserved() << '|' << std::setw(20) << offer.getPrice() << '|' << std::setw(20) << offer.getFreeNum() << '|' << std::setw(20) << offer.getOfferStateString() << '|' << std::endl;
            }
            else if((atoi(offer.getFreeNum().c_str()) == filter.freeNum)  && filter.freeNum != 0){
                std::cout <<'|' << std::setw(8) << (i) << "." << '|' << std::setw(20) << offer.getHotelName() << '|' << std::setw(20) << offer.getWhoReserved() << '|' << std::setw(20) << offer.getPrice() << '|' << std::setw(20) << offer.getFreeNum() << '|' << std::setw(20) << offer.getOfferStateString() << '|' << std::endl;
            }
            else if((offer.getPrice() == filter.price)  && filter.price != 0){
                std::cout <<'|' << std::setw(8) << (i) << "." << '|' << std::setw(20) << offer.getHotelName() << '|' << std::setw(20) << offer.getWhoReserved() << '|' << std::setw(20) << offer.getPrice() << '|' << std::setw(20) << offer.getFreeNum() << '|' << std::setw(20) << offer.getOfferStateString() << '|' << std::endl;
            }else{
                std::cout << "" << std::endl;
                std::cout << "Brak ofert z takimi parametrami";
                std::cout << "" << std::endl;
            }
        }
         std::cout << "" << std::endl;
         return BACK_TO_MAIN_MENU;
    }
    int showOffers(){
        clear_screen();
        std::cout << "Dostepne oferty: " << std::endl;
        std::cout <<'|' << std::setw(8) << "Id oferty" << '|' << std::setw(20) << "Nazwa hotelu" << '|' << std::setw(20) << "Rezerwujacy" << '|' << std::setw(20) << "cena" << '|' << std::setw(20) << "liczba miejsc" << '|'  << std::setw(20) << "stan"<< '|' << std::endl;
        for(int i = 0; i < offers.size(); i++) {
            Offer offer = offers[i];
            std::cout <<'|' << std::setw(8) << (i) << "." << '|' << std::setw(20) << offer.getHotelName() << '|' << std::setw(20) << offer.getWhoReserved() << '|' << std::setw(20) << offer.getPrice() << '|' << std::setw(20) << offer.getFreeNum() << '|' << std::setw(20) << offer.getOfferStateString() << '|' << std::endl;
            //std::cout << (i+1) << ". "<<offer.getHotelName() << std::endl; //Patrz na id
        }
         std::cout << "" << std::endl;
         return BACK_TO_MAIN_MENU;
    }
    int showClientMenu(){
        std::string char_input;
        int input = 0;
        do{
            std::cout<< "Wybierz zadanie (nr), ktore chcesz wykonac: "<<std::endl;
            std::cout << "1. Pokaz oferty" << std::endl;
            std::cout << "2. Pokaz oferty uzywajac filtrowania danych" << std::endl;
            std::cout << "3. Zarezerwuj oferte" << std::endl;
            std::cout << "4. Powrot do menu" << std::endl;

            std::cin >> char_input;
            input = atoi(char_input.c_str());
            if(input == 0){
                clear_screen();
                std::cout<< "Podany znak nie jest cyfra lub wpisales zla opcje! Sprobuj ponownie!"<<std::endl;
            }else{
                if(char_input != "1" && char_input != "2" && char_input != "3" && char_input != "4" && char_input != "5" && char_input != "6"){
                    clear_screen();
                    std::cout<< "Wybrales zla opcje! Sprobuj ponownie!"<<std::endl;
                    input = 0;
                }
            }
        }while(input == 0);
        return input;
    }
    int showOwnerMenu(){
        std::string char_input;
        int input = 0;
        do{
            std::cout<< "Wybierz zadanie (nr), ktore chcesz wykonac: "<<std::endl;
            std::cout << "1. Dodaj oferte" << std::endl;
            std::cout << "2. Wyswietl rezerwacje" << std::endl;
            std::cout << "3. Zaakceptuj rezerwacje" << std::endl;
            std::cout << "4. Odrzuc rezerwacje"<< std::endl;
            std::cout << "5. Powrot do menu glownego"<< std::endl;

            std::cin >> char_input;
            input = atoi(char_input.c_str());
            if(input == 0){
                clear_screen();
                std::cout<< "Podany znak nie jest cyfra lub wpisales zla opcje! Sprobuj ponownie!"<<std::endl;
            }else{
                if(char_input != "1" && char_input != "2" && char_input != "3" && char_input != "4" && char_input != "5" && char_input != "6"){
                    clear_screen();
                    std::cout<< "Wybrales zla opcje! Sprobuj ponownie!"<<std::endl;
                    input = 0;
                }
            }
        }while(input == 0);
        return input;
    }
    int addOffer(){
        User user = users.find(loggedInUsername)->second;
        std::string ownerUsername = loggedInUsername;
        std::string hotelName;
        std::string freeNum;
        std::string startDayOffer, startMonthOffer, startYearOffer;
        std::string endDayOffer, endMonthOffer, endYearOffer;
        std::string price;
        std::string answer = "";
        OFFER_STATE offerState;
        std::cout << "Podaj nazwe hotelu" << std::endl;
        std::cin >> hotelName;
        std::cout << "Podaj ilosc miejsc" << std::endl;
        std::cin >> freeNum;
        std::cout << "Podaj dzien poczatku oferty" << std::endl;
        std::cin >> startDayOffer;
        std::cout << "Podaj miesiac poczatku oferty" << std::endl;
        std::cin >> startMonthOffer;
        std::cout << "Podaj rok poczatku oferty" << std::endl;
        std::cin >> startYearOffer;
        std::cout << "Podaj dzien konca oferty" << std::endl;
        std::cin >> endDayOffer;
        std::cout << "Podaj miesiac konca oferty" << std::endl;
        std::cin >> endMonthOffer;
        std::cout << "Podaj rok konca oferty" << std::endl;
        std::cin >> endYearOffer;
        std::cout << "Podaj cene oferty" << std::endl;
        std::cin >> price;
        if( atoi(startDayOffer.c_str())  == 0 || atoi(startDayOffer.c_str()) > 31){
            clear_screen();
            std::cout << "Podana data nie jest poprawna!" << std::endl;
            std::cout << "Przykladowa poprawny numer to 10" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        if( atoi(startMonthOffer.c_str())  == 0 || atoi(startMonthOffer.c_str())  > 12){
            clear_screen();
            std::cout << "Podana data nie jest poprawna!" << std::endl;
            std::cout << "Przykladowa poprawny numer to 10" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        if( atoi(startYearOffer.c_str())  == 0 || atoi(startYearOffer.c_str()) < 2016){
            clear_screen();
            std::cout << "Podana data nie jest poprawna!" << std::endl;
            std::cout << "Przykladowa poprawny numer to 2016" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        if( atoi(endDayOffer.c_str())  == 0 || atoi(endDayOffer.c_str()) > 31){
            clear_screen();
            std::cout << "Podana data nie jest poprawna!" << std::endl;
            std::cout << "Przykladowa poprawny numer to 10" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        if( atoi(endMonthOffer.c_str())  == 0 || atoi(endMonthOffer.c_str())  > 12){
            clear_screen();
            std::cout << "Podana data nie jest poprawna!" << std::endl;
            std::cout << "Przykladowa poprawny numer to 10" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        if( atoi(endYearOffer.c_str())  == 0 || atoi(endYearOffer.c_str()) < 2016){
            clear_screen();
            std::cout << "Podana data nie jest poprawna!" << std::endl;
            std::cout << "Przykladowa poprawny numer to 2016" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        if( atof(price.c_str()) == 0 ){
            clear_screen();
            std::cout << "Podana kwota nie jest poprawna!" << std::endl;
            std::cout << "Przykladowa poprawna kwota to 500.0" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        while( answer != "wolna" && answer != "zarezerwowana" && answer != "sprzedana"){
            std::cout << "Podaj stan oferty tzn. wolna, zarezerwowana lub sprzedana" << std::endl;
            std::cin >> answer;
        }
        if(answer == "wolna"){
            offerState = FREE;
        }else if(answer == "zarezerwowana"){
            offerState = RESERVED;
        }else{
            offerState = SOLD;
        }
        Offer offer = Offer(ownerUsername, hotelName, freeNum, startDayOffer, startMonthOffer, startYearOffer, endDayOffer, endMonthOffer, endYearOffer, "", offerState, atof(price.c_str()));
        offers.push_back(offer);
        offerData.push_back(offer.toString());
        saveFile("offers.txt", offerData);
        std::cout << "Pomyslnie dodano oferte!" << std::endl;
        return BACK_TO_MAIN_MENU;
    }
    int acceptReservation(){
        std::string offerIdString = "";
        int offerId;
        std::cout << "Podaj nr. id oferty" << std::endl;
        std::cin >> offerIdString;
        offerId = atoi(offerIdString.c_str());
        if(offerIdString != "0" && offerId == 0 || offerId >= offers.size() || offerId < 0){
            std::cout<< "Podano niepoprawny numer id oferty!" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        Offer &offer = offers[offerId]; // Niech pobierze wartosc a nie KOPIE
        if(offer.getOfferState() == FREE || offer.getOfferState() == SOLD){
            clear_screen();
            std::cout << "" << std::endl;
            std::cout << "Nie mozesz zaakceptowac tej!" << std::endl;
            std::cout << "" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        std::string offTostr = offer.toString();
        int dataId = -1;
        bool found = false;
        for(int i = 0; i < offerData.size(); i ++){
            std::cout << offTostr << " and " << offerData[i] << std::endl;
            if(offTostr == offerData[i]){
                offerData.erase(offerData.begin() + i);
                found = true;
                break;
            }
        }
        if(!found){
            //clear_screen();
            std::cout << "" << std::endl;
            std::cout << "Nie znaleziono wybranej oferty" << std::endl;
            std::cout << "" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        offer.setOfferState(SOLD);
        offerData.push_back(offer.toString());
        //clear_screen();
        saveFile("offers.txt", offerData);
        std::cout << "Pomyslnie zaakceptowano oferte!" << std::endl;
        return BACK_TO_MAIN_MENU;
    }
    int denyReservation(){
        std::string offerIdString = "";
        int offerId;
        std::cout << "Podaj nr. id oferty" << std::endl;
        std::cin >> offerIdString;
        offerId = atoi(offerIdString.c_str());
        if(offerIdString != "0" && offerId == 0 || offerId >= offers.size() || offerId < 0){
            std::cout<< "Podano niepoprawny numer id oferty!" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        Offer &offer = offers[offerId]; // Niech pobierze wartosc a nie KOPIE
        if(offer.getOfferState() == FREE || offer.getOfferState() == SOLD){
            clear_screen();
            std::cout << "" << std::endl;
            std::cout << "Nie mozesz odrzucic tej oferty!" << std::endl;
            std::cout << "" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        std::string offTostr = offer.toString();
        int dataId = -1;
        bool found = false;
        for(int i = 0; i < offerData.size(); i ++){
            std::cout << offTostr << " and " << offerData[i] << std::endl;
            if(offTostr == offerData[i]){
                offerData.erase(offerData.begin() + i);
                found = true;
                break;
            }
        }
        if(!found){
            //clear_screen();
            std::cout << "" << std::endl;
            std::cout << "Nie znaleziono wybranej oferty" << std::endl;
            std::cout << "" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        offer.setOfferState(FREE);
        offerData.push_back(offer.toString());
        //clear_screen();
        saveFile("offers.txt", offerData);
        std::cout << "Pomyslnie odzrucono oferte!" << std::endl;
        return BACK_TO_MAIN_MENU;
    }
    int reserveOffer(){
        std::string offerIdString = "";
        int offerId;
        std::cout << "Podaj nr. id oferty" << std::endl;
        std::cin >> offerIdString;
        offerId = atoi(offerIdString.c_str());
        if(offerIdString != "0" && offerId == 0 || offerId >= offers.size() || offerId < 0){
            std::cout<< "Podano niepoprawny numer id oferty!" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        Offer &offer = offers[offerId]; // Niech pobierze wartosc a nie KOPIE
        if(offer.getOfferState() == RESERVED || offer.getOfferState() == SOLD){
            clear_screen();
            std::cout << "" << std::endl;
            std::cout << "Nie mozesz zarezerwowac tej ofery!" << std::endl;
            std::cout << "" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        std::string offTostr = offer.toString();
        int dataId = -1;
        bool found = false;
        for(int i = 0; i < offerData.size(); i ++){
            std::cout << offTostr << " and " << offerData[i] << std::endl;
            if(offTostr == offerData[i]){
                offerData.erase(offerData.begin() + i);
                found = true;
                break;
            }
        }
        if(!found){
            //clear_screen();
            std::cout << "" << std::endl;
            std::cout << "Nie znaleziono wybranej oferty" << std::endl;
            std::cout << "" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
        offer.setOfferState(RESERVED);
        offer.setWhoReserved(loggedInUsername);
        offerData.push_back(offer.toString());
        //clear_screen();
        saveFile("offers.txt", offerData);
        std::cout << "Pomyslnie zarezerwowano oferte!" << std::endl;
        return BACK_TO_MAIN_MENU;
    }
    int createUser(){
        std::string endUserCreation = "nie";
        do{
            std::string username;
            std::string password;
            std::string firstname;
            std::string lastname;
            std::string userTypeString;
            USER_TYPE userType;
            std::cout << "Tworzenie nowego uzytkownika: " << std::endl;
            std::cout << "Podaj nazwe nowego uzytkownika: " << std::endl;
            std::cin >> username;
            if (users.count(username) > 0){
                clear_screen();
                std::cout << "" << std::endl;
                std::cout << "Ten uzytkownik juz istnieje!" << std::endl;
                std::cout << "" << std::endl;
                return BACK_TO_MAIN_MENU;
            }
            std::cout << "Podaj haslo uzytkownika" << std::endl;
            std::cin >> password;
            std::cout << "Podaj imie uzytkownika: " << std::endl;
            std::cin >> firstname;
            std::cout << "Podaj nazwisko uzytkownika: " << std::endl;
            std::cin >> lastname;
            do{
                std::cout << "Podaj typ konta: oferujacy albo rezerwujacy" << std::endl;
                std::cin >> userTypeString;
            }while(userTypeString != "oferujacy" && userTypeString != "rezerwujacy");

            if(userTypeString == "oferujacy"){
                userType = OWNER;
            }else{
                userType = CLIENT;
            }
            User user = User(username, firstname, lastname, userType, password);
            users.insert(
                     std::pair<std::string, User>
                     (username, user));
            userData.push_back(user.toString());
            saveFile("users.txt", userData);

            std::cout << "Konto uzytkownika o nazwie " << username << " zostalo utworzone!" << std::endl;
            std::cout << "Aby zakonczyc tworzenie uzytkownika wpisz tak" << std::endl;
            std::cin >> endUserCreation;
        }while(endUserCreation == "nie");
        return BACK_TO_MAIN_MENU;
    }
    bool logInUser(std::string username, std::string password){
        if (users.count(username) > 0){
            std::cout << "Znalazlem uzytkownika " << username;
            std::cin.get();
            User user = users.find(username)->second;
            if(user.getPassword() == password){
                return true;
            }
        }else{
            return false;
        }
        return false;
    }
    bool chooseClientMenuOption(int input){
        switch (input) {
            case  1:
                return showOffers();
            break;
            case  2:
                return showOffersUsingFilters();
            break;
            case  3:
                return reserveOffer();
            break;
            case  4:
                return EXIT_SOFT;
            break;
        }
        return EXIT_SOFT;
    }
    int showReservations(){
        std::cout << "Osoby, ktore zarezerwowaly oferty:" << std::endl;
        std::cout << "" << std::endl;
        std::cout <<'|' << std::setw(8) << "Id oferty" << '|' << std::setw(20) << "Nazwa hotelu" << '|' << std::setw(20) << "Rezerwujacy" << '|' << std::setw(20) << "cena" << '|' << std::setw(20) << "liczba miejsc" << '|'  << std::setw(20) << "stan"<< '|' << std::endl;

        for(int i = 0; i < offers.size(); i++) {
            Offer offer = offers[i];
            User user = users.find(loggedInUsername)->second;
            if(offer.getOwnerUsername() == user.getUsername()){
                if(offer.getOfferState() == RESERVED){
                    std::cout <<'|' << std::setw(8) << (i) << "." << '|' << std::setw(20) << offer.getHotelName() << '|' << std::setw(20) << offer.getWhoReserved() << '|' << std::setw(20) << offer.getPrice() << '|' << std::setw(20) << offer.getFreeNum() << '|' << std::setw(20) << offer.getOfferStateString() << '|' << std::endl;
                    std::cout << "" << std::endl;
                }
            }
        }
        std::cout << "" << std::endl;
        return BACK_TO_MAIN_MENU;
    }
    bool chooseOwnerMenuOption(int input){
        switch (input) {
            case  1:
                return addOffer();
            break;
            case  2:
                return showReservations();
            break;
            case  3:
                return acceptReservation();
            break;
            case  4:
                return denyReservation();
            break;
            case  5:
                return EXIT_SOFT;
            break;
        }
        return EXIT_SOFT;
    }
    int showOwnerInterface(){
        int val = -1;
        do{
            int input = showOwnerMenu();
            val = chooseOwnerMenuOption(input);
            //std::cout<<"Obecny nr to "<<val;
        }while(val != 0);
        return BACK_TO_MAIN_MENU;
    }
    int showClientInterface(){
        int val = -1;
        do{
            int input = showClientMenu();
            val = chooseClientMenuOption(input);
            //std::cout<<"Obecny nr to "<<val;
        }while(val != 0);
        return BACK_TO_MAIN_MENU;
    }

    int showLoginPage(){
        std::string repeat = "tak";
        std::string username;
        std::string password;
        do{
            std::cout << "Wpisz nazwe uzytkownika: "<<std::endl;
            std::cin >> username;
            std::cout << "Wpisz haslo: "<<std::endl;

            std::cin >> password;
            clear_screen();
            bool logged = logInUser(username, password);

            if(!logged){
                std::cout << "Podales niepoprawne haslo badz uzytkownik nie istnieje!" << std::endl;
                std::cout << "Wrocic do menu glownego?" << std::endl;
                std::cout << "Wpisz tak lub nie" << std::endl;
                std::cin >> repeat;
            }else{
                loggedInUsername = username;
                std::cout << "Zostales pomyslnie zalogowany! " << std::endl;
                User user = users.find(username)->second;
                if(user.getUserTypeString() == "oferujacy"){
                    return showOwnerInterface();
                }else{
                    return showClientInterface();
                }
            }
        }while(repeat == "nie");
        return BACK_TO_MAIN_MENU;
    }

    int showHelp(){
        std::cout << std::endl;
        std::cout << std::endl;
        std::vector<std::string> helpLines = readFile("help.txt");
        for(int i = 0; i < helpLines.size(); i++){
            std::cout << helpLines[i];
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cin.get();
        return BACK_TO_MAIN_MENU;
    }
    int removeUser(){
        return BACK_TO_MAIN_MENU;
    }

    bool chooseStartMenuOption(int input){
        switch (input) {
            case  1:
                return showLoginPage();
            break;
            case  2:
                return createUser();
            break;
            case  3:
                return removeUser();
            break;
            case  4:
                return showHelp();
            break;
            case  5:
                return EXIT_SOFT;
            break;
        }
        return EXIT_SOFT;
    }
    void loadUsers(std::vector<std::string> userData){
        users.clear();
        for(int i = 0; i < userData.size(); i++){
            std::vector<std::string> uData = split(userData[i], ':');
            if(uData.empty()){
               continue;
            }
            USER_TYPE userType;
            if(uData[3] == "oferujacy"){
                userType = OWNER;
            }else{
                userType = CLIENT;
            }
            users.insert(
                     std::pair<std::string, User>
                     (uData[0], User(uData[0], uData[1], uData[2], userType, uData[4]))
                    );
        }
    }
    void loadOffers(std::vector<std::string> offerData){
        offers.clear();
        for(int i = 0; i < offerData.size(); i++){
            std::vector<std::string> oData = split(offerData[i], ':');
            if(oData.empty()){
               continue;
            }
            OFFER_STATE offerState;
            if(oData[10] == "wolna") {
                offerState = FREE;
            } else if(oData[10] == "zarezerwowana") {
                offerState = RESERVED;
            } else {
                offerState = SOLD;
            }
            offers.push_back(Offer(oData[0], oData[1], oData[2], oData[3] , oData[4], oData[5], oData[6], oData[7], oData[8], oData[9], offerState, atof(oData[11].c_str()))
                    );
        }
    }
    void runInterface(){
        int val = -1;
        do{
            int input = showStartMenu();
            val = chooseStartMenuOption(input);
            //std::cout<<"Obecny nr to "<<val;
        }while(val != 0);
    }
    int main(){
        userData = readFile("users.txt");
        offerData = readFile("offers.txt");
        loadUsers(userData);
        loadOffers(offerData);
        std::cout << "Wczytano " << userData.size() << " uzytkownikow" << std::endl << std::endl;
        runInterface();
        return 0;
    }
