//
// Created by Mateusz on 2019-10-08.
//

#ifndef BLUEENGINE_TRIANGLESSEQUENCE_H
#define BLUEENGINE_TRIANGLESSEQUENCE_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef class TrianglesSequenceClass TrianglesSequence;
    }
}

#include "../../Basics/BitField.hpp"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct TrianglesSequenceDrawModeStruct {};
        typedef BitField <TrianglesSequenceDrawModeStruct>
            TrianglesSequenceDrawMode;
        const TrianglesSequenceDrawMode TrianglesStrip(BitFieldSymbols::Reset);
        const TrianglesSequenceDrawMode TrianglesFan;
        class TrianglesSequenceClass
        {
            protected:
            
            
        };
    }
}

#endif //BLUEENGINE_TRIANGLE_H
