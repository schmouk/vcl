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
#include <vector>
#include "vcl_concepts.h"

export module vectors.vect2;

import vectors.vector;


//===========================================================================
namespace vcl::vect {

//-----------------------------------------------------------------------
    // Forward declaration and Specializations
    export template<typename TScalar>
        requires vcl::concepts::is_numeric<TScalar>
    class Vect2;

    /** \brief The class of 2D vectors with 8bits signed components (8 bits). */
    export using Vect2c = Vect2<char>;
    //export typedef Vect2<char> Vect2c;

    /** \brief The class of 2D vectors with bytes components (8 bits). */
    //export using Vect2b = Vect2<unsigned char>;
    export typedef Vect2<unsigned char> Vect2b;

    /** \brief The class of 2D vectors with short components (16 bits). */
    export using Vect2s = Vect2<short>;
    //export typedef Vect2<short> Vect2s;

    /** \brief The class of 2D vectors with unsigned short components (16 bits). */
    export using Vect2us = Vect2<unsigned short>;
    //export typedef Vect2<unsigned short> Vect2us;

    /** \brief The class of 2D vectors with long int components (32 bits). */
    export using Vect2i = Vect2<long>;
    //export typedef Vect2<long> Vect2i;

    /** \brief The class of 2D vectors with unsigned long int components (32 bits). */
    export using Vect2ui = Vect2<unsigned long>;
    //export typedef Vect2<unsigned long> Vect2ui;

    /** \brief The class of 2D vectors with float components (32 bits). */
    export using Vect2f = Vect2<float>;
    //export typedef Vect2<float> Vect2f;

    /** \brief The class of 2D vectors with double components (64 bits). */
    export using Vect2d = Vect2<double>;
    //export typedef Vect2<double> Vect2d;

    /** \brief The class of 2D vectors with long double components (128 bits). */
    export using Vect2ld = Vect2<long double>;
    //export typedef Vect2<long double> Vect2ld;


