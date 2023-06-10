#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>

#include <mutex>

using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_service& io_context, short port, std::size_t bulk);

private:
    void do_accept();

    tcp::acceptor _acceptor;
    std::size_t _bulk;
};

#endif