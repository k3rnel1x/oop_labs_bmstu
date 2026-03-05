// TODO create a classes for objects
#include <iostream>
#include <array>
#include <vector>
using std::string;
using std::array;
using std::vector;

class Geometry
{
private:
    string name;
public:
    /* Setters */
    void setName(const string str);

    /* Getters */
    string getName();
};

class Circle : Geometry
{
private:
    double center;
    double radius;
public:
    /* Setters */
    void   setCenter(double num) { this->center = num; }
    void   setRadius(double num) { this->radius = num; }

    /* Getters */
    double getCenter() { return  this->center; }
    double getRadius() { return  this->radius; }
};

class Rectangle : Geometry
{
private:
    double leftTopCoord;
    double rightBottCoord;
public:
    /* Setters */
    void   setLCoord(double leftTopCoord);
    void   setRCoord(double rightBottCoord);

    /* Getters */
    double getLCoord();
    double getRCoord();
};


class Triangle : Geometry
{
private:
    double aCoord, bCoord, cCoord;
public:
    /* Setters */
    void setACoord(double a);
    void setBCoord(double b);
    void setCCoord(double c);
    void setAllCoords(double a, double b, double c);
    void setAllCoords(array<int, 5> arr);

    /* Getters */
    double getACoord();
    double getBCoord();
    double getCCoord();
};

class ConvexPolygone : Geometry
{
private:
    vector<double> coords;
public:
    /* Setters */
    void setCoords(const vector<double> vec);

    /* Getters */
    vector<double> getCoords();
};

