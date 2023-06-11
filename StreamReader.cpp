#include <iostream>
#include "Include/StreamReader.hpp"

StreamReader::StreamReader(IManager& cmdManager): 
_cmdManager(cmdManager)
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
            addCommand(line);
        }
    }
}

void StreamReader::addCommand(std::string_view cmd) {
    if (_bracesCount == 0) {
        _cmdManager.addCommand(cmd);
    } else {
        _myCommands.push_back(std::move(cmd.data()));
    }
}

void StreamReader::notifyEndCommand() {
    _cmdManager.endCommand(_myCommands);
    _myCommands.clear();
}

void StreamReader::openBrace() {
    ++_bracesCount;
    if (_bracesCount == 1) {
        _cmdManager.processCommonCmd();
    }
}

void StreamReader::closeBrace() {
    --_bracesCount;
    if (_bracesCount == 0) {
        _cmdManager.endCommand(_myCommands);
        _myCommands.clear();
    }
}