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

#include <cmath>
#include <string>
#include "Point.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        class VectorClass
        {
            protected:
            float *components;
            bool outerData;
            
            void Init(float *data);
            
            public:
            VectorClass(float *data = nullptr);
            
            VectorClass(float aComp, float bComp, float cComp,
                        float *data = nullptr);
            
            VectorClass(const Point &aPoint, const Point &bPoint,
                        float *data = nullptr);
            
            VectorClass(const VectorClass &vector);
            
            VectorClass(const VectorClass &vector, float *data);
            
            ~VectorClass();
            
            VectorClass &operator=(const VectorClass &vector);
    
            float * GetData() const;
            
            float A() const;
            
            float B() const;
            
            float C() const;
            
            float VectorNorm() const;
            
            Vector &Normalize();
            
            Vector VectorProduct(const Vector &vector) const;
            
            float ScalarProduct(const Vector &vector) const;
            
            Vector &IncreaseA(float delta);
            
            Vector &IncreaseB(float delta);
            
            Vector &IncreaseC(float delta);
            
            Vector &ScaleX(float factor);
            
            Vector &ScaleY(float factor);
            
            Vector &ScaleZ(float factor);
            
            Vector &RotX(float angle);
            
            Vector &RotY(float angle);
            
            Vector &RotZ(float angle);
            
            Vector &RotVector(const Vector &vector, float angle);
    
            operator std::string () const;
        };
        
        const Vector operator+(const Vector &aVector,
                               const Vector &bVector);
        
        const Vector operator-(const Vector &aVector,
                               const Vector &bVector);
        
        const Vector operator-(const Vector &vector);
        
        const Vector operator*(const Vector &vector, float factor);
        
        const Vector operator*(float factor, const Vector &vector);
        
        const Vector operator&(const Vector &aVector,
                               const Vector &bVector);
        
        float operator*(const Vector &aVector,
                        const Vector &bVector);
    }
}

#endif //BLUEENGINE_VECTOR_H
