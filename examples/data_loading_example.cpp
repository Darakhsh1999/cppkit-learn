#include "../csv_reader.h"
#include<iostream>
#include<vector>


int main() {

    std::string filename = "data/matrix_data_with_headers.csv";
    bool contains_headers = true;

    std::cout << "Executing data loading example" << std::endl;
    std::vector<std::string> headers;

    try {
        
        // Read in data from file
        auto data = readCSVToMatrix(filename, contains_headers, headers);

        // Summary
        std::cout << "Loaded matrix: " << data.rows() << " rows x " << data.cols() << " cols \n\n";

        // Header names
        std::cout << "Header columns: ";
        for (size_t i = 0; i < headers.size(); i++)
            std::cout << headers[i] << (i + 1 < headers.size() ? ", " : "\n");

        // Print matrix content
        std::cout << "\n\n Data:\n" << data << "\n\n";


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Finished example" << std::endl;
    return 0;
}