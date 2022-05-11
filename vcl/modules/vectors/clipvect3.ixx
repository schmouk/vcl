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

export module vectors.clipvect3;

import vectors.vector;
import vectors.vect3;


//===========================================================================
namespace vcl::vect {

    //=======================================================================
    // Forward declaration and Specializations
    /** \brief The generic class of 3D vectors with clipped scalar components. */
    export template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
        requires std::is_arithmetic_v<TScalar>
    class ClipVect3T;

    /** \brief The class of 3D vectors with signed 8-bits components (8 bits). */
    export using ClipVect3c = ClipVect3T<char, std::numeric_limits<char>::min(), std::numeric_limits<char>::max()>;

    /** \brief The class of 3D vectors with bytes components (8 bits). */
    export using ClipVect3b = ClipVect3T<unsigned char, std::numeric_limits<unsigned char>::min(), std::numeric_limits<unsigned char>::max()>;

    /** \brief The class of 3D vectors with short components (16 bits). */
    export using ClipVect3s = ClipVect3T<short, std::numeric_limits<short>::min(), std::numeric_limits<short>::max()>;
    export using ClipVect3 = ClipVect3s;

    /** \brief The class of 3D vectors with unsigned short components (16 bits). */
    export using ClipVect3us = ClipVect3T<short, std::numeric_limits<unsigned short>::min(), std::numeric_limits<unsigned short>::max()>;

    /** \brief The class of 3D vectors with long int components (32 bits). */
    export using ClipVect3i = ClipVect3T<long, std::numeric_limits<long>::min(), std::numeric_limits<long>::max()>;

    /** \brief The class of 3D vectors with unsigned long int components (32 bits). */
    export using ClipVect3ui = ClipVect3T<unsigned long, std::numeric_limits<unsigned long>::min(), std::numeric_limits<unsigned long>::max()>;

    /** \brief The class of 3D vectors with long int components (32 bits). */
    export using ClipVect3ll = ClipVect3T<long long, std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max()>;

    /** \brief The class of 3D vectors with unsigned long int components (32 bits). */
    export using ClipVect3ull = ClipVect3T<unsigned long long, std::numeric_limits<unsigned long long>::min(), std::numeric_limits<unsigned long long>::max()>;

    /** \brief The class of 3D vectors with float components (32 bits). */
    export using ClipVect3f = ClipVect3T<float, 0.0f, 1.0f>;

    /** \brief The class of 3D vectors with double components (64 bits). */
    export using ClipVect3d = ClipVect3T<double, 0.0, 1.0>;


    //=======================================================================
    /** \brief the generic class for 3-D clipped vectors.
    *
    * \sa its specializations ClipVect3d, ClipVect3f, ClipVect3b, ClipVect3s, ClipVect3us, ClipVect3i, and ClipVect3ui.
    */
    template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
        requires std::is_arithmetic_v<TScalar>
    class ClipVect3T : public vcl::vect::Vect3T<TScalar>
    {
    public:
        using MyBaseType =  vcl::vect::Vect3T<TScalar>                ;  //!< shortcut to this class inherited class naming.
        using MyType     =  vcl::vect::ClipVect3T<TScalar, Kmin, Kmax>;  //!< shortcut to this class naming.
            
        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect3T<TScalar, Kmin, Kmax>()
            : MyBaseType()
        {
            this->fill(this->clipped(TScalar(0)));
        }

        /** \brief Constructor with value.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline ClipVect3T<TScalar, Kmin, Kmax>(const T value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
        inline ClipVect3T<TScalar, Kmin, Kmax>(const T x_, const U y_, const V z_ = V(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
        }

        /** \brief Copy constructor (const vcl::vect::VectorT&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline ClipVect3T<TScalar, Kmin, Kmax>(const vcl::vect::VectorT<T, S>& other)
            : MyBaseType()
        {
            this->copy(other);
        }

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline ClipVect3T<TScalar, Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType()
        {
            this->copy(vect);
        }

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline ClipVect3T<TScalar, Kmin, Kmax>(const std::array<T, S>& arr)
            : MyBaseType()
        {
            this->copy(arr);
        }

        /** \brief Copy constructor (const std::pair&).
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline ClipVect3T<TScalar, Kmin, Kmax>(const std::pair<T, U>& pair)
            : MyBaseType()
        {
            this->copy(pair);
        }

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect3T<TScalar, Kmin, Kmax>()
        {}

        //---   Components accessors / mutators   --------------------------------------
        /** \brief component x accessor */
        inline const TScalar& x() const
        {
            return (*this)[0];
        }

        /** \brief component x accessor */
        inline TScalar& x()
        {
            return (*this)[0];
        }

        /** \brief component x mutator */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline TScalar x(const T new_x)
        {
            return (*this)[0] = clipped(new_x);
        }

        /** \brief component y accessor */
        inline TScalar& y()
        {
            return (*this)[1];
        }

        /** \brief component y accessor */
        inline const TScalar& y() const
        {
            return (*this)[1];
        }

        /** \brief component y mutator */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline TScalar y(const T new_y)
        {
            return (*this)[1] = clipped(new_y);
        }

        /** \brief component z accessor */
        inline TScalar& z()
        {
            return (*this)[2];
        }

        /** \brief component z accessor */
        inline const TScalar& z() const
        {
            return (*this)[2];
        }

        /** \brief component z mutator */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline TScalar z(const T new_z)
        {
            return (*this)[2] = clipped(new_z);
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
