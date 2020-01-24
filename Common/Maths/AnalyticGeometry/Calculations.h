//
// Created by Mateusz on 2019-10-07.
//

#ifndef BLUEENGINE_CALCULATIONS_H
#define BLUEENGINE_CALCULATIONS_H

#include "Point.h"
#include "Vector.h"
#include "Plane.h"
#include "StraightLine.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        Point operator&(const Plane &plane,
                        const StraightLine &straightLine);
    }
}

#endif //BLUEENGINE_CALCULATIONS_H
