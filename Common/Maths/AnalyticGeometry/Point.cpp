//
// Created by Mateusz on 2019-10-02.
//

#include <cmath>
#include "Point.h"
#include "../Matrices/Matrix.hpp"

namespace MatWiecz
{
    namespace BlueEngine
    {
        PointClass::PointClass(): pos({0.0})
        {
        }
        
        PointClass::PointClass(double xPos, double yPos, double zPos):
            pos({xPos, yPos, zPos})
        {
        }
        
        double PointClass::X() const
        {
            return pos[0];
        }
        
        double PointClass::Y() const
        {
            return pos[1];
        }
        
        double PointClass::Z() const
        {
            return pos[2];
        }
        
        double PointClass::GetDistance(const Point &otherPoint) const
        {
            return sqrt(pow(otherPoint.X() - X(), 2.0) +
                        pow(otherPoint.Y() - Y(), 2.0) +
                        pow(otherPoint.Z() - Z(), 2.0));
        }
        
        Point &PointClass::TransX(double delta)
        {
            pos[0] += delta;
            return *this;
        }
        
        Point &PointClass::TransY(double delta)
        {
            pos[1] += delta;
            return *this;
        }
        
        Point &PointClass::TransZ(double delta)
        {
            pos[2] += delta;
            return *this;
        }
        
        Point &PointClass::TransVector(const Vector &vector)
        {
            pos[0] += vector.A();
            pos[1] += vector.B();
            pos[2] += vector.C();
            return *this;
        }
        
        Point &PointClass::RotVector(const Point &point,
                                     const Vector &vector,
                                     double angle)
        {
            TransX(-point.X()).TransY(-point.Y()).TransZ(-point.Z());
            Vector nV = vector;
            nV.Normalize();
            double cosV = cos(angle);
            double sinV = sin(angle);
            double rotMatrixData[9]
                {cosV + nV.A() * nV.A() * (1.0 - cosV),
                 nV.A() * nV.B() * (1.0 - cosV) - nV.C() * sinV,
                 nV.A() * nV.C() * (1.0 - cosV) + nV.B() * sinV,
                
                 nV.B() * nV.A() * (1.0 - cosV) + nV.C() * sinV,
                 cosV + nV.B() + nV.B() * (1.0 - cosV),
                 nV.B() * nV.C() * (1.0 - cosV) - nV.A() * sinV,
                
                 nV.C() * nV.A() * (1.0 - cosV) - nV.B() * sinV,
                 nV.C() * nV.B() * (1.0 - cosV) + nV.A() * sinV,
                 cosV + nV.C() * nV.C() * (1.0 - cosV)
                };
            Matrix <double, 3, 3> rotMatrix(UseSourceArray, rotMatrixData);
            Matrix <double, 3, 1> posMatrix(UseSourceArray, pos);
            posMatrix = rotMatrix * posMatrix;
            TransX(point.X()).TransY(point.Y()).TransZ(point.Z());
            return *this;
        }
    }
}