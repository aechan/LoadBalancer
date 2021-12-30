# CMakeList.txt : CMake project for LoadBalancer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
# Add source to this project's executable.
add_executable (LoadBalancer "LoadBalancer.cpp" "LoadBalancer.h" "Config.h" "Config.cpp" "Backends.h" "main.cpp" "main.h" "TestBackend.h" "TestBackend.cpp" "TestClient.h" "TestClient.cpp" "Timer.h" )
target_compile_features(LoadBalancer PRIVATE cxx_std_17)
target_link_libraries(LoadBalancer PUBLIC
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::SSL>
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::Crypto>)
target_compile_definitions(LoadBalancer PUBLIC
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:CPPHTTPLIB_OPENSSL_SUPPORT>
    )
target_link_libraries(LoadBalancer PRIVATE nlohmann_json::nlohmann_json httplib::httplib)
