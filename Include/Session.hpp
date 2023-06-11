#ifndef SESSION_HPP
#define SESSION_HPP

#include "StreamReader.hpp"

#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <mutex>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(std::atomic<std::uint32_t>& sessionCnt, std::size_t bulk, tcp::socket socket);
    void start();

private:
    void do_read();

    static constexpr std::size_t BUFFER_SIZE = 1024;
    tcp::socket _socket;
    char _buffer[BUFFER_SIZE];
    std::string _streamStr;
    StreamReader _reader;
    std::atomic<std::uint32_t>& _sessionCnt;
};

#endif // NETWORK_SESSION_H
