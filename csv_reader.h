#pragma once
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> parseCSVRow(const std::string& csvRow);
Eigen::MatrixXf readCSVToMatrix(const std::string& filename, bool contains_header, std::vector<std::string>& headers);