#define UNUSED(expr) (void)(expr) //clang-tidy

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>

#include <pistache/endpoint.h>

using namespace Pistache;

class HelloHandler : public Http::Handler
{
public:
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request &request, Http::ResponseWriter response)
    {
        response.send(Http::Code::Ok, "Hello, World\n");
    }
};

int main(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);

    std::cout << "Starting listener on localhost:12345" << std::endl;

    //Listener
    Address addr(Ipv4::any(), Port(12345));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<HelloHandler>());
    server.serve();

    return 0;
}