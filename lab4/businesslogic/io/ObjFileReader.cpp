#include "ObjFileReader.h"
#include <sstream>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

Scene ObjFileReader::ReadScene(std::string path, NormalizationParameters nparams)
{
    using namespace std;
    std::ifstream f = _openValidFile(path);

    vector<Vertex> vertices;
    string line;
    while (!f.eof())
    {
        if (!getline(f, line))
            break;
        if (line[0] == 'v' && line[1] == ' ')
        {
            stringstream ss(line);
            string part;
            getline(ss, part, ' '); // skip v


            Point3D p;
            // Get X
            getline(ss, part, ' ');
            p.x = stoi(part);
            part.clear();

            // Get Y
            getline(ss, part, ' ');
            p.y = stoi(part);
            part.clear();

            // Get Z
            getline(ss, part, ' ');
            p.z = stoi(part);

            cout << p.x << " " << p.y << " " << p.z << endl;
            vertices.push_back(Vertex(p));
        }
    }

    f.seekg (0, ios::beg);
    while (!f.eof())
    {
        if (!getline(f, line))
            break;

        if (line[0] == 'f' && line[1] == ' ')
        {
            string part;
            stringstream ss(line);
            getline(ss, part, ' '); // skip f
            getline(ss, part, ' '); // get n/n/n

            auto v = _split(part, '/');

        }
    }

    f.close();

    vector<Edge> edges;

    Figure figure(std::move(vertices), std::move(edges));
    vector figures{figure};
    Scene scene{std::move(figures), std::move(nparams)};
    return scene;
}

std::ifstream ObjFileReader::_openValidFile(std::string path)
{
    using namespace std;
    if (path.empty())
        throw std::invalid_argument("Path cannot be empty");

    fs::path fspath(path);
    if (fspath.extension() != OBJFILEFORMAT)
        throw std::invalid_argument("File must be a CSV");

    ifstream f(fspath);
    if (!f.is_open())
        throw std::invalid_argument("Cannot open file");

    if (f.eof() || f.peek() == EOF)
        throw std::invalid_argument("File is empty");

    return f;
}

std::vector<std::string> ObjFileReader::_split(const std::string& s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}