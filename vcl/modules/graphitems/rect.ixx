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
    /** \brief The class of rectangles with integer positions and unsigned integer dimensions (32 bits). */
    export typedef RectT<long> Rect;

    /** \brief The class of rectangles with float components (32 bits). */
    export typedef RectT<float> Rect_f;

    /** \brief The class of rectangles with double components (64 bits). */
    export typedef RectT<double> Rect_d;


    //=======================================================================
    /** \brief The generic class for rectangles.
    * 
    * Notice: this template class in vcl inherits from OpenCV class
    *   Rect_<_Tp>. meanwhile, it exposes a rather different API. Mostly:
    *       - the origin of the plane is at top-left  corner  of  screen,
    *         while  in  openCV  it is positionned at bottom-left corner.
    *         This means that in  vcl,  y_top  coordinate  gets  a  lower 
    *         value  than  y_bottom  coordinate.  In OpenCV,  the related
    *         values are inverted.
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
            : MyBaseType(other.left_x(), other.bottom_y(), other.width(), other.height())
        {}

        /** \brief Move constructor (&&).
        */
        inline RectT<TScalar>(MyType&& other)
            : MyBaseType(&other.left_x(), &other.bottom_y(), &other.width(), &other.height())
        {}

        /** \brief Constructor (4-D vcl::vector positions).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const vcl::vect::Vect4<T>& vect)
            : MyBaseType(TScalar(vect[0]),
                         TScalar(vect[3]),
                         TScalar(vect[1] - vect[0] + 1),
                         TScalar(vect[3] - vect[2] + 1))
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const std::array<T, S>& arr)
            : MyBaseType(vcl::vect::Vect4<T>(arr))
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const std::vector<T>& vect)
            : MyBaseType(vcl::vect::Vect4<T>(vect))
        {}

        /** \brief Constructor (4 scalar positions).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const T left_x, const T right_x, const T top_y, const T bottom_y)
            : MyBaseType(left_x, bottom_y, right_x - left_x + 1, bottom_y - top_y + 1)
        {}

        /** \brief Constructor (2 scalar positions + dimensions).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const T left_x, const T top_y, const vcl::utils::DimsT<T>& dims)
            : MyBaseType()
        {}

        /** \brief Constructor (top left position + dimensions).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const vcl::utils::PosT<T>& top_left,
                                const vcl::utils::DimsT<T>& dims)
            : MyBaseType()
        {
            set(top_left, dims);
        }

        /** \brief Constructor (2 opposite corners positions).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const vcl::utils::PosT<T>& top_left,
                                const vcl::utils::PosT<T>& bottom_right)
            : MyBaseType()
        {
            set(top_left, bottom_right);
        }

        /** \brief Constructor (top left position + width + height).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline RectT<TScalar>(const vcl::utils::PosT<T>& top_left,
                                const T width, const T height)
            : MyBaseType()
        {
            set(top_left, width, height);
        }

        //---  Destructor   -------------------------------------------------
        virtual inline ~RectT<TScalar>()
        {}

        //---  Accessors/Mutators   -----------------------------------------
        /** \brief component dx mutator */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline TScalar dx(const T new_dx)
        {
            return (*this)[0] = new_dx;
        }

        /** \brief component dx accessor */
        inline const TScalar dx() const
        {
            return (*this)[0];
        }

        /** \brief component dy mutator */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline TScalar dy(const T new_dy)
        {
            return (*this)[1] = new_dy;
        }

        /** \brief component dy accessor */
        inline const TScalar dy() const
        {
            return (*this)[1];
        }
    };

}
