#include"Matrix.hpp"
int main()
{
	try
	{
		Matrix<int,3, 5>mat_0;
		Matrix<int,3, 9>mat_1(15);
		Matrix<double, 4,6>mat_2(6);
		mat_0.Print();
		//should be all ones
		for (std::size_t x = 0; x < 3; ++x)
		{
			for (std::size_t y = 0; y < 5; ++y)
			{
				mat_0(x, y) = 1;
				std::cout << mat_0(x,y) << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
		mat_1.Print();
		mat_2.Print();
		//Unary minus operator
		mat_0 = -mat_0;
		mat_0.Print();
		//Test out addtion and subtract
		Matrix<int,3, 9>mat_4(20);
		Matrix<int,3, 9>mat_5 = mat_1 + mat_4;
		Matrix<int,3, 9>mat_6 = mat_1 - mat_4;
		mat_5.Print();
		mat_6.Print();
		Matrix<double,4, 6>arr_7 = 7.0 * mat_2;
		Matrix<double, 4, 6>arr_8 = mat_2 * 7.0;
		arr_7.Print();
		//Try the modification functions 
		std::function<double(double)>func = [](double a) ->double
		{
			return a * a;
		};
		arr_7.modify(func);
		arr_7.Print();
	}
	catch (const std::out_of_range& err)
	{
		std::cout << err.what()<< std::endl;
	}
	catch (const std::domain_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}