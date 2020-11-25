#include <iostream>
#include <algorithm>
#include <string>
#include "httperr.h"
#include "test_runner.h"
#include "message.h"

void TestRequestStartLine();
void TestRequestHeaders();
void TestResponce();
void TestBody();

void TestRequestStartLine() {
    try {
        http::Request r("asdasd");
        ASSERT(false);
    } catch (http::IncorrectData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "asdasd");
    }

    try {
        http::Request r("DELE");
        ASSERT(false);
    } catch (http::ExpectingData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "DELETE");
    }

    try {
        http::Request r("GETqwe");
        ASSERT(false);
    } catch (http::IncorrectData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "GETqwe");
    }

    try {
        http::Request r("GET /");
        ASSERT(false);
    } catch (http::IncorrectData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Invalid request protocol");
    }

    try {
        http::Request r("GET /asads HTT");
        ASSERT(false);
    } catch (http::ExpectingData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "HTTP/");
    }

    try {
        http::Request r("GET / HTTP");
        ASSERT(false);
    } catch (http::ExpectingData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "HTTP/");
    }

    try {
        http::Request r("GET / HTTP/");
        ASSERT(false);
    } catch (http::ExpectingData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Request protocol version");
    }

    try {
        http::Request r("GET / HTTP/1.3");
        ASSERT(false);
    } catch (http::IncorrectData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Request version");
    }

    try {
        http::Request r("GET / HTTP/1.1asc\r\n");
        ASSERT(false);
    } catch (http::IncorrectData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Request version");
    }

    try {
        http::Request r("GET / HTTP/1.1 asd\r\n");
        ASSERT(false);
    } catch (http::IncorrectData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Start line");
    }

    try {
        http::Request r("GET / HTTP/1.1 \t \r\n\r\n");
        ASSERT(r.method() == "GET");
        ASSERT(r.target() == "/");
        ASSERT(r.version() == "1.1");
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }
    try {
        http::Request r("GET / HTTP/1.1\r\n\r\n");
        ASSERT(r.method() == "GET");
        ASSERT(r.target() == "/");
        ASSERT(r.version() == "1.1");
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }
}

void TestRequestHeaders() {
    try {
        http::Request r("GET / HTTP/1.1\r\n\r\n");
        ASSERT_EQUAL(r.headers().size(), 0u);
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }

    try {
        http::Request r("GET / HTTP/1.1\r\nasdas\r\n\r\n");
        ASSERT(false);
    } catch (http::IncorrectData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Header name");
    }

    try {
        http::Request r("GET / HTTP/1.1\r\n Ho:st 5\r\n\r\n");
        ASSERT(false);
    } catch (http::IncorrectData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Header name");
    }

    try {
        http::Request r("GET / HTTP/1.1\r\n Host:\r\n\r\n");
        ASSERT_EQUAL(r.headers().size(), 1u);
        ASSERT_EQUAL(http::to_string(r.headers()[0]), "Host: \r\n");
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }

    try {
        http::Request r("GET / HTTP/1.1\r\nHost: \r\n\r\n");
        ASSERT_EQUAL(r.headers().size(), 1u);
        ASSERT_EQUAL(http::to_string(r.headers()[0]), "Host: \r\n");
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }

    try {
        http::Request r("GET / HTTP/1.1\r\nHost: localhost:8080\r\n\r\n");
        ASSERT_EQUAL(r.headers().size(), 1u);
        ASSERT_EQUAL(r.headers().begin()->value, "localhost:8080");
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }

    try {
        http::Request r("GET / HTTP/1.1\r\nHost: localhost:8080\r\n \r\n");
    } catch (http::IncorrectData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Header name");
    }

    try {
        http::Request r("GET / HTTP/1.1\r\nHost: localhost:8080\r\nasdasd\r\n");
    } catch (http::IncorrectData& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Header name");
    }

    try {
        http::Request r("GET / HTTP/1.1\r\nHost: localhost:8080\r\nFrom:\r\n");
    } catch (http::ParsingError& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Expecting \\r\\n\\r\\n before body");
    }

    try {
        http::Request r("GET / HTTP/1.1\r\nHost: localhost:8080\r\n\r\n");
        ASSERT_EQUAL(r.headers().size(), 1u);
        ASSERT_EQUAL(r.headers().begin()->value, "localhost:8080");
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }

    try {
        http::Request r("GET / HTTP/1.1\r\nHost: localhost:8080\r\nFrom: \r\n\r\n");
        ASSERT_EQUAL(r.headers().size(), 2u);
        ASSERT_EQUAL(http::to_string(r.headers()[0]), "Host: localhost:8080\r\n");
        ASSERT_EQUAL(http::to_string(r.headers()[1]), "From: \r\n");
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }

    try {
        http::Request r("GET / HTTP/1.1\r\n Host: localhost:8080\r\nConnection: keep-alive\r\n\r\n");
        ASSERT_EQUAL(r.headers().size(), 2u);
        ASSERT_EQUAL(http::to_string(r.headers()[0]), "Host: localhost:8080\r\n");
        ASSERT_EQUAL(http::to_string(r.headers()[1]), "Connection: keep-alive\r\n");
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }

    try {
        http::Request r("GET / HTTP/1.1\r\n \t \t Host: localhost:8080\r\n  \t  \tConnection: keep-alive\r\n\r\n");
        ASSERT_EQUAL(r.headers().size(), 2u);
        ASSERT_EQUAL(http::to_string(r.headers()[0]), "Host: localhost:8080\r\n");
        ASSERT_EQUAL(http::to_string(r.headers()[1]), "Connection: keep-alive\r\n");
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }
}

