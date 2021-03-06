#include <iostream>
#include "service.h"
#include "bufconnection.h"
#include "tcperr.h"

class EchoListner : public net::IServiceListener {
    void onNewConnection(net::BufferedConnection& cn) override {
        std::cout << "New client: " << cn.address() << std::endl;
        cn.subscribe(net::OPTION::READ);
        (void) cn;
    }
    void onClose(net::BufferedConnection& cn) override {
        std::cout << "Client " << cn.address() << " disconnected!" << std::endl;
        (void) cn;
    }
    void onWriteDone(net::BufferedConnection& cn) override {
        std::cout << "Write happened!" << std::endl;
        cn.unsubscribe(net::OPTION::WRITE);
        (void) cn;
    }
    void onReadAvailable(net::BufferedConnection& cn) override {
        std::cout << "Client wrote: " << cn.read_buf() << std::endl;
        if (cn.read_buf().find("end") != cn.read_buf().npos) {
            cn.unsubscribe(net::OPTION::READ);
            cn.write({cn.read_buf().rbegin(), cn.read_buf().rend()});
            cn.subscribe(net::OPTION::WRITE);
        }
    }
    void onError(net::BufferedConnection& cn)         override {
        std::cout << "Error happened!" << std::endl;
        (void) cn;
    }
};

int main() {
    EchoListner el;
    try {
        net::Service service({"127.0.0.1", 8080}, &el);
        service.run();
    } catch (tcp::AddressError& ex) {
        std::cout << ex.what() << std::endl;
    }
}

