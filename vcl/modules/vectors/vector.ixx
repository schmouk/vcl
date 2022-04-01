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

#include <opencv2/core/matx.hpp>  // to get access to cv::Vec<_Tp, cn>

#include "vcl_concepts.h"

export module vectors.vector;


//===========================================================================
namespace vcl::vect {

    //-----------------------------------------------------------------------
    /** \brief the generic class for vectors.
    */
    export
    template<typename TScalar, const size_t Ksize>
        requires vcl::concepts::is_numeric<TScalar>
    class Vector : public cv::Vec<TScalar, Ksize>
    {
    public:
        typedef cv::Vec<TScalar, Ksize>           MyBaseType; //<! wrapper to the inherited class naming.
        typedef vcl::vect::Vector<TScalar, Ksize> MyType;     //<! wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline Vector<TScalar, Ksize>()
            : MyBaseType()
        {}

        /** \brief Constructor with scalar args.
        * Notice:  if one and only one scalar argument x_ is passed  at
        * construction time, then all the components of this vector are
        * assigned with this single scalar value (fill operation).
        */
        template<typename T, typename... Ts>
            requires vcl::concepts::is_numeric<T>
        inline Vector<TScalar, Ksize>(const T x_, Ts const... rest)
            : MyBaseType()
        {
            if (sizeof...(rest) > 0)
                _set(begin(), x_, rest...);
            else
                fill<T>(x_);
        }

        /** \brief Copy constructor (const&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline Vector<TScalar, Ksize>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType()
        {
            copy(other);
        }

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline Vector<TScalar, Ksize>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType()
        {
            copy(&other);
        }

        /** \brief Constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        explicit inline Vector<TScalar, Ksize>(const std::array<T, S>& arr)
            : MyBaseType()
        {
            copy(arr);
        }

        /** \brief Constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        explicit inline Vector<TScalar, Ksize>(const std::vector<T>& vect)
            : MyBaseType()
        {
            copy(vect);
        }

        /** \brief Constructor (const std::pair&).
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline Vector<TScalar, Ksize>(const std::pair<T, U>& pair)
            : MyBaseType()
        {
            copy(pair);
        }

        //---  Destructor   -------------------------------------------------
        virtual inline ~Vector<TScalar, Ksize>()
        {}


        //---   fill()   ----------------------------------------------------
        /** \brief Fills vectors with a single scalar value. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void fill(const T scalar_value)
        {
            const TScalar val = clipped(scalar_value);
            //for (auto it = begin(); it != end(); *it++ = val);
            for_each([val](TScalar& c){ c = val; });
        }


        //---   for_each()   ------------------------------------------------
        /** \brief Applies the parameter function to each component of this vcl::vector.
        * The argument must be a function, a method or a lambda and must
        * accept a component value as its parameter.
        */
        template<typename TFunc>
        inline void for_each(TFunc f)
        {
            for (auto it = begin(); it != end(); it++)
                f(*it);
        }


