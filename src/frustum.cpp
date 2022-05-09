// frustum.cpp

#include "frustum.h"
#include <cmath>
#define PI 3.141592653589793


void Frustum::setFrustum(double near, double far, double fov,
    double aspect, int hfov)
{
    this->near = near;
    this->far = far;

    double theta = fov / 2;

    if (hfov)
    {
        this->right = near * tan(theta * PI / 180);
        this->top = right / aspect;
    }
    else
    {
        this->top = near * tan(theta * PI / 180);
        this->right = top * aspect;
    }

    this->left = -right;
    this->bottom = -top;
}
