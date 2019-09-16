//
// Created by Mateusz on 2019-08-25.
//

#ifndef BLUEENGINE_BITFIELD_H
#define BLUEENGINE_BITFIELD_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef enum class BitFieldSymbolsEnum
        {
            Auto,
            Reset
        } BitFieldSymbols;
        
        template <typename T>
        class BitField
        {
            private:
            static const T *watermark;
            static int nextInitValue;
            int value;
            
            public:
            BitField(int initValue);
    
            BitField(BitFieldSymbols initValue = BitFieldSymbols::Auto);
            
            ~BitField() = default;
            
            explicit operator int() const;
            
            const BitField <T> operator&(
                const BitField <T> &other) const;
            
            const BitField <T> operator|(
                const BitField <T> &other) const;
            
            const BitField <T> operator^(
                const BitField <T> &other) const;
            
            const BitField <T> operator~() const;
            
            BitField <T> &operator=(const BitField <T> &other);
            
            BitField <T> &operator&=(const BitField <T> &other);
            
            BitField <T> &operator|=(const BitField <T> &other);
            
            BitField <T> &operator^=(const BitField <T> &other);
            
        };
        
        template <typename T>
        int BitField <T>::nextInitValue = 1;
        
        template <typename T>
        BitField <T>::BitField(int initValue)
        {
            value = initValue;
        }
    
        template <typename T>
        BitField <T>::BitField(BitFieldSymbols initValue)
        {
            switch (initValue)
            {
                case BitFieldSymbols::Auto:
                    value = nextInitValue;
                    nextInitValue <<= 1;
                    break;
                case BitFieldSymbols::Reset:
                    value = 1;
                    nextInitValue = 2;
                    break;
            }
        }
        
        template <typename T>
        BitField <T>::operator int() const
        {
            return value;
        }
        
        template <typename T>
        const BitField <T> BitField <T>::operator&(
            const BitField <T> &other) const
        {
            return BitField <T>(value & other.value);
        }
        
        template <typename T>
        const BitField <T> BitField <T>::operator|(
            const BitField <T> &other) const
        {
            return BitField <T>(value | other.value);
        }
        
        template <typename T>
        const BitField <T> BitField <T>::operator^(
            const BitField <T> &other) const
        {
            return BitField <T>(value ^ other.value);
        }
        
        template <typename T>
        const BitField <T> BitField <T>::operator~() const
        {
            return BitField <T>(~value);
        }
    
        template <typename T>
        BitField <T> &BitField <T>::operator=(
            const BitField <T> &other)
        {
            value = other.value;
            return *this;
        }
        
        template <typename T>
        BitField <T> &BitField <T>::operator&=(
            const BitField <T> &other)
        {
            value &= other.value;
            return *this;
        }
        
        template <typename T>
        BitField <T> &BitField <T>::operator|=(
            const BitField <T> &other)
        {
            value |= other.value;
            return *this;
        }
        
        template <typename T>
        BitField <T> &BitField <T>::operator^=(
            const BitField <T> &other)
        {
            value ^= other.value;
            return *this;
        }
    }
}

#endif //BLUEENGINE_BITFIELD_H
