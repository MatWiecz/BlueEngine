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

#include <string>
#include "Point.h"
#include "Vector.h"
#include "../Matrices/Matrix.hpp"

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
            
            PlaneClass(const PlaneClass &plane);
            
            PlaneClass(float *pointData,
                       float *vectorData);
            
            PlaneClass(const Point &aPoint,
                       const Point &bPoint,
                       const Point &cPoint,
                       float *pointData,
                       float *vectorData);
            
            PlaneClass(const Point &planeMainPoint,
                       const Vector &planeNormalVector,
                       float *pointData,
                       float *vectorData);
            
            PlaneClass(const Point &planePoint,
                       const Vector &aVector,
                       const Vector &bVector,
                       float *pointData,
                       float *vectorData);
            
            PlaneClass(const PlaneClass &plane,
                       float *pointData,
                       float *vectorData);
            
            PlaneClass &operator=(const PlaneClass &plane);
            
            Point MainPoint() const;
            
            Vector NormalVector() const;
            
            Plane &TransNormal(float delta);
            
            Plane &TransVector(const Vector &vector);
            
            Plane &TransX(float delta);
            
            Plane &TransY(float delta);
            
            Plane &TransZ(float delta);
            
            Plane &RotVector(const Point &point,
                             const Vector &vector,
                             float angle);
            
            Matrix <float, 1, 4> GetGeneralFormMatrix() const;
    
            operator std::string () const;
        };
    }
}

#endif //BLUEENGINE_PLANE_H
