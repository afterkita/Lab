#include <BMP.hpp>
#include <iostream>
#include <cmath>

int main()
{
    try
    {
       mt::images::BMP test_bmp1(200, 100);
       test_bmp1.Fill({ 0,205,0 });
       test_bmp1.Rotate(1.37 );
        test_bmp1.Refactor();
        test_bmp1.Save("test.bmp");

        mt::images::BMP bmp_real;
        bmp_real.Open("in.bmp");
        bmp_real.Rotate(1.37);
        bmp_real.Refactor();
        bmp_real.Save("out.bmp");


    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}