        //---   equality operators   ----------------------------------------
        /** \brief operator == (vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        bool operator == (const vcl::vect::Vector<T, S>& other)
        {
            constexpr bool same_sizes = (S == Ksize);
            if (!same_sizes)
                return false;

            const T* pot = other.cbegin();
            for (TScalar* ptr = this->begin(); ptr != this->end() && pot < other.cend(); )
                if (*ptr++ != TScalar(*pot++))
                    return false;
            return true;
        }

        /** \brief operator == (std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        bool operator == (const std::array<T, S>& other)
        {
            constexpr bool same_sizes = (S == Ksize);
            if (!same_sizes)
                return false;

            const T* pot = other.cbegin();
            for (TScalar* ptr = this->begin(); ptr != this->end() && pot < other.cend(); )
                if (*ptr++ != TScalar(*pot++))
                    return false;
            return true;
        }

        /** \brief operator == (std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend bool operator == (const std::array<T, S>& lhs, const MyType& rhs)
        {
            constexpr bool same_sizes = (S == Ksize);
            if (!same_sizes)
                return false;

            const TScalar* rit = rhs.cbegin();
            for (auto lit = lhs.cbegin(); lit != lhs->cend() && rit != rhs.cend(); )
                if (*lit++ != T(*rit++))
                    return false;
            return true;
        }

        /** \brief operator == (std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        bool operator == (const std::vector<T>& other)
        {
            if (other.size() != Ksize)
                return false;

            const T* pot = other.cbegin();
            for (TScalar* ptr = this->cbegin(); ptr != this->cend() && pot < other.cend(); )
                if (*ptr++ != TScalar(*pot++))
                    return false;
            return true;
        }

        /** \brief operator == (std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend bool operator == (const std::vector<T>& lhs, const MyType& rhs)
        {
            if (lhs.size() != Ksize)
                return false;

            const TScalar* rit = rhs.cbegin();
            for (auto lit = lhs.cbegin(); lit != lhs->cend() && rit != rhs.cend(); )
                if (*lit++ != T(*rit++))
                    return false;
            return true;
        }

        /** \brief operator == (std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        bool operator == (const std::pair<T, U>& other)
        {
            if (2 != Ksize)
                return false;

            const T* pot = other.cbegin();
            for (TScalar* ptr = this->cbegin(); ptr != this->cend() && pot < other.cend(); )
                if (*ptr++ != TScalar(*pot++))
                    return false;
            return true;
        }

        /** \brief operator == (std::vector, vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend bool operator == (const std::pair<T, U>& lhs, const MyType& rhs)
        {
            if (2 != Ksize)
                return false;

            const TScalar* rit = rhs.cbegin();
            for (auto lit = lhs.cbegin(); lit != lhs->cend() && rit != rhs.cend(); )
                if (*lit++ != T(*rit++))
                    return false;
            return true;
        }

        /** \brief operator != (vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline bool operator != (const vcl::vect::Vector<T, S>& other)
        {
            return !(*this == other);
        }

        /** \brief operator != (std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline bool operator != (const std::array<T, S>& other)
        {
            return !(*this == other);
        }

        /** \brief operator != (std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline bool operator != (const std::array<T, S>& lhs, const MyType& rhs)
        {
            return !(rhs == lhs);
        }

        /** \brief operator != (std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline bool operator != (const std::vector<T>& other)
        {
            return !(*this == other);
        }

        /** \brief operator != (std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline bool operator != (const std::vector<T>& lhs, const MyType& rhs)
        {
            return !(rhs == lhs);
        }

        /** \brief operator == (std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline bool operator != (const std::pair<T, U>& other)
        {
            return !(*this == other);
        }

        /** \brief operator == (std::vector, vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline bool operator != (const std::pair<T, U>& lhs, const MyType& rhs)
        {
            return !(rhs == lhs);
        }


        //---   copy()   ----------------------------------------------------
        /** \brief Copies a const vcl::vect::Vector. */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void copy(const vcl::vect::Vector<T, S>& other)
        {
            if (*this != other) {
                const T* pot = other.cbegin();
                for (TScalar* ptr = this->begin(); ptr != this->end() && pot < other.cend(); )
                    *ptr++ = clipped(*pot++);
            }
        }

        /** \brief Copies a const std::array. */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void copy(const std::array<T, S>& other)
        {
            auto ot = other.cbegin();
            for (TScalar* ptr = begin(); ptr != end() && ot != other.cend(); )
                *ptr++ = clipped(*ot++);
        }

        /** \brief Copies into a std::array. */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline void copy(std::array<T, S>&& lhs, MyType&& rhs)
        {
            TScalar p_rhs = &rhs.begin();
            for (T* p_lhs = &lhs.begin(); p_lhs != &lhs.end() && p_rhs != &rhs.end(); )
                *p_lhs++ = T(*p_rhs++);
        }

