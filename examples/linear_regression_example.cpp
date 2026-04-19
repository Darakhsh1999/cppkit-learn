#include "../LinearRegression.h"
#include "../csv_reader.h"
#include "../timer.h"

#include <string>
#include <csignal>
#include <vector>
#include <iostream>
#include <iomanip>

int main() {

    // Benchmark timer
    Timer performance_timer;

    // Load in data
    std::string filename_train = "data/regression_data_train.csv";
    std::string filename_test = "data/regression_data_test.csv";
    bool contains_headers = true;
    std::vector<std::string> headers;

    performance_timer.start();
    auto train_data = readCSVToMatrix(filename_train, contains_headers, headers);
    auto t_data_loading = performance_timer.stop();

    headers.clear();
    auto test_data = readCSVToMatrix(filename_test, contains_headers, headers);

    // Summary of data
    std::cout << "Loaded matrix: " << train_data.rows() << " rows x " << train_data.cols() << " cols \n\n";

    // Header names
    std::cout << "Header columns: ";
    for (size_t i = 0; i < headers.size(); i++)
        std::cout << headers[i] << (i + 1 < headers.size() ? ", " : "\n");

    // Split data into X,y
    Eigen::MatrixXf X_train = train_data.leftCols(train_data.cols() - 1);
    Eigen::VectorXf y_train = train_data.col(train_data.cols() - 1);
    Eigen::MatrixXf X_test = test_data.leftCols(test_data.cols() - 1);
    Eigen::VectorXf y_test = test_data.col(test_data.cols() - 1);


    // Define Linear Regression model
    bool include_bias = true;
    LinearRegression model(include_bias);

    // Fit model on data
    performance_timer.start();
    model.fit(X_train, y_train);
    auto t_model_fit = performance_timer.stop();

    // Print beta estimators
    auto betas = model.getBetas();
    const size_t n_features = betas.size();
    std::cout << "[";
    for (size_t feature_idx = 0; feature_idx < n_features; feature_idx++) {
        std::cout << std::fixed << std::setprecision(3) << betas[feature_idx] << ((feature_idx < n_features-1) ? ", " : "");
    }
    std::cout << "]" << std::endl;

    // Predict on new data sample
    Eigen::VectorXf y_predictions(X_test.rows());
    for (size_t pred_idx = 0; pred_idx < X_test.rows(); pred_idx++) {
        Eigen::VectorXf x_test = X_test.row(pred_idx);
        y_predictions[pred_idx] = model.predict(x_test);
    }

    // Print y_predict prediction
    std::cout << "y_predict = " << std::fixed << std::setprecision(3) << y_predictions[0] << std::endl;

    // Print timings
    std::cout << "Data Loading:" << t_data_loading << " ms" << std::endl;
    std::cout << "Model Fit: " << t_model_fit << " ms" << std::endl;

    std::cout << "Linear Regression example finished" << std::endl;
    return 0;
}