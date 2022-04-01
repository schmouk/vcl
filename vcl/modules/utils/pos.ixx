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
module;

#include <limits>
#include <opencv2/core/types.hpp>
#include "vcl_concepts.h"

export module utils.pos;

import vectors.clipvect2;


//===========================================================================
namespace vcl::utils {

    //===================================================================
    /** \brief class PosT: the generic class for 2-D clipped positions. */
    export template<typename TScalar,
                    const TScalar Kmin = std::numeric_limits<TScalar>::min,
                    const TScalar Kmax = std::numeric_limits<TScalar>::max> 
        requires vcl::concepts::is_numeric<TScalar>
    class PosT;

    // Specializations
    /** \brief The class of 2D positions with short components (16 bits). */
    export using Pos_s = PosT<short, -32768, 32767>;

    /** \brief The class of 2D positions with unsigned short components (16 bits). */
    export using Pos_us = PosT<unsigned short, 0, 65535>;

    /** \brief The class of 2D positions with long int components (32 bits). */
    export using Pos_i = PosT<long, -2147483648, 2147483647>;

    /** \brief The class of 2D positions with unsigned long int components (32 bits). */
    export using Pos_ui = PosT<unsigned long, 0, 4294967295>;

    /** \brief The class of 2D positions with float components (32 bits). */
    export using Pos_f = PosT<float, 0.0f, 1.0f>;

    /** \brief The class of 2D positions with double components (64 bits). */
    export using Pos_d = PosT<double, 0.0, 1.0>;


    //===================================================================
    /** \brief The templated class of 2D positions.
    *
    * Notice: vcl::utils::PosT does not inherit from cv::Point,  but rather
    * inherits from vcl::vect::Vect2<>.  This  way,  vcl::utils::PosT  gets
    * more functionalities than cv::Point. Casting constructor and operator 
    * exist nevertheless.
    */
    template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
        requires vcl::concepts::is_numeric<TScalar>
    class PosT : public vcl::vect::ClipVect2<TScalar, Kmin, Kmax>
    {
    public:
        typedef vcl::vect::ClipVect2<TScalar, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::utils::PosT<TScalar, Kmin, Kmax>     MyType;     //!< wrapper to this class naming.


        //---   constructors   ------------------------------------------
        /** \brief Empty constructor.
        */
        inline PosT<TScalar, Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline PosT<TScalar, Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline PosT<TScalar, Kmin, Kmax>(const T x, const U y)
            : MyBaseType(x, y)
        {}

        /** \brief Copy constructor (const&).
        */
        inline PosT<TScalar, Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline PosT<TScalar, Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (vcl::vect::Vector&&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline PosT<TScalar, Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline PosT<TScalar, Kmin, Kmax>(const std::array<T, S>& arr)
            : MyBaseType(arr)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline PosT<TScalar, Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Copy constructor (const cv::Point_&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline PosT<TScalar, Kmin, Kmax>(const cv::Point_<T>& pt)
            : MyBaseType(TScalar(pt.x), TScalar(pt.y))
        {}

        //---  Destructor   ---------------------------------------------
        virtual inline ~PosT<TScalar, Kmin, Kmax>()
        {}

        //---   Casting operator   --------------------------------------
        /** \brief cast operator to cv::Point_<_Tp> */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline operator cv::Point_<T>& ()
        {
            return cv::Point_<T>(T(this->x()), T(this->y()));
        }

        //---   origin   ------------------------------------------------
        /* \brief returns the origin position (short).
        */
        static inline MyType origin()
        {
            return MyType();
        }
    };

}