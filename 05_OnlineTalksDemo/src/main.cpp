#include "stdafx.h"
#include <thread>

#include "cpprest/handler.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace web::http::client;
using namespace concurrency::streams; // Asynchronous streams
using namespace web::http; // Common HTTP functionality

std::unique_ptr<handler> g_httpHandler;

void client_request_demo(
    const std::string path = "https://www.apache.org/licenses/LICENSE-2.0.txt",
    web::http::method method = web::http::methods::GET)
{
    /*
    //Simple, locking approach
    web::http::client::http_client client_dummy(U(path));
    auto response_dummy = client_dummy.request(method).get();
    std::cout << response_dummy.to_string();
    
    return;
    */

    //Advanced thread approach
    std::cout << "Caller thread ID - " << std::this_thread::get_id() << std::endl;

    auto task
        = pplx::create_task([&] {
              web::http::client::http_client client_dummy(U(path));
              return client_dummy.request(method);
          });

    task.then([](http_response response) {
            std::cout << std::endl
                      << "--------------------------------------------" << std::endl;
            printf("Received response status code:%u\n", response.status_code());
            std::cout << response.to_string() << std::endl;
            std::cout << response.extract_string().get() << std::endl; //Same problem behavior as in example above, but made due to simplicity
            std::cout << std::endl
                      << "--------------------------------------------" << std::endl;
            std::cout << "Callback thread ID - " << std::this_thread::get_id() << std::endl;
        })
        .wait();

    std::cout << "HTTP request done " << std::endl;

    return;
}

void on_initialize(const string_t& address)
{
    web::uri_builder uri(address);

    auto addr = uri.to_uri().to_string();
    g_httpHandler = std::unique_ptr<handler>(new handler(addr));
    g_httpHandler->open().wait();

    ucout << "Example: GET request to 127.0.0.1:34569" << std::endl;
    ucout << utility::string_t(U("Listening for requests at: ")) << addr
          << std::endl;

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
    client_request_demo();
    return 0;

    utility::string_t port
        = U("34569");
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
};