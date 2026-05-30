#include "CsvFileReader.h"
#include <sstream>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

Scene CsvFileReader::ReadScene(std::string path, NormalizationParameters nparams)
{
    using namespace std;
    std::ifstream f = _openValidFile(path);
    std::cout << "Reading file " << path << std::endl;

    // Fill vertices
    vector<Vertex> vertices;
    string line;
    int r = 0;
    int c = 0;
    while (!f.eof())
    {
        if (!getline(f, line))
            break;

        stringstream ss(line);
        string part;
        c = 0;
        while (getline(ss, part, ','))
        {
            Point3D p{double(r), double(c++), stod(part)};
            vertices.push_back(Vertex(p));
        }
        ++r;
    }
    f.close();
    int size = c;
    // cout << "size = " << size << endl;

    // Get zMax and zMin
    Point3D first = vertices[0].GetPosition();
    double zMax = first.z, zMin = first.z;
    for (const auto& v : vertices) {
        Point3D p = v.GetPosition();
        zMax = std::max(zMax, p.z);
        zMin = std::min(zMin, p.z);
    }

    // Normalize
    for (auto& v : vertices)
    {
        Point3D p = v.GetPosition();
        p.x *= nparams.DxScale;
        p.y *= nparams.DyScale;
        double normZ = nparams.Min + double(p.z - zMin) / double(zMax - zMin) * double(nparams.Max - nparams.Min);
        p.z = normZ;
        v = Vertex(p);
    }

    std::cout << "readed " << vertices.size() << " vertices" << std::endl;

    // Construct Edges
    vector<Edge> edges;
    for (int i = 0; i < vertices.size(); ++i)
    {
        if (( i + 1 < vertices.size() ) && ( (i+1) % size != 0 ))
            edges.push_back(Edge(vertices[i], vertices[i+1]));

        if(i + size < vertices.size())
            edges.push_back(Edge(vertices[i], vertices[i + size]));
    }

    Figure figure(std::move(vertices), std::move(edges));
    vector figures{figure};
    Scene scene{std::move(figures), std::move(nparams)};
    return scene;
}

// Scene CsvFileReader::ReadScene(std::string path, NormalizationParameters nparams)
// {
//     using namespace std;
//     std::ifstream f = _openValidFile(path);
//     std::cout << "Reading file " << path << std::endl;
//
//     FILE* file = fopen(path.c_str(), "r");
//     char buff[200] = {0};
//
//     double row = 0;
//     vector<Vertex> vertices;
//     char* res;
//     do {
//         res = std::fgets(buff, 200, file);
//         if(!res)
//             break;
//
//         char* ptr = buff;
//         char* endPtr;
//         double col = 0;
//         while(*ptr)
//         {
//
//             double val = strtod(ptr, &endPtr);
//
//             Point3D point = {
//                 .x = col,
//                 .y = row,
//                 .z = val,
//             };
//
//             vertices.push_back(Vertex(point));
//             ptr = endPtr + 1;
//             ++col;
//         }
//
//         ++row;
//     } while(1);
//     int size = row;
//     fclose(file);
//     // Get zMax and zMin
//     Point3D first = vertices[0].GetPosition();
//     double zMax = first.z, zMin = first.z;
//     for (const auto& v : vertices) {
//         Point3D p = v.GetPosition();
//         zMax = std::max(zMax, p.z);
//         zMin = std::min(zMin, p.z);
//     }
//
//     for (auto& v : vertices)
//     {
//         Point3D p = v.GetPosition();
//         p.x *= nparams.DxScale;
//         p.y *= nparams.DyScale;
//         double normZ = nparams.Min + (double)(p.z - zMin) / (double)(zMax - zMin) * (double)(nparams.Max - nparams.Min);
//         p.z = normZ;
//         v = Vertex(p);
//     }
//
//     // Construct Edges
//     vector<Edge> edges;
//     for (int i = 0; i < vertices.size(); ++i)
//     {
//         if (( i + 1 < vertices.size() ) && ( (i+1) % size != 0 ))
//             edges.push_back(Edge(vertices[i], vertices[i+1]));
//
//         if(i + size < vertices.size())
//             edges.push_back(Edge(vertices[i], vertices[i + size]));
//     }
//
//     Figure figure(std::move(vertices), std::move(edges));
//     vector figures{figure};
//     Scene scene{std::move(figures), std::move(nparams)};
//     return scene;
// }

std::ifstream CsvFileReader::_openValidFile(std::string path)
{
    using namespace std;
    if (path.empty())
        throw std::invalid_argument("Path cannot be empty");

    fs::path fspath(path);
    if (fspath.extension() != CSVFILEFORMAT)
        throw std::invalid_argument("File must be a CSV");

    ifstream f(fspath);
    if (!f.is_open())
        throw std::invalid_argument("Cannot open file");

    if (f.eof() || f.peek() == EOF)
        throw std::invalid_argument("File is empty");

    return f;
}