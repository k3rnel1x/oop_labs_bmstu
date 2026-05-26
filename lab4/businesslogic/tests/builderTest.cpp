#include <cassert>

#include "../math/Vertex.h"
#include "../math/TransformMatrixBuilder.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    Point3D point{1, 2, 3};
    Vertex v(point);

    TransformMatrix Rmatrix = TransformMatrixBuilder::CreateRotationMatrix(1, 2, 2);
    TransformMatrix Mmatrix = TransformMatrixBuilder::CreateMoveMatrix(1, 2, 2);
    TransformMatrix Smatrix = TransformMatrixBuilder::CreateScaleMatrix(1, 2, 2);
    Point3D p1 = Rmatrix(point);
    Point3D p2 = Mmatrix(point);
    Point3D p3 = Smatrix(point);

    cout << "p1: " << p1.x << " " << p1.y << " " << p1.z << endl;
    cout << "p2: " << p2.x << " " << p2.y << " " << p2.z << endl;
    cout << "p3: " << p3.x << " " << p3.y << " " << p3.z << endl;
}
