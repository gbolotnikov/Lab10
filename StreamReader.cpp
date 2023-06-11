#include <iostream>
#include "Include/StreamReader.hpp"

size_t StreamReader::_linesCount = 0;

StreamReader::StreamReader(IManager& cmdManager, size_t commandCount): 
_cmdManager(cmdManager),
_commandCount(commandCount)
{

}

void StreamReader::setStream(std::istream& input) {
    _input = &input;
}

void StreamReader::read() {
    std::string line;
    while (std::getline(*_input, line)) {
        if (line == "{") {
            openBrace();
        }
        else if (line == "}") {
            closeBrace();
        } else {
            ++_linesCount;
            notifyNewCommand(line);
            if (_linesCount == _commandCount && _bracesCount == 0) {
                _linesCount = 0;
                notifyEndCommand();
            }
        }
    }
}

void StreamReader::notifyNewCommand(std::string_view cmd) {
    _cmdManager.newCommand(cmd);
}

void StreamReader::notifyEndCommand() {
    _cmdManager.endCommand();
}

void StreamReader::openBrace() {
    _linesCount = 0;
    ++_bracesCount;
    if (_bracesCount == 1) {
        notifyEndCommand();
    }
}

void StreamReader::closeBrace() {
    _linesCount = 0;
    --_bracesCount;
    if (_bracesCount == 0) {
        notifyEndCommand();
    }
}