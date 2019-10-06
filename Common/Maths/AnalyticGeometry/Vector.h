//
// Created by Mateusz on 2019-10-02.
//

#ifndef BLUEENGINE_VECTOR_H
#define BLUEENGINE_VECTOR_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef class VectorClass Vector;
    }
}

#include "Point.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        class VectorClass
        {
            protected:
            double components[3];
            
            public:
            VectorClass();
            
            VectorClass(double aComp, double bComp, double cComp);
            
            VectorClass(const Point &aPoint, const Point &bPoint);
            
            ~VectorClass() = default;
            
            double A() const;
            
            double B() const;
            
            double C() const;
            
            double VectorNorm() const;
            
            Vector &Normalize();
            
            Vector VectorProduct(const Vector &vector) const;
            
            double ScalarProduct(const Vector &vector) const;
            
            Vector &IncreaseA(double delta);
            
            Vector &IncreaseB(double delta);
            
            Vector &IncreaseC(double delta);
            
            Vector &ScaleX(double factor);
            
            Vector &ScaleY(double factor);
            
            Vector &ScaleZ(double factor);
            
            Vector &RotX(double angle);
            
            Vector &RotY(double angle);
            
            Vector &RotZ(double angle);
            
            Vector &RotVector(const Vector &vector, double angle);
        };
    
        const Vector operator+(const Vector &aVector,
                               const Vector &bVector);
    
        const Vector operator-(const Vector &aVector,
                               const Vector &bVector);
    
        const Vector operator-(const Vector &vector);
    
        const Vector operator*(const Vector &vector, double factor);
    
        const Vector operator*(double factor, const Vector &vector);
    
        const Vector operator&(const Vector &aVector,
                               const Vector &bVector);
    
        double operator*(const Vector &aVector,
                         const Vector &bVector);
    }
}

#endif //BLUEENGINE_VECTOR_H
