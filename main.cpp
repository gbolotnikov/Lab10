#include <boost/program_options.hpp>
#include <boost/asio.hpp>

#include <iostream>
#include <stdexcept>

struct Context
{
    uint32_t port;
    size_t bulkSize;
};

namespace po = boost::program_options;
Context parse_command_options(int argc, char* argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help",                                                      "Print this message")
        ("port", po::value<uint32_t>()->required(),                   "Server port")
        ("bulk", po::value<std::size_t>()->required(),                "Command block size");

    po::variables_map vm;
    try {
        po::store(parse_command_line(argc, argv, desc), vm);
        if (vm.count("help") != 0) {
            std::cout << desc << "\n";
            throw;
        }
        po::notify(vm);
    }
    catch (const po::error& error) {
        std::cerr << "Error while parsing command-line arguments: "
                << error.what() << "\nPlease use --help to see help message\n";
        throw;
    }
    uint32_t port = vm["port"].as<uint32_t>();
    size_t bulkSize = vm["bulk"].as<size_t>();
    if (bulkSize < 1) {
        std::cerr << ("Block size mininum 1 current = ") + std::to_string(bulkSize) + '\n';
        throw;
    }
    return Context{port, bulkSize};
}

int main(int argc, char* argv[]) {
    try {
        Context context;
        try {
            context = parse_command_options(argc, argv);
        }
        catch (...) {
            return 0;
        }
        boost::asio::io_service io_context;
        // my::Server server(io_context, context.port, context.bulkSize);
        io_context.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

