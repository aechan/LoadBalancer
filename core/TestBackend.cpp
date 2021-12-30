#include "TestBackend.h"
#include <stdio.h>
#include "Timer.h"

TestBackend::TestBackend(const std::string& listenAddr, int listenPort, int killAfterMs) {
	srv.Get("/alive", [&](const httplib::Request&, httplib::Response& res) {
		res.status = 200;
	});

	srv.Get("/hit", [&](const httplib::Request&, httplib::Response& res) {
		res.status = 200;
	});

	std::cout << "Test Backend listening on " + listenAddr + ":" + std::to_string(listenPort) << std::endl;

	if (killAfterMs > -1) {
		Timer t;
		t.setTimeout([&]() {
			std::cout << "Killing backend on " + listenAddr + ":" + std::to_string(listenPort) << std::endl;
			srv.stop();
			}, killAfterMs);
	}
	srv.listen(listenAddr.c_str(), listenPort);
}