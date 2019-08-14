#ifndef __Vector2D_h__
#define __Vector2D_h__

#include <math.h>

class Vector2D {
    private:
        float x;
        float y;
    public:
        Vector2D(): x(0), y(0){}
        Vector2D(float x2, float y2): x(x2), y(y2) {}
        ~Vector2D(){}
        float getX() { return x; }
        float getY() { return y; }
        void setX(float x2) { x = x2; }
        void setY(float y2) { y = y2; }
        float length() { return sqrt(x * x + y * y); }

        void normalize() {
            float l = length();
            if ( l > 0) {// we never want to attempt to divide by 0
                (*this) *= 1 / l;
            }
        }

        Vector2D operator+(const Vector2D& v2) const {
            return Vector2D(x + v2.x, y + v2.y);
        }
        friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2) {
            v1.x += v2.x;
            v1.y += v2.y;
            return v1;
        }
        Vector2D operator*(float scalar) {
            return Vector2D(x * scalar, y * scalar);
        }
        Vector2D& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
        Vector2D operator-(const Vector2D& v2) const {
            return Vector2D(x - v2.x, y - v2.y);
        }
        friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2) {
            v1.x -= v2.x;
            v1.y -= v2.y;
            return v1;
        }
        Vector2D operator/(float scalar) {
            return Vector2D(x / scalar, y / scalar);
        }
        Vector2D& operator/=(float scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }
};

#endif