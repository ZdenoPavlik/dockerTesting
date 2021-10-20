#define UNUSED(expr) (void)(expr) //clang-tidy

#include <chrono>
#include <csignal>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "cpprest/handler.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<handler> g_httpHandler;

void on_initialize(const string_t& address)
{

    web::uri_builder uri(address);

    auto addr = uri.to_uri().to_string();
    g_httpHandler = std::unique_ptr<handler>(new handler(addr));
    g_httpHandler->open().wait();

    ucout << "Example: GET request to 127.0.0.1:34569" << std::endl;
    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

    return;
}

void on_shutdown(int signal)
{
    g_httpHandler->close().wait();
    std::cout << "Exiting with signal " << signal << std::endl;
    std::_Exit(0);
}

int main(int argc, char* argv[])
{
    utility::string_t port = U("34569");
    if (argc == 2) {
        port = argv[1];
    }

    utility::string_t address = U("http://0.0.0.0:");
    address.append(port);

    on_initialize(address);

    std::signal(SIGTERM, on_shutdown);
    std::signal(SIGKILL, on_shutdown);
    while (true) {
    };

    return 0;
}