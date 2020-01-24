//
// Created by Mateusz on 2019-10-02.
//

#include "Plane.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        PlaneClass::PlaneClass(): mainPoint(0.0f, 0.0f, 0.0f),
                                  normalVector(0.0f, 0.0f, 1.0f)
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
        
        Plane &PlaneClass::TransNormal(float delta)
        {
            mainPoint.TransVector(delta * normalVector);
            return *this;
        }
        
        Plane &PlaneClass::TransVector(const Vector &vector)
        {
            mainPoint.TransVector(vector);
            return *this;
        }
        
        Plane &PlaneClass::TransX(float delta)
        {
            mainPoint.TransX(delta);
            return *this;
        }
        
        Plane &PlaneClass::TransY(float delta)
        {
            mainPoint.TransY(delta);
            return *this;
        }
        
        Plane &PlaneClass::TransZ(float delta)
        {
            mainPoint.TransZ(delta);
            return *this;
        }
        
        Plane &PlaneClass::RotVector(const Point &point,
                                     const Vector &vector,
                                     float angle)
        {
            mainPoint.RotVector(point, vector, angle);
            normalVector.RotVector(vector, angle);
            return *this;
        }
        
        Matrix <float, 1, 4> PlaneClass::GetGeneralFormMatrix() const
        {
            Matrix <float, 1, 4> tempMatrix;
            float *tempData = (float *) tempMatrix;
            tempMatrix(0, 0) = normalVector.A();
            tempMatrix(0, 1) = normalVector.B();
            tempMatrix(0, 2) = normalVector.C();
            tempMatrix(0, 3) = -normalVector.A() * mainPoint.X()
                               - normalVector.B() * mainPoint.Y()
                               - normalVector.C() * mainPoint.Z();
            return Matrix<float, 1, 4>(MatrixOptions(0), tempData);
        }
    }
}
