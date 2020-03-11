//
// Created by Mateusz on 2019-10-02.
//

#ifndef BLUEENGINE_POINT_H
#define BLUEENGINE_POINT_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef class PointClass Point;
    }
}

#include "Vector.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        class PointClass
        {
            protected:
            float *pos;
            bool outerData;
            
            void Init(float * data);
            
            public:
            PointClass(float *data = nullptr);
            
            PointClass(float xPos, float yPos, float zPos,
                       float *data = nullptr);
            
            PointClass(const PointClass & point);
            
            PointClass(const PointClass & point, float *data);
            
            ~PointClass();
            
            PointClass &operator=(const PointClass & point);
            
            float X() const;
            
            float Y() const;
            
            float Z() const;
            
            float GetDistance(const Point &otherPoint) const;
            
            Point &TransX(float delta);
            
            Point &TransY(float delta);
            
            Point &TransZ(float delta);
            
            Point &TransVector(const Vector &vector);
            
            Point &RotVector(const Point &point,
                             const Vector &vector,
                             float angle);
        };
    }
}

#endif //BLUEENGINE_POINT_H
