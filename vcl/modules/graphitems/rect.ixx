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
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include <opencv2/core/types.hpp> // to get access to cv::Rect_<_Tp> and cv::Point_<_Tp>
#include <opencv2/core/mat.hpp>   // to get access to cv::Mat (i.e. image container)
#include <opencv2/imgproc.hpp>    // to get access to OpenCV drawing functions

#include "vcl_concepts.h"

export module graphitems.rect;

import utils.base_funcs;
import utils.colors;
import utils.dims;
import utils.offsets;
import utils.pos;
import vectors.vect2;
import vectors.vect4;


//===========================================================================
namespace vcl::graphitems {

    //===================================================================
    /** \brief class RectT: the generic class for 2-D rectangles. */
    export template<typename TScalar>
        requires vcl::concepts::is_numeric<TScalar>
    class RectT;

    // Specializations
    /** \brief The class of rectangles with integer positions and dimensions (32 bits). */
    export typedef RectT<long> Rect;

    /** \brief The class of rectangles with float components (32 bits). */
    export typedef RectT<float> Rect_f;

    /** \brief The class of rectangles with double components (64 bits). */
    export typedef RectT<double> Rect_d;


    //=======================================================================
    /** \brief The generic class for rectangles.
    * 
    * Notice: this template class in vcl inherits from  the  OpenCV  class
    *   Rect_<_Tp>.  Meanwhile, it exposes a rather different API. Mostly:
    *   the origin of the plane is at top-left corner of screen,  while in
    *   openCV it is positionned at bottom-left corner. This means that in
    *   vcl, y_top coordinate gets a lower value than y_bottom coordinate.
    *   In OpenCV, the related values are inverted.
    * 
    * Since vcl::graphitems::Rect inherits from class  cv::Rect_,  it gets
    * access  to  attributes  '.x' (left x),  '.y' (top y),  '.width'  and
    * '.height' as well as to methods '.area()', '.size()' and '.empty()'.
    */
    template<typename TScalar>
        requires vcl::concepts::is_numeric<TScalar>
    class RectT : public cv::Rect_<TScalar>
    {
    public:
        typedef cv::Rect_<TScalar>              MyBaseType; //!< wrapper to the inherited cv::Rect_ class naming.
        typedef vcl::graphitems::RectT<TScalar> MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline RectT<TScalar>()
            : MyBaseType()
        {}

        /** \brief Copy constructor (const&).
        */
        inline RectT<TScalar>(const MyType& other)
            : MyBaseType(other.x, other.y, other.width, other.height)
        {}

        /** \brief Move constructor (&&).
        */
        inline RectT<TScalar>(MyType&& other)
            : MyBaseType(&other.x, &other.y, &other.width, &other.height)
        {}

        /** \brief Constructor (4-D vcl::vector positions).
        * Notice: order of coordinates in vector: left, right, top, bottom.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const vcl::vect::Vect4<T>& vect)
            : MyBaseType(TScalar(vect[0]),
                         TScalar(vect[2]),
                         TScalar(vect[1] - vect[0] + 1),
                         TScalar(vect[3] - vect[2] + 1))
        {}

        /** \brief Copy constructor (const std::array&).
        * Notice: order of coordinates in vector: left, right, top, bottom.
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const std::array<T, S>& arr)
            : MyBaseType(vcl::vect::Vect4<T>(arr))
        {}

        /** \brief Copy constructor (const std::vector&).
        * Notice: order of coordinates in vector: left, right, top, bottom.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const std::vector<T>& vect)
            : MyBaseType(vcl::vect::Vect4<T>(vect))
        {}

        /** \brief Constructor (4 scalar positions & dimensions).
        */
        template<typename T, typename U, typename V, typename W>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U> && vcl::concepts::is_numeric<V> && vcl::concepts::is_numeric<W>
        inline RectT<TScalar>(const T left_x, const U right_x, const V top_y, const W bottom_y)
            : MyBaseType(left_x, top_y, right_x - left_x + 1, bottom_y - top_y + 1)
        {}

