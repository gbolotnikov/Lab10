#ifndef CONSOLE_READER_HPP
#define CONSOLE_READER_HPP

#include <iostream>
#include "Interfaces/Manager.hpp"

class ConsoleReader {
public:
    void read();
    void notifyEndCommand();
    void setStream(std::istream& input);
    ConsoleReader(IManager& cmdManager, size_t commandCount);
    ~ConsoleReader() {
        // std::cout << "Destroy Reader" << std::endl;
    }       
private:    
    void openBrace();
    void closeBrace();
    void notifyNewCommand(std::string_view cmd);
    
    size_t _commandCount;
    IManager& _cmdManager;
    size_t _linesCount = 0;
    size_t _bracesCount = 0;
    std::istream* _input = {&std::cin};
    std::vector<std::string> _commands;
    static std::vector<std::string> _commonCommands;
    

};

#endif