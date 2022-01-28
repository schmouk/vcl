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
        typedef std::array<TScalar, Ksize> MyBaseType; //<! shortcut to this class inherited class naming.
        typedef Vector<TScalar, Ksize>     MyType;     //<! shortcut to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Constructor with a filling value (defaults to 0).
        */
        inline Vector<TScalar, Ksize>(const TScalar value = TScalar(0))
            : MyBaseType()
        {
            this->fill(value);
        }

        /** \brief Copy constructor (const&).
        */
        inline Vector<TScalar, Ksize>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (&).
        */
        inline Vector<TScalar, Ksize>(MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        inline Vector<TScalar, Ksize>(const MyBaseType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (std::array&).
        */
        inline Vector<TScalar, Ksize>(MyBaseType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        inline Vector<TScalar, Ksize>(const std::vector<TScalar>& vect)
            : MyBaseType()
        {
            copy(vect);
        }

        /** \brief Copy constructor (std::vector&).
        */
        inline Vector<TScalar, Ksize>(std::vector<TScalar>& vect)
            : MyBaseType()
        {
            copy(vect);
        }

        /** \brief Copy Constructor (const buffer).
        */
        inline Vector<TScalar, Ksize>(const TScalar buffer[Ksize])
            : MyBaseType()
        {
            copy(buffer);
        }

        /** \brief Copy constructor (buffer).
        */
        inline Vector<TScalar, Ksize>(TScalar buffer[Ksize])
            : MyBaseType()
        {
            copy(buffer);
        }

        //---  Destructor   -------------------------------------------------
        virtual inline ~Vector<TScalar, Ksize>()
        {}

        //---   copy()   ----------------------------------------------------
        /** \brief Copies a const vcl::Vector. */
        virtual inline void copy(const MyType& other)
        {
            auto ot = other.cbegin();
            for (auto it = this->begin(); it != this->end(); )
                *it++ = *ot++;
        }

        /** \brief Copies a vcl::Vector. */
        virtual inline void copy(MyType& other)
        {
            for (auto it = this->begin(), ot = other.begin(); it != this->end(); )
                *it++ = *ot++;
        }

        /** \brief Copies a const std::array. */
        virtual inline void copy(const MyBaseType& other)
        {
            auto it = this->begin();
            for (auto ot = other.cbegin(); it != this->end(); )
                *it++ = *ot++;
        }

        /** \brief Copies an std::array. */
        virtual inline void copy(MyBaseType& other)
        {
            auto it = this->begin();
            for (auto ot = other.begin(); it != this->end(); )
                *it++ = *ot++;
        }

        /** \brief Copies a const std::vector. */
        virtual inline void copy(const std::vector<TScalar>& other)
        {
            auto it = this->begin();
            for (auto ot = other.cbegin(); it != this->end() && ot != other.end(); )
                *it++ = *ot++;
            // checks for length of other < length of this
            while (it != this->end())
                *it++ = TScalar(0);
        }
        
        /** \brief Copies a std::vector. */
        virtual inline void copy(std::vector<TScalar>& other)
        {
            auto it = this->begin();
            for (auto ot = other.begin(); it != this->end() && ot != other.end(); )
                *it++ = *ot++;
            // checks for length of other < length of this
            while (it != this->end())
                *it++ = TScalar(0);
        }

        /** \brief Copies a const buffer. */
        virtual inline void copy(const TScalar buffer[Ksize])
        {
            const TScalar* b = buffer;
            for (auto it = this->begin(); it != this->end(); )
                *it++ = *b++;
        }

        /** \brief Copies a buffer. */
        virtual inline void copy(TScalar buffer[Ksize])
        {
            TScalar* b = buffer;
            for (auto it = this->begin(); it != this->end(); )
                *it++ = *b++;
        }

        //---   assignment operator   ---------------------------------------
        /** \brief assign operator with specified value */
        virtual inline MyType& operator= (const TScalar value)
        {
            this->fill(value);
            return *this;
        }

        /** \brief assign operator (const vcl::Vector). */
        virtual inline MyType& operator= (const MyType& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (vcl::Vector). */
        virtual inline MyType& operator= (MyType& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (const std::array). */
        virtual inline MyType& operator= (const MyBaseType& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (std::array). */
        virtual inline MyType& operator= (MyBaseType& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (const std::vector). */
        virtual inline MyType& operator= (const std::vector<TScalar>& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (std::vector). */
        virtual inline MyType& operator= (std::vector<TScalar>& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (const buffer). */
        virtual inline MyType& operator= (const TScalar buffer[Ksize])
        {
            copy(buffer);
            return *this;
        }

        /** \brief assign operator (buffer). */
        virtual inline MyType& operator= (TScalar buffer[Ksize])
        {
            copy(buffer);
            return *this;
        }

        //---   operators += and  +   ---------------------------------------
        /** \brief += operator (const reference) */
        virtual inline MyType& operator+= (const MyType& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (reference) */
        virtual inline MyType& operator+= (MyType& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (const TScalar) */
        virtual inline MyType& operator+= (const TScalar value)
        {
            add(value);
            return *this;
        }

        /** \brief += operator (const std::array) */
        virtual inline MyType& operator+= (const MyBaseType& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (std::array) */
        virtual inline MyType& operator+= (MyBaseType& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (const std::vector) */
        virtual inline MyType& operator+= (const std::vector<TScalar>& rhs)
        {
            add(rhs);
            return *this;
        }
        
        /** \brief += operator (std::vector) */
        virtual inline MyType& operator+= (std::vector<TScalar>& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (const buffer) */
        virtual inline MyType& operator+= (const TScalar buffer[Ksize])
        {
            add(buffer);
            return *this;
        }

        /** \brief += operator (buffer) */
        virtual inline MyType& operator+= (TScalar buffer[Ksize])
        {
            add(buffer);
            return *this;
        }

        /** \brief + operator (const reference).
        * Note: optimized for chained v1+v2+v3
        */
        friend inline MyType operator+ (MyType lhs, const MyType& rhs)
        {
            return (lhs += rhs);
        }

        /** \brief + operator (reference)
        * Note: optimized for chained v1+v2+v3
        */
        friend inline MyType operator+ (MyType lhs, MyType& rhs)
        {
            return (lhs += rhs);
        }

        /** \brief + operator (const TScalar) */
        friend inline MyType operator+ (MyType lhs, const TScalar value)
        {
            return (lhs += value);
        }

        /** \brief + operator (const TScalar, vcl::Vector) */
        friend inline MyType operator+ (const TScalar value, MyType rhs)
        {
            return (rhs += value);
        }

        /** \brief + operator (const std::array) */
        friend inline MyType operator+ (MyType lhs, const MyBaseType& rhs)
        {
            return (lhs += rhs);
        }

        /** \brief + operator (const std::array, vcl::Vector) */
        friend inline MyType operator+ (MyBaseType lhs, MyType rhs)
        {
            return (rhs += lhs);
        }

        /** \brief + operator (const std::vector) */
        friend inline MyType operator+ (MyType lhs, const std::vector<TScalar> rhs)
        {
            return (lhs += rhs);
        }

        /** \brief + operator (const std::vector, vcl::Vector) */
        friend inline MyType operator+ (const std::vector<TScalar> lhs, MyType rhs)
        {
            return (rhs += lhs);
        }

        /** \brief + operator (const buffer) */
        friend inline MyType& operator+ (MyType lhs, const TScalar buffer[Ksize])
        {
            return (lhs += buffer);
        }

        /** \brief + operator (const buffer, vcl::Vector) */
        friend inline MyType& operator+ (const TScalar buffer[Ksize], MyType rhs)
        {
            return (rhs += buffer);
        }

        /** \brief unary operator + */
        MyType& operator+()
        {
            return *this;
        }


        //---   operators -= and  -   ---------------------------------------
        /** \brief -= operator (const reference) */
        virtual inline MyType& operator-= (const MyType& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (reference) */
        virtual inline MyType& operator-= (MyType& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (const TScalar) */
        virtual inline MyType& operator-= (const TScalar value)
        {
            sub(value);
            return *this;
        }

        /** \brief -= operator (const std::array) */
        virtual inline MyType& operator-= (const MyBaseType& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (std::array) */
        virtual inline MyType& operator-= (MyBaseType& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (const std::vector) */
        virtual inline MyType& operator-= (const std::vector<TScalar>& rhs)
        {
            sub(rhs);
            return *this;
        }
        
        /** \brief -= operator (std::vector) */
        virtual inline MyType& operator-= (std::vector<TScalar>& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (const buffer) */
        virtual inline MyType& operator-= (const TScalar buffer[Ksize])
        {
            sub(buffer);
            return *this;
        }

        /** \brief -= operator (buffer) */
        virtual inline MyType& operator-= (TScalar buffer[Ksize])
        {
            sub(buffer);
            return *this;
        }

        /** \brief - operator (const reference).
        * Note: optimized for chained v1-v2-v3
        */
        friend inline MyType operator- (MyType lhs, const MyType& rhs)
        {
            return (lhs -= rhs);
        }

        /** \brief - operator (reference).
        * Note: optimized for chained v1-v2-v3
        */
        friend inline MyType operator- (MyType lhs, MyType& rhs)
        {
            return (lhs -= rhs);
        }

        /** \brief - operator (const TScalar) */
        friend inline MyType operator- (MyType lhs, const TScalar value)
        {
            return (lhs -= value);
        }

        /** \brief - operator (const TScalar, vcl::Vector) */
        friend inline MyType operator- (const TScalar value, MyType rhs)
        {
            return (MyType(value) -= rhs);
        }

        /** \brief - operator (const std::array) */
        friend inline MyType operator- (MyType lhs, const MyBaseType& rhs)
        {
            return (lhs -= rhs);
        }

        /** \brief - operator (const std::array, vcl::Vector) */
        friend inline MyType operator- (MyBaseType lhs, MyType rhs)
        {
            return -(rhs -= lhs);
        }

        /** \brief - operator (const std::vector) */
        friend inline MyType operator- (MyType lhs, const std::vector<TScalar> rhs)
        {
            return (lhs -= rhs);
        }

        /** \brief - operator (const std::vector, vcl::Vector) */
        friend inline MyType operator- (const std::vector<TScalar> lhs, MyType rhs)
        {
            return -(rhs -= lhs);
        }

        /** \brief - operator (const buffer) */
        friend inline MyType& operator- (MyType lhs, const TScalar buffer[Ksize])
        {
            return (lhs -= buffer);
        }

        /** \brief - operator (const buffer, vcl::Vector) */
        friend inline MyType& operator- (const TScalar buffer[Ksize], MyType rhs)
        {
            return (MyType(buffer) -= rhs);
        }

        /** \brief unary operator + */
        MyType operator-()
        {
            return TScalar(0) - *this;
        }

        //---   operators *= and  *   ---------------------------------------
        /** \brief *= operator (const reference) */
        virtual inline MyType& operator*= (const MyType& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (reference) */
        virtual inline MyType& operator*= (MyType& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (const TScalar) */
        virtual inline MyType& operator*= (const TScalar value)
        {
            mul(value);
            return *this;
        }

        /** \brief *= operator (const std::array) */
        virtual inline MyType& operator*= (const MyBaseType& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (std::array) */
        virtual inline MyType& operator*= (MyBaseType& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (const std::vector) */
        virtual inline MyType& operator*= (const std::vector<TScalar>& rhs)
        {
            mul(rhs);
            return *this;
        }
        
        /** \brief *= operator (std::vector) */
        virtual inline MyType& operator*= (std::vector<TScalar>& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (const buffer) */
        virtual inline MyType& operator*= (const TScalar buffer[Ksize])
        {
            mul(buffer);
            return *this;
        }

        /** \brief *= operator (buffer) */
        virtual inline MyType& operator*= (TScalar buffer[Ksize])
        {
            mul(buffer);
            return *this;
        }

        /** \brief * operator (const reference).
        * Note: optimized for chained v1*v2*v3
        */
        friend inline MyType operator*(MyType lhs, const MyType& rhs)
        {
            return (lhs *= rhs);
        }

        /** \brief * operator (reference).
        * Note: optimized for chained v1*v2*v3
        */
        friend inline MyType operator* (MyType lhs, MyType& rhs)
        {
            return (lhs *= rhs);
        }

        /** \brief * operator (const TScalar) */
        friend inline MyType operator* (MyType lhs, const TScalar value)
        {
            return (lhs *= value);
        }

        /** \brief * operator (const TScalar, vcl::Vector) */
        friend inline MyType operator* (const TScalar value, MyType rhs)
        {
            return (rhs *= value);
        }

        /** \brief * operator (const std::array) */
        friend inline MyType operator* (MyType lhs, const MyBaseType& rhs)
        {
            return (lhs *= rhs);
        }

        /** \brief * operator (const std::array, vcl::Vector) */
        friend inline MyType operator* (MyBaseType lhs, MyType rhs)
        {
            return (rhs *= lhs);
        }

        /** \brief * operator (const std::vector) */
        friend inline MyType operator* (MyType lhs, const std::vector<TScalar> rhs)
        {
            return (lhs *= rhs);
        }

        /** \brief * operator (const std::vector, vcl::Vector) */
        friend inline MyType operator* (const std::vector<TScalar> lhs, MyType rhs)
        {
            return (rhs *= lhs);
        }

        /** \brief * operator (const buffer) */
        friend inline MyType operator* (MyType lhs, const TScalar buffer[Ksize])
        {
            return (lhs *= buffer);
        }

        /** \brief * operator (const buffer, vcl::Vector) */
        friend inline MyType operator* (const TScalar buffer[Ksize], MyType rhs)
        {
            return (rhs *= buffer);
        }

        //---   operators /= and  /   ---------------------------------------
        /** \brief /= operator (const reference) */
        virtual inline MyType& operator/= (const MyType& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (reference) */
        virtual inline MyType& operator/= (MyType& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (const TScalar) */
        virtual inline MyType& operator/= (const TScalar value)
        {
            div(value);
            return *this;
        }

        /** \brief /= operator (const std::array) */
        virtual inline MyType& operator/= (const MyBaseType& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (std::array) */
        virtual inline MyType& operator/= (MyBaseType& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (const std::vector) */
        virtual inline MyType& operator/= (const std::vector<TScalar>& rhs)
        {
            div(rhs);
            return *this;
        }
        
        /** \brief /= operator (std::vector) */
        virtual inline MyType& operator/= (std::vector<TScalar>& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (const buffer) */
        virtual inline MyType& operator/= (const TScalar buffer[Ksize])
        {
            div(buffer);
            return *this;
        }

        /** \brief /= operator (buffer) */
        virtual inline MyType& operator/= (TScalar buffer[Ksize])
        {
            div(buffer);
            return *this;
        }

        /** \brief / operator (const reference).
        * Note: optimized for chained v1*v2*v3
        */
        friend inline MyType operator/ (MyType lhs, const MyType& rhs)
        {
            return (lhs /= rhs);
        }

        /** \brief / operator (reference).
        * Note: optimized for chained v1*v2*v3
        */
        friend inline MyType operator/ (MyType lhs, MyType& rhs)
        {
            return (lhs /= rhs);
        }

        /** \brief / operator (const TScalar) */
        friend inline MyType operator/ (MyType lhs, const TScalar value)
        {
            return (lhs /= value);
        }

        /** \brief / operator (const TScalar, vcl::Vector) */
        friend inline MyType operator/ (const TScalar value, MyType rhs)
        {
            return (MyType(value) /= rhs);
        }

        /** \brief / operator (const std::array) */
        friend inline MyType operator/ (MyType lhs, const MyBaseType& rhs)
        {
            return (lhs /= rhs);
        }

        /** \brief / operator (const std::array, vcl::Vector) */
        friend inline MyType operator/ (MyBaseType lhs, MyType rhs)
        {

            return (MyType(lhs) /= rhs);
        }

        /** \brief / operator (const std::vector) */
        friend inline MyType operator/ (MyType lhs, const std::vector<TScalar> rhs)
        {
            return (lhs /= rhs);
        }

        /** \brief / operator (const std::vector, vcl::Vector) */
        friend inline MyType operator/ (const std::vector<TScalar> lhs, MyType rhs)
        {
            return (MyType(lhs) /= rhs);
        }

        /** \brief / operator (const buffer) */
        friend inline MyType operator/ (MyType lhs, const TScalar buffer[Ksize])
        {
            return (lhs /= buffer);
        }

        /** \brief / operator (const buffer, vcl::Vector) */
        friend inline MyType operator/ (const TScalar buffer[Ksize], MyType rhs)
        {
            return (MyType(buffer) /= rhs);
        }

        //---   miscelaneous   ----------------------------------------------
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
            fill(TScalar(0));
        }


    protected:
        //---   add()   -----------------------------------------------------
        /** \brief inplace add operation (const reference) */
        virtual inline void add(const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); )
                *it++ += *rit++;
        }

        /** \brief inplace add operation (reference) */
        virtual inline void add(MyType& rhs)
        {
            for (auto it = this->begin(), rit = rhs.begin(); it != this->end(); )
                *it++ += *rit++;
        }

        /** \brief inplace add operation (reference) */
        virtual inline void add(const TScalar value)
        {
            for (auto it = this->begin(); it != this->end(); )
                *it++ += value;
        }

        /** \brief inplace add operation (const std::array) */
        virtual inline void add(const MyBaseType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); )
                *it++ += *rit++;
        }

        /** \brief inplace add operation (std::array) */
        virtual inline void add(MyBaseType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); )
                *it++ += *rit++;
        }

        /** \brief inplace add operation (const std::vector) */
        virtual inline void add(const std::vector<TScalar>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); )
                *it++ += *rit++;
        }

        /** \brief inplace add operation (std::vector) */
        virtual inline void add(std::vector<TScalar>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); )
                *it++ += *rit++;
        }

        /** \brief inplace add operation (const buffer) */
        virtual inline void add(const TScalar buffer[Ksize])
        {
            const TScalar* b = buffer;
            for (auto it = this->begin(); it != this->end(); )
                *it++ += *b++;
        }

        /** \brief inplace add operation (buffer) */
        virtual inline void add(TScalar buffer[Ksize])
        {
            TScalar* b = buffer;
            for (auto it = this->begin(); it != this->end(); )
                *it++ += *b++;
        }

        //---   sub()   -----------------------------------------------------
        /** \brief inplace sub operation (const reference) */
        virtual inline void sub(const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); )
                *it++ -= *rit++;
        }

        /** \brief inplace sub operation (reference) */
        virtual inline void sub(MyType& rhs)
        {
            for (auto it = this->begin(), rit = rhs.begin(); it != this->end(); )
                *it++ -= *rit++;
        }

        /** \brief inplace sub operation (reference) */
        virtual inline void sub(const TScalar value)
        {
            for (auto it = this->begin(); it != this->end(); )
                *it++ -= value;
        }

        /** \brief inplace sub operation (const std::array) */
        virtual inline void sub(const MyBaseType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); )
                *it++ -= *rit++;
        }

        /** \brief inplace sub operation (std::array) */
        virtual inline void sub(MyBaseType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); )
                *it++ -= *rit++;
        }

        /** \brief inplace sub operation (const std::vector) */
        virtual inline void sub(const std::vector<TScalar>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); )
                *it++ -= *rit++;
        }
        
        /** \brief inplace sub operation (std::vector) */
        virtual inline void sub(std::vector<TScalar>& rhs)
        {
            auto rit = rhs.begin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); )
                *it++ -= *rit++;
        }

        /** \brief inplace sub operation (const buffer) */
        virtual inline void sub(const TScalar buffer[Ksize])
        {
            const TScalar* b = buffer;
            for (auto it = this->begin(); it != this->end(); )
                *it++ -= *b++;
        }

        /** \brief inplace sub operation (buffer) */
        virtual inline void sub(TScalar buffer[Ksize])
        {
            TScalar* b = buffer;
            for (auto it = this->begin(); it != this->end(); )
                *it++ -= *b++;
        }

        //---   mul()   -----------------------------------------------------
        /** \brief inplace mul operation (const reference) */
        virtual inline void mul(const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); )
                *it++ *= *rit++;
        }

        /** \brief inplace mul operation (reference) */
        virtual inline void mul(MyType& rhs)
        {
            for (auto it = this->begin(), rit = rhs.begin(); it != this->end(); )
                *it++ *= *rit++;
        }

        /** \brief inplace mul operation (reference) */
        virtual inline void mul(const TScalar value)
        {
            for (auto it = this->begin(); it != this->end(); )
                *it++ *= value;
        }

        /** \brief inplace mul operation (const std::array) */
        virtual inline void mul(const MyBaseType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); )
                *it++ *= *rit++;
        }

        /** \brief inplace mul operation (std::array) */
        virtual inline void mul(MyBaseType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); )
                *it++ *= *rit++;
        }

        /** \brief inplace mul operation (const std::vector) */
        virtual inline void mul(const std::vector<TScalar>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); )
                *it++ *= *rit++;
        }
        
        /** \brief inplace mul operation (std::vector) */
        virtual inline void mul(std::vector<TScalar>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); )
                *it++ *= *rit++;
        }

        /** \brief inplace mul operation (const buffer) */
        virtual inline void mul(const TScalar buffer[Ksize])
        {
            const TScalar* b = buffer;
            for (auto it = this->begin(); it != this->end(); )
                *it++ *= *b++;
        }

        /** \brief inplace mul operation (buffer) */
        virtual inline void mul(TScalar buffer[Ksize])
        {
            TScalar* b = buffer;
            for (auto it = this->begin(); it != this->end(); )
                *it++ *= *b++;
        }

        //---   div()   -----------------------------------------------------
        /** \brief inplace div operation (const reference) */
        virtual inline void div(const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); rit++)
                *it++ /= *rit != TScalar(0) ? *rit : TScalar(1);
        }

        /** \brief inplace div operation (reference) */
        virtual inline void div(MyType& rhs)
        {
            for (auto it = this->begin(), rit = rhs.begin(); it != this->end(); rit++)
                *it++ /= *rit != TScalar(0) ? *rit : TScalar(1);
        }

        /** \brief inplace div operation (reference) */
        virtual inline void div(const TScalar value)
        {
            if (value != TScalar(0))
              for (auto it = this->begin(); it != this->end(); )
                *it++ /= value;
        }

        /** \brief inplace div operation (const std::array) */
        virtual inline void div(const MyBaseType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); rit++)
                *it++ /= *rit != TScalar(0) ? *rit : TScalar(1);
        }

        /** \brief inplace div operation (std::array) */
        virtual inline void div(MyBaseType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); rit++)
                *it++ /= *rit != TScalar(0) ? *rit : TScalar(1);
        }

        /** \brief inplace div operation (const std::vector) */
        virtual inline void div(const std::vector<TScalar>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); rit++)
                *it++ /= *rit != TScalar(0) ? *rit : TScalar(1);
        }
        
        /** \brief inplace div operation (std::vector) */
        virtual inline void div(std::vector<TScalar>& rhs)
        {
            auto rit = rhs.begin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); rit++)
                *it++ /= *rit != TScalar(0) ? *rit : TScalar(1);
        }

        /** \brief inplace div operation (const buffer) */
        virtual inline void div(const TScalar buffer[Ksize])
        {
            const TScalar* b = buffer;
            for (auto it = this->begin(); it != this->end(); b++)
                *it++ /= *b != TScalar(0) ? *b : TScalar(1);
        }

        /** \brief inplace div operation (buffer) */
        virtual inline void div(TScalar buffer[Ksize])
        {
            TScalar* b = buffer;
            for (auto it = this->begin(); it != this->end(); b++)
                *it++ /= *b != TScalar(0) ? *b : TScalar(1);
        }

    };

} // end of namespace vcl
