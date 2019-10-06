//
// Created by Mateusz on 2019-10-02.
//

#include <cmath>
#include "Vector.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        VectorClass::VectorClass(): components({0.0})
        {
        }
        
        VectorClass::VectorClass(double aComp, double bComp, double cComp):
            components({aComp, bComp, cComp})
        {
        }
        
        VectorClass::VectorClass(const Point &aPoint, const Point &bPoint):
            components({bPoint.X() - aPoint.X(),
                        bPoint.Y() - aPoint.Y(),
                        bPoint.Z() - aPoint.Z()})
        {
        }
        
        double VectorClass::A() const
        {
            return components[0];
        }
        
        double VectorClass::B() const
        {
            return components[1];
        }
        
        double VectorClass::C() const
        {
            return components[2];
        }
        
        Vector VectorClass::VectorProduct(const Vector &vector) const
        {
            return Vector(B() * vector.C() - C() * vector.B(),
                          A() * vector.C() - C() * vector.A(),
                          A() * vector.B() - B() * vector.A());
        }
        
        double VectorClass::ScalarProduct(const Vector &vector) const
        {
            return A()*vector.A()+B()*vector.B()+C()*vector.C();
        }
        
        Vector &VectorClass::IncreaseA(double delta)
        {
            components[0] += delta;
            return *this;
        }
        
        Vector &VectorClass::IncreaseB(double delta)
        {
            components[1] += delta;
            return *this;
        }
        
        Vector &VectorClass::IncreaseC(double delta)
        {
            components[2] += delta;
            return *this;
        }
        
        double VectorClass::VectorNorm() const
        {
            return sqrt(A() * A() + B() * B() + C() * C());
        }
        
        Vector &VectorClass::Normalize()
        {
            double vectorNorm = VectorNorm();
            Vector normalizedVector = *this;
            if (vectorNorm == 0.0)
                return normalizedVector;
            normalizedVector.components[0] /= vectorNorm;
            normalizedVector.components[1] /= vectorNorm;
            normalizedVector.components[2] /= vectorNorm;
            return normalizedVector;
        }
        
        Vector &VectorClass::ScaleX(double factor)
        {
            components[0] *= factor;
            return *this;
        }
        
        Vector &VectorClass::ScaleY(double factor)
        {
            components[1] *= factor;
            return *this;
        }
        
        Vector &VectorClass::ScaleZ(double factor)
        {
            components[2] *= factor;
            return *this;
        }
        
        Vector &VectorClass::RotX(double angle)
        {
            double oldY = components[1];
            double oldZ = components[2];
            components[1] = oldY * cos(angle) - oldZ * sin(angle);
            components[2] = oldY * sin(angle) + oldZ * cos(angle);
            return *this;
        }
        
        Vector &VectorClass::RotY(double angle)
        {
            double oldX = components[0];
            double oldZ = components[2];
            components[0] = oldX * cos(angle) + oldZ * sin(angle);
            components[2] = -oldX * sin(angle) + oldZ * cos(angle);
            return *this;
        }
        
        Vector &VectorClass::RotZ(double angle)
        {
            double oldX = components[0];
            double oldY = components[1];
            components[0] = oldX * cos(angle) - oldY * sin(angle);
            components[2] = oldX * sin(angle) + oldY * cos(angle);
            return *this;
        }
        
        Vector &VectorClass::RotVector(const Vector &vector, double angle)
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
    
        const Vector operator*(const Vector &vector, double factor)
        {
            return Vector(factor*vector.A(),
                          factor*vector.B(),
                          factor*vector.C());
        }
    
        const Vector operator*(double factor, const Vector &vector)
        {
            return vector*factor;
        }
    
        const Vector operator&(const Vector &aVector,
                               const Vector &bVector)
        {
            return Vector(aVector.VectorProduct(bVector));
        }
    
        double operator*(const Vector &aVector,
                         const Vector &bVector)
        {
            return aVector.ScalarProduct(bVector);
        }
    }
}