#include <iostream>
#include <string>

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
