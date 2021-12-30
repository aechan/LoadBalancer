#include "config.h"
#include "httplib.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include <string>

using json = nlohmann::json;

void LoadBalancerConfig::parseConfig(const std::string& path) {
    std::ifstream input(path);

    std::stringstream strStream;
    strStream << input.rdbuf();
    const std::string& str = strStream.str();

    json root = json::parse(str);

    listenAddr = root["listen_addr"].get<std::string>();
    listenPort = root["listen_port"].get<int>();
    backendUrls = root["backend_urls"].get<std::vector<std::string>>();
    aliveCheckInterval = root["alive_check_interval"].get<int>();
}

void LoadBalancerConfig::setConfig(const std::vector<std::string>& urls, const std::string& listenAddr, int listenPort) {
    this->listenAddr = listenAddr;
    this->listenPort = listenPort;
    backendUrls = urls;
}

const std::string& LoadBalancerConfig::getListenAddr() const {
    return listenAddr;
}

const int LoadBalancerConfig::getListenPort() const {
    return listenPort;
}

const std::vector<std::string> LoadBalancerConfig::getBackendUrls() const {
    return backendUrls;
}

const int LoadBalancerConfig::getAliveCheckIntervalMs() const {
    return aliveCheckInterval;
}