#include<stdio>



class CSVReader {


	public:

		void read_from_file(std::string file_name) {

			std::ifstream fp{file_name};

			if (!fp)
				std::cerr << "Exception raised when trying to read in file: " << file_name;
				return;


				std::cout << "Successfully read in file: " << file_name;

		}










}



int main() {


	CSVReader file_reader;
	file_reader.read_from_file("matrix_data.csv");






return 0;

}
