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

#include "utils/vector.h"


//===========================================================================
namespace vcl {

    //-----------------------------------------------------------------------
    /** \brief the generic class for 2-D vectors.
    * 
    * \sa its specializations Vect2d, Vect2f, Vect2b, Vect2s, Vect2us, Vect2i, and Vect2ui.
    */
    template<typename TScalar>
    class Vect2 : public Vector<TScalar, 2>
    {
    public:
        typedef Vector<TScalar, 2> MyBaseType; //<! wrapper to this class inherited class naming.
        typedef Vect2<TScalar>     MyType;     //<! wrapper to this class naming.


        //---   constructors   ----------------------------------------------
        /** \brief Constructor with a filling value (defaults to 0).
        */
        inline Vect2<TScalar>(const TScalar value = TScalar(0))
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        inline Vect2<TScalar>(const MyType& other)
            : MyBaseType()
        {
            copy(other);
        }

        /** \brief Copy constructor (&).
        */
        inline Vect2<TScalar>(MyType& other)
            : MyBaseType()
        {
            copy(other);
        }

        /** \brief Copy constructor (const std::array&).
        */
        inline Vect2<TScalar>(const MyBaseType& other)
            : MyBaseType()
        {
            copy(other);
        }

        /** \brief Copy constructor (std::array&).
        */
        inline Vect2<TScalar>(MyBaseType& other)
            : MyBaseType()
        {
            copy(other);
        }

        /** \brief Copy constructor (const std::vector&).
        */
        inline Vect2<TScalar>(const std::vector<TScalar>& vect)
            : MyBaseType()
        {
            copy(vect);
        }

        /** \brief Copy constructor (std::vector&).
        */
        inline Vect2<TScalar>(std::vector<TScalar>& vect)
            : MyBaseType()
        {
            copy(vect);
        }

        /** \brief Copy Constructor (const buffer).
        */
        inline Vect2<TScalar>(const TScalar buffer[MyBaseType::KSize])
            : MyBaseType()
        {
            copy(buffer);
        }

        /** \brief Copy constructor (buffer).
        */
        inline Vect2<TScalar>(TScalar buffer[MyBaseType::KSize])
            : MyBaseType()
        {
            copy(buffer);
        }

        //---  Destructor   -------------------------------------------------
        virtual inline ~Vect2<TScalar>()
        {}

        //---   Components accessors   --------------------------------------
        /** \brief component x getter */
        virtual inline TScalar x()
        {
            return (*this)[0];
        }

        /** \brief component x getter (const) */
        virtual inline const TScalar x() const
        {
            return (*this)[0];
        }

        /** \brief component x setter */
        virtual inline TScalar x(const TScalar new_x)
        {
            return (*this)[0] = new_x;
        }

        /** \brief component y getter */
        virtual inline TScalar y()
        {
            return (*this)[1];
        }

        /** \brief component y getter (const) */
        virtual inline const TScalar y() const
        {
            return (*this)[1];
        }

        /** \brief component y setter */
        virtual inline TScalar y(const TScalar new_y)
        {
            return (*this)[1] = new_y;
        }

        //---   copy()   ----------------------------------------------------
        /** \brief Copies a const vcl::Vector. */
        virtual inline void copy(const MyType& other)
        {
            x(other.x());
            y(other.y());
        }

        /** \brief Copies a vcl::Vector. */
        virtual inline void copy(MyType& other)
        {
            x(other.x());
            y(other.y());
        }

        /** \brief Copies a const std::array. */
        virtual inline void copy(const MyBaseType& other)
        {
            x(other[0]);
            y(other[1]);
        }

        /** \brief Copies an std::array. */
        virtual inline void copy(MyBaseType& other)
        {
            x(other[0]);
            y(other[1]);
        }

        /** \brief Copies a const std::vector. */
        virtual inline void copy(const std::vector<TScalar>& other)
        {
            x(other[0]);
            y(other.size() > 1 ? other[1] : TScalar(0));
        }

        /** \brief Copies a std::vector. */
        virtual inline void copy(std::vector<TScalar>& other)
        {
            x(other[0]);
            y(other.size() > 1 ? other[1] : TScalar(0));
        }

        /** \brief Copies a const buffer. */
        virtual inline void copy(const TScalar buffer[2])
        {
            x(buffer[0]);
            y(buffer[1]);
        }

        /** \brief Copies a buffer. */
        virtual inline void copy(TScalar buffer[2])
        {
            x(buffer[0]);
            y(buffer[1]);
        }

