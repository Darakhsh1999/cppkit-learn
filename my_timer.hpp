#include <iostream>
#include <chrono>

class Timer {

    public:
        const char* algorithm_name;
        std::chrono::time_point<std::chrono::steady_clock> start, end;

        Timer(const char* name) {
            algorithm_name = name;
            start = std::chrono::steady_clock::now();
        }

        ~Timer() {
            end = std::chrono::steady_clock::now();
            auto t_diff = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count())*1e-3;
            std::cout << algorithm_name << " took " << t_diff << " ms" << std::endl;
        }

};