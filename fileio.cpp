#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

    std::vector<std::string> readFile(std::string filename){
        std::vector<std::string> lines;
        std::ifstream read;
        std::string line;
        read.open(filename.c_str());
        if(!read.good()){
            read.close();
            std::ofstream create;
            create.open(filename.c_str());
            return lines;
        }
        while(!read.eof()){
            getline(read, line);
            if(line != ""){
                std::cout<<"Wczytano "<<line<<std::endl;
                lines.push_back(line);
            }
        }
        read.close();
        return lines;
    }
    void saveFile(std::string filename, std::vector<std::string> lines){
        std::ofstream save;
        save.open(filename.c_str());
        for(int i = 0; i < lines.size(); i ++){
            save << lines[i] <<std::endl;
        }
        save.close();
    }
