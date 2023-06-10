
#include <ctime>
#include <string>
#include <algorithm>
#include "CommandManager.hpp"

void CommandManager::addWriter(const IWriter& writer) {
    _writers.emplace(&writer);
}

void CommandManager::addWriter(const FileWriter& writer) {
    _fileWriters.emplace(&writer);
}

void CommandManager::newCommand(std::string_view cmd) {
    if (_commands.empty()) {
        _firstCmdtimeStamp = std::time(nullptr);
    }
    _commands.push_back(std::move(cmd.data()));
}

void CommandManager::endCommand() {
    notifyWriter();
    _commands.clear();
}

void CommandManager::process(std::string out, size_t timeStamp, uint8_t id) {
    for (const IWriter* writer : _writers) {
        writer->write(out);
    };
    for (const FileWriter* writer : _fileWriters) {
        writer->write(out, timeStamp, id);
    };
}

void CommandManager::notifyWriter() {
    if (_commands.empty()) {
        return;
    }
    std::string out("bulk: ");
    for (auto it = _commands.begin(); it != _commands.end(); ++it) {
        if (it != _commands.begin()) {
            out += ", ";
        }
        out += *it;
    }
    auto job = [this, out](uint8_t id)
    {
        this->process(std::move(out), _firstCmdtimeStamp, id);
    };
    _worker.enqueue(job);
}