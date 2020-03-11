//
// Created by Mateusz on 2019-10-07.
//

#include "StraightLine.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        StraightLineClass::StraightLineClass(): mainPoint(0.0, 0.0, 0.0),
                                                directionVector(0.0, 1.0, 0.0)
        {
        }
        
        StraightLineClass::StraightLineClass(const Point &aPoint,
                                             const Point &bPoint):
            mainPoint(aPoint),
            directionVector(aPoint, bPoint)
        {
            directionVector.Normalize();
        }
        
        StraightLineClass::StraightLineClass(const Point &linePoint,
                                             const Vector &lineDirectionVector):
            mainPoint(linePoint),
            directionVector(lineDirectionVector)
        {
            directionVector.Normalize();
        }
        
        StraightLineClass::StraightLineClass(
            const StraightLineClass &straightLine):
            mainPoint(straightLine.mainPoint),
            directionVector(straightLine.directionVector)
        {
        }
        
        StraightLineClass::StraightLineClass(float *pointData,
                                             float *vectorData):
            mainPoint(pointData),
            directionVector(vectorData)
        {
            directionVector.Normalize();
        }
        
        StraightLineClass::StraightLineClass(const Point &aPoint,
                                             const Point &bPoint,
                                             float *pointData,
                                             float *vectorData):
            mainPoint(aPoint, pointData),
            directionVector(aPoint, bPoint, vectorData)
        {
            directionVector.Normalize();
        }
        
        StraightLineClass::StraightLineClass(const Point &linePoint,
                                             const Vector &lineDirectionVector,
                                             float *pointData,
                                             float *vectorData):
            mainPoint(linePoint, pointData),
            directionVector(lineDirectionVector, vectorData)
        {
            directionVector.Normalize();
        }
        
        StraightLineClass::StraightLineClass(
            const StraightLineClass &straightLine,
            float *pointData,
            float *vectorData):
            mainPoint(straightLine.mainPoint, pointData),
            directionVector(straightLine.directionVector, vectorData)
        {
        }
    
        StraightLineClass &StraightLineClass::operator=(
            const StraightLineClass &straightLine)
        {
            if(this != &straightLine)
            {
                mainPoint = straightLine.mainPoint;
                directionVector = straightLine.directionVector;
            }
            return *this;
        }
        
        Point StraightLineClass::MainPoint() const
        {
            return mainPoint;
        }
        
        Vector StraightLineClass::DirectionVector() const
        {
            return directionVector;
        }
        
        StraightLine &StraightLineClass::TransVector(const Vector &vector)
        {
            mainPoint.TransVector(vector);
            return *this;
        }
        
        StraightLine &StraightLineClass::TransX(float delta)
        {
            mainPoint.TransX(delta);
            return *this;
        }
        
        StraightLine &StraightLineClass::TransY(float delta)
        {
            mainPoint.TransY(delta);
            return *this;
        }
        
        StraightLine &StraightLineClass::TransZ(float delta)
        {
            mainPoint.TransZ(delta);
            return *this;
        }
        
        StraightLine &StraightLineClass::RotVector(const Point &point,
                                                   const Vector &vector,
                                                   float angle)
        {
            mainPoint.RotVector(point, vector, angle);
            directionVector.RotVector(vector, angle);
            return *this;
        }
        
        Matrix <float, 3, 2> StraightLineClass::GetParametricFormMatrix() const
        {
            Matrix <float, 3, 2> tempMatrix;
            float *tempData = (float *) tempMatrix;
            tempMatrix(0, 0) = mainPoint.X();
            tempMatrix(0, 1) = directionVector.A();
            tempMatrix(1, 0) = mainPoint.Y();
            tempMatrix(1, 1) = directionVector.B();
            tempMatrix(2, 0) = mainPoint.Z();
            tempMatrix(2, 1) = directionVector.C();
            return Matrix <float, 3, 2>(MatrixOptions(0), tempData);
        }
    }
}