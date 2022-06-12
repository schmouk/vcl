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

export module vectors.vect2;

import vectors.vector;


//===========================================================================
namespace vcl::vect {

//-----------------------------------------------------------------------
    // Forward declaration and Specializations
    /** \brief The generic class of 4D vectors with unclipped scalar components. */
    export template<typename TScalar>
        requires std::is_arithmetic_v<TScalar>
    class Vect2T;

    /** \brief The class of 2D vectors with 8bits signed components (8 bits). */
    export using Vect2c = Vect2T<char>;

    /** \brief The class of 2D vectors with bytes components (8 bits). */
    export using Vect2b = Vect2T<unsigned char>;

    /** \brief The class of 2D vectors with short components (16 bits). */
    export using Vect2s = Vect2T<short>;
    export using Vect2 = Vect2s;

    /** \brief The class of 2D vectors with unsigned short components (16 bits). */
    export using Vect2us = Vect2T<unsigned short>;

    /** \brief The class of 2D vectors with long int components (32 bits). */
    export using Vect2i = Vect2T<long>;

    /** \brief The class of 2D vectors with unsigned long int components (32 bits). */
    export using Vect2ui = Vect2T<unsigned long>;

    /** \brief The class of 2D vectors with long long components (64 bits). */
    export using Vect2li = Vect2T<long long>;

    /** \brief The class of 2D vectors with unsigned long long components (64 bits). */
    export using Vect2uli = Vect2T<unsigned long long>;

    /** \brief The class of 2D vectors with float components (32 bits). */
    export using Vect2f = Vect2T<float>;

    /** \brief The class of 2D vectors with double components (64 bits). */
    export using Vect2d = Vect2T<double>;

    /** \brief The class of 2D vectors with long double components (128 bits). */
    export using Vect2ld = Vect2T<long double>;


    //-----------------------------------------------------------------------
    /** \brief the generic class for 2-D vectors.
    *
    * \sa its specializations Vect2d, Vect2f, Vect2b, Vect2s, Vect2us, Vect2i, and Vect2ui.
    */
    template<typename TScalar>
        requires std::is_arithmetic_v<TScalar>
    class Vect2T : public vcl::vect::VectorT<TScalar, 2>
    {
    public:
        using MyBaseType = vcl::vect::VectorT<TScalar, 2> ;  //<! wrapper to the inherited class naming.
        using MyType     = vcl::vect::Vect2T<TScalar>     ;  //<! wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor (components default to 0).
        */
        inline Vect2T<TScalar>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vect2T<TScalar>(const T value)
            : MyBaseType()
        {
            this->fill(value);
        }

        /** \brief Constructor with values.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline Vect2T<TScalar>(const T x_, const U y_)
            : MyBaseType()
        {
            x(x_);
            y(y_);
        }

        /** \brief Copy constructor (const vcl::vect::VectorT&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline Vect2T<TScalar>(const vcl::vect::VectorT<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (vcl::vect::VectorT&&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline Vect2T<TScalar>(vcl::vect::VectorT<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Constructor (const std::vector&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vect2T<TScalar>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline Vect2T<TScalar>(const std::array<T, S>& arr)
            : MyBaseType(arr)
        {}

        /** \brief Constructor (const std::pair&).
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline Vect2T<TScalar>(const std::pair<T, U>& pair)
            : MyBaseType(pair)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~Vect2T<TScalar>()
        {}

        //---   Components accessors / mutators   --------------------------------------
        /** \brief component x accessor */
        inline TScalar& x()
        {
            return (*this)[0];
        }

        /** \brief component x accessor */
        inline const TScalar& x() const
        {
            return (*this)[0];
        }

        /** \brief component x mutator */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline TScalar x(const T new_x)
        {
            return (*this)[0] = this->clipped(new_x);
        }

        /** \brief component x accessor */
        inline TScalar& y()
        {
            return (*this)[1];
        }

        /** \brief component y accessor */
        inline const TScalar y() const
        {
            return (*this)[1];
        }

        /** \brief component y mutator */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline TScalar y(const T new_y)
        {
            return (*this)[1] = this->clipped(new_y);
        }

        //---   fill()   ----------------------------------------------------
        /** \brief Fills vectors with a single scalar value. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void fill(const T scalar_value)
        {
            (*this)[0] = (*this)[1] = this->clipped(scalar_value);
        }

        //---   for_each()   ------------------------------------------------
        /** \brief Applies the parameter function to each component of this vcl::vector.
        * The argument must be a function, a method or a lambda and must
        * accept a component value as its parameter.
        */
        template<typename TFunc>
        inline void for_each(TFunc f)
        {
            f((*this)[0]);
            f((*this)[1]);
        }

    };

}