    //-----------------------------------------------------------------------
    /** \brief the generic class for 2-D vectors.
    *
    * \sa its specializations Vect2d, Vect2f, Vect2b, Vect2s, Vect2us, Vect2i, and Vect2ui.
    */
    template<typename TScalar>
        requires vcl::concepts::is_numeric<TScalar>
    class Vect2 : public vcl::vect::Vector<TScalar, 2>
    {
    public:
        typedef vcl::vect::Vector<TScalar, 2> MyBaseType; //<! wrapper to the inherited class naming.
        typedef vcl::vect::Vect2<TScalar>     MyType;     //<! wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor (components default to 0).
        */
        inline Vect2<TScalar>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline Vect2<TScalar>(const T value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        /** \brief Constructor with values.
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline Vect2<TScalar>(const T x_, const U y_)
            : MyBaseType()
        {
            x(x_);
            y(y_);
        }

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline Vect2<TScalar>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (vcl::vect::Vector&&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline Vect2<TScalar>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline Vect2<TScalar>(const std::array<T, S>& arr)
            : MyBaseType(arr)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline Vect2<TScalar>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Copy constructor (const std::pair&).
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline Vect2<TScalar>(const std::pair<T, U>& pair)
            : MyBaseType(pair.first, pair.second)
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
            requires vcl::concepts::is_numeric<T>
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
            requires vcl::concepts::is_numeric<T>
        inline TScalar y(const T new_y)
        {
            return (*this)[1] = this->clipped(new_y);
        }

        //---   fill()   ----------------------------------------------------
        /** \brief Fills vectors with a single scalar value. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
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

        //---   equality operators   ----------------------------------------
        /** \brief operator == (vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline bool operator == (const vcl::vect::Vector<T, S>& other)
        {
            return MyBaseType::operator==(other);
        }

        /** \brief operator == (std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline bool operator == (const std::array<T, S>& other)
        {
            return MyBaseType::operator==(other);
        }

        /** \brief operator == (std::array, vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline bool operator == (const std::array<T, S>& lhs, const MyType& rhs)
        {
            return lhs == dynamic_cast<MyBaseType>(rhs);
        }

        /** \brief operator == (std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline bool operator == (const std::vector<T>& other)
        {
            return MyBaseType::operator==(other);
        }

        /** \brief operator == (std::vector, vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline bool operator == (const std::vector<T>& lhs, const MyType& rhs)
        {
            return lhs == dynamic_cast<MyBaseType>(rhs);
        }

        /** \brief operator == (std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        bool operator == (const std::pair<T, U>& pair)
        {
            return ((*this)[0] == TScalar(pair.first) && (*this)[1] == TScalar(pair.second));
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

        /** \brief operator != (std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        bool operator != (const std::pair<T, U>& pair)
        {
            return !(*this == pair);
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
                    *ptr++ = this->clipped(*pot++);
            }
        }

        /** \brief Copies a const std::array. */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void copy(const std::array<T, S>& other)
        {
            auto ot = other.cbegin();
            for (TScalar* ptr = this->begin(); ptr != this->end() && ot != other.cend(); )
                *ptr++ = this->clipped(*ot++);
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
            for (TScalar* ptr = this->begin(); ptr != this->end() && ot != other.cend(); )
                *ptr++ = this->clipped(*ot++);
        }

        /** \brief Copies into a std::vector. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline void copy(std::vector<T>&& lhs, MyType&& rhs)
        {
            TScalar p_rhs = &rhs.begin();
            for (T* p_lhs = lhs.begin(); p_lhs != lhs.end() && p_rhs != &rhs.end() + this->Ksize; )
                *p_lhs++ = T(*p_rhs++);
        }

        /** \brief Copies a const std::pair. */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline void copy(const std::pair<T, U>& pair)
        {
            (*this)[0] = this->clipped(pair.first);
            (*this)[1] = this->clipped(pair.second);
        }

        /** \brief Copies into a std::pair. */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline void copy(std::pair<T, U>&& pair, MyType&& rhs)
        {
            pair.first = T((*this)[0]);
            pair.second = U((*this)[1]);
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
        inline MyType& operator+= (const std::pair<T, U>& pair)
        {
            add(pair);
            return *this;
        }

        /** \brief += operator (std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator+= (std::pair<T, U> pair, const MyType& vect)
        {
            add(pair, vect);
            return pair;
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

        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline MyType operator+ (const T value, MyType rhs)
        {
            return MyType(value) += rhs;
        }

        /** \brief unary operator + */
        MyType& operator+()
        {
            return *this;
        }

        /** \brief + operator (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline MyType operator+ (MyType vect, const std::pair<T, U>& pair)
        {
            return vect += pair;
        }

        /** \brief + operator (const std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator+ (std::pair<T, U>& pair, MyType vect)
        {
            return pair += vect;
        }

        //---   operator -=   -----------------------------------------------
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
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline MyType& operator-= (const std::pair<T, U>& pair)
        {
            sub(pair);
            return *this;
        }

        /** \brief -= operator (std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator-= (std::pair<T, U> pair, const MyType& vect)
        {
            sub(pair, vect);
            return pair;
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

        /** \brief unary operator - */
        MyType operator-()
        {
            return (*this * TScalar(-1));
        }

        /** \brief - operator (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline MyType operator- (MyType vect, const std::pair<T, U>& pair)
        {
            return vect -= pair;
        }

        /** \brief - operator (const std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator- (std::pair<T, U>& pair, MyType vect)
        {
            return pair -= vect;
        }

        //---   operator *=   -----------------------------------------------
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
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline MyType& operator*= (const std::pair<T, U>& pair)
        {
            mul(pair);
            return *this;
        }

        /** \brief *= operator (std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator*= (std::pair<T, U> pair, const MyType& vect)
        {
            mul(pair, vect);
            return pair;
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
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline MyType operator* (MyType vect, const std::pair<T, U>& pair)
        {
            return vect *= pair;
        }

        /** \brief * operator (const std::pair, vcl::vect::Vect2) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline std::pair<T, U>& operator* (std::pair<T, U>& pair, MyType vect)
        {
            return pair *= vect;
        }

        //---   operator /=   -----------------------------------------------
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
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        inline MyType& operator/= (const std::pair<T, U>& pair)
        {
            div(pair);
            return *this;
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
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline MyType operator/ (MyType vect, const std::pair<T, U> pair)
        {
            return vect /= pair;
        }

        /** \brief / operator (const std::pair, vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U>
        friend inline MyType operator/ (const std::pair<T, U> pair, MyType& vect)
        {
            if (vect.x() != TScalar(0))
                pair.first /= vect.x();
            if (vect.y() != TScalar(0))
                pair.second /= vect.y();
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
                *it = this->clipped(*it + *rit++);
        }

        /** \brief inplace add operation (scalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void add(const T value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = this->clipped(*it + value);
        }

        /** \brief inplace add operation (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void add(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = this->clipped(*it + *rit++);
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
                *it = this->clipped(*it + *rit++);
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
        inline void add(const std::pair<T, U>& pair) noexcept
        {
            (*this[0]) = this->clipped((*this[0]) + TScalar(pair.first));
            (*this[1]) = this->clipped((*this[1]) + TScalar(pair.second));
        }

        /** \brief inplace add operation (std::pair, const vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline void add(std::pair<T, U>& pair, const MyType& vect) noexcept
        {
            pair.first += vect.x();
            pair.second += vect.y();
        }

        //---   sub()   -----------------------------------------------------
        /** \brief inplace sub operation (const reference) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void sub(const vcl::vect::Vector<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = this->clipped(*it - *rit++);
        }

        /** \brief inplace sub operation (scalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void sub(const T value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = this->clipped(*it - value);
        }

        /** \brief inplace sub operation (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void sub(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end(); it++)
                *it = this->clipped(*it - *rit++);
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
                *it = this->clipped(*it - *rit++);
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
        inline void sub(const std::pair<T, U>& pair) noexcept
        {
            (*this[0]) = this->clipped((*this[0]) - TScalar(pair.first));
            (*this[1]) = this->clipped((*this[1]) - TScalar(pair.second));
        }

        /** \brief inplace sub operation (std::pair, const vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline void sub(std::pair<T, U>& pair, const MyType& vect) noexcept
        {
            pair.first -= vect.x();
            pair.second -= vect.y();
        }

        //---   mul()   -----------------------------------------------------
        /** \brief inplace mul operation (const reference) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void mul(const vcl::vect::Vector<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = this->clipped(*it * *rit++);
        }

        /** \brief inplace mul operation (scalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void mul(const T value)
        {
            for (auto it = this->begin(); it != this->end(); it++)
                *it = this->clipped(*it * value);
        }

        /** \brief inplace mul operation (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void mul(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                *it = this->clipped(*it * *rit++);
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
                *it = this->clipped(*it * *rit++);
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
        inline void mul(const std::pair<T, U>& pair) noexcept
        {
            (*this[0]) = this->clipped((*this[0]) * TScalar(pair.first));
            (*this[1]) = this->clipped((*this[1]) * TScalar(pair.second));
        }

        /** \brief inplace mul operation (std::pair, const vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline void mul(std::pair<T, U>& pair, const MyType& vect) noexcept
        {
            pair.first *= vect.x();
            pair.second *= vect.y();
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
                    *it = this->clipped(*it / *rit);
        }

        /** \brief inplace div operation (scalar) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void div(const T value)
        {
            if (value != T(0))
                for (auto ptr = this->begin(); ptr != this->end(); )
                    *ptr++ = this->clipped(*ptr / value);
        }

        /** \brief inplace div operation (const std::array) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline void div(const std::array<T, S>& rhs)
        {
            auto rit = rhs.cbegin();
            for (TScalar* ptr = this->begin(); ptr != this->end() && rit != rhs.cend(); ptr++, rit++)
                if (*rit != T(0))
                    *ptr = this->clipped(*ptr / *rit);
        }

        /** \brief inplace div operation (std::array, const vcl::vect::Vector) */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        friend inline void div(std::array<T, S>& lhs, const MyType& rhs)
        {
            TScalar* ptr = rhs.begin();
            for (auto it = lhs.begin(); it != lhs.end() && ptr != rhs.end(); it++, ptr++)
                if (*ptr != TScalar(0))
                    *it = this->clipped(*it / *ptr);
        }

        /** \brief inplace div operation (const std::vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline void div(const std::vector<T>& rhs)
        {
            auto rit = rhs.cbegin();
            for (TScalar* ptr = this->begin(); ptr != this->end() && rit != rhs.cend(); ptr++, rit++)
                if (*rit != T(0))
                    *ptr = this->clipped(*ptr / *rit);
        }

        /** \brief inplace div operation (std::vector, const vcl::vect::Vector) */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        friend inline void div(std::vector<T>& lhs, const MyType& rhs)
        {
            TScalar* ptr = rhs.begin();
            for (auto it = lhs.begin(); it != lhs.end() && ptr != rhs.end(); it++, ptr++)
                if (*ptr != TScalar(0))
                    *it = this->clipped(*it / *ptr);
        }

        /** \brief inplace div operation (const std::pair) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        void div(const std::pair<T, U>& pair) noexcept
        {
            if (TScalar(pair.first) != TScalar(0))
                (*this[0]) = this->clipped((*this[0]) / TScalar(pair.first));
            if (TScalar(pair.second) != TScalar(0))
                (*this[1]) = this->clipped((*this[1]) / TScalar(pair.second));
        }

        /** \brief inplace div operation (std::pair, const vcl::vect::Vector) */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        friend inline void div(std::pair<T, U>& pair, const MyType& vect) noexcept
        {
            if (vect.x() != TScalar(0))
                pair.first *= vect.x();
            if (vect.y() != TScalar(0))
                pair.second *= vect.y();
        }

    };

}
