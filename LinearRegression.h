#pragma once

#include <Eigen/Dense>
#include <utility>

class LinearRegression {

public:
    LinearRegression(bool include_bias = true);

    void fit(Eigen::MatrixXf& X, Eigen::VectorXf& y);

    float predict(Eigen::VectorXf& x);

    Eigen::VectorXf getBetas();

    std::pair<int, int> getShape();

private:
    bool m_include_bias = false;
    int m_n {};
    int m_p {};
    Eigen::VectorXf m_betas;

};
