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
    /** \brief the generic class for 4-D vectors.
    *
    * \sa its specializations Vect4d, Vect4f, Vect4b, Vect4s, Vect4us, Vect4i, and Vect4ui.
    */
    template<typename TScalar>
    class Vect4 : public Vector<TScalar, 4>
    {
    public:
        typedef Vector<TScalar, 4> MyBaseType; //<! shortcut to this class inherited class naming.
        typedef Vect4<TScalar>     MyType;     //<! shortcut to this class naming.


        //---   constructors   ----------------------------------------------
        /** \brief Constructor with a filling value (defaults to 0).
        */
        inline Vect4<TScalar>(const TScalar value = TScalar(0))
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        inline Vect4<TScalar>(const MyType& other)
            : MyBaseType()
        {
            copy(other);
        }

        /** \brief Copy constructor (&).
        */
        inline Vect4<TScalar>(MyType& other)
            : MyBaseType()
        {
            copy(other);
        }

        /** \brief Copy constructor (const std::array&).
        */
        inline Vect4<TScalar>(const MyBaseType& other)
            : MyBaseType()
        {
            copy(other);
        }

        /** \brief Copy constructor (std::array&).
        */
        inline Vect4<TScalar>(MyBaseType& other)
            : MyBaseType()
        {
            copy(other);
        }

        /** \brief Copy constructor (const std::vector&).
        */
        inline Vect4<TScalar>(const std::vector<TScalar>& vect)
            : MyBaseType()
        {
            copy(vect);
        }

        /** \brief Copy constructor (std::vector&).
        */
        inline Vect4<TScalar>(std::vector<TScalar>& vect)
            : MyBaseType()
        {
            copy(vect);
        }

        /** \brief Copy Constructor (const buffer).
        */
        inline Vect4<TScalar>(const TScalar buffer[MyBaseType::KSize])
            : MyBaseType()
        {
            copy(buffer);
        }

        /** \brief Copy constructor (buffer).
        */
        inline Vect4<TScalar>(TScalar buffer[MyBaseType::KSize])
            : MyBaseType()
        {
            copy(buffer);
        }

        //---  Destructor   -------------------------------------------------
        virtual inline ~Vect4<TScalar>()
        {}

        //---   Components accessors   --------------------------------------
        /** \brief component x getter */
        inline TScalar x()
        {
            return (*this)[0];
        }

        /** \brief component x getter (const) */
        inline const TScalar x() const
        {
            return (*this)[0];
        }

        /** \brief component x setter */
        inline TScalar x(const TScalar new_x)
        {
            return (*this)[0] = new_x;
        }

        /** \brief component y getter */
        inline TScalar y()
        {
            return (*this)[1];
        }

        /** \brief component y getter (const) */
        inline const TScalar y() const
        {
            return (*this)[1];
        }

        /** \brief component y setter */
        inline TScalar y(const TScalar new_y)
        {
            return (*this)[1] = new_y;
        }

        /** \brief component z getter */
        inline TScalar z()
        {
            return (*this)[2];
        }

        /** \brief component z getter (const) */
        inline const TScalar z() const
        {
            return (*this)[2];
        }

        /** \brief component z setter */
        inline TScalar z(const TScalar new_z)
        {
            return (*this)[2] = new_z;
        }

        /** \brief component w getter (const) */
        inline const TScalar w() const
        {
            return (*this)[3];
        }

        /** \brief component w setter */
        inline TScalar w(const TScalar new_w)
        {
            return (*this)[3] = new_w;
        }

        //---   copy()   ----------------------------------------------------
        /** \brief Copies a const vcl::Vector. */
        virtual inline void copy(const MyType& other)
        {
            x(other.x());
            y(other.y());
            z(other.z());
            w(other.w());
        }

        /** \brief Copies a vcl::Vector. */
        virtual inline void copy(MyType& other)
        {
            x(other.x());
            y(other.y());
            z(other.z());
            w(other.w());
        }

        /** \brief Copies a const std::array. */
        virtual inline void copy(const MyBaseType& other)
        {
            x(other[0]);
            y(other[1]);
            z(other[2]);
            w(other[3]);
        }

        /** \brief Copies an std::array. */
        virtual inline void copy(MyBaseType& other)
        {
            x(other[0]);
            y(other[1]);
            z(other[2]);
            w(other[3]);
        }

        /** \brief Copies a const std::vector. */
        virtual inline void copy(const std::vector<TScalar>& other)
        {
            x(other[0]);
            y(other.size() > 1 ? other[1] : TScalar(0));
            z(other.size() > 2 ? other[2] : TScalar(0));
            w(other.size() > 3 ? other[3] : TScalar(0));
        }

        /** \brief Copies a std::vector. */
        virtual inline void copy(std::vector<TScalar>& other)
        {
            x(other[0]);
            y(other.size() > 1 ? other[1] : TScalar(0));
            z(other.size() > 2 ? other[2] : TScalar(0));
            w(other.size() > 3 ? other[3] : TScalar(0));
        }

        /** \brief Copies a const buffer. */
        virtual inline void copy(const TScalar buffer[2])
        {
            x(buffer[0]);
            y(buffer[1]);
            z(buffer[2]);
            w(buffer[3]);
        }

        /** \brief Copies a buffer. */
        virtual inline void copy(TScalar buffer[2])
        {
            x(buffer[0]);
            y(buffer[1]);
            z(buffer[2]);
            w(buffer[3]);
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
            (*this)[0] += rhs[0];
            (*this)[1] += rhs[1];
            (*this)[2] += rhs[2];
            (*this)[3] += rhs[3];
        }

        /** \brief inplace add operation (reference) */
        virtual inline void add(MyType& rhs)
        {
            (*this)[0] += rhs[0];
            (*this)[1] += rhs[1];
            (*this)[2] += rhs[2];
            (*this)[3] += rhs[3];
        }

        /** \brief inplace add operation (reference) */
        virtual inline void add(const TScalar value)
        {
            (*this)[0] += value;
            (*this)[1] += value;
            (*this)[2] += value;
            (*this)[3] += value;
        }

        /** \brief inplace add operation (const std::array) */
        virtual inline void add(const MyBaseType& rhs)
        {
            (*this)[0] += rhs[0];
            (*this)[1] += rhs[1];
            (*this)[2] += rhs[2];
            (*this)[3] += rhs[3];
        }

        /** \brief inplace add operation (std::array) */
        virtual inline void add(MyBaseType& rhs)
        {
            (*this)[0] += rhs[0];
            (*this)[1] += rhs[1];
            (*this)[2] += rhs[2];
            (*this)[3] += rhs[3];
        }

        /** \brief inplace add operation (const std::vector) */
        virtual inline void add(const std::vector<TScalar>& rhs)
        {
            (*this)[0] += rhs[0];
            if (rhs.size() > 1)
                (*this)[1] += rhs[1];
            if (rhs.size() > 2)
                (*this)[2] += rhs[2];
            if (rhs.size() > 3)
                (*this)[3] += rhs[3];
        }

        /** \brief inplace add operation (std::vector) */
        virtual inline void add(std::vector<TScalar>& rhs)
        {
            (*this)[0] += rhs[0];
            if (rhs.size() > 1)
                (*this)[1] += rhs[1];
            if (rhs.size() > 2)
                (*this)[2] += rhs[2];
            if (rhs.size() > 3)
                (*this)[3] += rhs[3];
        }

        /** \brief inplace add operation (const buffer) */
        virtual inline void add(const TScalar buffer[MyType::MyBaseType::KSize])
        {
            (*this)[0] += buffer[0];
            (*this)[1] += buffer[1];
            (*this)[2] += buffer[2];
            (*this)[3] += buffer[3];
        }

        /** \brief inplace add operation (buffer) */
        virtual inline void add(TScalar buffer[MyBaseType::KSize])
        {
            (*this)[0] += buffer[0];
            (*this)[1] += buffer[1];
            (*this)[2] += buffer[2];
            (*this)[3] += buffer[3];
        }

        //---   sub()   -----------------------------------------------------
        /** \brief inplace sub operation (const reference) */
        virtual inline void sub(const MyType& rhs)
        {
            (*this)[0] -= rhs[0];
            (*this)[1] -= rhs[1];
            (*this)[2] -= rhs[2];
            (*this)[3] -= rhs[3];
        }

        /** \brief inplace sub operation (reference) */
        virtual inline void sub(MyType& rhs)
        {
            (*this)[0] -= rhs[0];
            (*this)[1] -= rhs[1];
            (*this)[2] -= rhs[2];
            (*this)[3] -= rhs[3];
        }

        /** \brief inplace sub operation (reference) */
        virtual inline void sub(const TScalar value)
        {
            (*this)[0] -= value;
            (*this)[1] -= value;
            (*this)[2] -= value;
            (*this)[3] -= value;
        }

        /** \brief inplace sub operation (const std::array) */
        virtual inline void sub(const MyBaseType& rhs)
        {
            (*this)[0] -= rhs[0];
            (*this)[1] -= rhs[1];
            (*this)[2] -= rhs[2];
            (*this)[3] -= rhs[3];
        }

        /** \brief inplace sub operation (std::array) */
        virtual inline void sub(MyBaseType& rhs)
        {
            (*this)[0] -= rhs[0];
            (*this)[1] -= rhs[1];
            (*this)[2] -= rhs[2];
            (*this)[3] -= rhs[3];
        }

        /** \brief inplace sub operation (const std::vector) */
        virtual inline void sub(const std::vector<TScalar>& rhs)
        {
            (*this)[0] -= rhs[0];
            if (rhs.size() > 1)
                (*this)[1] -= rhs[1];
            if (rhs.size() > 2)
                (*this)[2] -= rhs[2];
            if (rhs.size() > 3)
                (*this)[3] -= rhs[3];
        }

        /** \brief inplace sub operation (std::vector) */
        virtual inline void sub(std::vector<TScalar>& rhs)
        {
            (*this)[0] -= rhs[0];
            if (rhs.size() > 1)
                (*this)[1] -= rhs[1];
            if (rhs.size() > 2)
                (*this)[2] -= rhs[2];
            if (rhs.size() > 3)
                (*this)[3] -= rhs[3];
        }

        /** \brief inplace sub operation (const buffer) */
        virtual inline void sub(const TScalar buffer[MyBaseType::KSize])
        {
            (*this)[0] -= buffer[0];
            (*this)[1] -= buffer[1];
            (*this)[2] -= buffer[2];
            (*this)[3] -= buffer[3];
        }

        /** \brief inplace sub operation (buffer) */
        virtual inline void sub(TScalar buffer[MyBaseType::KSize])
        {
            (*this)[0] -= buffer[0];
            (*this)[1] -= buffer[1];
            (*this)[2] -= buffer[2];
            (*this)[3] -= buffer[3];
        }

        //---   mul()   -----------------------------------------------------
        /** \brief inplace mul operation (const reference) */
        virtual inline void mul(const MyType& rhs)
        {
            (*this)[0] *= rhs[0];
            (*this)[1] *= rhs[1];
            (*this)[2] *= rhs[2];
            (*this)[3] *= rhs[3];
        }

        /** \brief inplace mul operation (reference) */
        virtual inline void mul(MyType& rhs)
        {
            (*this)[0] *= rhs[0];
            (*this)[1] *= rhs[1];
            (*this)[2] *= rhs[2];
            (*this)[3] *= rhs[3];
        }

        /** \brief inplace mul operation (reference) */
        virtual inline void mul(const TScalar value)
        {
            (*this)[0] *= value;
            (*this)[1] *= value;
            (*this)[2] *= value;
            (*this)[3] *= value;
        }

        /** \brief inplace mul operation (const std::array) */
        virtual inline void mul(const MyBaseType& rhs)
        {
            (*this)[0] *= rhs[0];
            (*this)[1] *= rhs[1];
            (*this)[2] *= rhs[2];
            (*this)[3] *= rhs[3];
        }

        /** \brief inplace mul operation (std::array) */
        virtual inline void mul(MyBaseType& rhs)
        {
            (*this)[0] *= rhs[0];
            (*this)[1] *= rhs[1];
            (*this)[2] *= rhs[2];
            (*this)[3] *= rhs[3];
        }

        /** \brief inplace mul operation (const std::vector) */
        virtual inline void mul(const std::vector<TScalar>& rhs)
        {
            (*this)[0] *= rhs[0];
            if (rhs.size() > 1)
                (*this)[1] *= rhs[1];
            if (rhs.size() > 2)
                (*this)[2] *= rhs[2];
            if (rhs.size() > 3)
                (*this)[3] *= rhs[3];
        }

        /** \brief inplace mul operation (std::vector) */
        virtual inline void mul(std::vector<TScalar>& rhs)
        {
            (*this)[0] *= rhs[0];
            if (rhs.size() > 1)
                (*this)[1] *= rhs[1];
            if (rhs.size() > 2)
                (*this)[2] *= rhs[2];
            if (rhs.size() > 3)
                (*this)[3] *= rhs[3];
        }

        /** \brief inplace mul operation (const buffer) */
        virtual inline void mul(const TScalar buffer[MyBaseType::KSize])
        {
            (*this)[0] *= buffer[0];
            (*this)[1] *= buffer[1];
            (*this)[2] *= buffer[2];
            (*this)[3] *= buffer[3];
        }

        /** \brief inplace mul operation (buffer) */
        virtual inline void mul(TScalar buffer[MyBaseType::KSize])
        {
            (*this)[0] *= buffer[0];
            (*this)[1] *= buffer[1];
            (*this)[2] *= buffer[2];
            (*this)[3] *= buffer[3];
        }

        //---   div()   -----------------------------------------------------
        /** \brief inplace div operation (const reference) */
        virtual inline void div(const MyType& rhs)
        {
            if (rhs[0] != TScalar(0))
                (*this)[0] /= rhs[0];
            if (rhs[1] != TScalar(0))
                (*this)[1] /= rhs[1];
            if (rhs[2] != TScalar(0))
                (*this)[2] /= rhs[2];
            if (rhs[3] != TScalar(0))
                (*this)[3] /= rhs[3];
        }

        /** \brief inplace div operation (reference) */
        virtual inline void div(MyType& rhs)
        {
            if (rhs[0] != TScalar(0))
                (*this)[0] /= rhs[0];
            if (rhs[1] != TScalar(0))
                (*this)[1] /= rhs[1];
            if (rhs[2] != TScalar(0))
                (*this)[2] /= rhs[2];
            if (rhs[3] != TScalar(0))
                (*this)[3] /= rhs[3];
        }

        /** \brief inplace div operation (reference) */
        virtual inline void div(const TScalar value)
        {
            if (value != TScalar(0)) {
                (*this)[0] /= value;
                (*this)[1] /= value;
                (*this)[2] /= value;
                (*this)[3] /= value;
            }
        }

        /** \brief inplace div operation (const std::array) */
        virtual inline void div(const MyBaseType& rhs)
        {
            if (rhs[0] != TScalar(0))
                (*this)[0] /= rhs[0];
            if (rhs[1] != TScalar(0))
                (*this)[1] /= rhs[1];
            if (rhs[2] != TScalar(0))
                (*this)[2] /= rhs[2];
            if (rhs[3] != TScalar(0))
                (*this)[3] /= rhs[3];
        }

        /** \brief inplace div operation (std::array) */
        virtual inline void div(MyBaseType& rhs)
        {
            if (rhs[0] != TScalar(0))
                (*this)[0] /= rhs[0];
            if (rhs[1] != TScalar(0))
                (*this)[1] /= rhs[1];
            if (rhs[2] != TScalar(0))
                (*this)[2] /= rhs[2];
            if (rhs[3] != TScalar(0))
                (*this)[3] /= rhs[3];
        }

        /** \brief inplace div operation (const std::vector) */
        virtual inline void div(const std::vector<TScalar>& rhs)
        {
            if (rhs[0] != TScalar(0))
                (*this)[0] /= rhs[0];
            if (rhs.size() > 1 && rhs[1] != TScalar(0))
                (*this)[1] /= rhs[1];
            if (rhs.size() > 2 && rhs[2] != TScalar(0))
                (*this)[2] /= rhs[2];
            if (rhs.size() > 2 && rhs[3] != TScalar(0))
                (*this)[3] /= rhs[3];
        }

        /** \brief inplace div operation (std::vector) */
        virtual inline void div(std::vector<TScalar>& rhs)
        {
            if (rhs[0] != TScalar(0))
                (*this)[0] /= rhs[0];
            if (rhs.size() > 1 && rhs[1] != TScalar(0))
                (*this)[1] /= rhs[1];
            if (rhs.size() > 2 && rhs[2] != TScalar(0))
                (*this)[2] /= rhs[2];
            if (rhs.size() > 2 && rhs[3] != TScalar(0))
                (*this)[3] /= rhs[3];
        }

        /** \brief inplace div operation (const buffer) */
        virtual inline void div(const TScalar buffer[MyBaseType::KSize])
        {
            if (buffer[0] != TScalar(0))
                (*this)[0] /= buffer[0];
            if (buffer[1] != TScalar(0))
                (*this)[1] /= buffer[1];
            if (buffer[2] != TScalar(0))
                (*this)[2] /= buffer[2];
            if (buffer[3] != TScalar(0))
                (*this)[3] /= buffer[3];
        }

        /** \brief inplace div operation (buffer) */
        virtual inline void div(TScalar buffer[MyBaseType::KSize])
        {
            if (buffer[0] != TScalar(0))
                (*this)[0] /= buffer[0];
            if (buffer[1] != TScalar(0))
                (*this)[1] /= buffer[1];
            if (buffer[2] != TScalar(0))
                (*this)[2] /= buffer[2];
            if (buffer[3] != TScalar(0))
                (*this)[3] /= buffer[3];
        }

    };


    /** \brief The class of 4D vectors with double components (64 bits). */
    typedef Vect4<double> Vect4d;


    /** \brief The class of 4D vectors with float components (32 bits). */
    typedef Vect4<float> Vect4f;


    /** \brief The class of 4D vectors with bytes components (8 bits). */
    typedef Vect4<unsigned char> Vect4b;


    /** \brief The class of 4D vectors with short components (16 bits). */
    typedef Vect4<short> Vect4s;


    /** \brief The class of 4D vectors with unsigned short components (16 bits). */
    typedef Vect4<unsigned short> Vect4us;


    /** \brief The class of 4D vectors with int components (32 bits). */
    typedef Vect4<int> Vect4i;


    /** \brief The class of 4D vectors with unsigned int components (32 bits). */
    typedef Vect4<unsigned int> Vect4ui;

} // end of namespace vcl
