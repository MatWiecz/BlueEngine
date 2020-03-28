//
// Created by Mateusz on 2019-10-02.
//

#include "Plane.h"
#include "Common.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        PlaneClass::PlaneClass(): mainPoint(0.0f, 0.0f, 0.0f),
                                  normalVector(0.0f, 1.0f, 0.0f)
        {
        }
        
        PlaneClass::PlaneClass(const Point &aPoint, const Point &bPoint,
                               const Point &cPoint):
            mainPoint(aPoint)
        {
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
        
        PlaneClass::PlaneClass(const PlaneClass &plane):
            mainPoint(plane.mainPoint),
            normalVector(plane.normalVector)
        {
        }
        
        PlaneClass::PlaneClass(float *pointData, float *vectorData):
            mainPoint(pointData),
            normalVector(vectorData)
        {
            normalVector.Normalize();
        }
        
        PlaneClass::PlaneClass(const Point &aPoint,
                               const Point &bPoint,
                               const Point &cPoint,
                               float *pointData, float *vectorData):
            mainPoint(aPoint, pointData),
            normalVector(vectorData)
        {
            Vector aVector(aPoint, bPoint);
            Vector bVector(aPoint, cPoint);
            normalVector = aVector.VectorProduct(bVector);
            normalVector.Normalize();
        }
        
        PlaneClass::PlaneClass(
            const Point &planeMainPoint,
            const Vector &planeNormalVector,
            float *pointData, float *vectorData):
            mainPoint(planeMainPoint, (pointData == UseObjectData)
                                      ? planeMainPoint.GetData()
                                      : pointData),
            normalVector(planeNormalVector, (vectorData == UseObjectData)
                                            ? planeNormalVector.GetData()
                                            : vectorData)
        {
            normalVector.Normalize();
        }
        
        PlaneClass::PlaneClass(const Point &planePoint,
                               const Vector &aVector,
                               const Vector &bVector,
                               float *pointData, float *vectorData):
            mainPoint(planePoint, (pointData == UseObjectData)
                                  ? planePoint.GetData()
                                  : pointData),
            normalVector(aVector.VectorProduct(bVector), vectorData)
        {
            normalVector.Normalize();
        }
        
        PlaneClass::PlaneClass(const PlaneClass &plane, float *pointData,
                               float *vectorData):
            mainPoint(plane.mainPoint, (pointData == UseObjectData)
                                       ? plane.mainPoint.GetData()
                                       : pointData),
            normalVector(plane.normalVector, (vectorData == UseObjectData)
                                             ? plane.normalVector.GetData()
                                             : vectorData)
        {
        }
        
        PlaneClass &PlaneClass::operator=(const PlaneClass &plane)
        {
            if (this != &plane)
            {
                mainPoint = plane.mainPoint;
                normalVector = plane.normalVector;
            }
            return *this;
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
            return Matrix <float, 1, 4>(MatrixOptions(0), tempData);
        }
    
        PlaneClass::operator std::string() const
        {
            return std::string("Plane{")
                   + std::string(mainPoint) + ";"
                   + std::string(normalVector) + "}";
        }
    }
}
