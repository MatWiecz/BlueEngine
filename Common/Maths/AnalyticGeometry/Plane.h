//
// Created by Mateusz on 2019-10-02.
//

#ifndef BLUEENGINE_PLANE_H
#define BLUEENGINE_PLANE_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef class PlaneClass Plane;
    }
}

#include "Vector.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        class PlaneClass
        {
            protected:
            Point mainPoint;
            Vector normalVector;
            
            public:
            PlaneClass();
            
            PlaneClass(const Point &aPoint,
                       const Point &bPoint,
                       const Point &cPoint);
            
            PlaneClass(const Point &planeMainPoint,
                       const Vector &planeNormalVector);
            
            PlaneClass(const Point &planePoint,
                       const Vector &aVector,
                       const Vector &bVector);
    
            Point MainPoint() const;
    
            Vector NormalVector() const;
            
            Plane & TransNormal(double delta);
            Plane & TransX(double delta);
            Plane & TransY(double delta);
            Plane & TransZ(double delta);
            
            Plane & RotVector(const Point & point,
                              const Vector & vector,
                              double angle);
        };
    };
}

#endif //BLUEENGINE_PLANE_H
