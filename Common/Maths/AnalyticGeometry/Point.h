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
            double pos[3];
            
            public:
            PointClass();
            PointClass(double xPos, double yPos, double zPos);
            ~PointClass() = default;
            
            double X() const;
            double Y() const;
            double Z() const;
    
            double GetDistance (const Point & otherPoint) const;
            
            Point & TransX(double delta);
            Point & TransY(double delta);
            Point & TransZ(double delta);
            
            Point & TransVector(const Vector & vector);
            
            Point & RotVector(const Point & point,
                              const Vector & vector,
                              double angle);
        };
    }
}

#endif //BLUEENGINE_POINT_H
