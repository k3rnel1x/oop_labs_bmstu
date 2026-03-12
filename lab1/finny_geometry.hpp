//
// Created by k3rnel1x on 10.03.2026.
//

#ifndef FINNY_GEOMETRY_H
#define FINNY_GEOMETRY_H
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

#define EPS 1e-6

// TODO get_perimeters in all figures
typedef struct Vector2 {
    double x;
    double y;
} Vector2;

class Figure {
public:
    Figure(std::string name)
    {
        if (name.empty())
            throw std::invalid_argument("Name must be non-emply.");

        _name = name;
    }

    std::string get_name()
    {
        return _name;
    }

    virtual double get_perimeter() = 0;

protected:
    bool _is_equal(double a, double b) { return fabs(a - b) < EPS; }
    bool _is_equal(Vector2 a, Vector2 b) { return (fabs(a.x - b.x) < EPS) && (fabs(a.y - b.y) < EPS); }
private:
    std::string _name;
};

class Circle : public  Figure {
public:
    Circle(std::string name, Vector2 center, double radius) :
    Figure(name),
    _center(center)
    {
        if (radius <= 0)
            throw std::invalid_argument("Radius must be great(more) than 0.");
        _radius = radius;
    }

private:
    Vector2 _center;
    double  _radius;
};

class Rectangle : public  Figure {
public:
    Rectangle(std::string name, Vector2 left, Vector2 right) :
    Figure(name)
    {
        if ( _is_equal(left.x, right.x) || _is_equal(left.y, right.y) )
            throw std::invalid_argument("Corners must be not a same point.");
        _left_corner  = left;
        _right_corner = right;
    }

private:
    Vector2 _left_corner;
    Vector2 _right_corner;
};

class Triangle : public  Figure {
public:
    Triangle(std::string name, Vector2 a, Vector2 b, Vector2 c) :
    Figure(name)
    {
        if ( !(_is_equal(a.x, b.x) && _is_equal(b.x, c.x)) )
        {
            if ( !(_is_equal(a.y, b.y) && _is_equal(b.y, c.y)) )
            {
                _a = a;
                _b = b;
                _c = c;
                return;
            }
        }
        throw std::invalid_argument("Corners must be not a same line.");
    }

private:
    Vector2 _a;
    Vector2 _b;
    Vector2 _c;
};

class PolyAngle : public  Figure {
public:
    PolyAngle(std::string name, std::vector<Vector2> dots) :
    Figure(name)
    {
        if (0 <= dots.size() && dots.size() <= 2)
            throw std::invalid_argument("Not enough points to create a polyangle.");

        bool flat_x = true;
        bool flat_y = true;
        Vector2 v_curr = dots[0];
        Vector2 v_next;
        for (int i = 1; i < dots.size(); i++)
        {
            v_next = dots[i];
            flat_x = flat_x && (v_curr.x == v_next.x);
            flat_y = flat_y && (v_curr.y == v_next.y);
            v_curr = v_next;
        }

        if (flat_x || flat_y)
            throw std::invalid_argument("Flat polyangle.");

        _dots = dots;
    }

private:
    std::vector<Vector2> _dots;
};

#endif //FINNY_GEOMETRY_H
