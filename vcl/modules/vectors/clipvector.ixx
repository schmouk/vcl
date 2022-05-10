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
