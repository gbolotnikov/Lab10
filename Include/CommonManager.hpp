#ifndef COMMON_MANAGER_HPP
#define COMMON_MANAGER_HPP

#include "Singletone.hpp"
#include "CommandManager.hpp"
#include "FileWriter.hpp"
#include "ConsoleWriter.hpp"

class CommonManager: public Singletone<CommonManager> {
public:

    IManager& getManager() {
        return _commandManager;
    }

    ~CommonManager() {
        _commandManager.processCommonCmd();
    }

private:
    CommonManager() {
        _commandManager.addWriter(_consoleWriter);
        _commandManager.addWriter(_fileWriter);
    }
    friend Singletone<CommonManager>;
    ConsoleWriter _consoleWriter;
    FileWriter _fileWriter = {"bulk"};
    CommandManager _commandManager;
};

#endif