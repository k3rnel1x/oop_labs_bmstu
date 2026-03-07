#include "geometry.hpp"
#include <stdexcept>


/// Geometry ///
/* Setters */
void Geometry::setName(const string str)
{
    if (!str.c_str())
        this->name = str;
}

/* Getters */
string Geometry::getName() { return  this->name; }

// ***********************************************************************************************
/// Rectangle ///

/* Setters */
void   Rectangle::setLCoord(double leftTopCoord)   { this->leftTopCoord   = leftTopCoord;   }
void   Rectangle::setRCoord(double rightBottCoord) { this->rightBottCoord = rightBottCoord; }

/* Getters */
double Rectangle::getLCoord() { return this->leftTopCoord;   }
double Rectangle::getRCoord() { return this->rightBottCoord; }

// ***********************************************************************************************
/// Triangle ///

/* Setters */
void Triangle::setACoord(double a) { this->aCoord = a; }
void Triangle::setBCoord(double b) { this->bCoord = b; }
void Triangle::setCCoord(double c) { this->cCoord = c; }

void Triangle::setAllCoords(double a, double b, double c)
{
    this->aCoord = a;
    this->bCoord = b;
    this->cCoord = c;
}
void Triangle::setAllCoords(array<int, 5> arr)
{
    this->aCoord = arr[0];
    this->bCoord = arr[1];
    this->cCoord = arr[2];
}

/* Getters */
double Triangle::getACoord() { return this->aCoord; }
double Triangle::getBCoord() { return this->bCoord; }
double Triangle::getCCoord() { return this->cCoord; }

// ***********************************************************************************************

/// ConvexPolygone ///
/* Setters */
void ConvexPolygone::setCoords(const vector<double> vec) { this->coords = vec; };

/* Getters */
vector<double> ConvexPolygone::getCoords() { return coords; }
