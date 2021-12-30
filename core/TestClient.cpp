#include "TestClient.h"
#include "httplib.h"

TestClient::TestClient(const std::string& lbAddr) {
	httplib::Client cli(lbAddr);

	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		cli.Get("/hit");
	}
}