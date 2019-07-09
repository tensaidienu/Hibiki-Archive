#ifndef __Layer_h__
#define __Layer_h__

class Layer {
    public:
        virtual ~Layer() {}
        virtual void render() = 0;
        virtual void update() = 0;
};

#endif