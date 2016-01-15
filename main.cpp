#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "fileio.h"
#include "stringutils.h"
#include "User.h"
#include <map>
#include <regex>

/*
 Program codes:
  0 exit program
  1 return main menu
  2 return client interface
  3 return owner interface

*/


/*

  int tries = 0;
  cin >> tries;
  for(int i = 0; i < tries; i++){
    string val = "";
    string key = "";
    cin >> key;
    cin >> val;
    //dict[key] = val;
    dict.insert(pair<string,string>(key,val) );
  }
  tries = 0;
  cin >> tries;
  map<string, string>::iterator it;
  for(int i = 0; i < tries; i++){
    string word = "";
    cin >> word;
    if (dict.count(word)>0){
      cout << dict.find(word)->second;
    }else{
      cout << word<<endl;
    }
  }

*/


    //std::vector<User> users;
    std::map<std::string, User> users;
    void clear_screen(){
        system("cls||clear");
    }
    int showStartMenu(){
        std::string char_input;
        int input = 0;
        do{
            std::cout<< "Wybierz zadanie (nr), ktore chcesz wykonac: "<<std::endl;
            std::cout << "1. Zaloguj sie jako pracownik" << std::endl;
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
        do{
            std::string username;
            std::string password;
            std::string firstname;
            std::string lastname;
            OWNER_TYPE ownerType;
            std::cout<<"Tworzenie nowego uzytkownika: "<<std::endl;
            std::cout<<"Podaj nazwe nowego uzytkownika: "<<std::endl;
            std::cin >> username;
            std::cout<<"Podaj imie uzytkownika: "<<std::endl;
            std::cin>> firstname;
            std::cout<<"Podaj nazwisko uzytkownika: "<<std::endl;
            std::cin> lastname;
            std::cout<<"Podaj typ konta oferuj¹cy albo rezerwuj¹cy"<<std::endl;


        }while();
        return 1;
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
                std::cout<<"Podales niepoprawne haslo badz uzytkownik nie istnieje!"<<std::endl;
            }else{
                std::cout<<"Zostales pomyslnie zalogowany!"<<std::endl;
                User user = users.find(username)->second;
                if(user.getUserTypeString() == "owner"){
                    return 3;
                }else{
                    return 2;
                }
            }
        }while(repeat == "tak");

    }
    int showOwnerInterface(){
        return 1;
    }
    int showClientInterface(){
        return 1;
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
                return 0;
            break;
        }
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
    int main(){
        int val = 0;
        std::vector<std::string> userData = readFile("users.txt");
        loadUsers(userData);
        std::cout<<"Wczytano "<<userData.size()<<" uzytkownikow"<<std::endl<<std::endl;
        do{
            int input = showStartMenu();
            int val = chooseStartOption(input);
            std::cout<<"Obecny nr to"<<val;

        }while(val == 0);
        return 0;
    }