void TestBody() {
    try {
        http::Request r("GET / HTTP/1.1\r\n\r\n");
        ASSERT_EQUAL(r.body().size(), 0u);
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }
    try {
        http::Request r("GET / HTTP/1.1\r\n\r\n\r\n");
        ASSERT(false);
    } catch (http::ParsingError& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Body exists, but no content length found");
    }
    try {
        http::Request r("GET / HTTP/1.1\r\n Host: localhost:8080\r\n\r\nasdasd");
        ASSERT(false);
    } catch (http::ParsingError& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Body exists, but no content length found");
    }
    try {
        http::Request r("GET / HTTP/1.1\r\n Host: localhost:8080\r\nContent-Length: \r\n\r\nasdasd");
        ASSERT(false);
    } catch (http::ParsingError& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Cannot convert content length");
    }
    try {
        http::Request r("GET / HTTP/1.1\r\n Host: localhost:8080\r\nContent-Length: asd\r\n\r\nasdasd");
        ASSERT(false);
    } catch (http::ParsingError& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Cannot convert content length");
    }
    try {
        http::Request r("GET / HTTP/1.1\r\n Host: localhost:8080\r\nContent-Length: 2\r\n\r\nasdasd");
        ASSERT(false);
    } catch (http::ParsingError& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Invalid length of body");
    }
    try {
        http::Request r("GET / HTTP/1.1\r\n Host: localhost:8080\r\nContent-Length: 6\r\n\r\n2");
        ASSERT(false);
    } catch (http::ParsingError& ex) {
        std::string e(ex.what());
        ASSERT_EQUAL(e, "Invalid length of body");
    }
    try {
        http::Request r("GET / HTTP/1.1\r\nHost: localhost:8080\r\nContent-Length: 13\r\n\r\nTechnosphere!");
        ASSERT_EQUAL(r.headers().size(), 2u);
        ASSERT_EQUAL(http::to_string(r.headers()[0]), "Host: localhost:8080\r\n");
        ASSERT_EQUAL(http::to_string(r.headers()[1]), "Content-Length: 13\r\n");
        ASSERT_EQUAL(r.body(), "Technosphere!");
    } catch (http::ParsingError& ex) {
        ASSERT(false);
    }
}

void TestResponce() {
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRequestStartLine);
    RUN_TEST(tr, TestRequestHeaders);
    RUN_TEST(tr, TestBody);
    RUN_TEST(tr, TestResponce);
}
