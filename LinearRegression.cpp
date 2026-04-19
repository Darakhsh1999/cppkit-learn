#include <iostream>
#include "LinearRegression.h"
#include <Eigen/Dense>

LinearRegression::LinearRegression(bool include_bias)
    : m_include_bias(include_bias) {}

void LinearRegression::fit(Eigen::MatrixXf& X, Eigen::VectorXf& y) {

    m_n = X.rows();
    m_p = X.cols();

    // Prepend column of 1s in the first column
    if (m_include_bias) {
        X.conservativeResize(X.rows(), X.cols()+1);
        X.rightCols(X.cols() - 1) = X.leftCols(X.cols() -1).eval();
        X.col(0).setOnes();
    }

    // beta = (X^T*X)^-1 * (X^T * y)
    m_betas = (X.transpose()*X).inverse()*(X.transpose()*y);
    auto betas2 = (X.transpose()*X).ldlt().solve(X.transpose() * y);

    std::cout << "Model fit completed" << std::endl;

}

float LinearRegression::predict(Eigen::VectorXf& x) {
    float y_pred;
    if (m_include_bias) {
        Eigen::VectorXf x_new(x.size() + 1);
        x_new << 1.0f, x;
        y_pred = x_new.dot(m_betas); // inner dot product: vector x vector -> float
    } else {
        y_pred = x.dot(m_betas); // inner dot product: vector x vector -> float
    }
    return y_pred;
}

Eigen::VectorXf LinearRegression::getBetas() {
    return m_betas;
}

std::pair<int, int> LinearRegression::getShape() {
    return std::pair(m_n, m_include_bias ? m_p+1 : m_p);
}
