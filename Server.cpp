#include "include/Server.hpp"
#include "include/Session.hpp"

Server::Server(boost::asio::io_service& io_context, short port, std::size_t bulk)
    : _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
    , _bulk(bulk)
{
    do_accept();
}

// не могу понять почему не рекурсия
void Server::do_accept()
{
    _acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                _sessionCnt++;
                std::make_shared<Session>(_sessionCnt, _bulk, std::move(socket))->start();
            }
            do_accept();
        });
}

