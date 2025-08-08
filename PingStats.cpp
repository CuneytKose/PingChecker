#include <iostream>
#include <string>
#include <array>
#include <memory>

void run_ping(const std::string& host) {
    std::string cmd = "ping -c 1 " + host;
    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "Ping failed!" << std::endl;
        return;
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        std::string line = buffer.data();
        if (line.find("time=") != std::string::npos) {
            std::cout << "Ping result: " << line;
        }
    }
}

int main() {
    std::string target;
    std::cout << "Enter domain or IP: ";
    std::cin >> target;

    run_ping(target);
    return 0;
}