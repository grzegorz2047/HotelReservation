#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "fileio.h"
#include "stringutils.h"
#include "User.h"
#include <map>
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

    void createUser(){
    }
    bool logInUser(std::string username, std::string password){
        if (users.count(username)>0){
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

    bool chooseStartOption(int input){
        switch (input) {
            case  1:
            std::cout<<"Siema! Wybrales opcje 1"<<std::endl;
            break;
            case  2:
            createUser();
            break;
            case  3:
            std::cout<<"Siema! Wybrales opcje 3"<<std::endl;
            break;
            case  4:
            std::cout<<"Siema! Wybrales opcje 4"<<std::endl;
            break;
            case  5:
            std::cout<<"Siema! Wybrales opcje 5"<<std::endl;
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
        std::vector<std::string> userData = readFile("users.txt");
        loadUsers(userData);
        std::cout<<"Wczytano "<<userData.size()<<" uzytkownikow"<<std::endl<<std::endl;
        int input = showStartMenu();
        chooseStartOption(input);
    }
