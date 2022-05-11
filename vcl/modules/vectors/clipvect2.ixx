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

#include <iostream>

#include <algorithm>
#include <array>
#include <type_traits>
#include <utility>
#include <vector>

export module vectors.clipvect2;

import vectors.vector;
import vectors.vect2;


//===========================================================================
namespace vcl::vect {

    //=======================================================================
    // Forward declaration and Specializations
    /** \brief The generic class of 2D vectors with clipped scalar components. */
    export template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
        requires std::is_arithmetic_v<TScalar>
    class ClipVect2T;

    /** \brief The class of 2D vectors with signed 8-bits components (8 bits). */
    export using ClipVect2c = ClipVect2T<char, std::numeric_limits<char>::min(), std::numeric_limits<char>::max()>;

    /** \brief The class of 2D vectors with bytes components (8 bits). */
    export using ClipVect2b = ClipVect2T<unsigned char, std::numeric_limits<unsigned char>::min(), std::numeric_limits<unsigned char>::max()>;

    /** \brief The class of 2D vectors with short components (16 bits). */
    export using ClipVect2s = ClipVect2T<short, std::numeric_limits<short>::min(), std::numeric_limits<short>::max()>;
    export using ClipVect2 = ClipVect2s;

    /** \brief The class of 2D vectors with unsigned short components (16 bits). */
    export using ClipVect2us = ClipVect2T<short, std::numeric_limits<unsigned short>::min(), std::numeric_limits<unsigned short>::max()>;

    /** \brief The class of 2D vectors with long int components (32 bits). */
    export using ClipVect2i = ClipVect2T<long, std::numeric_limits<long>::min(), std::numeric_limits<long>::max()>;

    /** \brief The class of 2D vectors with unsigned long int components (32 bits). */
    export using ClipVect2ui = ClipVect2T<unsigned long, std::numeric_limits<unsigned long>::min(), std::numeric_limits<unsigned long>::max()>;

    /** \brief The class of 2D vectors with long int components (32 bits). */
    export using ClipVect2ll = ClipVect2T<long long, std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max()>;

    /** \brief The class of 2D vectors with unsigned long int components (32 bits). */
    export using ClipVect2ull = ClipVect2T<unsigned long long, std::numeric_limits<unsigned long long>::min(), std::numeric_limits<unsigned long long>::max()>;

    /** \brief The class of 2D vectors with float components (32 bits). */
    export using ClipVect2f = ClipVect2T<float, 0.0f, 1.0f>;

    /** \brief The class of 2D vectors with double components (64 bits). */
    export using ClipVect2d = ClipVect2T<double, 0.0, 1.0>;


    //=======================================================================
    /** \brief the generic class for 2-D clipped vectors.
    *
    * \sa its specializations ClipVect2d, ClipVect2f, ClipVect2b, ClipVect2s, ClipVect2us, ClipVect2i, and ClipVect2ui.
    */
    template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
        requires std::is_arithmetic_v<TScalar>
    class ClipVect2T : public vcl::vect::Vect2T<TScalar>
    {
    public:
        using MyBaseType =  vcl::vect::Vect2T<TScalar>                ;  //!< wrapper to the inherited class naming.
        using MyType     =  vcl::vect::ClipVect2T<TScalar, Kmin, Kmax>;  //!< wrapper to this class naming.
        static inline size_t Ksize = 2;

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect2T<TScalar, Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline ClipVect2T<TScalar, Kmin, Kmax>(const T value)
            : MyBaseType()
        {
            this->fill(clipped(value));
        }

        /** \brief Constructor with values.
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline ClipVect2T<TScalar, Kmin, Kmax>(const T x_, const U y_)
            : MyBaseType()
        {
            x(x_);
            y(y_);
        }

        /** \brief Copy constructor (const vcl::vect::VectorT&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline ClipVect2T<TScalar, Kmin, Kmax>(const vcl::vect::VectorT<T, S>& other)
            : MyBaseType()
        {
            this->copy(other);
        }

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline ClipVect2T<TScalar, Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType()
        {
            this->copy(vect);
        }

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline ClipVect2T<TScalar, Kmin, Kmax>(const std::array<T, S>& arr)
            : MyBaseType()
        {
            this->copy(arr);
        }

        /** \brief Copy constructor (const std::pair&).
        */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        inline ClipVect2T<TScalar, Kmin, Kmax>(const std::pair<T, U>& pair)
            : MyBaseType()
        {
            this->copy(pair);
        }

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2T<TScalar, Kmin, Kmax>()
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


        //---   copy()   ----------------------------------------------------
        /** \brief Copies a const vcl::vect::VectorT. */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline void copy(const vcl::vect::VectorT<T, S>& other)
        {
            if (*this != other) {
                const T* pot = other.cbegin();
                for (TScalar* ptr = this->begin(); ptr != this->end() && pot < other.cend(); )
                    *ptr++ = clipped(*pot++);
            }
        }

        /** \brief Copies a const std::array. */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        inline void copy(const std::array<T, S>& other)
        {
            auto ot = other.cbegin();
            for (TScalar* ptr = this->begin(); ptr != this->end() && ot != other.cend(); )
                *ptr++ = clipped(*ot++);
        }

        /** \brief Copies into a std::array. */
        template<typename T, size_t S>
            requires std::is_arithmetic_v<T>
        friend inline void copy(std::array<T, S>&& lhs, MyType&& rhs)
        {
            TScalar p_rhs = &rhs.begin();
            for (T* p_lhs = &lhs.begin(); p_lhs != &lhs.end() && p_rhs != &rhs.end(); )
                *p_lhs++ = T(*p_rhs++);
        }

        /** \brief Copies a const std::vector. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void copy(const std::vector<T>& other)
        {
            auto ot = other.cbegin();
            for (TScalar* ptr = this->begin(); ptr != this->end() && ot != other.cend(); )
                *ptr++ = clipped(*ot++);
        }

        /** \brief Copies into a std::vector. */
        template<typename T>
            requires std::is_arithmetic_v<T>
        friend inline void copy(std::vector<T>&& lhs, MyType&& rhs)
        {
            TScalar p_rhs = &rhs.begin();
            for (T* p_lhs = lhs.begin(); p_lhs != lhs.end() && p_rhs != &rhs.end() + Ksize; )
                *p_lhs++ = T(*p_rhs++);
        }

        /** \brief Copies a const std::pair. */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        inline void copy(const std::pair<T, U>& other)
        {
            if (Ksize > 0)
                (*this)[0] = clipped(other.first);
            if (Ksize > 1)
                (*this)[1] = clipped(other.second);
        }

        /** \brief Copies into a std::pair. */
        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        friend inline void copy(std::pair<T, U>& lhs, MyType& rhs)
        {
            if (Ksize > 0)
                rhs[0] = clipped(lhs.first);
            if (Ksize > 1)
                rhs[1] = clipped(lhs.second);
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
