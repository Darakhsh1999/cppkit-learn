#include <cassert>
#include <cstddef>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <Eigen/Dense>
#include "csv_reader.h"


// Helper function to parse each line
std::vector<std::string> parseCSVRow(const std::string& csvRow) {

    std::vector<std::string> fields;
    std::string field;

    // Loop through the row
    for (size_t i = 0; i < csvRow.size(); i++) {

        char c = csvRow[i];

        if (c == ',') {
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }

    fields.push_back(field); // append the last number
    return fields;
};

Eigen::MatrixXf readCSVToMatrix(const std::string& filename, bool contains_header, std::vector<std::string>& headers) {

    // Read in the CSV file
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    // Text string for each row in CSV file
    std::string line;
    
    // Temporary Matrix of vectors
    std::vector<std::vector<float>> rowData;
    std::vector<std::string> fields;

    // Extract headers
    if (contains_header && std::getline(file, line))
        headers = parseCSVRow(line);

    // Parse numerical data
    size_t lineNumber = 1;
    while (std::getline(file, line)) {

        lineNumber++;

        if (line.empty())
            continue;

        fields = parseCSVRow(line);

        if (contains_header)
            assert(fields.size() == headers.size() && "Number of data elements equal number of header features");

        std::vector<float> row;
        row.reserve(fields.size());

        for (size_t col = 0; col < fields.size(); col++) {
            try {
                row.push_back(std::stof(fields[col]));
            } catch (const std::exception&) {
                throw std::runtime_error("Encountered nonnumerical value: " + fields[col]);
            }
        }
        rowData.push_back(std::move(row));
    }

    file.close();

    // Did not get any rows of data
    if (rowData.empty())
        throw std::length_error("Could not parse any data in the CSV file");

    // Allocate memory for Eigen matrix
    const size_t numRows = rowData.size();
    const size_t numCols = fields.size();
    Eigen::MatrixXf matrix(numRows, numCols);

    // Write to Eigen matrix
    for (size_t r = 0; r < numRows; r++)
        for (size_t c = 0; c < numCols; c++)
            matrix(r,c) = rowData[r][c];

    return matrix;
}