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

#include <array>
#include <type_traits>
#include <utility>
#include <vector>

#include <opencv2/core/types.hpp>

export module utils.dims;

import vectors.vect2;


//===========================================================================
namespace vcl::utils {

    //=======================================================================
    // Forward declaration
    export template<typename TScalar>
        requires std::is_arithmetic_v<TScalar>
    class DimsT;

    // Specializations
    /** \brief The class of 2D dimensions with unsigned char components (8 bits). */
    export using Dims_b = DimsT<unsigned char>;

    /** \brief The class of 2D dimensions with unsigned short components (16 bits). */
    export using Dims_us = DimsT<unsigned short>;
    export using Dims = Dims_us;

    /** \brief The class of 2D dimensions with unsigned long int components (32 bits). */
    export using Dims_ui = DimsT<unsigned long>;

    /** \brief The class of 2D dimensions with unsigned long long components (32 bits). */
    export using Dims_ull = DimsT<unsigned long long>;

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
        requires std::is_arithmetic_v<TScalar>
    class DimsT : public vcl::vect::Vect2T<TScalar>
    {
    public:
        using MyBaseType = vcl::vect::Vect2T<TScalar> ; //!< wrapper to the inherited class naming.
        using MyType     = vcl::utils::DimsT<TScalar>; //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline DimsT<TScalar>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline DimsT<TScalar>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename W, typename H>
            requires std::is_arithmetic_v<W>&& std::is_arithmetic_v<H>
        inline DimsT<TScalar>(const W width, const H height)
            : MyBaseType(width, height)
        {}

        /** \brief Copy constructor (const&).
        */
        inline DimsT<TScalar>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::VectorT&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline DimsT<TScalar>(const vcl::vect::VectorT<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (vcl::vect::VectorT&&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline DimsT<TScalar>(vcl::vect::VectorT<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline DimsT<TScalar>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline DimsT<TScalar>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::pair&).
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline DimsT<TScalar>(const std::pair<T, U>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const cv::Size_&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline DimsT<TScalar>(const cv::Size_<T>& sz)
            : MyBaseType(TScalar(sz.width), TScalar(sz.height))
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~DimsT<TScalar>()
        {}

        //---   Casting operator   --------------------------------------
        /** \brief cast operator to cv::Size_<_Tp> */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline operator cv::Size_<T>& ()
        {
            return cv::Size_<T>(T(this->width()), T(this->height()));
        }

        //---  Accessors/Mutators   -----------------------------------------
        /** \brief component width accessor */
        inline TScalar& width()
        {
            return (*this)[0];
        }

        /** \brief component width accessor */
        inline const TScalar& width() const
        {
            return (*this)[0];
        }

        /** \brief component width mutator */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline TScalar width(const T new_width)
        {
            TScalar w;
            if (new_width <= std::numeric_limits<TScalar>::min())
                w = std::numeric_limits<TScalar>::min();
            else if (new_width >= std::numeric_limits<TScalar>::max())
                w = std::numeric_limits<TScalar>::max();
            else
                w = TScalar(new_width);
            return (*this)[0] = w;
        }

        /** \brief component height accessor */
        inline TScalar& height()
        {
            return (*this)[1];
        }

        /** \brief component height accessor */
        inline const TScalar& height() const
        {
            return (*this)[1];
        }

        /** \brief component height mutator */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline TScalar height(const T new_height)
        {
            TScalar h;
            if (new_height <= std::numeric_limits<TScalar>::min())
                h = std::numeric_limits<TScalar>::min();
            else if (new_height >= std::numeric_limits<TScalar>::max())
                h = std::numeric_limits<TScalar>::max();
            else
                h = TScalar(new_height);
            return (*this)[1] = h;
        }

        //---  Miscelaneous   ----------------------------------------------
        /** \brief returns the area related to the dimensions */
        inline const TScalar area() const
        {
            return width() * height();  // CAUTION: may overfloaw
        }

        /** \brief returns the ratio of width / height */
        inline const double ratio_wh() const throw()
        {
            return double(width()) / double(height());  // CAUTION: may throw division by 0
        }

        //---  Comparison operators   --------------------------------------
        /** \brief operator == */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline bool operator== (const vcl::utils::DimsT<T>& other)
        {
            return width() == other.width() && height() == other.height();
        }

        /** \brief operator != */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline bool operator!= (const vcl::utils::DimsT<T>& other)
        {
            return !(*this == other);
        }

        /** \brief operator < */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline bool operator< (const vcl::utils::DimsT<T>& other)
        {
            return area() < other.area();
        }

        /** \brief operator <= */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline bool operator<= (const vcl::utils::DimsT<T>& other)
        {
            return area() <= other.area();
        }

        /** \brief operator > */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline bool operator> (const vcl::utils::DimsT<T>& other)
        {
            return area() > other.area();
        }

        /** \brief operator >= */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline bool operator>= (const vcl::utils::DimsT<T>& other)
        {
            return area() >= other.area();
        }
    };

}
