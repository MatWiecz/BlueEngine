//
// Created by Mateusz on 2019-10-02.
//

#include "Plane.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        PlaneClass::PlaneClass(): mainPoint(0.0, 0.0, 0.0),
                                  normalVector(0.0, 0.0, 1.0)
        {
        }
    
        PlaneClass::PlaneClass(const Point &aPoint, const Point &bPoint,
                               const Point &cPoint)
        {
            mainPoint = aPoint;
            Vector aVector(aPoint, bPoint);
            Vector bVector(aPoint, cPoint);
            normalVector = aVector.VectorProduct(bVector);
            normalVector.Normalize();
        }
    
        PlaneClass::PlaneClass(const Point &planeMainPoint,
                               const Vector &planeNormalVector):
        mainPoint(planeMainPoint),
        normalVector(planeNormalVector)
        {
            normalVector.Normalize();
        }
    
        PlaneClass::PlaneClass(const Point &planePoint, const Vector &aVector,
                               const Vector &bVector):
        mainPoint(planePoint),
        normalVector(aVector.VectorProduct(bVector))
        {
            normalVector.Normalize();
        }
    
        Point PlaneClass::MainPoint() const
        {
            return mainPoint;
        }
    
        Vector PlaneClass::NormalVector() const
        {
            return normalVector;
        }
    
        Plane& PlaneClass::TransNormal(double delta)
        {
            mainPoint.TransVector(delta*normalVector);
            return *this;
        }
    
        Plane& PlaneClass::TransX(double delta)
        {
            mainPoint.TransX(delta);
            return *this;
        }
    
        Plane& PlaneClass::TransY(double delta)
        {
            mainPoint.TransY(delta);
            return *this;
        }
    
        Plane& PlaneClass::TransZ(double delta)
        {
            mainPoint.TransZ(delta);
            return *this;
        }
    
        Plane& PlaneClass::RotVector(const Point & point,
                                     const Vector &vector,
                                     double angle)
        {
            mainPoint.RotVector(point, vector, angle);
            normalVector.RotVector(vector, angle);
            return *this;
        }
    }
}
