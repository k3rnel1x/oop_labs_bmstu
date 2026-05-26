#include "FileReader.h"

namespace fs = std::filesystem;

Scene FileReader::ReadScene(std::string path, NormalizationParameters nparams)
{
    using namespace std;
    std::ifstream f = _openValidFile(path);

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

    vector<Edge> edges;
    int size = c;
    for (int i = 0; i < vertices.size(); ++i)
    {
        if (( i + 1 < vertices.size() ) && ( (i+1) % size != 0 ))
            edges.push_back(Edge(vertices[i], vertices[i+1]));

        if(i + size < vertices.size())
            edges.push_back(Edge(vertices[i], vertices[i + size]));
    }

    Figure figure(vertices, edges);
    vector figures{figure};
    Scene scene{figures};
    return scene;
}

std::ifstream FileReader::_openValidFile(std::string path)
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