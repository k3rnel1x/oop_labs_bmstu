//
// Created by k3rnel1x on 07.03.2026.
//

#ifndef ITEM_H
#define ITEM_H
#include "base/base.h"

class Item : public Base {
private:
protected:
public:
    Item(const std::string name);
    virtual void exec();
};

inline Item::Item(const std::string name) : Base(name)
{
}
#endif //ITEM_H
