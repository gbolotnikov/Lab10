#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#include <iostream>
#include <unordered_set>
#include "ThreadPool.hpp"
#include "FileWriter.hpp"
#include "Interfaces/Manager.hpp"

// нужно делать через сингл тон возьми у Паскаля этот класс

class CommandManager: public IManager{
public:
    void addWriter(const IWriter& writer) override;
    void addWriter(const FileWriter& writer);
    void newCommand(std::string_view cmd) override;
    void endCommand() override;


    ~CommandManager() {
        // std::cout << "Destroy CommandManager" << std::endl;
    }
private:

    void notifyWriter();
    void process(std::string out, size_t timeStamp, uint8_t id);

    ThreadPool _worker {8};   
    size_t _firstCmdtimeStamp;
    
    std::unordered_set<const IWriter*> _writers;
    std::unordered_set<const FileWriter*> _fileWriters;

};

#endif