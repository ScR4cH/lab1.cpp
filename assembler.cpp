#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "assembler.hpp"

int GetRegIndex(std::string reg)
{
    return int(reg[1]);
}

int GetConstant(std::string constant)
{
    std::string constant_02 = constant.substr(1);
    int constant1 = stoi(constant_02);
    return constant1;
}

int IsReg(std::string term)
{
    return term[0] = 'R';
}

int ExtractValue(std::string source, int registers[])
{
    if (IsReg(source))
    {
        return registers[GetRegIndex(source)];
    }
    return GetConstant(source);
}

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

int PeekNextCommandIndex(int registers[]) {
    int reg1 = registers[REGISTER_SIZE - 1];
    return reg1;
}



int GetAndStepCommandIndex(int registers[]) {
    int reg1 = registers[REGISTER_SIZE - 1];
    registers[REGISTER_SIZE - 1] += 1;
    return reg1;
}



void MOV(std::vector<std::string>& command, int registers[]) {
    int destIndex = GetRegIndex(command[1]);
    int value = ExtractValue(command[2], registers);
    registers[destIndex] = value;
}


void ADD(std::vector<std::string>& command, int registers[]) {
    int destIndex;
    destIndex = GetRegIndex(command[1]);
    int term1 = ExtractValue(command[2], registers);
    int term2 = ExtractValue(command[3], registers);
    registers[destIndex] = term1 + term2;
}



void SUB(std::vector<std::string>& command, int registers[]) {
    int destIndex;
    destIndex = GetRegIndex(command[1]);
    int term1 = ExtractValue(command[2], registers);
    int term2 = ExtractValue(command[3], registers);
    registers[destIndex] = term1 - term2;
}


void JEQ(std::vector<std::string>& command, int registers[]) {
    int value1 = ExtractValue(command[1], registers);
    int value2 = ExtractValue(command[2], registers);
    if (value1 == value2) {
        int step = ExtractValue(command[3], registers) - 1;
        registers[REGISTER_SIZE - 1] += step;
    }
}


void JGT(std::vector<std::string>& command, int registers[]) {
    int value1 = ExtractValue(command[1], registers);
    int value2 = ExtractValue(command[2], registers);
    if (value1 > value2) {
        int step = ExtractValue(command[3], registers) - 1;
        registers[REGISTER_SIZE - 1] += step;
    }
}



void JLT(std::vector<std::string>& command, int registers[]) {
    int value1 = ExtractValue(command[1], registers);
    int value2 = ExtractValue(command[2], registers);
    if (value1 < value2) {
        int step = ExtractValue(command[3], registers) - 1;
        registers[REGISTER_SIZE - 1] += step;
    }
}