        /** \brief Constructor (2 scalar positions + dimensions).
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U> && vcl::concepts::is_numeric<V>
        inline RectT<TScalar>(const T left_x, const U top_y, const vcl::utils::DimsT<V>& dims)
            : MyBaseType(left_x, top_y, dims.width, dims.height)
        {}

        /** \brief Constructor (top left position + dimensions).
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline RectT<TScalar>(const vcl::utils::PosT<T>& top_left,
                              const vcl::utils::DimsT<U>& dims)
            : MyBaseType(top_left.x, top_left.y, dims.width, dims.height)
        {}

        /** \brief Constructor (2 opposite corners positions).
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline RectT<TScalar>(const vcl::utils::PosT<T>& top_left,
                              const vcl::utils::PosT<U>& bottom_right)
            : MyBaseType(top_left.x, top_left.y, bottom_right.x - top_left.x + 1, bottom_right.y - top_left.y + 1)
        {}

        /** \brief Constructor (top left position + width + height).
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U> && vcl::concepts::is_numeric<V>
        inline RectT<TScalar>(const vcl::utils::PosT<T>& top_left,
                              const U width, const V height)
            : MyBaseType(top_left.x, top_left.y, width, height)
        {}


        //---  Destructor   -------------------------------------------------
        virtual inline ~RectT<TScalar>()
        {}


        //--- Comparisons ---------------------------------------------------
        /** \brief Equality between rectangles. */
        inline const bool operator==(MyType& other) const
        {
            return MyBaseType::x == other.x && MyBaseType::y == other.y && MyBaseType::width == other.width && MyBaseType::height == other.height;
        }

        /** \brief Inequality between rectangles. */
        inline const bool operator != (MyType& other) const
        {
            return !(*this == other);
        }


        //--- Accessors / Mutators ------------------------------------------
        /** \brief left side position accessor. */
        inline const TScalar left_x() const noexcept
        {
            return MyBaseType::x;
        }
        /** \brief left side position mutator. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void left_x(const T& new_x) noexcept
        {
            MyBaseType::x = TScalar(new_x);
        }

        /** \brief right side position accessor. */
        inline const TScalar right_x() const noexcept
        {
            return MyBaseType::x + MyBaseType::width - 1;
        }
        /** \brief right side position mutator. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void right_x(const T& new_x) noexcept
        {
            if (new_x >= MyBaseType::x)
                MyBaseType::width = TScalar(new_x) - MyBaseType::x + 1;
            else
                MyBaseType::width = 0;
        }

        /** \brief top side position accessor. */
        inline const TScalar top_y() const noexcept
        {
            return MyBaseType::y;
        }
        /** \brief top side position mutator. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void top_y(const T& new_y) noexcept
        {
            MyBaseType::y = TScalar(new_y);
        }

        /** \brief bottom side position accessor. */
        inline const TScalar bottom_y() const noexcept
        {
            return MyBaseType::y + MyBaseType::height - 1;
        }
        /** \brief bottom side position mutator. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void bottom_y(const T& new_y) noexcept
        {
            if (new_y >= MyBaseType::y)
                MyBaseType::height = TScalar(new_y) - MyBaseType::y + 1;
            else
                MyBaseType::height = 0;
        }

        /** \brief top-left accessor. */
        inline vcl::utils::PosT<TScalar> top_left() const noexcept
        {
            return vcl::utils::PosT<TScalar>(MyBaseType::x, MyBaseType::y);
        }

        /** \brief top-left mutator. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void top_left(const vcl::utils::PosT<T>& new_pos) noexcept
        {
            MyBaseType::x = TScalar(new_pos.x());
            MyBaseType::y = TScalar(new_pos.y());
        }

        /** \brief bottom-right accessor. */
        inline vcl::utils::PosT<TScalar> bottom_right() const noexcept
        {
            return vcl::utils::PosT<TScalar>(MyBaseType::x + MyBaseType::width - 1, MyBaseType::y + MyBaseType::height - 1);
        }
        /** \brief bottom-right mutator. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void bottom_right(const vcl::utils::PosT<T>& new_pos) noexcept
        {
            right_x(new_pos.x());
            bottom_y(new_pos.y());
        }

        /** \brief center accessor. */
        inline vcl::utils::PosT<TScalar> center()
        {
            return vcl::utils::PosT<TScalar>(MyBaseType::x + MyBaseType::width  / 2,
                                             MyBaseType::y + MyBaseType::height / 2 );
        }

