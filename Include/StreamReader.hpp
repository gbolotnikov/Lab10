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
    StreamReader(IManager& cmdManager, size_t commandCount);
    ~StreamReader() {
        // std::cout << "Destroy Reader" << std::endl;
    }       
private:    
    void openBrace();
    void closeBrace();
    void notifyNewCommand(std::string_view cmd);
    
    size_t _commandCount;
    IManager& _cmdManager;
    size_t _bracesCount = 0;
    std::istream* _input;
    static size_t _linesCount;
    std::vector<std::string> _myCommands;
    

};

#endif