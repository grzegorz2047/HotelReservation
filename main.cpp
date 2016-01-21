#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "fileio.h"
#include "stringutils.h"
#include "User.h"
#include <map>
#include <regex>
enum PROGRAM_STATE{
    EXIT_SOFT = 0,
    TO_LOGIN_PAGE = 1,
    BACK_TO_MAIN_MENU = 2,
    TO_CLIENT_INTERFACE = 3,
    TO_OWNER_INTERFACE = 4
};
    //std::vector<User> users;
    std::map<std::string, User> users;
    std::vector<std::string> userData;
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
            std::cout << "4. Wyswietl menu klienta "<< std::endl;
            std::cout << "5. Zakoncz dzialanie programu"<< std::endl;

            std::cin >> char_input;
            input = atoi(char_input.c_str());
            if(input == 0){
                clear_screen();
                std::cout<< "Podany znak nie jest cyfra lub wpisales zla opcje! Sprobuj ponownie!"<<std::endl;
            }else{
                if(char_input != "1" && char_input != "2" && char_input != "3" && char_input != "4" && char_input != "5"){
                    clear_screen();
                    std::cout<< "Wybrales zla opcje! Sprobuj ponownie!"<<std::endl;
                    input = 0;
                }
            }
        }while(input == 0);
        return input;
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
            std::cout << "Konto uzytkownika o nazwie "<<username<<" zostalo utworzone!" << std::endl;
            std::cout << "Aby zakonczyc tworzenie uzytkownika wpisz tak" << std::endl;
            std::cin >> endUserCreation;
        }while(endUserCreation == "nie");
        return BACK_TO_MAIN_MENU;
    }
    bool logInUser(std::string username, std::string password){
        if (users.count(username) > 0){
            std::cout<<"Znalazlem uzytkownika "<<username;
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
    int showLoginPage(){
        std::string repeat = "tak";
        std::string username;
        std::string password;
        do{
            std::cout<<"Wpisz nazwe uzytkownika: "<<std::endl;
            std::cin>> username;
            std::cout<<"Wpisz haslo: "<<std::endl;

            std::cin>> password;
            clear_screen();
            bool logged = logInUser(username, password);

            if(!logged){
                std::cout << "Podales niepoprawne haslo badz uzytkownik nie istnieje!" << std::endl;
                std::cout << "Wrocic do menu glownego?" << std::endl;
                std::cout << "Wpisz tak lub nie" << std::endl;
                std::cin >> repeat;
            }else{
                std::cout << "Zostales pomyslnie zalogowany! " << std::endl;
                User user = users.find(username)->second;
                if(user.getUserTypeString() == "owner"){
                    return TO_OWNER_INTERFACE;
                }else{
                    return TO_CLIENT_INTERFACE;
                }
            }
        }while(repeat == "nie");
        return BACK_TO_MAIN_MENU;
    }
    int showOwnerInterface(){
        return BACK_TO_MAIN_MENU;
    }
    int showClientInterface(){
        return BACK_TO_MAIN_MENU;
    }

    bool chooseStartOption(int input){
        switch (input) {
            case  1:
                return showLoginPage();
            break;
            case  2:
                return createUser();
            break;
            case  3:
                return showOwnerInterface();
            break;
            case  4:
                return showClientInterface();
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
            if(uData[3] == "owner"){
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
    std::vector<std::string> usersToStringVector(std::vector<User> users){
        std::vector<std::string> userData;
        for(int i = 0; i < users.size(); i++){
            User user = users[i];
            std::string userstring;
            userstring.append(user.getUsername());
            userstring.append(user.getFirstName());
            userstring.append(user.getLastName());
            userstring.append(user.getUserTypeString());
            userstring.append(user.getPassword());
            userData.push_back(userstring);
        }
        return userData;
    }
    void runInterface(){
        int val = -1;
        do{
            int input = showStartMenu();
            val = chooseStartOption(input);
            std::cout<<"Obecny nr to "<<val;
        }while(val != 0);
    }
    int main(){
        int val = 0;
        userData = readFile("users.txt");
        loadUsers(userData);
        std::cout << "Wczytano " << userData.size() << " uzytkownikow" << std::endl << std::endl;
        runInterface();
        return 0;
    }
