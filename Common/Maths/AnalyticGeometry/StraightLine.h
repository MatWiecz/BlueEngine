//
// Created by Mateusz on 2019-10-07.
//

#ifndef BLUEENGINE_STRAIGHTLINE_H
#define BLUEENGINE_STRAIGHTLINE_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef class StraightLineClass StraightLine;
    }
}

#include "Point.h"
#include "Vector.h"
#include "../Matrices/Matrix.hpp"

namespace MatWiecz
{
    namespace BlueEngine
    {
        class StraightLineClass
        {
            protected:
            Point mainPoint;
            Vector directionVector;
            
            public:
            StraightLineClass();
            
            StraightLineClass(const Point &aPoint,
                              const Point &bPoint);
            
            StraightLineClass(const Point &linePoint,
                              const Vector &lineDirectionVector);
            
            Point MainPoint() const;
            
            Vector DirectionVector() const;
            
            StraightLine &TransVector(const Vector &vector);
            
            StraightLine &TransX(float delta);
            
            StraightLine &TransY(float delta);
            
            StraightLine &TransZ(float delta);
            
            StraightLine &RotVector(const Point &point,
                                    const Vector &vector,
                                    float angle);
            
            Matrix<float, 3, 2> GetParametricFormMatrix() const;
        };
    }
}


#endif //BLUEENGINE_STRAIGHTLINE_H