        //---   assignment operator   ---------------------------------------
        /** \brief assign operator (const std::array). */
        virtual inline MyType& operator= (const std::array<TScalar, MyBaseType::KSize>& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (std::array). */
        virtual inline MyType& operator= (std::array<TScalar, MyBaseType::KSize>& other)
        {
            copy(other);
            return *this;
        }

    protected:
        //---   add()   -----------------------------------------------------
        /** \brief inplace add operation (const reference) */
        virtual inline void add(const MyType& rhs)
        {
            x(x() + rhs.x());
            y(y() + rhs.y());
        }

        /** \brief inplace add operation (reference) */
        virtual inline void add(MyType& rhs)
        {
            x(x() + rhs.x());
            y(y() + rhs.y());
        }

        /** \brief inplace add operation (reference) */
        virtual inline void add(const TScalar value)
        {
            x(x() + value);
            y(y() + value);
        }

        /** \brief inplace add operation (const std::array) */
        virtual inline void add(const MyBaseType& rhs)
        {
            x(x() + rhs[0]);
            y(y() + rhs[1]);
        }

        /** \brief inplace add operation (std::array) */
        virtual inline void add(MyBaseType& rhs)
        {
            x(x() + rhs[0]);
            y(y() + rhs[1]);
        }

        /** \brief inplace add operation (const std::vector) */
        virtual inline void add(const std::vector<TScalar>& rhs)
        {
            x(x() + rhs[0]);
            if (rhs.size() > 1)
                y(y() + rhs[1]);
        }

        /** \brief inplace add operation (std::vector) */
        virtual inline void add(std::vector<TScalar>& rhs)
        {
            x(x() + rhs[0]);
            if (rhs.size() > 1)
                y(y() + rhs[1]);
        }

        /** \brief inplace add operation (const buffer) */
        virtual inline void add(const TScalar buffer[MyBaseType::KSize])
        {
            x(x() + buffer[0]);
            y(y() + buffer[1]);
        }

        /** \brief inplace add operation (buffer) */
        virtual inline void add(TScalar buffer[MyBaseType::KSize])
        {
            x(x() + buffer[0]);
            y(y() + buffer[1]);
        }

        //---   sub()   -----------------------------------------------------
        /** \brief inplace sub operation (const reference) */
        virtual inline void sub(const MyType& rhs)
        {
            x(x() - rhs.x());
            y(y() - rhs.y());
        }

        /** \brief inplace sub operation (reference) */
        virtual inline void sub(MyType& rhs)
        {
            x(x() - rhs.x());
            y(y() - rhs.y());
        }

        /** \brief inplace sub operation (reference) */
        virtual inline void sub(const TScalar value)
        {
            x(x() - value);
            y(y() - value);
        }

        /** \brief inplace sub operation (const std::array) */
        virtual inline void sub(const MyBaseType& rhs)
        {
            x(x() - rhs[0]);
            y(y() - rhs[1]);
        }

        /** \brief inplace sub operation (std::array) */
        virtual inline void sub(MyBaseType& rhs)
        {
            x(x() - rhs[0]);
            y(y() - rhs[1]);
        }

        /** \brief inplace sub operation (const std::vector) */
        virtual inline void sub(const std::vector<TScalar>& rhs)
        {
            x(x() - rhs[0]);
            if (rhs.size() > 1)
                y(y() - rhs[1]);
        }

        /** \brief inplace sub operation (std::vector) */
        virtual inline void sub(std::vector<TScalar>& rhs)
        {
            x(x() - rhs[0]);
            if (rhs.size() > 1)
                y(y() - rhs[1]);
        }

        /** \brief inplace sub operation (const buffer) */
        virtual inline void sub(const TScalar buffer[MyBaseType::KSize])
        {
            x(x() - buffer[0]);
            y(y() - buffer[1]);
        }

        /** \brief inplace sub operation (buffer) */
        virtual inline void sub(TScalar buffer[MyBaseType::KSize])
        {
            x(x() - buffer[0]);
            y(y() - buffer[1]);
        }

        //---   mul()   -----------------------------------------------------
        /** \brief inplace mul operation (const reference) */
        virtual inline void mul(const MyType& rhs)
        {
            x(x() * rhs.x());
            y(y() * rhs.y());
        }

        /** \brief inplace mul operation (reference) */
        virtual inline void mul(MyType& rhs)
        {
            x(x() * rhs.x());
            y(y() * rhs.y());
        }

        /** \brief inplace mul operation (reference) */
        virtual inline void mul(const TScalar value)
        {
            x(x() * value);
            y(y() * value);
        }

        /** \brief inplace mul operation (const std::array) */
        virtual inline void mul(const MyBaseType& rhs)
        {
            x(x() * rhs[0]);
            y(y() * rhs[1]);
        }

        /** \brief inplace mul operation (std::array) */
        virtual inline void mul(MyBaseType& rhs)
        {
            x(x() * rhs[0]);
            y(y() * rhs[1]);
        }

        /** \brief inplace mul operation (const std::vector) */
        virtual inline void mul(const std::vector<TScalar>& rhs)
        {
            x(x() * rhs[0]);
            if (rhs.size() > 1)
                y(y() * rhs[1]);
        }

        /** \brief inplace mul operation (std::vector) */
        virtual inline void mul(std::vector<TScalar>& rhs)
        {
            x(x() * rhs[0]);
            if (rhs.size() > 1)
                y(y() * rhs[1]);
        }

        /** \brief inplace mul operation (const buffer) */
        virtual inline void mul(const TScalar buffer[MyBaseType::KSize])
        {
            x(x() * buffer[0]);
            y(y() * buffer[1]);
        }

        /** \brief inplace mul operation (buffer) */
        virtual inline void mul(TScalar buffer[MyBaseType::KSize])
        {
            x(x() * buffer[0]);
            y(y() * buffer[1]);
        }

        //---   div()   -----------------------------------------------------
        /** \brief inplace div operation (const reference) */
        virtual inline void div(const MyType& rhs)
        {
            if (rhs.x() != TScalar(0))
                x(x() / rhs.x());
            if (rhs.y() != TScalar(0))
                y(y() / rhs.y());
        }

        /** \brief inplace div operation (reference) */
        virtual inline void div(MyType& rhs)
        {
            if (rhs.x() != TScalar(0))
                x(x() / rhs.x());
            if (rhs.y() != TScalar(0))
                y(y() / rhs.y());
        }

        /** \brief inplace div operation (reference) */
        virtual inline void div(const TScalar value)
        {
            if (value != TScalar(0)) {
                x(x() / value);
                y(y() / value);
            }
        }

        /** \brief inplace div operation (const std::array) */
        virtual inline void div(const MyBaseType& rhs)
        {
            if (rhs[0] != TScalar(0))
                x(x() / rhs[0]);
            if (rhs[1] != TScalar(0))
                y(y() / rhs[1]);
        }

        /** \brief inplace div operation (std::array) */
        virtual inline void div(MyBaseType& rhs)
        {
            if (rhs[0] != TScalar(0))
                x(x() / rhs[0]);
            if (rhs[1] != TScalar(0))
                y(y() / rhs[1]);
        }

        /** \brief inplace div operation (const std::vector) */
        virtual inline void div(const std::vector<TScalar>& rhs)
        {
            if (rhs[0] != TScalar(0))
                x(x() / rhs[0]);
            if (rhs.size() > 1  &&  rhs[1] != TScalar(0))
                y(y() / rhs[1]);
        }

        /** \brief inplace div operation (std::vector) */
        virtual inline void div(std::vector<TScalar>& rhs)
        {
            if (rhs[0] != TScalar(0))
                x(x() / rhs[0]);
            if (rhs.size() > 1 && rhs[1] != TScalar(0))
                y(y() / rhs[1]);
        }

        /** \brief inplace div operation (const buffer) */
        virtual inline void div(const TScalar buffer[MyBaseType::KSize])
        {
            if (buffer[0] != TScalar(0))
                x(x() / buffer[0]);
            if (buffer[1] != TScalar(0))
                y(y() / buffer[1]);
        }

        /** \brief inplace div operation (buffer) */
        virtual inline void div(TScalar buffer[MyBaseType::KSize])
        {
            if (buffer[0] != TScalar(0))
                x(x() / buffer[0]);
            if (buffer[1] != TScalar(0))
                y(y() / buffer[1]);
        }

    };


    /** \brief The class of 2D vectors with double components (64 bits). */
    typedef Vect2<double> Vect2d;
    

    /** \brief The class of 2D vectors with float components (32 bits). */
    typedef Vect2<float> Vect2f;


    /** \brief The class of 2D vectors with bytes components (8 bits). */
    typedef Vect2<unsigned char> Vect2b;


    /** \brief The class of 2D vectors with short components (16 bits). */
    typedef Vect2<short> Vect2s;


    /** \brief The class of 2D vectors with unsigned short components (16 bits). */
    typedef Vect2<unsigned short> Vect2us;


    /** \brief The class of 2D vectors with int components (32 bits). */
    typedef Vect2<int> Vect2i;


    /** \brief The class of 2D vectors with unsigned int components (32 bits). */
    typedef Vect2<unsigned int> Vect2ui;

} // end of namespace vcl
