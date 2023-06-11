#ifndef CONSOLE_READER_HPP
#define CONSOLE_READER_HPP

#include <memory>
#include <iostream>
#include "Interfaces/Manager.hpp"

class StreamReader {
public:
    void read();
    void notifyEndCommand();
    void setStream(std::istream& _input);
    StreamReader(IManager& cmdManager);
    ~StreamReader() {
        // std::cout << "Destroy Reader" << std::endl;
    }       
private:    
    void openBrace();
    void closeBrace();
    void addCommand(std::string_view line);
    
    IManager& _cmdManager;
    size_t _bracesCount = 0;
    std::istream* _input;
    std::vector<std::string> _myCommands;
    

};

#endif