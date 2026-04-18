#include <Eigen/Dense>
#include <iostream>

int main() {
    Eigen::MatrixXd m = Eigen::MatrixXd::Random(3, 3);
    std::cout << "Matrix:\n" << m << "\n";
    std::cout << "Inverse:\n" << m.inverse() << "\n\n";

    // Transpose
    std::cout << "Transpose:\n" << m.transpose() << "\n\n";

    // Matrix multiplication
    Eigen::MatrixXd result = m * m;
    std::cout << "Matrix multiplication (m * m):\n" << result << "\n\n";

    // Indexing - access elements
    std::cout << "Element at (0,0): " << m(0, 0) << "\n";
    std::cout << "Element at (1,2): " << m(1, 2) << "\n\n";

    // Create a 1D vector
    Eigen::VectorXd vec = Eigen::VectorXd::Random(3);
    std::cout << "1D Vector:\n" << vec << "\n\n";

    // Matrix-vector multiplication
    Eigen::VectorXd mv_result = m * vec;
    std::cout << "Matrix-vector multiplication (m * vec):\n" << mv_result << "\n\n";

    // X3 = X * X * X (matrix cubing)
    Eigen::MatrixXd X3 = m * m * m;
    std::cout << "X^3 (m * m * m):\n" << X3 << "\n";

    return 0;
}