        /** \brief Dimensions accessor. */
        inline vcl::utils::DimsT<TScalar>& dims()
        {
            return vcl::utils::DimsT<TScalar>(this->width, this->height);
        }
        /** \brief Dimensions mutator. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void dims(const vcl::utils::DimsT<T>& new_dims)
        {
            this->width = new_dims.width;
            this->height = new_dims.height;
        }


        //--- Casting operators ---------------------------------------------
        /** \brief casting operator to vcl::utils::DimsT<T>.
        * Returns the dimensions of this rectangle.
        */
        template<typename T = MYType::TScalar>
            requires vcl::concepts::is_numeric<T>
        inline operator vcl::utils::DimsT<T>()
        {
            return vcl::utils::DimsT<T>(this->width, this->height);
        }

        /** \brief casting operator to vcl::utils::PosT<T>.
        * Returns the top-left corner position of this rectangle.
        */
        template<typename T = MYType::TScalar>
            requires vcl::concepts::is_numeric<T>
        inline operator vcl::utils::PosT<T>()
        {
            return vcl::utils::PosT<T>(this->x, this->y);
        }


        //--- In place cropping ---------------------------------------------
        /** In-place cropping with 4 different margins. */
        template<typename T, typename U, typename V, typename W>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U> && vcl::concepts::is_numeric<V> && vcl::concepts::is_numeric<W>
        inline MyType& crop(const T& left_margin, const U& right_margin, const V& top_margin, const W& bottom_margin) noexcept
        {
            move(left_margin, top_margin);
            return resize(-left_margin - right_margin, -top_margin - bottom_margin);
        }

        /** In-place cropping with X- and Y- margins. */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline MyType& crop(const T& x_margins, const U& y_margins) noexcept
        {
            return crop(x_margins, x_margins, y_margins, y_margins);
        }

