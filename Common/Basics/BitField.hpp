//
// Created by Mateusz on 2019-08-25.
//

#ifndef BLUEENGINE_BITFIELD_H
#define BLUEENGINE_BITFIELD_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        template <typename T>
        class BitField
        {
            private:
            static const T *watermark;
            static int nextInitValue;
            int value;
            
            public:
            BitField(int initValue = -1);
            
            ~BitField() = default;
            
            explicit operator int() const;
            
            const BitField <T> operator&(
                const BitField <T> & other) const;
            
            const BitField <T> operator|(
                const BitField <T> & other) const;
            
            const BitField <T> operator^(
                const BitField <T> & other) const;
            
            const BitField <T> operator~() const;
            
            BitField <T> & operator&=(const BitField <T> & other);
            
            BitField <T> & operator|=(const BitField <T> & other);
            
            BitField <T> & operator^=(const BitField <T> & other);
            
        };
    
        template <typename T>
        int BitField<T>::nextInitValue = 1;
    
        template <typename T>
        BitField<T>::BitField(int initValue)
        {
            if(initValue == -1)
            {
                value = nextInitValue;
                nextInitValue <<= 1;
            }
            else
                value = initValue;
        }
    
        template <typename T>
        BitField<T>::operator int() const
        {
            return value;
        }
    
        template <typename T>
        const BitField <T> BitField<T>::operator&(
            const BitField <T> &other) const
        {
            return BitField <T>(value & other.value);
        }
    
        template <typename T>
        const BitField <T> BitField<T>::operator|(
            const BitField <T> &other) const
        {
            return BitField <T>(value | other.value);
        }
    
        template <typename T>
        const BitField <T> BitField<T>::operator^(
            const BitField <T> & other) const
        {
            return BitField <T>(value ^ other.value);
        }
    
        template <typename T>
        const BitField <T> BitField<T>::operator~() const
        {
            return BitField <T>(~value);
        }
    
        template <typename T>
        BitField <T> & BitField<T>::operator&=(
            const BitField <T> & other)
        {
            value &= other.value;
            return *this;
        }
    
        template <typename T>
        BitField <T> & BitField<T>::operator|=(
            const BitField <T> & other)
        {
            value |= other.value;
            return *this;
        }
    
        template <typename T>
        BitField <T> & BitField<T>::operator^=(
            const BitField <T> & other)
        {
            value ^= other.value;
            return *this;
        }
    }
}

#endif //BLUEENGINE_BITFIELD_H
