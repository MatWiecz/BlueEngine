//
// Created by Mateusz on 2019-09-29.
//

#ifndef BLUEENGINE_COLOURS_H
#define BLUEENGINE_COLOURS_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef class ColorClass Color;
        typedef class RGBColorClass RGBColor;
        typedef class GrayColorClass GrayColor;
    }
}

namespace MatWiecz
{
    namespace BlueEngine
    {
        class ColorClass
        {
            protected:
            float * floatData;
            
            public:
            ColorClass();
            ~ColorClass();
    
            operator float *();
            
            virtual float r() const = 0;
            virtual float g() const = 0;
            virtual float b() const = 0;
        };
        
        class RGBColorClass : public Color
        {
            private:
            unsigned char color[3];
            
            public:
            RGBColorClass();
            RGBColorClass(unsigned char red,
                          unsigned char green,
                          unsigned char blue);
            
            float r() const override;
            float g() const override;
            float b() const override;
            
            operator GrayColor() const;
        };
        
        class GrayColorClass : public Color
        {
            private:
            unsigned char color[1];
            
            public:
            GrayColorClass();
            GrayColorClass(unsigned char brightness);
    
            float r() const override;
            float g() const override;
            float b() const override;
            
            operator RGBColor() const;
            operator unsigned char() const;
        };
    }
}

#endif //BLUEENGINE_COLOURS_H