        /** \brief Copies a const std::vector. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void copy(const std::vector<T>& other)
        {
            auto ot = other.cbegin();
            for (TScalar* ptr = begin(); ptr != this->end() && ot != other.cend(); )
                *ptr++ = clipped(*ot++);
        }

        /** \brief Copies into a std::vector. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline void copy(std::vector<T>&& lhs, MyType&& rhs)
        {
            TScalar p_rhs = &rhs.begin();
            for (T* p_lhs = lhs.begin(); p_lhs != lhs.end() && p_rhs != &rhs.end() + Ksize; )
                *p_lhs++ = T(*p_rhs++);
        }

        /** \brief Copies a const std::pair. */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline void copy(const std::pair<T, U>& other)
        {
            auto ot = other.cbegin();
            for (TScalar* ptr = begin(); ptr != this->end() && ot != other.cend(); )
                *ptr++ = clipped(*ot++);
        }

        /** \brief Copies into a std::pair. */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline void copy(std::pair<T, U>&& lhs, MyType&& rhs)
        {
            TScalar p_rhs = &rhs.begin();
            for (T* p_lhs = lhs.begin(); p_lhs != lhs.end() && p_rhs != &rhs.end() + Ksize; )
                *p_lhs++ = T(*p_rhs++);
        }


        //---   assignment operator   ---------------------------------------
        /** \brief assign operator with specified value */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator= (const T scalar_value)
        {
            fill<T>(scalar_value);
            return *this;
        }

