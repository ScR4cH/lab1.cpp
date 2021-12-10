#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "assembler.hpp"

bool BuildCommandList(std::vector<std::vector<std::string>>& commandList, std::string filepath)//sätt in i ett eget dokument och felsök alla funktioner med egen input
{
    std::string line;
    std::vector<std::string> command;
    std::ifstream myfile;

    commandList.clear();

    myfile.open(filepath);
    if (myfile.is_open()) {
        std::cout << "File is open!";
    }
    else {
        std::cout << "Error file is not open!";
    }

    while (std::getline(myfile, line)) {
        if (line.length() != 0) {
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());//kan inte kompileras
            command.push_back(line);
            commandList.push_back(command);
            myfile.close();
            return true;
        }
        else {
            myfile.close();
            return false;
        }
    }
}