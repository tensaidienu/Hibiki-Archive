#ifndef __GameObject_h__
#define __GameObject_h__

#include <iostream>

#include "../LoaderParams.h"

class GameObject {
    protected:
        GameObject() {}
        virtual ~GameObject() {}
    public:
        virtual void load(const LoaderParams* params) = 0;
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void clean() = 0;        
};

#endif