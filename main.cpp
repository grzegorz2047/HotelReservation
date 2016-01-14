#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>


class User{
    private:
    //userType type;
    std::string password;
    std::string username;
    std::string firstname;
    std::string lastname;
    public:
    User(std::string _username, std::string _password){

    }
};
void clear_screen(){
    system("cls||clear");
}
int returnStartMenuOptionNumber(){
    std::string char_input;
    int input = 0;
    bool fail = false;
    do{
        std::cout<< "Wybierz zadanie (nr), ktore chcesz wykonac: "<<std::endl;
        std::cout << "1. Zaloguj sie jako pracownik" << std::endl;
        std::cout << "2. Wyswietl menu klienta "<< std::endl;
        std::cout << "3. Zakoncz dzialanie programu"<< std::endl;

        std::cin >> char_input;
        input = atoi(char_input.c_str());
        if(input == 0){
            fail = true;
            clear_screen();
            std::cout<< "Podany znak nie jest cyfra lub wpisales zla opcje! Sprobuj ponownie!"<<std::endl;
        }else{
            if(char_input != "1" && char_input != "2" && char_input != "3"){
                fail = true;
                clear_screen();
                std::cout<< "Wybrales zla opcje! Sprobuj ponownie!"<<std::endl;
                input = 0;
            }else{
                fail = false;
            }
        }
    }while(input == 0);
    return input;
}

void chooseStartOption(int input){
    switch (input) {
        case  1:
        std::cout<<"Siema! Wybrales opcje 1"<<std::endl;
        break;
    }
}

int main(){
    int input = returnStartMenuOptionNumber();
    chooseStartOption(input);
}
