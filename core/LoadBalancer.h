#define CPPHTTPLIB_OPENSSL_SUPPORT
#pragma once
#include "Backends.h"
#include "Config.h"
#include "httplib.h"

class LoadBalancer {
public:
    LoadBalancer(const LoadBalancerConfig& conf);

private:
    void aliveCheck();
    BackendPool pool;
    httplib::Server svr;
};
