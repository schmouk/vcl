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

#include "utils/vect2.h"


//===========================================================================
namespace vcl {

    //-----------------------------------------------------------------------
    /** \brief the generic class for 2-D clipped vectors.
    *
    * \sa its specializations ClipVect2d, ClipVect2f, ClipVect2b, ClipVect2s, ClipVect2us, ClipVect2i, and ClipVect2ui.
    */
    template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
    class ClipVect2 : public Vect2<TScalar>
    {
    public:
        typedef Vect2<TScalar>                 MyBaseType; //<! shortcut to this class inherited class naming.
        typedef ClipVect2<TScalar, Kmin, Kmax> MyType;     //<! shortcut to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Constructor with a filling value (defaults to 0).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(const TScalar value = TScalar(0))
            : MyBaseType(value <= Kmin ? Kmin : (value >= Kmax ? Kmax : value))
        {}

        /** \brief Copy constructor (const&).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (&).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::Vect2&).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(const MyBaseType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (vcl::Vect2&).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(MyBaseType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(const std::array<TScalar,2>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (std::array&).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(std::array<TScalar,2>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(const std::vector<TScalar>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Copy constructor (std::vector&).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(std::vector<TScalar>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Copy Constructor (const buffer).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(const TScalar buffer[MyBaseType::KSize])
            : MyBaseType(buffer)
        {
            //MyBaseType::copy(buffer);
        }

        /** \brief Copy constructor (buffer).
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(TScalar buffer[MyBaseType::KSize])
            : MyBaseType(buffer)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2<TScalar, Kmin, Kmax>()
        {}

        //---   Components accessors   --------------------------------------
        /** \brief clips value within valid range */
        inline const TScalar clip_value(const TScalar value) const
        {
            return TScalar(value <= Kmin ? Kmin : (value >= Kmax ? Kmax : value));
        }

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
            return (*this)[0] = clip_value(new_x);
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
            return (*this)[1] = clip_value(new_y);
        }

    };


    /** \brief The class of 2D vectors with double components (64 bits). */
    typedef ClipVect2<double, double(0.0), double(1.0)> ClipVect2d;


    /** \brief The class of 2D vectors with float components (32 bits). */
    typedef ClipVect2<float, float(0.0), float(1.0)> ClipVect2f;


    /** \brief The class of 2D vectors with bytes components (8 bits). */
    typedef ClipVect2<unsigned char, 0, 255> ClipVect2b;


    /** \brief The class of 2D vectors with short components (16 bits). */
    typedef ClipVect2<short, short(-32767), short(32767)> ClipVect2s;


    /** \brief The class of 2D vectors with unsigned short components (16 bits). */
    typedef ClipVect2<unsigned short, 0, 65535> ClipVect2us;


    /** \brief The class of 2D vectors with int components (32 bits). */
    typedef ClipVect2<int, int(-2147483647), int(2147483647)> ClipVect2i;


    /** \brief The class of 2D vectors with unsigned int components (32 bits). */
    typedef ClipVect2<unsigned int, 0, 4294967295> ClipVect2ui;

} // end of namespace vcl
