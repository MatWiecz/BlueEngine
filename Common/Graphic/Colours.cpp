//
// Created by Mateusz on 2019-09-29.
//

#include "Colours.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        ColorClass::ColorClass(): floatData(nullptr)
        {
        }
    
        ColorClass::~ColorClass()
        {
            if(floatData != nullptr)
                delete [] floatData;
        }
    
        ColorClass::operator float *()
        {
            if(floatData == nullptr)
            {
                floatData = new float[3];
                floatData[0] = r();
                floatData[1] = g();
                floatData[2] = b();
            }
            return floatData;
        }
        
        RGBColorClass::RGBColorClass(): color({0})
        {
        }
    
        RGBColorClass::RGBColorClass(unsigned char red, unsigned char green,
                                     unsigned char blue): color({red, green,
                                                                 blue})
        {
        }
    
        float RGBColorClass::r() const
        {
            return color[0]/255.0f;
        }
    
        float RGBColorClass::g() const
        {
            return color[1]/255.0f;
        }
    
        float RGBColorClass::b() const
        {
            return color[2]/255.0f;
        }
    
        RGBColorClass::operator GrayColor() const
        {
            return GrayColor((unsigned char)(255.0f * (r() * 0.299f +
                g() * 0.587f + b() * 0.114f)));
        }
    
        GrayColorClass::GrayColorClass(): color({0})
        {
        }
    
        GrayColorClass::GrayColorClass(unsigned char brightness):
            color({brightness})
        {
        }
    
        float GrayColorClass::r() const
        {
            return color[0]/255.0f;
        }
    
        float GrayColorClass::g() const
        {
            return color[0]/255.0f;
        }
    
        float GrayColorClass::b() const
        {
            return color[0]/255.0f;
        }
    
        GrayColorClass::operator RGBColor() const
        {
            return RGBColor(color[0], color[0], color[0]);
        }
    
        GrayColorClass::operator unsigned char() const
        {
            return color[0];
        }
    }
}