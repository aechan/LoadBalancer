#pragma once

#include "httplib.h"

class TestBackend {
public:
	TestBackend(const std::string& listenAddr, int listenPort, int killAfterMs = -1);
private:
	httplib::Server srv;
};