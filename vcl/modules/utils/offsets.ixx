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

#include "vcl_concepts.h"

export module utils.offsets;

import vectors.vect2;


//===========================================================================
namespace vcl::utils {

    //=======================================================================
    // Forward declaration
    export template<typename TScalar>
        requires vcl::concepts::is_numeric<TScalar>
    class OffsetsT;

    // Specializations
    /** \brief The class of 2D dimensions with short components (16 bits). */
    export using Offsets_s = OffsetsT<short>;

    /** \brief The class of 2D dimensions with unsigned short components (16 bits). */
    export using Offsets_us = OffsetsT<unsigned short>;

    /** \brief The class of 2D dimensions with long int components (32 bits). */
    export using Offsets_i = OffsetsT<long>;

    /** \brief The class of 2D dimensions with unsigned long int components (32 bits). */
    export using Offsets_ui = OffsetsT<unsigned long>;

    /** \brief The class of 2D dimensions with long long components (64 bits). */
    export using Offsets_li = OffsetsT<long long>;

    /** \brief The class of 2D dimensions with unsigned long long components (64 bits). */
    export using Offsets_uli = OffsetsT<unsigned long long>;

    /** \brief The class of 2D dimensions with float components (64 bits). */
    export using Offsets_f = OffsetsT<float>;

    /** \brief The class of 2D dimensions with double components (64 bits). */
    export using Offsets_d = OffsetsT<double>;

    /** \brief The class of 2D dimensions with long double components (128 bits). */
    export using Offsets_ld = OffsetsT<long double>;


    //=======================================================================
    /** \brief The generic class for 2D offsets. */
    template<typename TScalar>
        requires vcl::concepts::is_numeric<TScalar>
    class OffsetsT : public vcl::vect::Vect2<TScalar>
    {
    public:
        typedef vcl::vect::Vect2<TScalar>     MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::utils::OffsetsT<TScalar> MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline OffsetsT<TScalar>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline OffsetsT<TScalar>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline OffsetsT<TScalar>(const T dx, const U dy)
            : MyBaseType(dx, dy)
        {}

        /** \brief Copy constructor (const&).
        */
        inline OffsetsT<TScalar>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline OffsetsT<TScalar>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline OffsetsT<TScalar>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline OffsetsT<TScalar>(const std::array<T, S>& arr)
            : MyBaseType(arr)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline OffsetsT<TScalar>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~OffsetsT<TScalar>()
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
