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
#include <utility>
#include <type_traits>
#include <vector>

export module vectors.vect2;

import vectors.vector;


//===========================================================================
namespace vcl::vect {

//-----------------------------------------------------------------------
    // Forward declaration and Specializations
    export template<typename TScalar>
        requires std::is_arithmetic_v<TScalar>
    class Vect2;

    /** \brief The class of 2D vectors with 8bits signed components (8 bits). */
    export using Vect2c = Vect2<char>;

    /** \brief The class of 2D vectors with bytes components (8 bits). */
    export using Vect2b = Vect2<unsigned char>;

    /** \brief The class of 2D vectors with short components (16 bits). */
    export using Vect2s = Vect2<short>;

    /** \brief The class of 2D vectors with unsigned short components (16 bits). */
    export using Vect2us = Vect2<unsigned short>;

    /** \brief The class of 2D vectors with long int components (32 bits). */
    export using Vect2i = Vect2<long>;

    /** \brief The class of 2D vectors with unsigned long int components (32 bits). */
    export using Vect2ui = Vect2<unsigned long>;

    /** \brief The class of 2D vectors with long long components (64 bits). */
    export using Vect2li = Vect2<long long>;

    /** \brief The class of 2D vectors with unsigned long long components (64 bits). */
    export using Vect2uli = Vect2<unsigned long long>;

    /** \brief The class of 2D vectors with float components (32 bits). */
    export using Vect2f = Vect2<float>;

    /** \brief The class of 2D vectors with double components (64 bits). */
    export using Vect2d = Vect2<double>;

    /** \brief The class of 2D vectors with long double components (128 bits). */
    export using Vect2ld = Vect2<long double>;


    //-----------------------------------------------------------------------
    /** \brief the generic class for 2-D vectors.
    *
    * \sa its specializations Vect2d, Vect2f, Vect2b, Vect2s, Vect2us, Vect2i, and Vect2ui.
    */
    template<typename TScalar>
        requires std::is_arithmetic_v<TScalar>
    class Vect2 : public vcl::vect::Vector<TScalar, 2>
    {
    public:
        using MyBaseType = vcl::vect::Vector<TScalar, 2> ;  //<! wrapper to the inherited class naming.
        using MyType     = vcl::vect::Vect2<TScalar>     ;  //<! wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor (components default to 0).
        */
        inline Vect2<TScalar>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vect2<TScalar>(const T value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        /** \brief Constructor with values.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline Vect2<TScalar>(const T x_, const U y_)
            : MyBaseType()
        {
            x(x_);
            y(y_);
        }

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline Vect2<TScalar>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (vcl::vect::Vector&&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline Vect2<TScalar>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Constructor (const std::vector&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vect2<TScalar>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline Vect2<TScalar>(const std::array<T, S>& arr)
            : MyBaseType(arr)
        {}

        /** \brief Constructor (const std::pair&).
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline Vect2<TScalar>(const std::pair<T, U>& pair)
            : MyBaseType(pair)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~Vect2<TScalar>()
        {}

        //---   Components accessors / mutators   --------------------------------------
        /** \brief component x accessor */
        inline const TScalar x() const
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
