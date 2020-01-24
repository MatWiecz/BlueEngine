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
        void PointClass::Init(float *data)
        {
            if (data != nullptr)
            {
                pos = data;
                outerData = true;
            }
            else
            {
                pos = new float[3];
                outerData = false;
            }
        }
        
        PointClass::PointClass(float *data)
        {
            Init(data);
            if (!outerData)
                pos[0] = pos[1] = pos[2] = 0.0f;
        }
        
        PointClass::PointClass(float xPos, float yPos, float zPos, float *data):
        {
            Init(data);
            pos[0] = xPos;
            pos[1] = yPos;
            pos[2] = zPos;
        }
        
        PointClass::~PointClass()
        {
            if (!outerData)
                delete[] pos;
        }
        
        float PointClass::X() const
        {
            return pos[0];
        }
        
        float PointClass::Y() const
        {
            return pos[1];
        }
        
        float PointClass::Z() const
        {
            return pos[2];
        }
        
        float PointClass::GetDistance(const Point &otherPoint) const
        {
            return float(sqrt(pow(otherPoint.X() - X(), 2.0) +
                              pow(otherPoint.Y() - Y(), 2.0) +
                              pow(otherPoint.Z() - Z(), 2.0)));
        }
        
        Point &PointClass::TransX(float delta)
        {
            pos[0] += delta;
            return *this;
        }
        
        Point &PointClass::TransY(float delta)
        {
            pos[1] += delta;
            return *this;
        }
        
        Point &PointClass::TransZ(float delta)
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
                                     float angle)
        {
            TransX(-point.X()).TransY(-point.Y()).TransZ(-point.Z());
            Vector nV = vector;
            nV.Normalize();
            float cosV = float(cos(angle));
            float sinV = float(sin(angle));
            float rotMatrixData[9]
                {float(cosV + nV.A() * nV.A() * (1.0 - cosV)),
                 float(nV.A() * nV.B() * (1.0 - cosV) - nV.C() * sinV),
                 float(nV.A() * nV.C() * (1.0 - cosV) + nV.B() * sinV),
                
                 float(nV.B() * nV.A() * (1.0 - cosV) + nV.C() * sinV),
                 float(cosV + nV.B() + nV.B() * (1.0 - cosV)),
                 float(nV.B() * nV.C() * (1.0 - cosV) - nV.A() * sinV),
                
                 float(nV.C() * nV.A() * (1.0 - cosV) - nV.B() * sinV),
                 float(nV.C() * nV.B() * (1.0 - cosV) + nV.A() * sinV),
                 float(cosV + nV.C() * nV.C() * (1.0 - cosV))
                };
            Matrix <float, 3, 3> rotMatrix(UseSourceArray, rotMatrixData);
            Matrix <float, 3, 1> posMatrix(UseSourceArray, pos);
            posMatrix = rotMatrix * posMatrix;
            TransX(point.X()).TransY(point.Y()).TransZ(point.Z());
            return *this;
        }
    }
}