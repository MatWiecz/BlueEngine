//
// Created by Mateusz on 2019-10-01.
//

#ifndef BLUEENGINE_MATRIX_H
#define BLUEENGINE_MATRIX_H

#include <array>
#include "../Basics/BitField.hpp"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct MatrixOptionsStruct {};
        typedef BitField <MatrixOptionsStruct> MatrixOptions;
        const MatrixOptions UseSourceArray(BitFieldSymbols::Reset);
        const MatrixOptions ClearMatrix;
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        class Matrix
        {
            protected:
            dataType *data;
            MatrixOptions options;
            
            static dataType defaultValue;
            
            public:
            Matrix(
                MatrixOptions initOptions = MatrixOptions(0),
                dataType *sourceData = nullptr);
    
            ~Matrix();
            
            void SetMatrix(
                MatrixOptions newOptions, dataType *sourceData = nullptr);
            
            dataType &Elem(unsigned int row, unsigned int column);
            
            explicit operator dataType *() const;
            
        };
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        dataType Matrix <dataType, rows, columns>::defaultValue =
            (dataType) 0;
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        Matrix <dataType, rows, columns>::Matrix(
            MatrixOptions initOptions, dataType *sourceData): data(nullptr),
                                                              options(0)
        {
            SetMatrix(initOptions, sourceData);
        }
    
        template <typename dataType, unsigned int rows, unsigned int columns>
        Matrix <dataType, rows, columns>::~Matrix()
        {
            if (int(~options & UseSourceArray))
                delete[]data;
        }
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        void Matrix <dataType, rows, columns>::SetMatrix(
            MatrixOptions newOptions, dataType *sourceData)
        {
            if (data != nullptr && int(~options & UseSourceArray) &&
                int(newOptions & UseSourceArray))
            {
                delete[] data;
                data = nullptr;
            }
            if (int(newOptions & UseSourceArray) && sourceData != nullptr)
            {
                data = sourceData;
                options = UseSourceArray;
            }
            else
                if (data == nullptr || int(options & UseSourceArray))
                    data = new dataType[rows * columns];
            if (int(newOptions & ClearMatrix))
                std::fill(data, data + rows * columns, (dataType) 0);
            else
                if (int(~options & UseSourceArray) && sourceData != nullptr)
                    for (unsigned int i = 0; i < rows * columns; i++)
                        data[i] = sourceData[i];
        }
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        dataType &Matrix <dataType, rows, columns>::Elem(
            unsigned int row, unsigned int column)
        {
            if (row < rows & column < columns)
                return data[row * columns + column];
            return defaultValue;
        }
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        Matrix <dataType, rows, columns>::operator dataType *() const
        {
            return data;
        }
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        Matrix <dataType, rows, columns>
        operator+(const Matrix <dataType, rows, columns> &aMatrix,
                  const Matrix <dataType, rows, columns> &bMatrix)
        {
            Matrix <dataType, rows, columns> tempMatrix;
            dataType *aData = (dataType *) aMatrix;
            dataType *bData = (dataType *) bMatrix;
            dataType *tempData = (dataType *) tempMatrix;
            for (unsigned int i = 0; i < rows * columns; i++)
                tempData[i] = aData[i] + bData[i];
            return Matrix <dataType, rows, columns>(MatrixOptions(0), tempData);
        }
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        Matrix <dataType, rows, columns>
        operator-(const Matrix <dataType, rows, columns> &aMatrix,
                  const Matrix <dataType, rows, columns> &bMatrix)
        {
            Matrix <dataType, rows, columns> tempMatrix;
            dataType *aData = (dataType *) aMatrix;
            dataType *bData = (dataType *) bMatrix;
            dataType *tempData = (dataType *) tempMatrix;
            for (unsigned int i = 0; i < rows * columns; i++)
                tempData[i] = aData[i] - bData[i];
            return Matrix <dataType, rows, columns>(MatrixOptions(0), tempData);
        }
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        Matrix <dataType, rows, columns>
        operator-(const Matrix <dataType, rows, columns> &aMatrix)
        {
            Matrix <dataType, rows, columns> tempMatrix;
            dataType *aData = (dataType *) aMatrix;
            dataType *tempData = (dataType *) tempMatrix;
            for (unsigned int i = 0; i < rows * columns; i++)
                tempData[i] = -aData[i];
            return Matrix <dataType, rows, columns>(MatrixOptions(0), tempData);
        }
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        Matrix <dataType, rows, columns>
        operator*(dataType factor,
                  const Matrix <dataType, rows, columns> &aMatrix)
        {
            Matrix <dataType, rows, columns> tempMatrix;
            dataType *aData = (dataType *) aMatrix;
            dataType *tempData = (dataType *) tempMatrix;
            for (unsigned int i = 0; i < rows * columns; i++)
                tempData[i] = factor * aData[i];
            return Matrix <dataType, rows, columns>(MatrixOptions(0), tempData);
        }
        
        template <typename dataType, unsigned int rows, unsigned int columns>
        Matrix <dataType, rows, columns>
        operator*(const Matrix <dataType, rows, columns> &aMatrix,
                  dataType factor)
        {
            return factor * aMatrix;
        }
        
        template <typename dataType, unsigned int m, unsigned int n,
            unsigned int p>
        Matrix <dataType, m, p>
        operator*(const Matrix <dataType, m, n> &aMatrix,
                  const Matrix <dataType, n, p> &bMatrix)
        {
            Matrix <dataType, m, p> tempMatrix;
            dataType *aData = (dataType *) aMatrix;
            dataType *bData = (dataType *) bMatrix;
            dataType *tempData = (dataType *) tempMatrix;
            for (unsigned int row = 0; row < m; row++)
                for (unsigned int column = 0; column < p; column++)
                {
                    tempData[row*p+column] = (dataType)0;
                    for (unsigned int comp = 0; comp < n; comp++)
                        tempData[row*p+column] += aData[row*n+comp] *
                            bData[comp*p+column];
                }
            return Matrix <dataType, m, p>(MatrixOptions(0), tempData);
        }
    }
    
}

#endif //BLUEENGINE_MATRIX_H