        /** \brief assign operator (const vcl::vect::Vector). */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator= (vcl::vect::Vector<T, S>& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (std::array). */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator= (const std::array<T, S>& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (std::vector). */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator= (const std::vector<T>& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator with std::pair */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline MyType& operator= (const std::pair<T, U>& pair)
        {
            copy(pair);
            return *this;
        }

        //---   operator +=   -----------------------------------------------
        /** \brief += operator (reference) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator+= (const vcl::vect::Vector<T, S>& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (const TScalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator+= (const T value)
        {
            add<T>(value);
            return *this;
        }

        /** \brief += operator (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator+= (const std::array<T, S>& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline std::array<T, S>& operator+= (std::array<T, S> lhs, const MyType& rhs)
        {
            add(lhs, rhs);
            return lhs;
        }

        /** \brief += operator (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator+= (const std::vector<T>& rhs)
        {
            add<T>(rhs);
            return *this;
        }

        /** \brief += operator (std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline std::vector<T>& operator+= (std::vector<T> lhs, const MyType& rhs)
        {
            add(lhs, rhs);
            return lhs;
        }

        /** \brief += operator (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline MyType& operator+= (const std::pair<T, U>& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator+= (std::pair<T, U> lhs, const MyType& rhs)
        {
            add(lhs, rhs);
            return lhs;
        }

        //---   operator +   ------------------------------------------------
        /** \brief + operator (const reference).
        * Note: optimized for chained v1+v2+v3
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator+ (MyType lhs, const vcl::vect::Vector<T, S>& rhs)
        {
            return lhs += rhs;
        }

        /** \brief + operator (const TScalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator+ (MyType lhs, const T value)
        {
            return lhs += value;
        }

        /** \brief + operator (const TScalar, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator+ (const T value, MyType rhs)
        {
            return rhs += value;
        }

        /** \brief + operator (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator+ (MyType lhs, const std::array<T, S>& rhs)
        {
            return lhs += rhs;
        }

        /** \brief + operator (const std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline std::array<T, S> operator+ (std::array<T, S> lhs, MyType rhs)
        {
            return lhs += rhs;
        }

        /** \brief + operator (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator+ (MyType lhs, const std::vector<T> rhs)
        {
            return lhs += rhs;
        }

        /** \brief + operator (const std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline std::vector<T> operator+ (std::vector<T> lhs, MyType rhs)
        {
            return lhs += rhs;
        }

        /** \brief + operator (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline MyType operator+ (MyType lhs, const std::pair<T, U>& rhs)
        {
            return lhs += rhs;
        }

        /** \brief + operator (const std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator+ (std::pair<T, U> lhs, MyType rhs)
        {
            return lhs += rhs;
        }

        /** \brief unary operator + */
        MyType& operator+()
        {
            return *this;
        }


        //---   operators -=   ----------------------------------------------
        /** \brief -= operator (const reference) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator-= (const vcl::vect::Vector<T, S>& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (const TScalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator-= (const T value)
        {
            sub<T>(value);
            return *this;
        }

        /** \brief -= operator (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator-= (const std::array<T, S>& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline std::array<T, S>& operator-= (std::array<T, S> lhs, const MyType& rhs)
        {
            sub(lhs, rhs);
            return lhs;
        }

        /** \brief -= operator (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator-= (const std::vector<T>& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline std::vector<T>& operator-= (std::vector<T> lhs, const MyType& rhs)
        {
            sub(lhs, rhs);
            return lhs;
        }

        /** \brief -= operator (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline MyType& operator-= (const std::pair<T, U>& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator-= (std::pair<T, U> lhs, const MyType& rhs)
        {
            sub(lhs, rhs);
            return lhs;
        }

        //---   operator -   ------------------------------------------------
        /** \brief - operator (const reference).
        * Note: optimized for chained v1-v2-v3
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator- (MyType lhs, const vcl::vect::Vector<T, S>& rhs)
        {
            return lhs -= rhs;
        }

        /** \brief - operator (const TScalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator- (MyType lhs, const T value)
        {
            return lhs -= value;
        }

        /** \brief - operator (const TScalar, vcl::vect::Vector) */
        friend inline MyType operator- (const char value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator- (const T value, MyType rhs)
        {
            return MyType(value) -= rhs;
        }

        /** \brief - operator (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator- (MyType lhs, const std::array<T, S>& rhs)
        {
            return lhs -= rhs;
        }

        /** \brief - operator (const std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline std::array<T, S> operator- (std::array<T, S> lhs, MyType rhs)
        {
            return lhs -= rhs;
        }

        /** \brief - operator (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator- (MyType lhs, const std::vector<T> rhs)
        {
            return lhs -= rhs;
        }

        /** \brief - operator (const std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline std::vector<T> operator- (const std::vector<T> lhs, MyType rhs)
        {
            return lhs -= rhs;
        }

        /** \brief - operator (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline MyType operator- (MyType lhs, const std::pair<T, U> rhs)
        {
            return lhs -= rhs;
        }

        /** \brief - operator (const std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator- (std::pair<T, U> lhs, MyType rhs)
        {
            return lhs -= rhs;
        }

        /** \brief unary operator - */
        MyType operator-()
        {
            return (*this * TScalar(-1));
        }


        //---   operators *=   ----------------------------------------------
        /** \brief *= operator (const reference) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator*= (const vcl::vect::Vector<T, S>& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (const TScalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator*= (const T value)
        {
            mul<T>(value);
            return *this;
        }

        /** \brief *= operator (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator*= (const std::array<T, S>& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline std::array<T, S>& operator*= (std::array<T, S>& lhs, const MyType& rhs)
        {
            mul(lhs, rhs);
            return lhs;
        }

        /** \brief *= operator (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator*= (const std::vector<T>& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline std::vector<T>& operator*= (std::vector<T>& lhs, const MyType& rhs)
        {
            mul(lhs, rhs);
            return lhs;
        }

        /** \brief *= operator (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline MyType& operator*= (const std::pair<T, U>& rhs)
        {
            mul(rhs);
            return *this;
        }

        /** \brief *= operator (std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator*= (std::pair<T, U> lhs, const MyType& rhs)
        {
            mul(lhs, rhs);
            return lhs;
        }

        //---   operator *   ------------------------------------------------
        /** \brief + operator (const reference).
        * Note: optimized for chained v1*v2*v3
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator* (MyType lhs, const vcl::vect::Vector<T, S>& rhs)
        {
            return lhs *= rhs;
        }

        /** \brief * operator (vcl::vect::Vector, const TScalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator* (MyType lhs, const T value)
        {
            return lhs *= value;
        }

        /** \brief * operator (const TScalar, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator* (const T value, MyType rhs)
        {
            return rhs *= value;
        }

        /** \brief * operator (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator* (MyType lhs, const std::array<T, S>& rhs)
        {
            return lhs *= rhs;
        }

        /** \brief * operator (const std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline std::array<T, S> operator* (std::array<T, S> lhs, MyType rhs)
        {
            return lhs *= rhs;
        }

        /** \brief * operator (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator* (MyType lhs, const std::vector<T> rhs)
        {
            return lhs *= rhs;
        }

        /** \brief * operator (const std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline std::vector<T> operator* (std::vector<T> lhs, MyType rhs)
        {
            return lhs *= rhs;
        }

        /** \brief * operator (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline MyType operator* (MyType lhs, const std::pair<T, U>rhs)
        {
            return lhs *= rhs;
        }

        /** \brief * operator (const std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator* (std::pair<T, U> lhs, MyType rhs)
        {
            return lhs *= rhs;
        }

        //---   operators /=   ----------------------------------------------
        /** \brief /= operator (const reference) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator/= (const vcl::vect::Vector<T, S>& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (const TScalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator/= (const T value)
        {
            div(value);
            return *this;
        }

        /** \brief /= operator (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator/= (const std::array<T, S>& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline std::array<T, S>& operator/= (std::array<T, S> lhs, const MyType& rhs)
        {
            div(lhs, rhs);
            return lhs;
        }

        /** \brief /= operator (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline MyType& operator/= (const std::vector<T>& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline std::vector<T>& operator/= (std::vector<T> lhs, const MyType& rhs)
        {
            div(lhs, rhs);
            return lhs;
        }

        /** \brief /= operator (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline MyType& operator/= (const std::pair<T, U>& rhs)
        {
            div(rhs);
            return *this;
        }

        /** \brief /= operator (std::pair, vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator/= (std::pair<T, U> lhs, const MyType& rhs)
        {
            div(lhs, rhs);
            return lhs;
        }

        //---   operator /   ------------------------------------------------
        /** \brief / operator (const reference).
        * Note: optimized for chained v1/v2/v3
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator/ (MyType lhs, const vcl::vect::Vector<T, S>& rhs)
        {
            return lhs /= rhs;
        }

        /** \brief / operator (vcl::vect::Vector, const TScalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator/ (MyType lhs, const T value)
        {
            return lhs /= value;
        }

        /** \brief / operator (const T Scalar, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator/ (const T value, MyType& rhs)
        {
            return MyType(value) /= rhs;
        }

        /** \brief / operator (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator/ (MyType lhs, const std::array<T, S>& rhs)
        {
            return lhs /= rhs;
        }

        /** \brief / operator (const std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline std::array<T, S> operator/ (std::array<T, S> lhs, MyType rhs)
        {
            return lhs /= rhs;
        }

        /** \brief / operator (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator/ (MyType lhs, const std::vector<T> rhs)
        {
            return lhs /= rhs;
        }

        /** \brief / operator (const std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline std::vector<T> operator/ (const std::vector<T> lhs, MyType rhs)
        {
            return lhs /= rhs;
        }

        /** \brief / operator (vcl::vect::Vector, const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline MyType operator/ (MyType lhs, const std::pair<T, U> rhs)
        {
            return lhs /= rhs;
        }

        /** \brief / operator (const std::pair, vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline MyType operator/ (const std::pair<T, U> lhs, MyType& rhs)
        {
            return lhs /= rhs;
        }

        //---   iterators   -------------------------------------------------
        /** \brief simulates an iterator over vector content.
        * \sa end().
        */
        inline TScalar* begin()
        {
            return this->val;
        }

        /** \brief simulates a const iterator over vector content.
        * \sa end().
        */
        inline const TScalar* cbegin() const
        {
            return this->val;
        }

        /** \brief simulates an iterator over vector content.
        * \sa begin().
        */
        inline TScalar* end()
        {
            return this->val + Ksize;
        }

        /** \brief simulates a const iterator over vector content.
        * \sa cbegin().
        */
        inline const TScalar* cend() const
        {
            return this->val + Ksize;
        }

        //---   miscelaneous   ----------------------------------------------
        /** \brief Returns the specified value clipped. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline const TScalar clipped(const T value)
        {
            return TScalar(value);
        }


        /** \brief Returns a string representation of this vector. */
        std::string repr()
        {
            std::ostringstream repr_ostr;

            repr_ostr << '(';
            auto it = this->begin();
            while (it != this->end() - 1)
                repr_ostr << *it++ << ", ";
            repr_ostr << *it << ')';

            return repr_ostr.str();
        }

        /** \brief Sets all components with value 0.
        * \sa method fill.
        */
        inline void zero()
        {
            this->fill(TScalar(0));
        }


    protected:
        //---   add()   -----------------------------------------------------
        /** \brief inplace add operation (const reference) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void add(const vcl::vect::Vector<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = clipped(*it + *rit++);
        }

        /** \brief inplace add operation (scalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void add(const T value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it + value);
        }

        /** \brief inplace add operation (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void add(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = clipped(*it + *rit++);
        }

        /** \brief inplace add operation (std::array, const vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline void add(std::array<T, S>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                *it++ += T(*rit++);
        }

        /** \brief inplace add operation (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void add(const std::vector<T>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); it++)
                *it = clipped(*it + *rit++);
        }

        /** \brief inplace add operation (std::vector, const vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline void add(std::vector<T>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                *it++ += T(*rit++);
        }

        /** \brief inplace add operation (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline void add(const std::pair<T, U>& rhs) noexcept
        {
            if (this->size() > 0)
                (*this[0]) = this->clipped((*this[0]) + TScalar(rhs.first));
            if (this->size() > 1)
                (*this[1]) = this->clipped((*this[1]) + TScalar(rhs.second));
        }

        /** \brief inplace add operation (std::pair, const vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline void add(std::pair<T, U>& lhs, const MyType& rhs) noexcept
        {
            if (rhs.size() > 0)
                lhs.first += T(rhs[0]);
            if (rhs.size() > 1)
                lhs.second += U(rhs[1]);
        }


        //---   sub()   -----------------------------------------------------
        /** \brief inplace sub operation (const reference) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void sub(const vcl::vect::Vector<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = clipped(*it - *rit++);
        }

        /** \brief inplace sub operation (scalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void sub(const T value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - value);
        }

        /** \brief inplace sub operation (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void sub(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it - *rit++);
        }

        /** \brief inplace sub operation (std::array, const vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline void sub(std::array<T, S>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                *it++ -= T(*rit++);
        }

        /** \brief inplace sub operation (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void sub(const std::vector<T>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); it++)
                *it = clipped(*it - *rit++);
        }

        /** \brief inplace sub operation (std::vector, const vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline void sub(std::vector<T>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                *it++ -= T(*rit++);
        }

        /** \brief inplace sub operation (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline void sub(const std::pair<T, U>& rhs) noexcept
        {
            if (this->size() > 0)
                (*this[0]) = this->clipped((*this[0]) - TScalar(rhs.first));
            if (this->size() > 1)
                (*this[1]) = this->clipped((*this[1]) - TScalar(rhs.second));
        }

        /** \brief inplace sub operation (std::pair, const vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline void sub(std::pair<T, U>& lhs, const MyType& rhs) noexcept
        {
            if (rhs.size() > 0)
                lhs.first -= T(rhs[0]);
            if (rhs.size() > 1)
                lhs.second -= U(rhs[1]);
        }


        //---   mul()   -----------------------------------------------------
        /** \brief inplace mul operation (const reference) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void mul(const vcl::vect::Vector<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = clipped(*it * *rit++);
        }

        /** \brief inplace mul operation (scalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void mul(const T value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = clipped(*it * value);
        }

        /** \brief inplace mul operation (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void mul(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = clipped(*it * *rit++);
        }

        /** \brief inplace mul operation (std::array, const vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline void mul(std::array<T, S>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != this->end() && rit != rhs.cend(); )
                *it++ *= T(*rit++);
        }

        /** \brief inplace mul operation (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void mul(const std::vector<T>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.end(); it++)
                *it = clipped(*it * *rit++);
        }

        /** \brief inplace mul operation (std::vector, const vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline void mul(std::vector<T>& lhs, const MyType& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = lhs.begin(); it != this->end() && rit != rhs.cend(); )
                *it++ *= T(*rit++);
        }

        /** \brief inplace mul operation (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline void mul(const std::pair<T, U>& rhs) noexcept
        {
            if (this->size() > 0)
                (*this[0]) = this->clipped((*this[0]) * TScalar(rhs.first));
            if (this->size() > 1)
                (*this[1]) = this->clipped((*this[1]) * TScalar(rhs.second));
        }

        /** \brief inplace mul operation (std::pair, const vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline void mul(std::pair<T, U>& lhs, const MyType& rhs) noexcept
        {
            if (rhs.size() > 0)
                lhs.first *= T(rhs[0]);
            if (rhs.size() > 1)
                lhs.second *= U(rhs[1]);
        }


        //---   div()   -----------------------------------------------------
        /** \brief inplace div operation (const reference) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void div(const vcl::vect::Vector<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++, rit++)
                if (*rit != T(0))
                    *it = clipped(*it / *rit);
        }

        /** \brief inplace div operation (scalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void div(const T value)
        {
            if (value != T(0))
                for (auto ptr = this->begin(); ptr != end(); )
                    *ptr++ = clipped(*ptr / value);
        }

        /** \brief inplace div operation (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void div(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (TScalar* ptr = begin(); ptr != end() && rit != rhs.cend(); ptr++, rit++)
                if (*rit != T(0))
                    *ptr = clipped(*ptr / *rit);
        }

        /** \brief inplace div operation (std::array, const vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline void div(std::array<T, S>& lhs, const MyType& rhs)
        {
            TScalar* ptr = rhs.begin();
            for (auto it = lhs.begin(); it != lhs.end() && ptr != rhs.end(); it++, ptr++)
                if (*ptr != TScalar(0))
                    *it = clipped(*it / *ptr);
        }

        /** \brief inplace div operation (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void div(const std::vector<T>& rhs)
        {
            auto rit = rhs.cbegin();
            for (TScalar* ptr = begin(); ptr != this->end() && rit != rhs.cend(); ptr++, rit++)
                if (*rit != T(0))
                    *ptr = clipped(*ptr / *rit);
        }

        /** \brief inplace div operation (std::vector, const vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline void div(std::vector<T>& lhs, const MyType& rhs)
        {
            TScalar* ptr = rhs.begin();
            for (auto it = lhs.begin(); it != lhs.end() && ptr != rhs.end(); it++, ptr++)
                if (*ptr != TScalar(0))
                    *it = clipped(*it / *ptr);
        }

        /** \brief inplace div operation (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline void div(const std::pair<T, U>& rhs) noexcept
        {
            if (this->size() > 0 && TScalar(rhs.first) != TScalar(0))
                (*this[0]) = this->clipped((*this[0]) * TScalar(rhs.first));
            if (this->size() > 1 && TScalar(rhs.second) != TScalar(0))
                (*this[1]) = this->clipped((*this[1]) * TScalar(rhs.second));
        }

        /** \brief inplace div operation (std::pair, const vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline void div(std::pair<T, U>& lhs, const MyType& rhs) noexcept
        {
            if (rhs.size() > 0 && rhs[0] != TScalar(0))
                rhs.first /=T(rhs[0]);
            if (rhs.size() > 1 && rhs[1] != TScalar(0))
                rhs.second /= U(rhs[1]);
        }


    private:
        //---   _set()   ----------------------------------------------------
        /** \brief Sets this vector components with a parameters pack. */
        template<typename T, typename... Ts>
        void _set(TScalar* it, const T& first, Ts const... rest) {
            if (it != end()) {
                *it++ = clipped(first);
                if constexpr (sizeof...(rest) > 0) {
                    _set(it, rest...);
                }
            }
        }

    }; // end of class Vector<typename TScalar, const size_t Ksize>

} // end of namespace vcl::vect
