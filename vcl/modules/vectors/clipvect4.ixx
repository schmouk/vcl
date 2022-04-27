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
#include <vector>

export module vectors.clipvect4;

import vectors.vector;
import vectors.vect4;


//===========================================================================
namespace vcl::vect {

    //=======================================================================
    // Forward declaration and Specializations
    export template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
        requires std::is_arithmetic_v<TScalar>
    class ClipVect4;

    /** \brief The class of 4D vectors with signed 8-bits components (8 bits). */
    export using ClipVect4c = ClipVect4<char, std::numeric_limits<char>::min(), std::numeric_limits<char>::max()>;

    /** \brief The class of 4D vectors with bytes components (8 bits). */
    export using ClipVect4b = ClipVect4<unsigned char, std::numeric_limits<unsigned char>::min(), std::numeric_limits<unsigned char>::max()>;

    /** \brief The class of 4D vectors with short components (16 bits). */
    export using ClipVect4s = ClipVect4<short, std::numeric_limits<short>::min(), std::numeric_limits<short>::max()>;

    /** \brief The class of 4D vectors with unsigned short components (16 bits). */
    export using ClipVect4us = ClipVect4<short, std::numeric_limits<unsigned short>::min(), std::numeric_limits<unsigned short>::max()>;

    /** \brief The class of 4D vectors with long int components (32 bits). */
    export using ClipVect4i = ClipVect4<long, std::numeric_limits<long>::min(), std::numeric_limits<long>::max()>;

    /** \brief The class of 4D vectors with unsigned long int components (32 bits). */
    export using ClipVect4ui = ClipVect4<unsigned long, std::numeric_limits<unsigned long>::min(), std::numeric_limits<unsigned long>::max()>;

    /** \brief The class of 4D vectors with long int components (32 bits). */
    export using ClipVect4ll = ClipVect4<long long, std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max()>;

    /** \brief The class of 4D vectors with unsigned long int components (32 bits). */
    export using ClipVect4ull = ClipVect4<unsigned long long, std::numeric_limits<unsigned long long>::min(), std::numeric_limits<unsigned long long>::max()>;

    /** \brief The class of 4D vectors with float components (32 bits). */
    export using ClipVect4f = ClipVect4<float, 0.0f, 1.0f>;

    /** \brief The class of 4D vectors with double components (64 bits). */
    export using ClipVect4d = ClipVect4<double, 0.0, 1.0>;


    //=======================================================================
    /** \brief the generic class for 4-D clipped vectors.
    *
    * \sa its specializations ClipVect4d, ClipVect4f, ClipVect4b, ClipVect4s, ClipVect4us, ClipVect4i, and ClipVect4ui.
    */
    template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
        requires std::is_arithmetic_v<TScalar>
    class ClipVect4 : public vcl::vect::Vect4<TScalar>
    {
    public:
        using MyBaseType =  vcl::vect::Vect4<TScalar>                ;  //!< wrapper to the inherited class naming..
        using MyType     =  vcl::vect::ClipVect4<TScalar, Kmin, Kmax>;  //!< wrapper to this class naming.
             //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect4<TScalar, Kmin, Kmax>()
            : MyBaseType()
        {
            this->fill(this->clipped(TScalar(0)));
        }

        /** \brief Constructor with value.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline ClipVect4<TScalar, Kmin, Kmax>(const T value)
            : MyBaseType()
        {
            this->fill<T>(this->clipped(value));
        }

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V, typename W>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V> && std::is_arithmetic_v<W>
        inline ClipVect4<TScalar, Kmin, Kmax>(const T x_, const U y_, const V z_ = V(0), const W w_ = W(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
            w(w_);
        }

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline ClipVect4<TScalar, Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline ClipVect4<TScalar, Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline ClipVect4<TScalar, Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::pair&).
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline ClipVect4<TScalar, Kmin, Kmax>(const std::pair<T, U>& pair)
            : MyBaseType(pair)
        {}

        /** \brief Copy constructor (const std::pair&, const std::pair&).
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline ClipVect4<TScalar, Kmin, Kmax>(const std::pair<T, U>& pair1, const std::pair<T, U>& pair2)
            : MyBaseType()
        {
            (*this)[0] = TScalar(pair1.first);
            (*this)[1] = TScalar(pair1.second);
            (*this)[2] = TScalar(pair2.first);
            (*this)[3] = TScalar(pair2.second);
        }

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect4<TScalar, Kmin, Kmax>()
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

        /** \brief component z accessor */
        inline const TScalar z() const
        {
            return (*this)[2];
        }

        /** \brief component z mutator */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline TScalar z(const T new_z)
        {
            return (*this)[2] = this->clipped(new_z);
        }

        /** \brief component w accessor */
        inline const TScalar w() const
        {
            return (*this)[3];
        }

        /** \brief component w mutator */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline TScalar w(const T new_w)
        {
            return (*this)[3] = this->clipped(new_w);
        }

        //---   miscelaneous   ----------------------------------------------
        /** \brief Returns the specified value clipped. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline const TScalar clipped(const T value) const
        {
            const auto val = std::is_unsigned_v<T> ? (long long)value : value;
            return val <= Kmin ? Kmin : (val >= Kmax ? Kmax : TScalar(val));
        }
    };

}
