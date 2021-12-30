#include "main.h"
#include "TestClient.h"
#include "TestBackend.h"
#include <thread>

int main(int argc, char* argv[]) {
    using namespace httplib;
    LoadBalancerConfig conf;
    if (argc != 2) {
        // for debug
        conf.setConfig({
            "http://localhost:1001",
            "http://localhost:1002",
            "http://localhost:1003"
        }, "0.0.0.0", 8080);

        std::thread tb1([] {
            TestBackend b1("0.0.0.0", 1001, 2000);
        });
        
        std::thread tb2([] {
            TestBackend b2("0.0.0.0", 1002);
        });

        std::thread tb3([] {
            TestBackend b3("0.0.0.0", 1003);
        });

        tb1.detach();
        tb2.detach();
        tb3.detach();
    }
    else {
        std::string path(argv[1]);

        conf.parseConfig(path);
    }

    
    LoadBalancer lb(conf);
    while (true) {}
}