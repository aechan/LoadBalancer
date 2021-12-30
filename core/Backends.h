#pragma once
#include <string>
#include <shared_mutex>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <iostream>

struct Backend {
    std::string url;
    bool alive = false;
    std::shared_mutex mut;

    Backend(const std::string& url) : url(url) {}

    void setAlive(bool alive) {
        std::lock_guard<std::shared_mutex> g(mut);
        this->alive = alive;
    }

    bool isAlive() {
        std::shared_lock<std::shared_mutex> g(mut);
        return alive;
    }

    void print() {
        std::shared_lock<std::shared_mutex> g(mut);
        std::cout << "\tURL: " + url << std::endl;
        std::cout << "\tAlive: " + std::string(alive ? "true" : "false") << std::endl << std::endl;
    }
};

struct BackendPool {
    std::vector<std::shared_ptr<Backend>> backends;
    std::atomic<int> curr = 0;

    BackendPool(std::vector<std::string> backendUrls) {
        for (const auto& str : backendUrls) {
            backends.push_back(std::make_shared<Backend>(str));
        }
    }

    int getNextIndex() {
        curr++;
        return curr % backends.size();
    }

    // round-robin policy
    std::shared_ptr<Backend> getNextBackend() {
        int next = getNextIndex();
        int lim = backends.size() + next;
        for (int i = next; i < lim; i++) {
            int idx = i % backends.size();

            if (backends[idx]->isAlive()) {
                if (i != next) {
                    curr = idx;
                }
                return backends[idx];
            }
        }

        // if we get here, no backends are alive
        return nullptr;
    }

    void print() {
        int aliveCount = 0;
        for (auto backend : backends) {
            backend->print();
            if (backend->isAlive()) {
                aliveCount++;
            }
        }

        std::cout << "BackendPool Status" << std::endl;
        std::cout << "\tAlive: " + std::to_string(aliveCount) + "/" + std::to_string(backends.size()) << std::endl;
        std::cout << "\tCurrent Target: " + std::to_string(curr % backends.size()) << std::endl;
    }
};