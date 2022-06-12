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

#include <algorithm>
#include <array>
#include <type_traits>
#include <utility>
#include <vector>

export module vectors.clipvector;

import vectors.vector;
import utils.base_funcs;


//===========================================================================
namespace vcl::vect {

    //=======================================================================
    // Forward declaration and Specializations
    /** \brief the generic class Clipped Vectors (i.e. with clipped components). */
    template<typename TScalar, const size_t Ksize, const TScalar Kmin, const TScalar Kmax>
        requires std::is_arithmetic_v<TScalar>
    class ClipVectorT;

    /** \brief The class of clipped vectors with signed 8-bits components (8 bits). */
    export
    template<const size_t Ksize>
    using ClipVector_c = ClipVectorT<char, Ksize, std::numeric_limits<char>::min(), std::numeric_limits<char>::max()>;

    /** \brief The class of 4D vectors with bytes components (8 bits). */
    export
    template<const size_t Ksize>
    using ClipVector_b = ClipVectorT<unsigned char, Ksize, std::numeric_limits<unsigned char>::min(), std::numeric_limits<unsigned char>::max()>;

    /** \brief The class of clipped vectors with short components (16 bits). */
    export
    template<const size_t Ksize>
    using ClipVector_s = ClipVectorT<short, Ksize, std::numeric_limits<short>::min(), std::numeric_limits<short>::max()>;
    
    export
    template<const size_t Ksize>
    using ClipVector = ClipVector_s<Ksize>;

    /** \brief The class of clipped vectors with unsigned short components (16 bits). */
    export
    template<const size_t Ksize>
    using ClipVector_us = ClipVectorT<unsigned short, Ksize, std::numeric_limits<unsigned short>::min(), std::numeric_limits<unsigned short>::max()>;

    /** \brief The class of clipped vectors with long int components (32 bits). */
    export
    template<const size_t Ksize>
    using ClipVector_i = ClipVectorT<long, Ksize, std::numeric_limits<long>::min(), std::numeric_limits<long>::max()>;

    /** \brief The class of clipped vectors with unsigned long int components (32 bits). */
    export
    template<const size_t Ksize>
    using ClipVector_ui = ClipVectorT<unsigned long, Ksize, std::numeric_limits<unsigned long>::min(), std::numeric_limits<unsigned long>::max()>;

    /** \brief The class of clipped vectors with long int components (32 bits). */
    export
    template<const size_t Ksize>
    using ClipVector_ll = ClipVectorT<long long, Ksize, std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max()>;

    /** \brief The class of clipped vectors with unsigned long int components (32 bits). */
    export
    template<const size_t Ksize>
    using ClipVector_ull = ClipVectorT<unsigned long long, Ksize, std::numeric_limits<unsigned long long>::min(), std::numeric_limits<unsigned long long>::max()>;

    /** \brief The class of clipped vectors with float components (32 bits). */
    export
    template<const size_t Ksize>
    using ClipVector_f = ClipVectorT<float, Ksize, 0.0f, 1.0f>;

    /** \brief The class of clipped vectors with double components (64 bits). */
    export
    template<const size_t Ksize>
    using ClipVector_d = ClipVectorT<double, Ksize, 0.0, 1.0>;


    //=======================================================================
    /** \brief the generic class Clipped Vectors.
    */
    template<typename TScalar, const size_t Ksize, const TScalar Kmin, const TScalar Kmax>
        requires std::is_arithmetic_v<TScalar>
    class ClipVectorT : public vcl::vect::VectorT<TScalar, Ksize>
    {
    public:
        using MyBaseType = vcl::vect::VectorT<TScalar, Ksize>;  //!< wrapper to the inherited class naming.
        using MyType = vcl::vect::ClipVectorT<TScalar, Ksize, Kmin, Kmax>;  //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVectorT<TScalar, Ksize, Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with scalar args.
        * Notice:  if one and only one scalar argument x_ is passed  at
        * construction time, then all the components of this vector are
        * assigned with this single scalar value (fill operation).
        */
        template<typename T, typename... Ts>
            requires std::is_arithmetic_v<T>
        inline ClipVectorT<TScalar, Ksize, Kmin, Kmax>(const T x_, Ts const... rest)
            : MyBaseType(x_, rest...)
        {}

        /** \brief Copy constructor (const&).
        */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        inline ClipVectorT<TScalar, Ksize, Kmin, Kmax>(const vcl::vect::VectorT<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires std::is_arithmetic_v<T>
        inline ClipVectorT<TScalar, Ksize, Kmin, Kmax>(vcl::vect::VectorT<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Constructor (const std::vector&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline ClipVectorT<TScalar, Ksize, Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline ClipVectorT<TScalar, Ksize, Kmin, Kmax>(const std::array<T, S>& arr)
            : MyBaseType(arr)
        {}

        /** \brief Constructor (const std::pair&).
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline ClipVectorT<TScalar, Ksize, Kmin, Kmax>(const std::pair<T, U>& pair)
            : MyBaseType(pair)
        {}


        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVectorT<TScalar, Ksize, Kmin, Kmax>()
        {}


        //---   miscelaneous   ----------------------------------------------
        /** \brief Returns the specified value clipped. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline const TScalar clipped(const T value) const
        {
            const auto val = std::is_unsigned_v<T> ? (long long)value : value;
            return vcl::utils::max(Kmin, vcl::utils::min(TScalar(val), Kmax));
        }
    };

}