        /** In-place croppping with all same margins. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& crop(const T& all_margins) noexcept
        {
            return crop(all_margins, all_margins, all_margins, all_margins);
        }


        //--- Moving --------------------------------------------------------


        //--- Resizing ------------------------------------------------------
        /** \brief Resizes this rectangle (1 scalar parameter).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& resize(const T& incr) noexcept
        {
            return resize(incr, incr);
        }

        /** \brief Resizes this rectangle (2 scalar arguments).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline MyType& resize(const T& incr_x, const U& incr_y) noexcept
        {
            this->width += TScalar(incr_x);
            this->height += TScalar(incr_y);
            return *this;
        }

        /** \brief Resizes this rectangle (1 Dims argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& resize(const vcl::utils::DimsT<T>& incr) noexcept
        {
            return resize(incr.width, incr.height);
        }

        /** \brief Resizes this rectangle (1 vcl::vectors::Vect2<> argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& resize(const vcl::vect::Vect2<T>& incr) noexcept
        {
            return resize(incr.x, incr.y);
        }

        /** \brief Resizes this rectangle (1 std::vector argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& resize(const std::vector<T>& incr) noexcept
        {
            if (incr.size() > 1)
                return resize(incr[0], incr[1]);
            else
                return resize(incr[0], incr[0]);
        }

        /** \brief Resizes this rectangle (1 std::array argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T, const size_t Ksize>
            requires vcl::concepts::is_numeric<T>
        inline MyType& resize(const std::array<T, Ksize>& incr) noexcept
        {
            if (Ksize > 1)
                return resize(incr[0], incr[1]);
            else
                return resize(incr[0], incr[0]);
        }

        /** \brief Resizes this rectangle according to an 'other' rectangle dimensions. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& resize(const vcl::graphitems::RectT<T>& other) noexcept
        {
            this->width = other.width;
            this->height = other.height;
            return *this;
        }


        //--- Scaling -------------------------------------------------------
        /** \brief Resizes this rectangle according to a scaling factor.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& scale(const T& factor)
        {
            return scale(factor, factor);
        }

        /** \brief Resizes this rectangle according to two scaling factors.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values raise an invalid_argument exception.
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        MyType& scale(const T& factor_x, const U& factor_y)
        {
            if (factor_x < T(0) || factor_y < T(0))
                throw std::invalid_argument("scaling factors cannot be negative");
            else
            {
                this->width = TScalar(this->width * factor_x);
                this->height = TScalar(this->height * factor_y);
            }
            return *this;
        }

        /** \brief Resizes this rectangle according to a scaling factor.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator *= (const T& factor)
        {
            return scale(factor, factor);
        }

        /** \brief Resizes this rectangle according to scaling factors.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T, const size_t Ksize>
            requires vcl::concepts::is_numeric<T>
        MyType& operator *= (const vcl::vect::Vector<T, Ksize>& vect)
        {
            switch (Ksize)
            {
            case 0:
                throw std::invalid_argument("factors vectors cannot be empty");
                return *this;
            case 1:
                return scale(vect[0], vect[0]);
            default:
                return scale(vect[0], vect[1]);
            }
        }

        /** \brief Resizes this rectangle according to scaling factors.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        MyType& operator *= (const std::vector<T>& vect)
        {
            switch (vect.size())
            {
            case 0:
                throw std::invalid_argument("factors vectors cannot be empty");
                return *this;
            case 1:
                return scale(vect[0], vect[0]);
            default:
                return scale(vect[0], vect[1]);
            }
        }

        /** \brief Resizes this rectangle according to scaling factors.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T, const size_t Ksize>
            requires vcl::concepts::is_numeric<T>
        MyType& operator *= (const std::array<T, Ksize>& arr)
        {
            switch (Ksize)
            {
            case 0:
                throw std::invalid_argument("factors vectors cannot be empty");
                return *this;
            case 1:
                return scale(arr[0], arr[0]);
            default:
                return scale(arr[0], arr[1]);
            }
        }

        /** \brief Resizing operator * (const TScalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator * (MyType lhs, const T value)
        {
            return lhs *= value;
        }

        /** \brief Resizing operator * (const TScalar, vcl::graphitems::RectT<>) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator * (const T value, MyType rhs)
        {
            return rhs *= value;
        }

        /** \brief Resizing operator * (const vcl::vect::Vector<>) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator * (MyType lhs, const vcl::vect::Vector<T, S>& vect)
        {
            return lhs *= vect;
        }

        /** \brief Resizing operator * (const vcl::vect::Vector<>, vcl::graphitems::RectT<>) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator * (const vcl::vect::Vector<T, S>& vect, MyType rhs)
        {
            return rhs *= vect;
        }

        /** \brief Resizing operator * (const std::vector<>) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator * (MyType lhs, const std::vector<T>& vect)
        {
            return lhs *= vect;
        }

        /** \brief Resizing operator * (const std::vector<>, vcl::graphitems::RectT<>) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator * (const std::vector<T>& vect, MyType rhs)
        {
            return rhs *= vect;
        }

        /** \brief Resizing operator * (const std::array<>) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator * (MyType lhs, const std::array<T, S>& arr)
        {
            return lhs *= arr;
        }

        /** \brief Resizing operator * (const std::array<>, vcl::graphitems::RectT<>) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator * (const std::array<T, S>& arr, MyType rhs)
        {
            return rhs *= arr;
        }


        //--- Inset / Outset ------------------------------------------------
        /** \brief Reduces the dimensions of this rectangle (1 scalar argument).
        * Also, modifies accordingly the position of this rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& inset(const T& offset) noexcept
        {
            return inset(offset, offset);
        }

        /** \brief Reduces the dimensions of this rectangle (2 scalar arguments).
        * Also, modifies accordingly the position of this rectangle.
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline MyType& inset(const T& offset_x, const U& offset_y) noexcept
        {
           return crop(TScalar(offset_x), TScalar(offset_y));
        }

        /** \brief Reduces the dimensions of this rectangle (1 Dims argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& inset(const vcl::utils::DimsT<T>& incr) noexcept
        {
            return inset(incr.width, incr.height);
        }

        /** \brief Reduces the dimensions of this rectangle (1 vcl::vectors::Vect2<> argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& inset(const vcl::vect::Vect2<T>& incr) noexcept
        {
            return inset(incr.x, incr.y);
        }

        /** \brief Reduces the dimensions of this rectangle (1 std::vector argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& inset(const std::vector<T>& incr) noexcept
        {
            if (incr.size() > 1)
                return inset(incr[0], incr[1]);
            else
                return inset(incr[0], incr[0]);
        }

        /** \brief Reduces the dimensions of this rectangle (1 std::array argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& inset(const std::array<T, S>& incr) noexcept
        {
            if (S > 1)
                return inset(incr[0], incr[1]);
            else
                return inset(incr[0], incr[0]);
        }

        /** \brief Augments the dimensions of this rectangle (1 scalar argument).
        * Also, modifies accordingly the position of this rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& outset(const T& offset) noexcept
        {
            return outset(offset, offset);
        }

        /** \brief Augments the dimensions of this rectangle (2 scalar arguments).
        * Also, modifies accordingly the position of this rectangle.
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline MyType& outset(const T& offset_x, const U& offset_y) noexcept
        {
            return crop(TScalar(-offset_x), TScalar(-offset_y));
        }

        /** \brief Augments the dimensions of this rectangle (1 Dims argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& outset(const vcl::utils::DimsT<T>& incr) noexcept
        {
            return outset(incr.width, incr.height);
        }

        /** \brief Augments the dimensions of this rectangle (1 vcl::vectors::Vect2<> argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& outset(const vcl::vect::Vect2<T>& incr) noexcept
        {
            return outset(incr.x, incr.y);
        }

        /** \brief Augments the dimensions of this rectangle (1 std::vector argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& outset(const std::vector<T>& incr) noexcept
        {
            if (incr.size() > 1)
                return outset(incr[0], incr[1]);
            else
                return outset(incr[0], incr[0]);
        }

        /** \brief Augments the dimensions of this rectangle (1 std::array argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& outset(const std::array<T, S>& incr) noexcept
        {
            if (S > 1)
                return outset(incr[0], incr[1]);
            else
                return outset(incr[0], incr[0]);
        }


        //--- Intersection / Union / Containment ----------------------------
        /** \brief Returns true if this rectangle contains a specified position. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline const bool contains(vcl::utils::PosT<T>& pos) const noexcept
        {
            return MyBaseType::x <= pos.x() && pos.x() <= right_x() && MyBaseType::y <= pos.y() && pos.y() <= bottom_y();
        }

        /** \brief Returns true if this rectangle contains the 'other' one.
        * \sa does_embed().
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline const bool contains(vcl::graphitems::RectT<T>& other) const noexcept
        {
            return does_embed(other);
        }

        /** \brief Returns true if this rectangle fully contains the 'other' one.
        * \sa contains(const RectT<T>&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline const bool does_embed(vcl::graphitems::RectT<T>& other) const noexcept
        {
            return intersection(other) == other;
        }

        /** \brief Returns true if this rectangle intersects with the 'other' one. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline bool does_intersect(const vcl::graphitems::RectT<T>& other) const noexcept
        {
            return other.bottom_y() >= MyBaseType::y &&
                other.y <= bottom_y() &&
                other.right_x() >= MyBaseType::x &&
                other.x <= right_x();
        }

        /** \brief Returns the intersection of this rectangle with the 'other' one. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        MyType& intersection_rect(const vcl::graphitems::RectT<T>& other) noexcept
        {
            if (does_intersect(other))
                return MyType( vcl::utils::PosT<TScalar>(vcl::utils::max(MyBaseType::x, other.x),
                                                         vcl::utils::max(MyBaseType::y, other.y)),
                               vcl::utils::PosT<TScalar>(vcl::utils::min(right_x() , other.right_x()),
                                                         vcl::utils::min(bottom_y(), other.bottom_y())) );
            else
                return MyType(0, 0, vcl::utils::DimsT(0, 0));
        }

        /** \brief Returns the union of this rectangle with the 'other' one.
        *   If 'b_strict' is true and 'this' rectangle does not intersect
        *   with 'other',  the returned union result is 'this' rectangle.
        *   Otherwise, the returned rectangle is the global union of both 
        *   rectangles. Notice: 'b_strict' defaults to true.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        MyType& union_rect(const vcl::graphitems::RectT<T>& other, const bool b_strict = true) noexcept
        {
            if (b_strict && !does_intersect(other))
                return *this;
            else
                return MyType(vcl::utils::PosT<TScalar>(vcl::utils::min(MyBaseType::x, other.x),
                                                        vcl::utils::min(MyBaseType::y, other.y)),
                              vcl::utils::PosT<TScalar>(vcl::utils::max(right_x(), other.right_x()),
                                                        vcl::utils::max(bottom_y(), other.bottom_y())) );
        }

        /** \brief Wrapper to the non-strict union of two rectangles. 
        * \sa union_rect().
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator + (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return union_rect(other, false);
        }

        /** \brief In-place non-strict union of this rectangle with an 'other' one. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator += (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return *this = union_rect(other, false);
        }

        /** \brief Returns true if this rectangle is fully embedded in the 'other' one or if it equals it. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline const bool operator <= (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return other.does_embed(*this);
        }

        /** \brief Returns true if this rectangle is fully embedded in the 'other' one. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline const bool operator < (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return *this != other && other.does_embed(*this);
        }

        /** \brief Returns true if this rectangle fully embeds in the 'other' one or if it equals it. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline const bool operator >= (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return does_embed(other);
        }

        /** \brief Returns true if this rectangle fully embeds in the 'other' one. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline const bool operator > (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return *this != other && does_embed(other);
        }


        //--- Drawing -------------------------------------------------------
        /** \brief Draws this rectangle contours in a specified frame (whole arguments provided). */
        inline void draw(cv::Mat&                 frame,
                         const vcl::utils::Color& border_color,
                         const int                border_thickness,
                         const cv::LineTypes      border_type)
        {
            prvt_last_border_color = border_color;
            prvt_last_border_thickness = border_thickness;
            prvt_last_border_type = border_type;
            draw(frame);
        }

