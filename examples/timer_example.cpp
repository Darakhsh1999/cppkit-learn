#include "../timer.h"
#include <iostream>



int main() {

    Timer timer;

    size_t N = 524288;
    int sum {0};


    timer.start();
    for (size_t i = 0; i < N; i++) {
        sum += 2*i*i;
    }
    double t_loop = timer.stop();

    std::cout << "Sum is equal to " << sum << std::endl;
    std::cout << "Elapsed time: " << t_loop << " ms" << std::endl;

    return 0;
}