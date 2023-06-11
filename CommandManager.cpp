
#include <ctime>
#include <string>
#include <algorithm>
#include "Include/CommandManager.hpp"

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

void CommandManager::endCommand(const std::vector<std::string>& commands) {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    notifyWriter(commands);
    _linesCount = 0;
}

void CommandManager::processCommonCmd() {
    endCommand(_commands);
}

void CommandManager::setBulkSize(size_t commandCount) {
    _commandCount = commandCount;
}

void CommandManager::addCommand(std::string_view line) {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    ++_linesCount;
    newCommand(line);
    if (_linesCount == _commandCount) {
        endCommand(_commands);
        _commands.clear();
    }
}

void CommandManager::process(std::string out, size_t timeStamp, uint8_t id) {
    for (const IWriter* writer : _writers) {
        writer->write(out);
    };
    for (const FileWriter* writer : _fileWriters) {
        writer->write(out, timeStamp, id);
    };
}

void CommandManager::notifyWriter(const std::vector<std::string>& commands) {
    if (commands.empty()) {
        return;
    }
    std::string out("bulk: ");
    for (auto it = commands.begin(); it != commands.end(); ++it) {
        if (it != commands.begin()) {
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