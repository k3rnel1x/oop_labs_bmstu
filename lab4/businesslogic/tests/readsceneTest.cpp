#include "../io/CsvFileReader.h"
#include <iostream>
#define PATH "/Users/k3rnel1x/Programming/oop_labs_bmstu/lab4/test_files/students_exams (вариант 2).csv"
using namespace std;

int main(int argc, char *argv[])
{
    CsvFileReader reader;
    NormalizationParameters nparams;
    Scene scene;
    try
    {
        scene = reader.ReadScene(PATH, nparams);
    } catch (exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    vector<Figure> figures = scene.GetFigures();

    for (auto& figure : figures)
    {
        for (auto& v : figure.GetVertices())
        {
            Point3D p = v.GetPosition();
            cout << p.x << ' ' << p.y << ' ' << p.z << ' ' << endl;
        }
    }
}
