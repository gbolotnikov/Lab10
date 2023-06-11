#include <sstream>
#include <memory>
#include "Include/Session.hpp"
#include "Include/CommonManager.hpp"


Session::Session(std::atomic<std::uint32_t>& sessionCnt, std::size_t bulk, tcp::socket socket)
    : _socket(std::move(socket)),
    _reader(CommonManager::instance().getManager()),
    _sessionCnt(sessionCnt)
{
    CommonManager::instance().getManager().setBulkSize(bulk);
}

void Session::start()
{
    do_read();
}

// копится же список вызовов do_read, на стеке  
void Session::do_read()
{
    auto self(shared_from_this());
    _socket.async_read_some(boost::asio::buffer(_buffer, BUFFER_SIZE),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                _streamStr += std::string(_buffer, length);
                std::string_view view(_buffer, length);
                std::size_t pos = view.rfind('\n');
                if (pos == std::string_view::npos) {
                    return;
                }
                std::istringstream input(_streamStr);
                _streamStr.clear();
                _reader.setStream(input);
                _reader.read();
                do_read();
            } else {
                _reader.notifyEndCommand();
                // не знаю нужно или нет по-идее сервер еще крутится
                // хорошо бы в деструктор запихнуть вот это вот все 
                // if (--_sessionCnt == 0) {
                //     CommonManager::instance().getManager().processCommonCmd();
                // }
                _streamStr.clear();
            }
        });
}