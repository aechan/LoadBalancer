#include "LoadBalancer.h"
#include "Timer.h"
#include <iostream>
#include <string>
using namespace httplib;

LoadBalancer::LoadBalancer(const LoadBalancerConfig& conf)
    : pool(conf.getBackendUrls()) {
    svr.set_pre_routing_handler([&](const Request& req, Response& res) {

        std::shared_ptr<Backend> backend = pool.getNextBackend();
        if (!backend) {
            res.status = 500;
            res.reason = "All backends offline";
            return Server::HandlerResponse::Unhandled;
        }

        Client cli(backend->url);
        auto result = cli.send(req);
        res = *result;

        return Server::HandlerResponse::Handled;
    });

    // do initial live check
    aliveCheck();

    Timer t;
    // do alive checks at interval
    t.setInterval([this]() {
        aliveCheck();
    }, conf.getAliveCheckIntervalMs());

    svr.listen(conf.getListenAddr().c_str(), conf.getListenPort());
    std::cout << "Listening on " + conf.getListenAddr() + ":" + std::to_string(conf.getListenPort()) << std::endl;
}

void LoadBalancer::aliveCheck() {
    std::cout << "\nPerforming alive check..." << std::endl;
    for (auto& backend : pool.backends) {
        if (backend) {
            Client cli(backend->url);
            auto result = cli.Get("/alive");
            if (result && result->status == 200) {
                backend->setAlive(true);
            }
            else {
                backend->setAlive(false);
            }
        }
    }

    pool.print();
}