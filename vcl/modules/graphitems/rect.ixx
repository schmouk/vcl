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
#include <utility>
#include <vector>

#include <opencv2/core/types.hpp> // to get access to cv::Rect_<_Tp>

#include "vcl_concepts.h"

export module graphitems.rect;

import utils.dims;
import utils.offsets;
import utils.pos;
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


        //--- Accessors / Mutators ------------------------------------------
        /** \brief left side position accessor. */
        inline const TScalar left_x() const noexcept
        {
            return MyBaseType::x;
        }
        /** \brief left side position mutator. */
        template<typename T>
            requires vcl::concepts::is_scalar<T>
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
            requires vcl::concepts::is_scalar<T>
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
            requires vcl::concepts::is_scalar<T>
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
            requires vcl::concepts::is_scalar<T>
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
            requires vcl::concepts::is_scalar<T>
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
            requires vcl::concepts::is_scalar<T>
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


        //--- In place cropping ---------------------------------------------
        /** In-place cropping with 4 different margins. */
        template<typename T, typename U, typename V, typename W>
            requires vcl::concepts::is_scalar<T> && vcl::concepts::is_scalar<U> && vcl::concepts::is_scalar<V> && vcl::concepts::is_scalar<W>
        MyType& crop(const T& left_margin, const U& right_margin, const V& top_margin, const W& bottom_margin) noexcept
        {
            MyBaseType::x += left_margin;
            MyBaseType::y += top_margin;
            MyBaseType::width -= left_margin + right_margin;
            MyBaseType::height -= top_margin + bottom_margin;
            if (MyBaseType::width < 0)
                MyBaseType::width = 0;
            if (MyBaseType::height < 0)
                MyBaseType::height = 0;

            return *this;
        }

        /** In-place cropping with X- and Y- margins. */
        template<typename T, typename U>
            requires vcl::concepts::is_scalar<T> && vcl::concepts::is_scalar<U>
        inline MyType& crop(const T& x_margins, const U& y_margins) noexcept
        {
            return crop(x_margins, x_margins, y_margins, y_margins);
        }

        /** In-place croppping with all same margins. */
        template<typename T>
            requires vcl::concepts::is_scalar<T>
        inline MyType& crop(const T& all_margins) noexcept
        {
            return crop(all_margins, all_margins, all_margins, all_margins);
        }


        //--- Intersections / Unions / Containment --------------------------
        /** \brief Returns true if this rectangle intersects with the 'other' one. */
        template<typename T>
            requires vcl::concepts::is_scalar<T>
        const bool does_intersect(vcl::graphitems::Rect<T>& other) const noexcept
        {
            return other.bottom_y() >= self.y &&
                    other.y <= self.bottom_y() &&
                    other.right_x() >= self.x &&
                    other.x <= self.right_x();
        }

        /** \brief Returns true if this rectangle fully contains the 'other' one. */
        template<typename T>
            requires vcl::concepts::is_scalar<T>
        const bool does_embed(vcl::graphitems::Rect<T>& other) const noexcept
        {
            return intersection(other) == other;
        }

        /** \brief Returns the intersection of this rectangle with the 'other' one. */
        template<typename T>
            requires vcl::concepts::is_scalar<T>
        MyType& intersection(vcl::graphitmes::Rect<T>& other)
        {
            if (does_intersect(other))
            {
                top_left(vcl::utils::PosT<TScalar>()
            }
            else:
            return MyType(0, 0, vcl::utils::DimsT(0, 0));
        }
            if self.does_intersect(other) :
                top_left = Point2D(max(other.x_left, self.x_left), max(other.y_top, self.y_top))
                bottom_right = Point2D(min(other.x_right, self.x_right), min(other.y_bottom, self.y_bottom))
                return Rect(top_left, bottom_right)
            else:
                return None

    };

}
