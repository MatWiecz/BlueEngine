//
// Created by Mateusz on 2019-10-07.
//

#include "Calculations.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        Point operator&(const Plane &plane,
                        const StraightLine &straightLine)
        {
            auto pM = plane.GetGeneralFormMatrix();
            auto lM = straightLine.GetParametricFormMatrix();
            float numerator = -pM(0, 0) * lM(0, 0)
                               - pM(0, 1) * lM(1, 0)
                               - pM(0, 2) * lM(2, 0)
                               - pM(0, 3);
            float denominator = pM(0, 0) * lM(0, 1)
                                 + pM(0, 1) * lM(1, 1)
                                 + pM(0, 2) * lM(2, 1);
            float inf = 1.0f / 0.0f;
            if (denominator == 0.0)
            {
                if (numerator == 0.0)
                    return Point(+inf, +inf, +inf);
                else
                    return Point(-inf, -inf, -inf);
            }
            float t = numerator / denominator;
            return Point(lM(0, 0)+lM(0, 1)*t,
                         lM(1, 0)+lM(1, 1)*t,
                         lM(2, 0)+lM(2, 1)*t);
            
        }
    }
}