//
// Created by k3rnel1x on 07.03.2026.
//

#ifndef BASE_H
#define BASE_H
#include <string>
#include <vector>

typedef struct AppContext {
    std::vector<Geometry*> geos;
}AppContext;

class Base {
private:
    std::string name;
protected:
    AppContext ctx;
    void clear();
public:
    Base(const std::string name);
    virtual ~Base();
    std::string getName() { return this->name; };
    virtual void exec() { };
};

inline void Base::clear()
{
    std::cout.clear();
}

inline Base::Base(const std::string name)
{
    this->name = name;
}

inline Base::~Base()
{
}

#endif //BASE_H
