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

#include <opencv2/core/types.hpp>
#include "vcl_concepts.h"

export module utils.dims;

import vectors.vect2;


//===========================================================================
namespace vcl::utils {

    //=======================================================================
    // Forward declaration
    export template<typename TScalar>
        requires vcl::concepts::is_numeric<TScalar>
    class DimsT;

    // Specializations
    /** \brief The class of 2D dimensions with unsigned short components (16 bits). */
    export using Dims_us = DimsT<unsigned short>;

    /** \brief The class of 2D dimensions with unsigned long int components (32 bits). */
    export using Dims_ui = DimsT<unsigned long>;

    /** \brief The class of 2D dimensions with unsigned long long components (32 bits). */
    export using Dims_uli = DimsT<unsigned long long>;

    /** \brief The class of 2D dimensions with float components (64 bits). */
    export using Dims_f = DimsT<float>;

    /** \brief The class of 2D dimensions with double components (64 bits). */
    export using Dims_d = DimsT<double>;

    /** \brief The class of 2D dimensions with long double components (128 bits). */
    export using Dims_ld = DimsT<long double>;


    //=======================================================================
    /** \brief The generic class for 2D dimensions.
    *
    * Notice: vcl::utils::Size does not inherit from cv::Size,  but rather
    * inherits from vcl::vect::Vect2<>.  This way, vcl::utils::Size  gets
    * more functionalities than cv::Size. Casting constructor and operator 
    * exist nevertheless.
    */
    template<typename TScalar>
        requires vcl::concepts::is_numeric<TScalar>
    class DimsT : public vcl::vect::Vect2<TScalar>
    {
    public:
        typedef vcl::vect::Vect2<TScalar>  MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::utils::DimsT<TScalar> MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline DimsT<TScalar>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline DimsT<TScalar>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename W, typename H>
            requires vcl::concepts::is_numeric<W>&& vcl::concepts::is_numeric<H>
        inline DimsT<TScalar>(const W width, const H height)
            : MyBaseType(width, height)
        {}

        /** \brief Copy constructor (const&).
        */
        inline DimsT<TScalar>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline DimsT<TScalar>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (vcl::vect::Vector&&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline DimsT<TScalar>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline DimsT<TScalar>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline DimsT<TScalar>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Copy constructor (const cv::Size_&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline DimsT<TScalar>(const cv::Size_<T>& sz)
            : MyBaseType(TScalar(sz.width), TScalar(sz.height))
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~DimsT<TScalar>()
        {}

        //---   Casting operator   --------------------------------------
        /** \brief cast operator to cv::Size_<_Tp> */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline operator cv::Size_<T>& ()
        {
            return cv::Size_<T>(T(this->width()), T(this->height()));
        }

        //---  Accessors/Mutators   -----------------------------------------
        /** \brief component width accessor */
        inline const TScalar width() const
        {
            return (*this)[0];
        }

        /** \brief component width mutator */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline TScalar width(const T new_width)
        {
            return (*this)[0] = new_width;
        }

        /** \brief component height accessor */
        inline const TScalar height() const
        {
            return (*this)[1];
        }

        /** \brief component height mutator */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline TScalar height(const T new_height)
        {
            return (*this)[1] = new_height;
        }

        //---  Miscelaneous   ----------------------------------------------
        /** \brief returns the area related to the dimensions */
        inline const TScalar area() const
        {
            return width() * height();  // CAUTION: may overfloaw
        }

        /** \brief returns the ratio of width / height */
        inline const double ratio_wh() const
        {
            return double(width()) / double(height());
        }

        //---  Comparison operators   --------------------------------------
        /** \brief operator == */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline bool operator== (const vcl::utils::DimsT<T>& other)
        {
            return width() == other.width() && height() == other.height();
        }

        /** \brief operator != */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline bool operator!= (const vcl::utils::DimsT<T>& other)
        {
            return !(*this == other);
        }

        /** \brief operator < */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline bool operator< (const vcl::utils::DimsT<T>& other)
        {
            return area() < other.area();
        }

        /** \brief operator <= */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline bool operator<= (const vcl::utils::DimsT<T>& other)
        {
            return *this < other || *this == other;
        }

        /** \brief operator > */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline bool operator> (const vcl::utils::DimsT<T>& other)
        {
            return area() > other.area();
        }

        /** \brief operator >= */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline bool operator>= (const vcl::utils::DimsT<T>& other)
        {
            return area() >= other.area();
        }
    };

}
