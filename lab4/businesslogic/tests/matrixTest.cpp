#include <cassert>

#include "../TransformMatrix.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    TransformMatrix matrix1{
            {1, 3, 5},
            {2, 2, 1},
            {1, 4, 5}
    };

    matrix1.printToStdout();

    TransformMatrix matrix2{
                {1, 3, 2},
                {0,-1, 1},
                {2, 1, 2}
    };
    matrix2.printToStdout();

    TransformMatrix matrix3 = matrix1 * matrix2;
    matrix3.printToStdout();
}
