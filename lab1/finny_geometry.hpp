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
#define PI 3.1415926
#define HYPOTINUSE(a, b) sqrt((a)*(a) + (b)*(b))

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
    double _perimeter = -1.0;
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
    
    double get_perimeter()
    {
        if (_perimeter != -1.0)
            return _perimeter;

        double perimeter = 2.0 * PI * _radius;

        _perimeter = perimeter;
        return perimeter;
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

    double get_perimeter()
    {
        if (_perimeter != -1.0)
            return _perimeter;

        double a = fabs(_left_corner.x - _right_corner.x);
        double b = fabs(_left_corner.y - _right_corner.y);
        double perimeter = 2.0 * (a + b);

        _perimeter = perimeter;
        return perimeter;
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

    double get_perimeter()
    {
        if (_perimeter != -1.0)
            return _perimeter;

        double a = HYPOTINUSE(fabs(_a.x - _b.x), fabs(_a.y - _b.y));
        double b = HYPOTINUSE(fabs(_b.x - _c.x), fabs(_b.y - _c.y));
        double c = HYPOTINUSE(fabs(_c.x - _a.x), fabs(_c.y - _a.y));
        double perimeter = a + b + c;

        _perimeter = perimeter;
        return perimeter;
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

        // Checks it flat
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
    double relative_orintation(Vector2 a, Vector2 b, Vector2 c)
    {
        return (b.x-a.x)*(c.y-b.y) - (b.y-a.y)*(c.x-b.x);
    }

    std::vector<Vector2> get_wrapping_path(std::vector<Vector2>& points)
    {
        int l = 0;
        for (int i = 1; i < points.size(); i++)
            l = HYPOTINUSE(points[l].x, points[l].y) < HYPOTINUSE(points[i].x, points[i].y)? l : i;

        std::vector<Vector2> way;
        int p = l, q;
        do {
            way.push_back(points[p]);
            q = ( p + 1 < points.size() )? p + 1 : 0;

            for (int i = 0; i < points.size(); i++) {
                if (relative_orintation(points[p], points[i], points[q]) < 0)
                    q = i;
            }

            p = q;
        } while (p != l);
        return way;
    }

    double get_perimeter()
    {
        if (_perimeter != -1.0)
            return _perimeter;

        std::vector<Vector2> w_path = get_wrapping_path(_dots);
        // std::cout << std::endl;
        // for (auto v: w_path)
        // {
        //     std::cout << v.x << ' ' << v.y << std::endl;
        // }

        double perimeter = 0;
        for (int i = 0; i < w_path.size() - 1; i++)
        {
            double a = fabs(w_path[i].x - w_path[i+1].x);
            double b = fabs(w_path[i].y - w_path[i+1].y);
            perimeter += HYPOTINUSE(a, b);
        }
        _perimeter = perimeter;
        return perimeter;
    }

private:
    std::vector<Vector2> _dots;

};

#endif //FINNY_GEOMETRY_H
