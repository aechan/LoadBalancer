#pragma once
#include <vector>
#include <string>

class LoadBalancerConfig {
public:
    void parseConfig(const std::string& path);
    void setConfig(const std::vector<std::string>& urls, const std::string& listenAddr, int listenPort);

    const std::string& getListenAddr() const;
    const int getListenPort() const;
    const std::vector<std::string> getBackendUrls() const;
    const int getAliveCheckIntervalMs() const;
private:
    std::vector<std::string> backendUrls;
    std::string listenAddr = "http://localhost";
    int listenPort = 8080;
    int aliveCheckInterval = 5000;
};
