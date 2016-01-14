#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "fileio.h"
#include "stringutils.h"

    enum USER_TYPE {
        OWNER = 1,
        CLIENT = 0
    };

    class User{
        private:
        USER_TYPE userType;
        std::string password;
        std::string username;
        std::string firstname;
        std::string lastname;

        public:
        User(std::string username, std::string firstname, std::string lastname, USER_TYPE userType, std::string password){
            this->username = username;
            this->firstname = firstname;
            this->lastname = lastname;
            this->userType = userType;
            this->password = password;
        }
        std::string getUsername(){
            return this->username;
        }
        std::string getFirstName(){
            return this->firstname;
        }
        std::string getLastName(){
            return this->lastname;
        }
        std::string getPassword(){
            return this->password;
        }
        USER_TYPE getUserType(){
            return this->userType;
        }
        std::string getUserTypeString(){
            if(this->userType == OWNER){
                return "owner";
            }else{
                return "client";
            }
        }
    };
    std::vector<User> users;

    void clear_screen(){
        system("cls||clear");
    }
    int returnStartMenuOptionNumber(){
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
    void logInUser(std::string username, std::string password){
        for(int i = 0; i < users.size(); i ++){
            User user = users[i];
            if(user.getUsername() == username && user.getPassword() == password){
                clear_screen();
                std::cout<<"Zostales pomyslnie zalogowany!"<<std::endl;
            }else{
                clear_screen();
                std::cout<<"Podales niepoprawne haslo badz uzytkownik nie istnieje!"<<std::endl;
            }
        }
    }
    void chooseStartOption(int input){
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
    std::vector<User> loadUsers(std::vector<std::string> userData){
        std::vector<User> users;
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
            users.push_back(User(uData[0], uData[1], uData[2], userType, uData[4]));
        }
        return users;
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
        users = loadUsers(userData);
        std::cout<<"Wczytano "<<userData.size()<<" uzytkownikow"<<std::endl<<std::endl;
        int input = returnStartMenuOptionNumber();
        chooseStartOption(input);
    }
