#ifndef TCP_ERROR_H
#define TCP_ERROR_H
#include <string>
#include <stdexcept>
#include "address.h"

namespace tcp {
class Error : public std::runtime_error {
 public:
    using std::runtime_error::runtime_error;
};

class DescriptorError : public Error {
 public:
    explicit DescriptorError(const std::string& what);
};

class SocketError : public Error {
 public:
    explicit SocketError(const std::string& what);
};

class TimeOutError : public Error {
 public:
    explicit TimeOutError(const std::string& what);
};

class AddressError : public Error {
 private:
    const Address _addr;
 public:
    explicit AddressError(const std::string& what, const Address& addr);

    Address address() const;
};

class SocketOptionError : public Error {
 private:
    std::string _opt;
 public:
    SocketOptionError(const std::string& what, const std::string& option_name);

    std::string option() const;
};

}  // namespace tcp

#endif  // TCP_ERROR_H
