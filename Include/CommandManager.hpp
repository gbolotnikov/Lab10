#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#include <iostream>
#include <unordered_set>
#include "ThreadPool.hpp"
#include "FileWriter.hpp"
#include "Interfaces/Manager.hpp"

// нужно делать через сингл тон возьми у Паскаля этот класс

class CommandManager: public IManager { 
public:
    void addWriter(const IWriter& writer) override;
    void addWriter(const FileWriter& writer);
    void newCommand(std::string_view cmd) override;
    void endCommand(const std::vector<std::string>& commands) override;
    void addCommand(std::string_view line) override;
    void setBulkSize(size_t commandCount) override;
    void processCommonCmd() override;

    ~CommandManager() {
        // std::cout << "Destroy CommandManager" << std::endl;
    }
private:
    void notifyWriter(const std::vector<std::string>& commands);
    void process(std::string out, size_t timeStamp, uint8_t id);

    std::recursive_mutex _mutex;
    ThreadPool _worker {8};   
    size_t _firstCmdtimeStamp;
    size_t _linesCount;
    size_t _commandCount;
    std::vector<std::string> _commands;
    std::unordered_set<const IWriter*> _writers;
    std::unordered_set<const FileWriter*> _fileWriters;

};

#endif