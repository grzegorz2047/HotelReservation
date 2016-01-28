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
    std::vector<std::string> offersData;
    std::vector<Offer> offers;
    std::string loggedInUsername;
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
    int showOffers(){
        for(int i = 0; i < offers.size(); i++) {
            Offer offer = offers[i];
            std::cout <<'|' << std::setw(10) << (i) << ". " << '|' << std::setw(30) << offer.getHotelName() << '|' << std::setw(30) << offer.getFreeNum() << '|' << std::endl;
            //std::cout << (i+1) << ". "<<offer.getHotelName() << std::endl; //Patrz na id
        }
    }
    int showClientMenu(){
        std::string char_input;
        int input = 0;
        do{
            std::cout<< "Wybierz zadanie (nr), ktore chcesz wykonac: "<<std::endl;
            std::cout << "1. Pokaz oferty" << std::endl;
            std::cout << "2. Zarezerwuj oferte" << std::endl;
            std::cout << "3. Powrot do menu" << std::endl;

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
    int addOffer(){
        std::string ownerUsername;
        std::string hotelName;
        std::string freeNum;
        std::string startDayOffer, startMonthOffer, startYearOffer;
        std::string endDayOffer, endMonthOffer, endYearOffer;
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

        std::cout << "Pomyslnie dodano oferte!" << std::endl;
        return BACK_TO_MAIN_MENU;
    }

    int reserveOffer(){
        std::string offerIdString;
        int offerId;
        std::cout << "Podaj nr. id oferty" << std::endl;
        std::cin >> offerIdString;
        offerId = atoi(offerIdString.c_str());
        if(offerId == 0 || offerId >= (offers.size()-1)){
            std::cout<< "Podano niepoprawny numer id oferty!" << std::endl;
            return BACK_TO_MAIN_MENU;
        }
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
                std::cout << "Ten uzytkownik juz istnieje!" << std::endl;
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
            users.insert(
                     std::pair<std::string, User>
                     (username, User(username, firstname, lastname, userType, password)));
            std::string userToString = "";
            userToString.append(username).append(":");
            userToString.append(firstname).append(":");;
            userToString.append(lastname).append(":");;
            userToString.append(userTypeString).append(":");
            userToString.append(password);
            userData.push_back(userToString);
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
                return reserveOffer();
            break;
            case  3:
                return EXIT_SOFT;
            break;
        }
        return EXIT_SOFT;
    }
    int showReservations(){
        for(int i = 0; i < offers.size(); i++) {
            Offer offer = offers[i];
             std::cout << "Osoby, ktore zarezerwowaly oferty:" << std::endl;
            User user = users.find(loggedInUsername)->second;
            if(offer.getOwnerUsername() == user.getUsername()){
                std::cout << "id oferty: " << i << std::endl
                << "rezerwujacy: " << offer.getWhoReserved() << std::endl
                << "Nazwa hotelu: " << offer.getHotelName() << std::endl;
            }
        }
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
                return EXIT_SOFT;
            break;
            case  4:
                return EXIT_SOFT;
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
                if(user.getUserTypeString() == "owner"){
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
            if(oData[9] == "free") {
                offerState = FREE;
            } else if(oData[9] == "reserved") {
                offerState = RESERVED;
            } else {
                offerState = SOLD;
            }
            offers.push_back(Offer(oData[0], oData[1], oData[2], oData[3] , oData[4], oData[5], oData[6], oData[7], oData[8], oData[10], offerState)
                    );
        }
    }
    std::vector<std::string> usersToStringVector(std::vector<User> users){
        std::vector<std::string> userData;
        for(int i = 0; i < users.size(); i++){
            User user = users[i];
            std::string userstring;
            userstring.append(user.getUsername()).append(":");
            userstring.append(user.getFirstName()).append(":");
            userstring.append(user.getLastName()).append(":");
            userstring.append(user.getUserTypeString()).append(":");
            userstring.append(user.getPassword());
            userData.push_back(userstring);
        }
        return userData;
    }
    std::vector<std::string> offersToStringVector(std::vector<Offer> offers){
        std::vector<std::string> userData;
        for(int i = 0; i < offers.size(); i++){
            Offer offer = offers[i];
            std::string oferrStr;
            oferrStr.append(offer.getOwnerUsername()).append(":");
            oferrStr.append(offer.getHotelName()).append(":");
            oferrStr.append(offer.getFreeNum()).append(":");
            oferrStr.append(offer.getStartDayOffer()).append(":");
            oferrStr.append(offer.getStartMonthOffer()).append(":");
            oferrStr.append(offer.getStartYearOffer()).append(":");
            oferrStr.append(offer.getEndDayOffer()).append(":");
            oferrStr.append(offer.getEndMonthOffer()).append(":");
            oferrStr.append(offer.getEndYearOffer()).append(":");
            oferrStr.append(offer.getWhoReserved()).append(":");
            oferrStr.append(offer.getOfferStateString());

            userData.push_back(oferrStr);
        }
        return userData;
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
        loadUsers(userData);
        std::cout << "Wczytano " << userData.size() << " uzytkownikow" << std::endl << std::endl;
        runInterface();
        return 0;
    }
