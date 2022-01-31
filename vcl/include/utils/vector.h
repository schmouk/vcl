#pragma once
/*
MIT License

Copyright (c) 2022 Philippe Schmouker, ph.schmouker (at) gmail.com

Permission is hereby granted,  free of charge,  to any person obtaining a copy
of this software and associated documentation files (the "Software"),  to deal
in the Software without restriction,  including without limitation the  rights
to use,  copy,  modify,  merge,  publish,  distribute, sublicense, and/or sell
copies of the Software,  and  to  permit  persons  to  whom  the  Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY  KIND,  EXPRESS  OR
IMPLIED,  INCLUDING  BUT  NOT  LIMITED  TO  THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT  SHALL  THE
AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM,  DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM,
OUT  OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


//===========================================================================
#include <array>
#include <compare>
#include <iostream>
#include <sstream>
#include <vector>


//===========================================================================
namespace vcl {

    //-----------------------------------------------------------------------
    /** \brief the generic class for vectors.
    */
    template<typename TScalar, const size_t Ksize>
    class Vector : public std::array<TScalar, Ksize>
    {
    public:
        typedef std::array<TScalar, Ksize> MyBaseType; //<! wrapper to the inherited class naming.
        typedef Vector<TScalar, Ksize>     MyType;     //<! wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Constructor with a filling value (defaults to 0).
        */
        inline Vector<TScalar, Ksize>()
            : MyBaseType()
        {
            zero();
        }

        explicit inline Vector<TScalar, Ksize>(const char value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const unsigned char value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const short value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const unsigned short value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const int value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const unsigned int value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const long value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const unsigned long value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const long long value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const unsigned long long value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const float value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const double value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        explicit inline Vector<TScalar, Ksize>(const long double value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        /** \brief Copy constructor (const&).
        */
        template<typename T, size_t S>
        inline Vector<TScalar, Ksize>(const vcl::Vector<T,S>& other)
            : MyBaseType()
        {
            zero();
            copy(other);
        }

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline Vector<TScalar, Ksize>(const std::array<T, S>& other)
            : MyBaseType()
        {
            zero();
            copy(other);
        }

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline Vector<TScalar, Ksize>(const std::vector<T>& vect)
            : MyBaseType()
        {
            zero();
            copy(vect);
        }


        //---  Destructor   -------------------------------------------------
        virtual inline ~Vector<TScalar, Ksize>()
        {}


        //---   copy()   ----------------------------------------------------
        /** \brief Copies a const vcl::Vector. */
        template<typename T, size_t S>
        inline void copy(const vcl::Vector<T,S>& other)
        {
            auto ot = other.cbegin();
            for (auto it = this->begin(); it != this->end() && ot !=  other.cend(); )
                *it++ = clipped(*ot++);
        }

        /** \brief Copies a const std::array. */
        template<typename T, size_t S>
        inline void copy(const std::array<T, S>& other)
        {
            auto it = this->begin();
            for (auto ot = other.cbegin(); it != this->end() && ot != other.cend(); )
                *it++ = clipped(*ot++);
        }

        /** \brief Copies into a std::array. */
        template<typename T, size_t S>
        friend inline void copy(std::array<T, S>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                *it++ = T(*rit++);
        }

        /** \brief Copies a const std::vector. */
        template<typename T>
        inline void copy(const std::vector<T>& other)
        {
            auto it = this->begin();
            for (auto ot = other.cbegin(); it != this->end() && ot != other.cend(); )
                *it++ = clipped(*ot++);
        }

        /** \brief Copies into a std::vector. */
        template<typename T>
        friend inline void copy(std::vector<T>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                *it++ = T(*rit++);
        }


        //---   assignment operator   ---------------------------------------
        /** \brief assign operator with specified value */
        inline MyType& operator= (const char value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const unsigned char value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const short value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const unsigned short value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const int value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const unsigned int value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const long value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const unsigned long value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const long long value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const unsigned long long value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const float value)
        {
            this->fill(clipped(value));
            return *this;
        }

        inline MyType& operator= (const double value)
        {
            this->fill(clipped(value));
            return *this;
        }
        
        inline MyType& operator= (const long double value)
        {
            this->fill(clipped(value));
            return *this;
        }

        /** \brief assign operator (const vcl::Vector). */
        template<typename T, size_t S>
        inline MyType& operator= (const vcl::Vector<T,S>& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (const std::array). */
        template<typename T, size_t S>
        inline MyType& operator= (const std::array<T, S>& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (const std::vector). */
        template<typename T>
        inline MyType& operator= (const std::vector<T>& other)
        {
            copy(other);
            return *this;
        }

        //---   operator +=   -----------------------------------------------
        /** \brief += operator (const reference) */
        template<typename T, size_t S>
        inline MyType& operator+= (const vcl::Vector<T,S>& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (const TScalar) */
        inline MyType& operator+= (const char value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const unsigned char value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const short value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const unsigned short value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const int value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const unsigned int value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const long value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const unsigned long value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const long long value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const unsigned long long value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const float value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const double value)
        {
            add(value);
            return *this;
        }

        inline MyType& operator+= (const long double value)
        {
            add(value);
            return *this;
        }

        /** \brief += operator (const std::array) */
        template<typename T, size_t S>
        inline MyType& operator+= (const std::array<T, S>& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (std::array, vcl::Vector) */
        template<typename T, size_t S>
        friend inline std::array<T, S>& operator+= (std::array<T, S> lhs, const MyType& rhs)
        {
            add(lhs, rhs);
            return lhs;
        }

        /** \brief += operator (const std::vector) */
        template<typename T>
        inline MyType& operator+= (const std::vector<T>& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (std::vector, vcl::Vector) */
        template<typename T>
        friend inline std::vector<T>& operator+= (std::vector<T> lhs, const MyType& rhs)
        {
            add(lhs, rhs);
            return lhs;
        }

        //---   operator +   ------------------------------------------------
        /** \brief + operator (const reference).
        * Note: optimized for chained v1+v2+v3
        */
        template<typename T, size_t S>
        friend inline MyType operator+ (MyType lhs, const vcl::Vector<T, S>& rhs)
        {
            return lhs += rhs;
        }

        /** \brief + operator (const TScalar) */
        friend inline MyType operator+ (MyType lhs, const char value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const unsigned char value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const short value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const unsigned short value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const int value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const unsigned int value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const long value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const unsigned long value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const long long value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const unsigned long long value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const float value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const double value)
        {
            return lhs += value;
        }

        friend inline MyType operator+ (MyType lhs, const long double value)
        {
            return lhs += value;
        }

        /** \brief + operator (const TScalar, vcl::Vector) */
        friend inline MyType operator+ (const char value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const unsigned char value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const short value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const unsigned short value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const int value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const unsigned int value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const long value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const unsigned long value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const  long long value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const unsigned  long long value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const float value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const double value, MyType rhs)
        {
            return rhs += value;
        }

        friend inline MyType operator+ (const long double value, MyType rhs)
        {
            return rhs += value;
        }

        /** \brief + operator (const std::array) */
        template<typename T, size_t S>
        friend inline MyType operator+ (MyType lhs, const std::array<T, S>& rhs)
        {
            return lhs += rhs;
        }

        /** \brief + operator (const std::array, vcl::Vector) */
        template<typename T, size_t S>
        friend inline std::array<T, S> operator+ (std::array<T, S> lhs, MyType rhs)
        {
            return lhs += rhs;
        }

        /** \brief + operator (const std::vector) */
        template<typename T>
        friend inline MyType operator+ (MyType lhs, const std::vector<T> rhs)
        {
            return lhs += rhs;
        }

        /** \brief + operator (const std::vector, vcl::Vector) */
        template<typename T>
        friend inline std::vector<T> operator+ (std::vector<T> lhs, MyType rhs)
        {
            return lhs += rhs;
        }

        /** \brief unary operator + */
        MyType& operator+()
        {
            return *this;
        }


        //---   operators -=   ----------------------------------------------
        /** \brief -= operator (const reference) */
        template<typename T, size_t S>
        inline MyType& operator-= (const vcl::Vector<T,S>& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (const TScalar) */
        inline MyType& operator-= (const char value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const unsigned char value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const short value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const unsigned short value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const int value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const unsigned int value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const long value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const unsigned long value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const long long value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const unsigned long long value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const float value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const double value)
        {
            sub(value);
            return *this;
        }

        inline MyType& operator-= (const long double value)
        {
            sub(value);
            return *this;
        }

        /** \brief -= operator (const std::array) */
        template<typename T, size_t S>
        inline MyType& operator-= (const std::array<T, S>& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (std::array, vcl::Vector) */
        template<typename T, size_t S>
        friend inline std::array<T, S>& operator-= (std::array<T, S> lhs, const MyType& rhs)
        {
            sub(lhs, rhs);
            return lhs;
        }

        /** \brief -= operator (const std::vector) */
        template<typename T>
        inline MyType& operator-= (const std::vector<T>& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (std::vector, vcl::Vector) */
        template<typename T>
        friend inline std::vector<T>& operator-= (std::vector<T> lhs, const MyType& rhs)
        {
            sub(lhs, rhs);
            return lhs;
        }

        //---   operator -   ------------------------------------------------
        /** \brief + operator (const reference).
        * Note: optimized for chained v1-v2-v3
        */
        template<typename T, size_t S>
        friend inline MyType operator- (MyType lhs, const vcl::Vector<T, S>& rhs)
        {
            return lhs -= rhs;
        }

        /** \brief - operator (const TScalar) */
        friend inline MyType operator- (MyType lhs, const char value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const unsigned char value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const short value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const unsigned short value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const int value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const unsigned int value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const long value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const unsigned long value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const long long value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const unsigned long long value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const float value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const double value)
        {
            return lhs -= value;
        }

        friend inline MyType operator- (MyType lhs, const long double value)
        {
            return lhs -= value;
        }

        /** \brief - operator (const TScalar, vcl::Vector) */
        friend inline MyType operator- (const char value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const unsigned char value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const short value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const unsigned short value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const int value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const unsigned int value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const long value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const unsigned long value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const  long long value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const unsigned  long long value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const float value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const double value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        friend inline MyType operator- (const long double value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        /** \brief - operator (const std::array) */
        template<typename T, size_t S>
        friend inline MyType operator- (MyType lhs, const std::array<T, S>& rhs)
        {
            return lhs -= rhs;
        }

        /** \brief - operator (const std::array, vcl::Vector) */
        template<typename T, size_t S>
        friend inline std::array<T, S> operator- (std::array<T, S> lhs, MyType rhs)
        {
            return lhs -= rhs;
        }

        /** \brief - operator (const std::vector) */
        template<typename T>
        friend inline MyType operator- (MyType lhs, const std::vector<T> rhs)
        {
            return lhs -= rhs;
        }

        /** \brief - operator (const std::vector, vcl::Vector) */
        template<typename T>
        friend inline std::vector<T> operator- (const std::vector<T> lhs, MyType rhs)
        {
            return lhs -= rhs;
        }
        /** \brief unary operator - */
        MyType operator-()
        {
            return (*this * TScalar(-1));
        }


        //---   operators *= and  *   ---------------------------------------
        /** \brief *= operator (const reference) */
        template<typename T, size_t S>
        inline MyType& operator*= (const vcl::Vector<T,S>& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (const TScalar) */
        inline MyType& operator*= (const char value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const unsigned char value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const short value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const unsigned short value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const int value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const unsigned int value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const long value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const unsigned long value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const long long value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const unsigned long long value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const float value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const double value)
        {
            mul(value);
            return *this;
        }

        inline MyType& operator*= (const long double value)
        {
            mul(value);
            return *this;
        }

        /** \brief *= operator (const std::array) */
        template<typename T>
        inline MyType& operator*= (const std::array<T, Ksize>& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (std::array, vcl::Vector) */
        template<typename T, size_t S>
        friend inline std::array<T, S>& operator*= (std::array<T, S>& lhs, const MyType& rhs)
        {
            mul(lhs, rhs);
            return lhs;
        }

        /** \brief *= operator (const std::vector) */
        template<typename T>
        inline MyType& operator*= (const std::vector<T>& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (std::vector, vcl::Vector) */
        template<typename T>
        friend inline std::vector<T>& operator*= (std::vector<T>& lhs, const MyType& rhs)
        {
            mul(lhs, rhs);
            return lhs;
        }

        //---   operator *   ------------------------------------------------
        /** \brief + operator (const reference).
        * Note: optimized for chained v1*v2*v3
        */
        template<typename T, size_t S>
        friend inline MyType operator* (MyType lhs, const vcl::Vector<T, S>& rhs)
        {
            return lhs *= rhs;
        }

        /** \brief * operator (vcl::Vector, const TScalar) */
        friend inline MyType operator* (MyType lhs, const char value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const unsigned char value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const short value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const unsigned short value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const int value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const unsigned int value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const long value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const unsigned long value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const long long value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const unsigned long long value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const float value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const double value)
        {
            return lhs *= value;
        }

        friend inline MyType operator* (MyType lhs, const long double value)
        {
            return lhs *= value;
        }

        /** \brief * operator (const TScalar, vcl::Vector) */
        friend inline MyType operator* (const char value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const unsigned char value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const short value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const unsigned short value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const int value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const unsigned int value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const long value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const unsigned long value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const  long long value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const unsigned  long long value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const float value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const double value, MyType rhs)
        {
            return rhs *= value;
        }

        friend inline MyType operator* (const long double value, MyType rhs)
        {
            return rhs *= value;
        }

        /** \brief * operator (const std::array) */
        template<typename T, size_t S>
        friend inline MyType operator* (MyType lhs, const std::array<T, S>& rhs)
        {
            return lhs *= rhs;
        }

        /** \brief * operator (const std::array, vcl::Vector) */
        template<typename T, size_t S>
        friend inline std::array<T, S> operator* (std::array<T, S> lhs, MyType rhs)
        {
            return lhs *= rhs;
        }

        /** \brief * operator (const std::vector) */
        template<typename T>
        friend inline MyType operator* (MyType lhs, const std::vector<T> rhs)
        {
            return lhs *= rhs;
        }

        /** \brief * operator (const std::vector, vcl::Vector) */
        template<typename T>
        friend inline std::vector<T> operator* (std::vector<T> lhs, MyType rhs)
        {
            return lhs *= rhs;
        }


        //---   operators /= and  /   ---------------------------------------
        /** \brief /= operator (const reference) */
        template<typename T, size_t S>
        inline MyType& operator/= (const vcl::Vector<T, S>& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (const TScalar) */
        inline MyType& operator/= (const char value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const unsigned char value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const short value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const unsigned short value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const int value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const unsigned int value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const long value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const unsigned long value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const long long value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const unsigned long long value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const float value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const double value)
        {
            div(value);
            return *this;
        }

        inline MyType& operator/= (const long double value)
        {
            div(value);
            return *this;
        }

        /** \brief /= operator (const std::array) */
        template<typename T, size_t S>
        inline MyType& operator/= (const std::array<T, S>& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (std::array, vcl::Vector) */
        template<typename T, size_t S>
        friend inline std::array<T, S>& operator/= (std::array<T, S> lhs, const MyType& rhs)
        {
            div(lhs, rhs);
            return lhs;
        }

        /** \brief /= operator (const std::vector) */
        template<typename T>
        inline MyType& operator/= (const std::vector<T>& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (std::vector, vcl::Vector) */
        template<typename T>
        friend inline std::vector<T>& operator/= (std::vector<T> lhs, const MyType& rhs)
        {
            div(lhs, rhs);
            return lhs;
        }


        //---   operator /   ------------------------------------------------
        /** \brief / operator (const reference).
        * Note: optimized for chained v1/v2/v3
        */
        template<typename T, size_t S>
        friend inline MyType operator/ (MyType lhs, const vcl::Vector<T, S>& rhs)
        {
            return lhs /= rhs;
        }

        /** \brief / operator (vcl::Vector, const TScalar) */
        friend inline MyType operator/ (MyType lhs, const char value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const unsigned char value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const short value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const unsigned short value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const int value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const unsigned int value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const long value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const unsigned long value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const long long value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const unsigned long long value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const float value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const double value)
        {
            return lhs /= value;
        }

        friend inline MyType operator/ (MyType lhs, const long double value)
        {
            return lhs /= value;
        }

        /** \brief / operator (const T Scalar, vcl::Vector) */
        friend inline MyType operator/ (const char value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const unsigned char value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const short value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const unsigned short value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const int value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const unsigned int value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const long value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const unsigned long value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const  long long value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const unsigned  long long value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const float value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const double value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        friend inline MyType operator/ (const long double value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        /** \brief / operator (const std::array) */
        template<typename T, size_t S>
        friend inline MyType operator/ (MyType lhs, const std::array<T, S>& rhs)
        {
            return lhs /= rhs;
        }

        /** \brief / operator (const std::array, vcl::Vector) */
        template<typename T, size_t S>
        friend inline std::array<T, S> operator/ (std::array<T, S> lhs, MyType rhs)
        {
            return lhs /= rhs;
        }

        /** \brief / operator (const std::vector) */
        template<typename T>
        friend inline MyType operator/ (MyType lhs, const std::vector<T> rhs)
        {
            return lhs /= rhs;
        }

        /** \brief / operator (const std::vector, vcl::Vector) */
        template<typename T>
        friend inline std::vector<T> operator/ (const std::vector<T> lhs, MyType rhs)
        {
            return lhs /= rhs;
        }


        //---   miscelaneous   ----------------------------------------------
        /** \brief Returns the specified value clipped - does no clipping in this base class. */
        template<typename T>
        inline const TScalar clipped(const T value)
        {
            return TScalar(value);
        }

        /** \brief Returns a string representation of this vector. */
        std::string repr()
        {
            std::ostringstream repr_ostr;
        
            repr_ostr << '(';
            auto it = this->begin();
            while (it != this->end() - 1)
                repr_ostr << *it++ << ", ";
            repr_ostr << *it << ')';
        
            return repr_ostr.str();
        }

        /** \brief Sets all components with value 0.
        * \sa method fill.
        */
        inline void zero()
        {
            this->fill(clipped(0));
        }


    protected:
        //---   add()   -----------------------------------------------------
        /** \brief inplace add operation (const reference) */
        template<typename T, size_t S>
        inline void add(const vcl::Vector<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); )
                *it++ += *rit++;
        }

        /** \brief inplace add operation (scalar) */
        inline void add(const char value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const unsigned char value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const short value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const unsigned short value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const int value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const unsigned int value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const unsigned long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const long long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const unsigned long long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const float value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const double value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        inline void add(const long double value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        /** \brief inplace add operation (const std::array) */
        template<typename T, size_t S>
        inline void add(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = clipped(*it + *rit++);
        }

        /** \brief inplace add operation (std::array, const vcl::Vector) */
        template<typename T, size_t S>
        friend inline void add(std::array<T, S>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                *it++ += T(*rit++);
        }

        /** \brief inplace add operation (const std::vector) */
        template<typename T>
        inline void add(const std::vector<T>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); it++)
                *it = clipped(*it + *rit++);
        }

        /** \brief inplace add operation (std::vector, const vcl::Vector) */
        template<typename T>
        friend inline void add(std::vector<T>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                *it++ += T(*rit++);
        }


        //---   sub()   -----------------------------------------------------
        /** \brief inplace sub operation (const reference) */
        template<typename T, size_t S>
        inline void sub(const vcl::Vector<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); )
                *it++ -= *rit++;
        }

        /** \brief inplace sub operation (scalar) */
        inline void sub(const char value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const unsigned char value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const short value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const unsigned short value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const int value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const unsigned int value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const unsigned long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const long long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const unsigned long long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const float value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const double value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        inline void sub(const long double value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        /** \brief inplace sub operation (const std::array) */
        template<typename T, size_t S>
        inline void sub(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - *rit++);
        }

        /** \brief inplace sub operation (std::array, const vcl::Vector) */
        template<typename T, size_t S>
        friend inline void sub(std::array<T, S>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                *it++ -= T(*rit++);
        }

        /** \brief inplace sub operation (const std::vector) */
        template<typename T>
        inline void sub(const std::vector<T>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); it++)
                *it = clipped(*it - *rit++);
        }

        /** \brief inplace sub operation (std::vector, const vcl::Vector) */
        template<typename T>
        friend inline void sub(std::vector<T>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                *it++ -= T(*rit++);
        }


        //---   mul()   -----------------------------------------------------
        /** \brief inplace mul operation (const reference) */
        template<typename T, size_t S>
        inline void mul(const vcl::Vector<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); )
                *it++ *= *rit++;
        }

        /** \brief inplace mul operation (scalar) */
        inline void mul(const char value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const unsigned char value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const short value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const unsigned short value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const int value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const unsigned int value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const unsigned long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const long long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const unsigned long long value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const float value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const double value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        inline void mul(const long double value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        /** \brief inplace mul operation (const std::array) */
        template<typename T, size_t S>
        inline void mul(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = clipped(*it * *rit++);
        }

        /** \brief inplace mul operation (std::array, const vcl::Vector) */
        template<typename T, size_t S>
        friend inline void mul(std::array<T, S>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != it->end() && rit != rhs.cend(); )
                *it++ *= T(*rit++);
        }

        /** \brief inplace mul operation (const std::vector) */
        template<typename T>
        inline void mul(const std::vector<T>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); it++)
                *it = clipped(*it * *rit++);
        }

        /** \brief inplace mul operation (std::vector, const vcl::Vector) */
        template<typename T>
        friend inline void mul(std::vector<T>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != this->end() && rit != rhs.cend(); )
                *it++ *= T(*rit++);
        }


        //---   div()   -----------------------------------------------------
        /** \brief inplace div operation (const reference) */
        template<typename T, size_t S>
        inline void div(const vcl::Vector<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++, rit++)
                if (*rit != TScalar(0))
                    *it /= *rit;
        }

        /** \brief inplace div operation (scalar) */
        inline void div(const char value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const unsigned char value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const short value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const unsigned short value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const int value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const unsigned int value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const long value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const unsigned long value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const long long value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const unsigned long long value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const float value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const double value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        inline void div(const long double value)
        {
            if (value != 0)
                for (auto it = this->begin(); it != this->end(); )
                    *it++ = clipped(*it / value);
        }

        /** \brief inplace div operation (const std::array) */
        template<typename T, size_t S>
        inline void div(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++, rit++)
                if (*rit != T(0))
                    *it = clipped(*it / *rit);
        }

        /** \brief inplace div operation (std::array, const vcl::Vector) */
        template<typename T, size_t S>
        friend inline void div(std::array<T, S>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); it++, rit++)
                if (*rit != T(0))
                    *it = clipped(*it / *rit);
        }

        /** \brief inplace div operation (const std::vector) */
        template<typename T>
        inline void div(const std::vector<T>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); it++, rit++)
                if (*rit != T(0))
                    *it = clipped(*it / *rit);
        }

        /** \brief inplace div operation (std::vector, const vcl::Vector) */
        template<typename T>
        friend inline void div(std::vector<T>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); it++, rit++)
                if (*rit != T(0))
                    *it = clipped(*it / *rit);
        }

    }; // end of class Vector<typename TScalar, const size_t Ksize>

} // end of namespace vcl
