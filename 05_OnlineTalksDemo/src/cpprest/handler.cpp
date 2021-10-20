#include "handler.h"

#include "../FakeDb.hpp"

FakeDB fakeDb;

int getIdFromUrl(const std::string& path);

handler::handler(utility::string_t url)
    : m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&handler::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&handler::handle_delete, this, std::placeholders::_1));
}

void handler::handle_error(pplx::task<void>& t)
{
    try {
        t.get();
    } catch (...) {
        // Ignore the error, Log it if a logger is available
    }
}

//
// GET Request
//
void handler::handle_get(http_request message)
{
    std::cout << message.to_string() << endl;

    web::json::value responseArray;
    const int count = fakeDb.getStudentCount();
    if (count == 0) {
        message.reply(status_codes::NoContent, web::json::value::array()); //Return empty array
        return;
    }

    for (int i = 0; i < fakeDb.getStudentCount(); i++) {
        web::json::value test = fakeDb.getStudentById(i).toJson();

        responseArray[i] = test;
    }

    message.reply(status_codes::OK, responseArray);

    return;
};

//
// A POST request
//
void handler::handle_post(http_request message)
{
    ucout << message.to_string() << endl;

    web::json::value body = message.extract_json().get();

    if (body.has_integer_field("age") && body.has_integer_field("id") && body.has_string_field("name") && body.has_string_field("surname")) {
        Student newStudent(body);
        fakeDb.addStudent(newStudent); // ADD student
        message.reply(status_codes::Created);
    } else {
        message.reply(status_codes::BadRequest);
    }

    return;
};

//
// A DELETE request
//
void handler::handle_delete(http_request message)
{
    try { // HEADS UP -> example of general error handling

        int id = getIdFromUrl(message.request_uri().path());

        fakeDb.removeStudent(id); // REMOVE student
        message.reply(status_codes::OK);
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        message.reply(status_codes::InternalError);
    } catch (...) {
        message.reply(status_codes::InternalError);
    }

    return;
};

//
// A PUT request
//
void handler::handle_put(http_request message)
{
    ucout << message.to_string() << endl;

    web::json::value body = message.extract_json().get();

    if (body.has_integer_field("age") && body.has_integer_field("id") && body.has_string_field("name") && body.has_string_field("surname")) {
        Student newStudent(body);
        fakeDb.modifyStudentAtIndex(getIdFromUrl(message.request_uri().path()),
            newStudent); // MODIFY student
        message.reply(status_codes::OK);
    } else {
        message.reply(status_codes::BadRequest);
    }

    return;
};

int getIdFromUrl(const std::string& path)
{
    const std::string key = "/api/students/";
    auto tempString = path.substr(path.find(key) + key.length(), path.length() - key.length());
    int id = stoi(tempString);

    std::cout << "Parsed ID " << id << std::endl;
    return id;
}