        /** \brief Draws this rectangle contours in a specified frame (use previous border_color again). */
        inline void draw(cv::Mat&            frame,
                         const int           border_thickness,
                         const cv::LineTypes border_type)
        {
            prvt_last_border_thickness = border_thickness;
            prvt_last_border_type = border_type;
            draw(frame);
        }

        /** \brief Draws this rectangle contours in a specified frame (use previous border_thickness again). */
        inline void draw(cv::Mat&                 frame,
                         const vcl::utils::Color& border_color,
                         const cv::LineTypes      border_type)
        {
            prvt_last_border_color = border_color;
            prvt_last_border_type = border_type;
            draw(frame);
        }

        /** \brief Draws this rectangle contours in a specified frame (use previous border_type again). */
        inline void draw(cv::Mat& frame,
                         const vcl::utils::Color& border_color,
                         const int                border_thickness)
        {
            prvt_last_border_color = border_color;
            prvt_last_border_thickness = border_thickness;
            draw(frame);
        }

        /** \brief Draws this rectangle contours in a specified frame (use previous border_color and _thickness again). */
        inline void draw(cv::Mat& frame, const cv::LineTypes border_type)
        {
            prvt_last_border_type = border_type;
            draw(frame);
        }

        /** \brief Draws this rectangle contours in a specified frame (use previous border_color and _type again). */
        inline void draw(cv::Mat& frame, const int border_thickness)
        {
            prvt_last_border_thickness = border_thickness;
            draw(frame);
        }

        /** \brief Draws this rectangle contours in a specified frame (use previous border_thickness and _ttype again). */
        inline void draw(cv::Mat& frame, const vcl::utils::Color& border_color)
        {
            prvt_last_border_color = border_color;
            draw(frame);
        }


        /** \brief Draws this rectangle contours in a specified frame (use all previous specifiers again).
        * CAUTION: while first calling method  'draw()'  on  a  rectangle,
        *       color  MUST BE specified. Not doing so may lead to the not 
        *       display of the rectangle in the frame  or  may  result  to 
        *       unpredictable color used for the display of the rectangle.
        */
        inline void draw(cv::Mat& frame)
        {
            cv::rectangle(
                frame,
                cv::Point_<TScalar>(top_left()),
                cv::Point_<TScalar>(bottom_right()),
                prvt_last_border_color,
                prvt_last_border_thickness,
                prvt_last_border_type,
                0  // notice: in vcl, the number of fractional bits in the point coordinates is forced to zero.  
            );
        }


    private:
        vcl::utils::Color prvt_last_border_color{ };
        int               prvt_last_border_thickness{ 1 };
        cv::LineTypes     prvt_last_border_type{ cv::LINE_8 };

    };

}
