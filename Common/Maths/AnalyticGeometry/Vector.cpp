//
// Created by Mateusz on 2019-10-02.
//

#include <cmath>
#include "Vector.h"
#include "Common.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        void VectorClass::Init(float *data)
        {
            if (data != nullptr && data != UseObjectData)
            {
                components = data;
                outerData = true;
            }
            else
            {
                components = new float[3];
                outerData = false;
            }
        }
        
        VectorClass::VectorClass(float *data)
        {
            Init(data);
            if (!outerData)
            {
                components[0] = components[2] = 0.0f;
                components[1] = 1.0f;
            }
        }
        
        VectorClass::VectorClass(float aComp, float bComp, float cComp,
                                 float *data)
        {
            Init(data);
            components[0] = aComp;
            components[1] = bComp;
            components[2] = cComp;
        }
        
        VectorClass::VectorClass(const Point &aPoint, const Point &bPoint,
                                 float *data)
        {
            Init(data);
            components[0] = bPoint.X() - aPoint.X();
            components[1] = bPoint.Y() - aPoint.Y();
            components[2] = bPoint.Z() - aPoint.Z();
        }
        
        VectorClass::VectorClass(const VectorClass &vector)
        {
            Init(nullptr);
            components[0] = vector.A();
            components[1] = vector.B();
            components[2] = vector.C();
        }
        
        VectorClass::VectorClass(const VectorClass &vector, float *data)
        {
            Init(data);
            components[0] = vector.A();
            components[1] = vector.B();
            components[2] = vector.C();
        }
        
        VectorClass::~VectorClass()
        {
            if (!outerData)
                delete[] components;
        }
        
        VectorClass &VectorClass::operator=(const VectorClass &vector)
        {
            if (this != &vector)
            {
                components[0] = vector.A();
                components[1] = vector.B();
                components[2] = vector.C();
            }
            return *this;
        }
        
        float *VectorClass::GetData() const
        {
            return components;
        }
        
        float VectorClass::A() const
        {
            return components[0];
        }
        
        float VectorClass::B() const
        {
            return components[1];
        }
        
        float VectorClass::C() const
        {
            return components[2];
        }
        
        Vector VectorClass::VectorProduct(const Vector &vector) const
        {
            return Vector(B() * vector.C() - C() * vector.B(),
                          A() * vector.C() - C() * vector.A(),
                          A() * vector.B() - B() * vector.A());
        }
        
        float VectorClass::ScalarProduct(const Vector &vector) const
        {
            return A() * vector.A() + B() * vector.B() + C() * vector.C();
        }
        
        Vector &VectorClass::IncreaseA(float delta)
        {
            components[0] += delta;
            return *this;
        }
        
        Vector &VectorClass::IncreaseB(float delta)
        {
            components[1] += delta;
            return *this;
        }
        
        Vector &VectorClass::IncreaseC(float delta)
        {
            components[2] += delta;
            return *this;
        }
        
        float VectorClass::VectorNorm() const
        {
            return float(sqrt(A() * A() + B() * B() + C() * C()));
        }
        
        Vector &VectorClass::Normalize()
        {
            float vectorNorm = VectorNorm();
            if (vectorNorm == 0.0f)
                return *this;
            components[0] /= vectorNorm;
            components[1] /= vectorNorm;
            components[2] /= vectorNorm;
            return *this;
        }
        
        Vector &VectorClass::ScaleX(float factor)
        {
            components[0] *= factor;
            return *this;
        }
        
        Vector &VectorClass::ScaleY(float factor)
        {
            components[1] *= factor;
            return *this;
        }
        
        Vector &VectorClass::ScaleZ(float factor)
        {
            components[2] *= factor;
            return *this;
        }
        
        Vector &VectorClass::RotX(float angle)
        {
            float oldY = components[1];
            float oldZ = components[2];
            components[1] = float(oldY * cos(angle) - oldZ * sin(angle));
            components[2] = float(oldY * sin(angle) + oldZ * cos(angle));
            return *this;
        }
        
        Vector &VectorClass::RotY(float angle)
        {
            float oldX = components[0];
            float oldZ = components[2];
            components[0] = float(oldX * cos(angle) + oldZ * sin(angle));
            components[2] = float(-oldX * sin(angle) + oldZ * cos(angle));
            return *this;
        }
        
        Vector &VectorClass::RotZ(float angle)
        {
            float oldX = components[0];
            float oldY = components[1];
            components[0] = float(oldX * cos(angle) - oldY * sin(angle));
            components[2] = float(oldX * sin(angle) + oldY * cos(angle));
            return *this;
        }
        
        Vector &VectorClass::RotVector(const Vector &vector, float angle)
        {
            Point vectorEnd(A(), B(), C());
            vectorEnd.RotVector(Point(), vector, angle);
            components[0] = vectorEnd.X();
            components[1] = vectorEnd.Y();
            components[2] = vectorEnd.Z();
            return *this;
        }
        
        const Vector operator+(const Vector &aVector,
                               const Vector &bVector)
        {
            return Vector(aVector.A() + bVector.A(),
                          aVector.B() + bVector.B(),
                          aVector.C() + bVector.C());
        }
        
        const Vector operator-(const Vector &aVector,
                               const Vector &bVector)
        {
            return Vector(aVector.A() - bVector.A(),
                          aVector.B() - bVector.B(),
                          aVector.C() - bVector.C());
        }
        
        const Vector operator-(const Vector &vector)
        {
            return Vector(-vector.A(), -vector.B(), -vector.C());
        }
        
        const Vector operator*(const Vector &vector, float factor)
        {
            return Vector(factor * vector.A(),
                          factor * vector.B(),
                          factor * vector.C());
        }
        
        const Vector operator*(float factor, const Vector &vector)
        {
            return vector * factor;
        }
        
        const Vector operator&(const Vector &aVector,
                               const Vector &bVector)
        {
            return Vector(aVector.VectorProduct(bVector));
        }
        
        float operator*(const Vector &aVector,
                        const Vector &bVector)
        {
            return aVector.ScalarProduct(bVector);
        }
    }
}