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
#include <type_traits>
#include <utility>
#include <vector>

#include <opencv2/core/mat.hpp>   // to get access to cv::Mat (i.e. image container)
#include <opencv2/core/types.hpp> // to get access to cv::Rect_<_Tp> and cv::Point_<_Tp>
#include <opencv2/imgproc.hpp>    // to get access to OpenCV drawing functions

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
        requires std::is_arithmetic_v<TScalar>
    class RectT;

    // Specializations
    /** \brief The class of rectangles with integer positions and dimensions (16 bits). */
    export using Rect = RectT<short>;

    /** \brief The class of rectangles with integer positions and dimensions (32 bits). */
    export using Rect_i = RectT<long>;

    /** \brief The class of rectangles with float positions and dimensions (32 bits). */
    export using Rect_f = RectT<float>;

    /** \brief The class of rectangles with double positions and dimensions (64 bits). */
    export using Rect_d = RectT<double>;


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
        requires std::is_arithmetic_v<TScalar>
    class RectT : public cv::Rect_<TScalar>
    {
    public:
        using MyBaseType = cv::Rect_<TScalar>;              //!< wrapper to the inherited cv::Rect_ class naming.
        using MyType     = vcl::graphitems::RectT<TScalar>; //!< wrapper to this class naming.
        using PosType    = vcl::utils::PosT<TScalar>;       //!< wrapper to this class specialized PosT type.
        using DimsType   = vcl::utils::DimsT<TScalar> ;     //!< wrapper to this class specialized DimsT type.

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

        /** \brief Constructor (4-D vcl::vector positions).
        * Notice: order of coordinates in vector: left, right, top, bottom.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline explicit RectT<TScalar>(const vcl::vect::Vect4<T>& vect)
            : MyBaseType(TScalar(vect[0]),
                         TScalar(vect[2]),
                         TScalar(vect[1] - vect[0] + 1),
                         TScalar(vect[3] - vect[2] + 1))
        {}

        /** \brief Copy constructor (const std::array&).
        * Notice: order of coordinates in vector: left, right, top, bottom.
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        explicit RectT<TScalar>(const std::array<T, S>& arr)
            : MyBaseType()
        {
            if (S > 0)  (*this).x      = TScalar(arr[0]);
            if (S > 1)  (*this).width  = TScalar(arr[1] - arr[0] + 1);
            if (S > 2)  (*this).y      = TScalar(arr[2]);
            if (S > 3)  (*this).height = TScalar(arr[3] - arr[2] + 1);
        }

        /** \brief Copy constructor (const std::vector&).
        * Notice: order of coordinates in vector: left, right, top, bottom.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        explicit RectT<TScalar>(const std::vector<T>& vect)
            : MyBaseType()
        {
            const size_t S = vect.size();
            if (S > 0)  (*this).x      = TScalar(vect[0]);
            if (S > 1)  (*this).width  = TScalar(vect[1] - vect[0] + 1);
            if (S > 2)  (*this).y      = TScalar(vect[2]);
            if (S > 3)  (*this).height = TScalar(vect[3] - vect[2] + 1);
        }

        /** \brief Constructor (4 scalar border positions).
        */
        template<typename T, typename U, typename V, typename W>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V> && std::is_arithmetic_v<W>
        inline explicit RectT<TScalar>(const T left_x, const U right_x, const V top_y, const W bottom_y)
            : MyBaseType(TScalar(left_x),
                         TScalar(top_y),
                         TScalar(right_x) - TScalar(left_x) + TScalar(1),
                         TScalar(bottom_y) - TScalar(top_y) + TScalar(1))
        {}

        /** \brief Constructor (2 scalar positions + dimensions).
        */
        template<typename T, typename U, typename V>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
        inline explicit RectT<TScalar>(const T left_x, const U top_y, const vcl::utils::DimsT<V>& dims)
            : MyBaseType(TScalar(left_x), TScalar(top_y), TScalar(dims.width()), TScalar(dims.height()))
        {}

        /** \brief Constructor (top left position + dimensions).
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline RectT<TScalar>(const vcl::utils::PosT<T>& top_left, const vcl::utils::DimsT<U>& dims)
            : MyBaseType(TScalar(top_left.x()), TScalar(top_left.y()), TScalar(dims.width()), TScalar(dims.height()))
        {}

        /** \brief Constructor (2 opposite corners positions).
        */
       template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline explicit RectT<TScalar>(const vcl::utils::PosT<T>& top_left,
                                       const vcl::utils::PosT<U>& bottom_right)
            : MyBaseType(TScalar(top_left.x()),
                         TScalar(top_left.y()),
                         TScalar(bottom_right.x()) - TScalar(top_left.x()) + TScalar(1),
                         TScalar(bottom_right.y()) - TScalar(top_left.y()) + TScalar(1))
        {}

        /** \brief Constructor (top left position + width + height).
        */
        template<typename T, typename U, typename V>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
        inline explicit RectT<TScalar>(const vcl::utils::PosT<T>& top_left,
                                       const U width, const V height)
            : MyBaseType(TScalar(top_left.x()), TScalar(top_left.y()), TScalar(width), TScalar(height))
        {}

        /** \brief Constructor (std::pair<>, std::pair<>).
        */
        template<typename T, typename U, typename V, typename W>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V> && std::is_arithmetic_v<W>
        inline explicit RectT<TScalar>(const std::pair<T, U>& pos_pair,
                                       const std::pair<V, W>& dims_pair)
            : MyBaseType(TScalar(pos_pair.first), TScalar(pos_pair.second), TScalar(dims_pair.first), TScalar(dims_pair.second))
        {}


        //---  Destructor   -------------------------------------------------
        virtual inline ~RectT<TScalar>()
        {}


        //--- Assignment ----------------------------------------------------
        /** \brief Copy assign operator (const vcl::graphitems::RectT<>&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        MyType& operator= (vcl::graphitems::RectT<T>& other)
        {
            this->x = TScalar(other.x);
            this->y = TScalar(other.y);
            this->width = TScalar(other.width);
            this->height = TScalar(other.height);
            return *this;
        }

        /** \brief Move assign operator (const vcl::graphitems::RectT<>&&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        MyType& operator= (vcl::graphitems::RectT<T>&& other)
        {
            this->x = TScalar((&other)->x);
            this->y = TScalar((&other)->y);
            this->width = TScalar((&other)->width);
            this->height = TScalar((&other)->height);
            return *this;
        }

        /** \brief assign operator (const vcl::vect::Vect4<>).
        * The vector components are: {left_x, top_y, width, height}.
        * Notice: assignment operators with argument of type Rect are
        *         provided per inheritance from base class cv::Rect_.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        MyType& operator= (vcl::vect::Vect4<T>& other) noexcept
        {
            this->x = TScalar(other.x());
            this->y = TScalar(other.y());
            this->width = TScalar(other.z());
            this->height = TScalar(other.w());
            return *this;
        }

        /** \brief assign operator (const std::vector<>).
        * The vector components must be: {left_x, top_y, width, height}.
        * At least four components must be provided. If more than 4
        * of them are provided, the next ones are ignored.
        * Notice: assignment operators with argument of type Rect are
        *         provided per inheritance from base class cv::Rect_.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        MyType& operator= (std::vector<T>& vect)
        {
            if (vect.size() < 4) {
                throw std::invalid_argument("vectors used for assignment must contain at least 4 components.");
            }
            else {
                this->x = TScalar(vect[0]);
                this->y = TScalar(vect[1]);
                this->width = TScalar(vect[2]);
                this->height = TScalar(vect[3]);
            }
            return *this;
        }

        /** \brief assign operator (const std::array<>).
        * The array components must be: {left_x, top_y, width, height}.
        * At least four components must be provided. If more than 4
        * of them are provided, the next ones are ignored.
        * Notice: assignment operators with argument of type Rect are
        *         provided per inheritance from base class cv::Rect_.
        */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        MyType& operator= (std::array<T, S>& arr)
        {
            if (S < 4) {
                throw std::invalid_argument("arrays used for assignment must contain at least 4 components.");
            }
            else {
                this->x = TScalar(arr[0]);
                this->y = TScalar(arr[1]);
                this->width = TScalar(arr[2]);
                this->height = TScalar(arr[3]);
            }
            return *this;
        }


        //--- Comparisons ---------------------------------------------------
        /** \brief Equality between rectangles. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline const bool operator== (vcl::graphitems::RectT<T>& other) const
        {
            return this->x == TScalar(other.x) &&
                   this->y == TScalar(other.y) &&
                   this->width == TScalar(other.width) &&
                   this->height == TScalar(other.height);
        }

        /** \brief Inequality between rectangles. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline const bool operator != (vcl::graphitems::RectT<T>& other) const
        {
            return !(*this == other);
        }


        //--- Accessors / Mutators ------------------------------------------
        /** \brief left side position accessor. */
        inline const TScalar left_x() const noexcept
        {
            return this->x;
        }

        /** \brief left side position mutator. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void left_x(const T& new_x) noexcept
        {
            this->x = TScalar(new_x);
        }

        /** \brief right side position accessor. */
        inline const TScalar right_x() const noexcept
        {
            return this->x + this->width - 1;
        }

        /** \brief right side position mutator. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void right_x(const T& new_x) noexcept
        {
            if (new_x >= this->x)
                this->width = TScalar(new_x) - this->x + 1;
            else
                this->width = 0;
        }

        /** \brief top side position accessor. */
        inline const TScalar top_y() const noexcept
        {
            return this->y;
        }

        /** \brief top side position mutator. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void top_y(const T& new_y) noexcept
        {
            this->y = TScalar(new_y);
        }

        /** \brief bottom side position accessor. */
        inline const TScalar bottom_y() const noexcept
        {
            return this->y + this->height - 1;
        }

        /** \brief bottom side position mutator. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void bottom_y(const T& new_y) noexcept
        {
            if (new_y >= this->y)
                this->height = TScalar(new_y) - this->y + 1;
            else
                this->height = 0;
        }

        /** \brief top-left accessor. */
        template<typename T = TScalar>
            requires std::is_arithmetic_v<T>
        inline vcl::utils::PosT<T> top_left() const noexcept
        {
            return vcl::utils::PosT<T>(this->x, this->y);
        }

        /** \brief top-left mutator (2 scalars). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline void top_left(const T new_x, const U new_y) noexcept
        {
            this->x = TScalar(new_x);
            this->y = TScalar(new_y);
        }

        /** \brief top-left mutator (1 PosT). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void top_left(const vcl::utils::PosT<T>& new_pos) noexcept
        {
            top_left(new_pos.x(), new_pos.y());
        }

        /** \brief bottom-right accessor. */
        template<typename T = TScalar>
            requires std::is_arithmetic_v<T>
        inline vcl::utils::PosT<T> bottom_right() const noexcept
        {
            return vcl::utils::PosT<T>(this->x + this->width  - 1,
                                       this->y + this->height - 1);
        }

        /** \brief bottom-right mutator. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void bottom_right(const vcl::utils::PosT<T>& new_pos) noexcept
        {
            right_x(new_pos.x());
            bottom_y(new_pos.y());
        }

        /** \brief center accessor. */
        template<typename T = TScalar>
            requires std::is_arithmetic_v<T>
        inline vcl::utils::PosT<T> center() const noexcept
        {
            return vcl::utils::PosT<T>(this->x + this->width  / 2,
                                       this->y + this->height / 2);
        }

        /** \brief center mutator. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void center(const vcl::utils::PosT<T>& new_pos) noexcept
        {
            move(new_pos - center());
        }

        /** \brief Dimensions accessor. */
        template<typename T = TScalar>
            requires std::is_arithmetic_v<T>
        inline vcl::utils::DimsT<T> dims() const noexcept
        {
            return vcl::utils::DimsT<T>(this->width, this->height);
        }

        /** \brief Dimensions mutator (2 TScalar). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline void dims(const T new_width, const U new_height)
        {
            this->width = TScalar(new_width);
            this->height = TScalar(new_height);
        }

        /** \brief Dimensions mutator (1 DimsT). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void dims(const vcl::utils::DimsT<T>& new_dims)
        {
            dims(new_dims.width(), new_dims.height());
        }


        //--- Casting operators ---------------------------------------------
        /** \brief casting operator to scalar type T.
        * Returns the area of this rectangle.
        */
        inline explicit operator short() const
        {
            return short(this->area());
        }

        inline explicit operator unsigned short() const
        {
            return (unsigned short)this->area();
        }

        inline explicit operator int() const
        {
            return int(this->area());
        }

        inline explicit operator unsigned int() const
        {
            return (unsigned int)this->area();
        }

        inline explicit operator long() const
        {
            return long(this->area());
        }

        inline explicit operator unsigned long() const
        {
            return (unsigned long)this->area();
        }

        inline explicit operator long long() const
        {
            return (long long)this->area();
        }

        inline explicit operator unsigned long long() const
        {
            return (unsigned long long)this->area();
        }

        inline explicit operator float() const
        {
            return float(this->area());
        }

        inline explicit operator double() const
        {
            return double(this->area());
        }

        inline explicit operator long double() const
        {
            return (long double)this->area();
        }


        /** \brief casting operator to vcl::utils::PosT<T>.
        * Returns the top-left corner position of this rectangle.
        */
        template<typename T = TScalar>
            requires std::is_arithmetic_v<T>
        inline operator vcl::utils::PosT<T>()
        {
            return vcl::utils::PosT<T>(this->x, this->y);
        }

        /** \brief casting operator to vcl::utils::DimsT<T>.
        * Returns the dimensions of this rectangle.
        */
        template<typename T = TScalar>
            requires std::is_arithmetic_v<T>
        inline operator vcl::utils::DimsT<T>()
        {
            return vcl::utils::DimsT<T>(this->width, this->height);
        }

        /** \brief casting operator to vcl::vect::Vect4<T>.
        * Returns a 4-components vcl::vect::Vect4 (left_x, top_y, width, height).
        */
        template<typename T = TScalar>
            requires std::is_arithmetic_v<T>
        inline operator vcl::vect::Vect4<T>()
        {
            return vcl::vect::Vect4<T>(this->x, this->y, this->width, this->height);
        }

        /** \brief casting operator to std::vector<T>.
        * Returns a 4-components std::vector (left_x, top_y, width, height).
        */
        template<typename T = TScalar>
            requires std::is_arithmetic_v<T>
        operator std::vector<T>()
        {
            std::vector<T> v;
            v.push_back(T(this->x));
            v.push_back(T(this->y));
            v.push_back(T(this->width));
            v.push_back(T(this->height));
            return v;
        }

        /** \brief casting operator to std::array<T, 4>.
        * Returns a 4-components std::array (left_x, top_y, width, height).
        */
        template<typename T = TScalar>
            requires std::is_arithmetic_v<T>
        inline operator std::array<T, 4>()
        {
            std::array<T, 4> arr{T(this->x), T(this->y), T(this->width), T(this->height)};
            return arr;
        }

        
        //--- In place cropping ---------------------------------------------
        /** In-place cropping with 4 different margins. */
        template<typename T, typename U, typename V, typename W>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V> && std::is_arithmetic_v<W>
        MyType& crop(const T& left_margin, const U& right_margin, const V& top_margin, const W& bottom_margin) noexcept
        {
            move(left_margin, top_margin);
            auto left_m = std::is_unsigned_v<T> ? (long long)left_margin : left_margin;
            auto right_m = std::is_unsigned_v<U> ? (long long)right_margin : right_margin;
            auto top_m = std::is_unsigned_v<V> ? (long long)top_margin : top_margin;
            auto bottom_m = std::is_unsigned_v<W> ? (long long)bottom_margin : bottom_margin;
            return resize(-(left_m + right_m), -(top_m + bottom_m));
        }

        /** In-place cropping with X- and Y- margins. */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline MyType& crop(const T& x_margins, const U& y_margins) noexcept
        {
            return crop(x_margins, x_margins, y_margins, y_margins);
        }

        /** In-place croppping with all same margins. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& crop(const T& all_margins) noexcept
        {
            return crop(all_margins, all_margins, all_margins, all_margins);
        }


        //--- Moving --------------------------------------------------------
        /** \brief Moves this rectangle with specified offsets (2 scalars). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline MyType& move(const T dx, const U dy) noexcept
        {
            this->x += TScalar(dx);
            this->y += TScalar(dy);
            return *this;
        }

        /** \brief Moves this rectangle with specified offset (vcl::utils::Offset). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& move(const vcl::utils::OffsetsT<T>& offset) noexcept
        {
            return move(offset.dx(), offset.dy());
        }

        /** \brief Moves this rectangle with specified offset (vcl::vect::Vector). */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        inline MyType& move(const vcl::vect::Vector<T, Ksize>& offset)
        {
            if (Ksize < 2) {
                throw std::invalid_argument("vectors used for offsets must contain at least 2 components.");
                return *this;
            }
            else {
                return move(offset[0], offset[1]);
            }
        }

        /** \brief Moves this rectangle with specified offset (std::vector). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& move(const std::vector<T>& offset)
        {
            if (offset.size() < 2) {
                throw std::invalid_argument("vectors used for offsets must contain at least 2 components.");
                return *this;
            }
            else {
                return move(offset[0], offset[1]);
            }
        }

        /** \brief Moves this rectangle with specified offset (std::array). */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        inline MyType& move(const std::array<T, S>& offset)
        {
            if (S < 2) {
                throw std::invalid_argument("arrays used for offsets must contain at least 2 components.");
                return *this;
            }
            else {
                return move(offset[0], offset[1]);
            }
        }

        /** \brief Moves this rectangle with specified offset (std::pair). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>
        inline MyType& move(const std::pair<T, U>& offset) noexcept
        {
            return move(offset.first, offset.second);
        }

        /** \brief Moves this rectangle with specified offset (vcl::utils::Offset). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& operator += (const vcl::utils::OffsetsT<T>& offset) noexcept
        {
            return move(offset);
        }

        /** \brief Moves this rectangle with specified offset (vcl::vect::Vector). */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        inline MyType& operator += (const vcl::vect::Vector<T, Ksize>& offset)
        {
            return move(offset);
        }

        /** \brief Moves this rectangle with specified offset (std::vector). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& operator += (const std::vector<T>& offset)
        {
            return move(offset);
        }

        /** \brief Moves this rectangle with specified offset (std::array). */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        inline MyType& operator += (const std::array<T, S>& offset)
        {
            return move(offset);
        }

        /** \brief Moves this rectangle with specified offset (std::pair). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>
        inline MyType& operator += (const std::pair<T, U>& offset) noexcept
        {
            return move(offset);
        }

        /** \brief Moves this rectangle with specified offset (vcl::graphitems::RectT, vcl::utils::Offset). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline friend MyType operator + (MyType rect, const vcl::utils::OffsetsT<T>& offset) noexcept
        {
            return rect += offset;
        }

        /** \brief Moves this rectangle with specified offset (vcl::utils::Offset, vcl::graphitems::RectT). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline friend MyType operator + (const vcl::utils::OffsetsT<T>& offset, MyType rect) noexcept
        {
            return rect += offset;
        }

        /** \brief Moves this rectangle with specified offset (vcl::vect::Vector). */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        inline friend MyType operator + (MyType rect, const vcl::vect::Vector<T, Ksize>& offset)
        {
            return rect += offset;
        }

        /** \brief Moves this rectangle with specified offset (vcl::vect::Vector). */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        inline friend MyType operator + (const vcl::vect::Vector<T, Ksize>& offset, MyType rect)
        {
            return rect += offset;
        }

        /** \brief Moves this rectangle with specified offset (std::vector). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline friend MyType operator + (MyType rect, const std::vector<T>& offset)
        {
            return rect += offset;
        }

        /** \brief Moves this rectangle with specified offset (std::vector). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline friend MyType operator + (const std::vector<T>& offset, MyType rect)
        {
            return rect += offset;
        }

        /** \brief Moves this rectangle with specified offset (std::array). */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        inline friend MyType operator + (MyType rect, const std::array<T, S>& offset)
        {
            return rect += offset;
        }

        /** \brief Moves this rectangle with specified offset (std::array). */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        inline friend MyType operator + (const std::array<T, S>& offset, MyType rect)
        {
            return rect += offset;
        }

        /** \brief Moves this rectangle with specified offset (std::pair). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>
        inline friend MyType operator + (MyType rect, const std::pair<T, U>& offset) noexcept
        {
            return rect += offset;
        }

        /** \brief Moves this rectangle with specified offset (std::pair). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>
        inline friend MyType operator + (const std::pair<T, U>& offset, MyType rect) noexcept
        {
            return rect += offset;
        }


        //--- Moving at -----------------------------------------------------
        /** \brief Moves top-left corner of this this rectangle to specified position (2 scalars). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline MyType& move_at(const T left_x, const U top_y) noexcept
        {
            this->x = (TScalar)left_x;
            this->y = (TScalar)top_y;
            return *this;
        }

        /** \brief Moves top-left corner of this this rectangle to specified position (vcl::utils::PosT). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& move_at(const vcl::utils::PosT<T>& new_pos) noexcept
        {
            return move_at(TScalar(new_pos.x()), TScalar(new_pos.y()));
        }

        /** \brief Moves top-left corner of this this rectangle to specified position (vcl::vect::Vector). */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        inline MyType& move_at(const vcl::vect::Vector<T, Ksize>& new_pos)
        {
            return Ksize >= 2 ? move_at(TScalar(new_pos[0]), TScalar(new_pos[1])) : *this;
        }

        /** \brief Moves top-left corner of this this rectangle to specified position (std::vector). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& move_at(const std::vector<T>& new_pos)
        {
            return new_pos.size() >= 2 ? move_at(TScalar(new_pos[0]), TScalar(new_pos[1])) : *this;
        }

        /** \brief Moves top-left corner of this this rectangle to specified position (std::array). */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        inline MyType& move_at(const std::array<T, S>& new_pos)
        {
            return S >= 2 ? move_at(TScalar(new_pos[0]), TScalar(new_pos[1])) : *this;
        }

        /** \brief Moves top-left corner of this this rectangle to specified position (std::pair). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>
        inline MyType& move_at(const std::pair<T, U>& new_pos) noexcept
        {
            return move_at(TScalar(new_pos.first), TScalar(new_pos.second));
        }


        //--- Resizing ------------------------------------------------------
        /** \brief Resizes this rectangle (1 scalar parameter).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& resize(const T& incr) noexcept
        {
            return resize(incr, incr);
        }

        /** \brief Resizes this rectangle (2 scalar arguments).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline MyType& resize(const T& incr_x, const U& incr_y) noexcept
        {
            this->width = TScalar(this->width + incr_x);
            this->height = TScalar(this->height + incr_y);
            return *this;
        }

        /** \brief Resizes this rectangle (1 Dims argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& resize(const vcl::utils::DimsT<T>& incr) noexcept
        {
            return resize(incr.width(), incr.height());
        }

        /** \brief Resizes this rectangle (1 Offset argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& resize(const vcl::utils::OffsetsT<T>& incr) noexcept
        {
            return resize(incr.dx(), incr.dy());
        }

        /** \brief Resizes this rectangle (1 vcl::vectors::Vect2<> argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& resize(const vcl::vect::Vect2<T>& incr) noexcept
        {
            return resize(incr.x(), incr.y());
        }

        /** \brief Resizes this rectangle (1 std::vector argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& resize(const std::vector<T>& incr) noexcept
        {
            if (incr.size() > 1)
                return resize(incr[0], incr[1]);
            else
                return resize(incr[0]);
        }

        /** \brief Resizes this rectangle (1 std::array argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        inline MyType& resize(const std::array<T, Ksize>& incr) noexcept
        {
            if (Ksize > 1)
                return resize(incr[0], incr[1]);
            else
                return resize(incr[0]);
        }

        /** \brief Resizes this rectangle (1 std::pair argument).
        * Negative values for argument 'incr' decreases the size of the rectangle.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>
        inline MyType& resize(const std::pair<T, U>& new_pos) noexcept
        {
            return resize(new_pos.first, new_pos.second);
        }


        //--- Scaling -------------------------------------------------------
        /** \brief Resizes this rectangle according to a scaling factor.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& scale(const T& factor)
        {
            return scale(factor, factor);
        }

        /** \brief Resizes this rectangle according to two scaling factors.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values raise an invalid_argument exception.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        MyType& scale(const T& factor_x, const U& factor_y)
        {
            if (factor_x < T(0) || factor_y < U(0))
                throw std::invalid_argument("scaling factors cannot be negative");
            else
            {
                this->width = TScalar(this->width * factor_x);
                this->height = TScalar(this->height * factor_y);
            }
            return *this;
        }

        /** \brief Resizes this rectangle according to scaling factors (const vcl::vect::Vector&).
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        MyType& scale(const vcl::vect::Vector<T, Ksize>& vect)
        {
            switch (Ksize)
            {
            case 0:
                throw std::invalid_argument("factor vectors cannot be empty");
                return *this;
            case 1:
                return scale(vect[0]);
            default:
                return scale(vect[0], vect[1]);
            }
        }

        /** \brief Resizes this rectangle according to scaling factors (const std::vector&).
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        MyType& scale(const std::vector<T>& vect)
        {
            switch (vect.size())
            {
            case 0:
                throw std::invalid_argument("factor vectors cannot be empty");
                return *this;
            case 1:
                return scale(vect[0]);
            default:
                return scale(vect[0], vect[1]);
            }
        }

        /** \brief Resizes this rectangle according to scaling factors (const std::array&).
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        MyType& scale(const std::array<T, Ksize>& arr)
        {
            switch (Ksize)
            {
            case 0:
                throw std::invalid_argument("factor arrays cannot be empty");
                return *this;
            case 1:
                return scale(arr[0]);
            default:
                return scale(arr[0], arr[1]);
            }
        }

        /** \brief Resizes this rectangle according to a pair of scaling factors (const std::pair&).
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values raise an invalid_argument exception.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline MyType& scale(const std::pair<T, U>& pair)
        {
            return scale(pair.first, pair.second);
        }

        /** \brief Resizes this rectangle according to a scaling factor.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& operator *= (const T& factor)
        {
            return scale(factor, factor);
        }

        /** \brief Resizes this rectangle according to scaling factors.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        inline MyType& operator *= (const vcl::vect::Vector<T, Ksize>& vect)
        {
            return scale(vect);
        }

        /** \brief Resizes this rectangle according to scaling factors.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& operator *= (const std::vector<T>& vect)
        {
            return scale(vect);
        }

        /** \brief Resizes this rectangle according to scaling factors.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values for 'factor' raise an invalid_argument exception.
        */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        inline MyType& operator *= (const std::array<T, Ksize>& arr)
        {
            return scale(arr);
        }

        /** \brief Resizes this rectangle according to two scaling factors.
        * Factors less than 1 reduce the size of this rectangle.
        * Negative values raise an invalid_argument exception.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline MyType& operator *= (const std::pair<T, U>& pair)
        {
           return scale(pair);
        }

        /** \brief Resizing operator * (const TScalar) */
        template<typename T>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator * (MyType lhs, const T value)
        {
            return lhs *= value;
        }

        /** \brief Resizing operator * (const TScalar, vcl::graphitems::RectT<>) */
        template<typename T>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator * (const T value, MyType rhs)
        {
            return rhs *= value;
        }

        /** \brief Resizing operator * (const vcl::vect::Vector<>) */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator * (MyType lhs, const vcl::vect::Vector<T, S>& vect)
        {
            return lhs *= vect;
        }

        /** \brief Resizing operator * (const vcl::vect::Vector<>, vcl::graphitems::RectT<>) */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator * (const vcl::vect::Vector<T, S>& vect, MyType rhs)
        {
            return rhs *= vect;
        }

        /** \brief Resizing operator * (const std::vector<>) */
        template<typename T>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator * (MyType lhs, const std::vector<T>& vect)
        {
            return lhs *= vect;
        }

        /** \brief Resizing operator * (const std::vector<>, vcl::graphitems::RectT<>) */
        template<typename T>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator * (const std::vector<T>& vect, MyType rhs)
        {
            return rhs *= vect;
        }

        /** \brief Resizing operator * (const std::array<>) */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator * (MyType lhs, const std::array<T, S>& rhs)
        {
            return lhs *= rhs;
        }

        /** \brief Resizing operator * (const std::array<>, vcl::graphitems::RectT<>) */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator * (const std::array<T, S>& lhs, MyType rhs)
        {
            return rhs *= lhs;
        }

        /** \brief Resizing operator * (const std::pair<>) */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        friend inline MyType operator * (MyType lhs, const std::pair<T, U>& rhs)
        {
            return lhs *= rhs;
        }

        /** \brief Resizing operator * (const std::pair<>, vcl::graphitems::RectT<>) */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        friend inline MyType operator * (const std::pair<T, U>& lhs, MyType rhs)
        {
            return rhs *= lhs;
        }

        /** \brief Scales this rectangle from its center (1 scalar factor).
        * Scales this rectangle from its center as  the  origin
        * of the scaling. As such, modifies the top-left corner 
        * position.
        * Values less than 1.0 shrink this rectangle.
        * \sa \c shrink_from_center() and \c scale()
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& scale_from_center(const T& factor)
        {
            return scale_from_center(factor, factor);
        }

        /** \brief Scales this rectangle from its center (2 scalar factors).
        * Scales this rectangle from its center as  the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 shrink this rectangle.
        * \sa \c shrink_from_center() and \c scale()
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        MyType& scale_from_center(const T& factor_x, const U& factor_y)
        {
            const vcl::utils::DimsT<TScalar> prev_dims = dims();
            scale(factor_x, factor_y);
            return move(0.5 * (prev_dims - dims()));
        }

        /** \brief Scales this rectangle from its center (1 vcl::utils:VectorT<>).
        * Scales this rectangle from its center as  the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 shrink this rectangle.
        * \sa \c shrink_from_center() and \c scale()
        */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        MyType& scale_from_center(const vcl::vect::Vector<T, S>& vect)
        {
            switch (vect.size())
            {
            case 0:
                throw std::invalid_argument("factor vectors cannot be empty");
                return *this;
            case 1:
                return scale_from_center(vect[0]);
            default:
                return scale_from_center(vect[0], vect[1]);
            }
        }

        /** \brief Scales this rectangle from its center (1 std::vector<>).
        * Scales this rectangle from its center as  the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 shrink this rectangle.
        * \sa \c shrink_from_center() and \c scale()
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        MyType& scale_from_center(const std::vector<T>& vect)
        {
            switch (vect.size())
            {
            case 0:
                throw std::invalid_argument("factor vectors cannot be empty");
                return *this;
            case 1:
                return scale_from_center(vect[0]);
            default:
                return scale_from_center(vect[0], vect[1]);
            }
        }

        /** \brief Scales this rectangle from its center (1 std::array<>).
        * Scales this rectangle from its center as  the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 shrink this rectangle.
        * \sa \c shrink_from_center() and \c scale()
        */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        MyType& scale_from_center(const std::array<T, S>& arr)
        {
            switch (S)
            {
            case 0:
                throw std::invalid_argument("factor arrays cannot be empty");
                return *this;
            case 1:
                return scale_from_center(arr[0]);
            default:
                return scale_from_center(arr[0], arr[1]);
            }
        }

        /** \brief Scales this rectangle from its center (1 std::pair).
        * Scales this rectangle from its center as  the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 shrink this rectangle.
        * \sa \c shrink_from_center() and \c scale()
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline MyType& scale_from_center(const std::pair<T, U>& pair) noexcept
        {
            scale_from_center(pair.first, pair.second);
        }


        //--- Shrinking -----------------------------------------------------
        /** \brief Resizes this rectangle according to a reducing factor.
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& shrink(const T& factor)
        {
            return shrink(factor, factor);
        }

        /** \brief Resizes this rectangle according to two reducing factors.
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values raise an invalid_argument exception.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        MyType& shrink(const T& factor_x, const U& factor_y)
        {
            if (factor_x == T(0) || factor_y == T(0))
                throw std::invalid_argument("reducing factors cannot be zero");
            else if (factor_x < T(0) || factor_y < T(0))
                throw std::invalid_argument("reducing factors cannot be negative");
            else
            {
                this->width = TScalar(this->width / factor_x);
                this->height = TScalar(this->height / factor_y);
            }
            return *this;
        }

        /** \brief Resizes this rectangle according to reducing factors (const vcl::vect::Vector&).
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values for 'factor' raise an invalid_argument exception.
        */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        MyType& shrink(const vcl::vect::Vector<T, Ksize>& vect)
        {
            switch (Ksize)
            {
            case 0:
                throw std::invalid_argument("factors vectors cannot be empty");
                return *this;
            case 1:
                return shrink(vect[0], vect[0]);
            default:
                return shrink(vect[0], vect[1]);
            }
        }

        /** \brief Resizes this rectangle according to reducing factors (const std::vector&).
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        MyType& shrink(const std::vector<T>& vect)
        {
            switch (vect.size())
            {
            case 0:
                throw std::invalid_argument("factors vectors cannot be empty");
                return *this;
            case 1:
                return shrink(vect[0], vect[0]);
            default:
                return shrink(vect[0], vect[1]);
            }
        }

        /** \brief Resizes this rectangle according to reducing factors (const std::array&).
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values for 'factor' raise an invalid_argument exception.
        */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        MyType& shrink(const std::array<T, Ksize>& arr)
        {
            switch (Ksize)
            {
            case 0:
                throw std::invalid_argument("factors vectors cannot be empty");
                return *this;
            case 1:
                return shrink(arr[0], arr[0]);
            default:
                return shrink(arr[0], arr[1]);
            }
        }

        /** \brief Resizes this rectangle according to a pair of reducing factors (const std::pair&).
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values raise an invalid_argument exception.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline MyType& shrink(const std::pair<T, U>& pair)
        {
            return shrink(pair.first, pair.second);
        }

        /** \brief Resizes this rectangle according to a reducing factor.
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& operator /= (const T& factor)
        {
            return shrink(factor, factor);
        }

        /** \brief Resizes this rectangle according to reducing factors.
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values for 'factor' raise an invalid_argument exception.
        */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        inline MyType& operator /= (const vcl::vect::Vector<T, Ksize>& vect)
        {
            return shrink(vect);
        }

        /** \brief Resizes this rectangle according to reducing factors.
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values for 'factor' raise an invalid_argument exception.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& operator /= (const std::vector<T>& vect)
        {
            return shrink(vect);
        }

        /** \brief Resizes this rectangle according to reducing factors.
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values for 'factor' raise an invalid_argument exception.
        */
        template<typename T, const size_t Ksize>
            requires std::is_arithmetic_v<T>
        inline MyType& operator /= (const std::array<T, Ksize>& arr)
        {
            return shrink(arr);
        }

        /** \brief Resizes this rectangle according to a pair of reducing factors (const std::pair&).
        * Factors less than 1 augment the size of this rectangle.
        * Negative and null values raise an invalid_argument exception.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline MyType& operator /= (const std::pair<T, U>& pair)
        {
            return shrink(pair);
        }

        /** \brief Shrinking operator / (const TScalar) */
        template<typename T>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator / (MyType lhs, const T value)
        {
            return lhs /= value;
        }

        /** \brief Shrinking operator / (const vcl::vect::Vector<>) */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator / (MyType lhs, const vcl::vect::Vector<T, S>& vect)
        {
            return lhs /= vect;
        }

        /** \brief Shrinking operator / (const std::vector<>) */
        template<typename T>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator / (MyType lhs, const std::vector<T>& vect)
        {
            return lhs /= vect;
        }

        /** \brief Shrinking operator / (const std::array<>) */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        friend inline MyType operator / (MyType lhs, const std::array<T, S>& arr)
        {
            return lhs /= arr;
        }

        /** \brief Shrinking operator / (const std::pair<>) */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        friend inline MyType operator / (MyType lhs, const std::pair<T, U>& rhs)
        {
            return lhs /= rhs;
        }

        /** \brief Shrinks this rectangle from its center (1 scalar factor).
        * Shrinks this rectangle from its center as the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 augment this rectangle.
        * \sa \c scale_from_center() and \c skrink()
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& shrink_from_center(const T& factor)
        {
            return shrink_from_center(factor, factor);
        }

        /** \brief Shrinks this rectangle from its center (2 scalar factors).
        * Shrinks this rectangle from its center as the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 augment this rectangle.
        * \sa \c scale_from_center() and \c skrink()
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        MyType& shrink_from_center(const T& factor_x, const U& factor_y)
        {
            const vcl::utils::DimsT<TScalar> prev_dims = dims();
            shrink(factor_x, factor_y);
            return move(0.5 * (prev_dims - dims()));
        }

        /** \brief Shrinks this rectangle from its center (1 vcl::utils:VectorT<>).
        * Shrinks this rectangle from its center as the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 augment this rectangle.
        * \sa \c scale_from_center() and \c skrink()
        */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        MyType& shrink_from_center(const vcl::vect::Vector<T, S>& vect)
        {
            switch (vect.size())
            {
            case 0:
                throw std::invalid_argument("factor vectors cannot be empty");
                return *this;
            case 1:
                return shrink_from_center(vect[0]);
            default:
                return shrink_from_center(vect[0], vect[1]);
            }
        }

        /** \brief Shrinks this rectangle from its center (1 std::vector<>).
        * Shrinks this rectangle from its center as the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 augment this rectangle.
        * \sa \c scale_from_center() and \c skrink()
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        MyType& shrink_from_center(const std::vector<T>& vect)
        {
            switch (vect.size())
            {
            case 0:
                throw std::invalid_argument("factor vectors cannot be empty");
                return *this;
            case 1:
                return shrink_from_center(vect[0]);
            default:
                return shrink_from_center(vect[0], vect[1]);
            }
        }

        /** \brief Shrinks this rectangle from its center (1 std::array<>).
        * Shrinks this rectangle from its center as the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 augment this rectangle.
        * \sa \c scale_from_center() and \c skrink()
        */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        MyType& shrink_from_center(const std::array<T, S>& arr)
        {
            switch (S)
            {
            case 0:
                throw std::invalid_argument("factor arrays cannot be empty");
                return *this;
            case 1:
                return shrink_from_center(arr[0]);
            default:
                return shrink_from_center(arr[0], arr[1]);
            }
        }

        /** \brief Shrinks this rectangle from its center (1 std::pair).
        * Shrinks this rectangle from its center as the  origin
        * of the scaling. As such, modifies the top-left corner
        * position.
        * Values less than 1.0 augment this rectangle.
        * \sa \c scale_from_center() and \c skrink()
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline MyType& shrink_from_center(const std::pair<T, U>& pair) noexcept
        {
            shrink_from_center(pair.first, pair.second);
        }


        //--- Inset / Outset ------------------------------------------------
        /** \brief Reduces the dimensions of this rectangle (1 scalar argument).
        * Also, modifies accordingly the position of this rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& inset(const T& offset) noexcept
        {
            return inset(offset, offset);
        }

        /** \brief Reduces the dimensions of this rectangle (2 scalar arguments).
        * Also, modifies accordingly the position of this rectangle.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline MyType& inset(const T& offset_x, const U& offset_y) noexcept
        {
           return crop(TScalar(offset_x), TScalar(offset_y));
        }

        /** \brief Reduces the dimensions of this rectangle (1 Dims argument).
        * Negative values for argument 'incr' augment the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& inset(const vcl::utils::DimsT<T>& incr) noexcept
        {
            return inset(incr.width(), incr.height());
        }

        /** \brief Reduces the dimensions of this rectangle (1 Offsets argument).
        * Negative values for argument 'incr' augment the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& inset(const vcl::utils::OffsetsT<T>& incr) noexcept
        {
            return inset(incr.dx(), incr.dy());
        }

        /** \brief Reduces the dimensions of this rectangle (1 vcl::vectors::Vect2<> argument).
        * Negative values for argument 'incr' augment the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& inset(const vcl::vect::Vect2<T>& vect) noexcept
        {
            return inset(vect.x(), vect.y());
        }

        /** \brief Reduces the dimensions of this rectangle (1 std::vector argument).
        * Negative values for argument 'incr' augment the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& inset(const std::vector<T>& vect) noexcept
        {
            if (vect.size() > 1)
                return inset(vect[0], vect[1]);
            else
                return inset(vect[0], vect[0]);
        }

        /** \brief Reduces the dimensions of this rectangle (1 std::array argument).
        * Negative values for argument 'incr' augment the size of the rectangle.
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline MyType& inset(const std::array<T, S>& arr) noexcept
        {
            if (S > 1)
                return inset(arr[0], arr[1]);
            else
                return inset(arr[0], arr[0]);
        }

        /** \brief Reduces the dimensions of this rectangle (1 std::pair argument).
        * Also, modifies accordingly the position of this rectangle.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline MyType& inset(const std::pair<T, U>& pair) noexcept
        {
            return inset(pair.first, pair.second);
        }

        /** \brief Augments the dimensions of this rectangle (1 scalar argument).
        * Also, modifies accordingly the position of this rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& outset(const T& offset) noexcept
        {
            return outset(offset, offset);
        }

        /** \brief Augments the dimensions of this rectangle (2 scalar arguments).
        * Also, modifies accordingly the position of this rectangle.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline MyType& outset(const T& offset_x, const U& offset_y) noexcept
        {
            auto x_offset = std::is_unsigned_v<T> ? (long long)offset_x : offset_x;
            auto y_offset = std::is_unsigned_v<U> ? (long long)offset_y : offset_y;
            return crop(-x_offset, -y_offset);
        }

        /** \brief Augments the dimensions of this rectangle (1 Dims argument).
        * Negative values for argument 'incr' decrease the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& outset(const vcl::utils::DimsT<T>& incr) noexcept
        {
            return outset(incr.width(), incr.height());
        }

        /** \brief Augments the dimensions of this rectangle (1 vcl::vectors::Vect2<> argument).
        * Negative values for argument 'incr' decrease the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& outset(const vcl::vect::Vect2<T>& incr) noexcept
        {
            return outset(incr.x, incr.y);
        }

        /** \brief Augments the dimensions of this rectangle (1 std::vector argument).
        * Negative values for argument 'incr' decrease the size of the rectangle.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& outset(const std::vector<T>& incr) noexcept
        {
            if (incr.size() > 1)
                return outset(incr[0], incr[1]);
            else
                return outset(incr[0], incr[0]);
        }

        /** \brief Augments the dimensions of this rectangle (1 std::array argument).
        * Negative values for argument 'incr' decrease the size of the rectangle.
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline MyType& outset(const std::array<T, S>& incr) noexcept
        {
            if (S > 1)
                return outset(incr[0], incr[1]);
            else
                return outset(incr[0], incr[0]);
        }


        //--- Intersection / Union / Containment ----------------------------
        /** \brief Returns true if this rectangle contains a specified position (2 scalar args). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline const bool contains(const T x, const U y) const noexcept
        {
            return this->x <= x && x <= right_x() && this->y <= y && y <= bottom_y();
        }

        /** \brief Returns true if this rectangle contains a specified position (1 Pos argument). */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline const bool contains(vcl::utils::PosT<T>& pos) const noexcept
        {
            return contains(pos.x(), pos.y());
        }

        /** \brief Returns true if this rectangle contains a specified position (1 std::pair argument). */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline const bool contains(std::pair<T, U>& pair) const noexcept
        {
            return contains(pair.first, pair.second);
        }

        /** \brief Returns true if this rectangle contains the 'other' one.
        * \sa does_embed().
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline const bool contains(vcl::graphitems::RectT<T>& other) const noexcept
        {
            return does_embed(other);
        }

        /** \brief Returns true if this rectangle fully contains the 'other' one.
        * \sa contains(const RectT<T>&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline const bool does_embed(vcl::graphitems::RectT<T>& other) const noexcept
        {
            return intersection(other) == other;
        }

        /** \brief Returns true if this rectangle intersects with the 'other' one. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline bool does_intersect(const vcl::graphitems::RectT<T>& other) const noexcept
        {
            return other.bottom_y() >= this->y &&
                other.y <= bottom_y() &&
                other.right_x() >= this->x &&
                other.x <= right_x();
        }

        /** \brief Returns the intersection of this rectangle with the 'other' one. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        MyType& intersection_rect(const vcl::graphitems::RectT<T>& other) noexcept
        {
            if (does_intersect(other))
                return MyType( vcl::utils::PosT<TScalar>(vcl::utils::max(this->x, other.x),
                                                         vcl::utils::max(this->y, other.y)),
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
            requires std::is_arithmetic_v<T>
        MyType& union_rect(const vcl::graphitems::RectT<T>& other, const bool b_strict = true) noexcept
        {
            if (b_strict && !does_intersect(other))
                return *this;
            else
                return MyType(vcl::utils::PosT<TScalar>(vcl::utils::min(this->x, other.x),
                                                        vcl::utils::min(this->y, other.y)),
                              vcl::utils::PosT<TScalar>(vcl::utils::max(right_x(), other.right_x()),
                                                        vcl::utils::max(bottom_y(), other.bottom_y())) );
        }

        /** \brief Wrapper to the non-strict union of two rectangles. 
        * \sa union_rect().
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& operator + (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return union_rect(other, false);
        }

        /** \brief In-place non-strict union of this rectangle with an 'other' one. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline MyType& operator += (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return *this = union_rect(other, false);
        }

        /** \brief Returns true if this rectangle is fully embedded in the 'other' one or if it equals it. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline const bool operator <= (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return other.does_embed(*this);
        }

        /** \brief Returns true if this rectangle is fully embedded in the 'other' one. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline const bool operator < (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return *this != other && other.does_embed(*this);
        }

        /** \brief Returns true if this rectangle fully embeds in the 'other' one or if it equals it. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline const bool operator >= (const vcl::graphitems::RectT<T>& other) noexcept
        {
            return does_embed(other);
        }

        /** \brief Returns true if this rectangle fully embeds in the 'other' one. */
        template<typename T>
            requires std::is_arithmetic_v<T>
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
