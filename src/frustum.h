// frustum.h

#ifndef SRC_FRUSTUM_H_
#define SRC_FRUSTUM_H_


struct Frustum
{
    double near, far;
    double left, right, top, bottom;

    Frustum() = default;

    void setFrustum(double near, double far, double fov,
        double aspect = 1, int hfov = true);
};

#endif  // SRC_FRUSTUM_H_
