#include<vector>



template<typename T>
class Vector()
{
	public:

		Vector(int n_elements)
			: n_rows(n_rows), n_cols(n_cols)
		{

			std::vector<T>  
		}

		int length() { return n_elements }
		int size() { return n_elements }


		Vector operator+(const Vector& v1, const Vector& v2)
		{
			assert v1.size() == v2.size();
			Vector v3{};



		}

		Vector operator*(double scalar, const Vector& v2)
		{

		}

	private:
		int n_elements{};
		std::vector<T> data;
		



}


template<typename T>
class Matrix()
{

	public:

		Matrix(int n_rows, int n_cols)
			: n_rows(n_rows), n_cols(n_cols)
		{

			std::vector<T>  
		}


	private:
		int n_rows{};
		int n_cols{};
		std::vector<T> data;
		



}
