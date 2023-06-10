#include "Include/Session.hpp"
#include "Include/CommonManager.hpp"
#include <sstream>

Session::Session(std::size_t bulk, tcp::socket socket)
    : _socket(std::move(socket)),
    _reader(CommonManager::instance().getManager(), bulk)
{
}

void Session::start()
{
    do_read();
}

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
                std::istringstream input(std::move(_streamStr));
                // _streamStr.clear();
                // m_controller.receive(m_buffer, length);
                do_read();
            }
        });
}