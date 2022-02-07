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
#include <cstdarg>
#include <sstream>
#include <utility>
#include <vector>

#include <opencv2/core/matx.hpp>  // to get access to cv::Vec<_Tp, cn>

export module vectors.vector;


//===========================================================================
namespace vcl {
    namespace vect {

        //-----------------------------------------------------------------------
        /** \brief the generic class for vectors.
        */
        export
        template<typename TScalar, const size_t Ksize>
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

            /** \brief Filling constructor (single scalar).
            */
            template<typename T>
            inline Vector<TScalar, Ksize>(const T& value)
                : MyBaseType()
            {
                fill(value);
            }

            /** \brief Constructor with Ksize number of scalar args */
            inline Vector<TScalar, Ksize>(size_t n, ...)
                : MyBaseType()
            {
                va_list components;
                va_start(components, n);
                TScalar* ptr = begin();
                while (n-- && ptr != end())
                    *ptr++ = clipped(va_arg(components, TScalar));
                va_end(components);
            }

            /** \brief Copy constructor (const&).
            */
            template<typename T, const size_t S>
            inline Vector<TScalar, Ksize>(const vcl::vect::Vector<T, S>& other)
                : MyBaseType()
            {
                copy(other);
            }

            /** \brief Move constructor (&&).
            */
            template<typename T, const size_t S>
            inline Vector<TScalar, Ksize>(vcl::vect::Vector<T, S>&& other)
                : MyBaseType()
            {
                copy(&other);
            }

            /** \brief Constructor (const std::array&).
            */
            template<typename T, size_t S>
            inline Vector<TScalar, Ksize>(const std::array<T, S>& other)
                : MyBaseType()
            {
                copy(other);
            }

            /** \brief Constructor (const std::vector&).
            */
            template<typename T>
            inline Vector<TScalar, Ksize>(const std::vector<T>& vect)
                : MyBaseType()
            {
                copy(vect);
            }


            //---  Destructor   -------------------------------------------------
            virtual inline ~Vector<TScalar, Ksize>()
            {}


            //---   fill()   ----------------------------------------------------
            /** \brief Fills vectors with a single scalar value. */
            template<typename T>
            inline void fill(const T scalar_value)
            {
                const TScalar val = clipped(scalar_value);
                for (auto it = begin(); it != end(); *it++ = val);
            }


            //---   equality operators   ----------------------------------------
            /** \brief operator == (vcl::vect::Vector) */
            template<typename T, size_t S>
            inline bool operator == (const vcl::vect::Vector<T, S>& other)
            {
                const T* pot = other.cbegin();
                for (TScalar* ptr = this->begin(); ptr != this->end() && pot < other.cend(); )
                    if (*ptr++ != *pot++)
                        return false;
                return true;
            }

            /** \brief operator == (std::array) */
            template<typename T, size_t S>
            inline bool operator == (const std::array<T, S>& other)
            {
                const T* pot = other.cbegin();
                for (TScalar* ptr = this->begin(); ptr != this->end() && pot < other.cend(); )
                    if (*ptr++ != *pot++)
                        return false;
                return true;
            }

            /** \brief operator == (std::array, vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline bool operator == (const std::array<T, S>& lhs, const MyType& rhs)
            {
                const TScalar* rit = rhs.cbegin();
                for (auto lit = lhs.cbegin(); lit != lhs->cend() && rit != rhs.cend(); )
                    if (*lit++ != *rit++)
                        return false;
                return true;
            }

            /** \brief operator == (std::vector) */
            template<typename T>
            inline bool operator == (const std::vector<T>& other)
            {
                const T* pot = other.cbegin();
                for (TScalar* ptr = this->cbegin(); ptr != this->cend() && pot < other.cend(); )
                    if (*ptr++ != *pot++)
                        return false;
                return true;
            }

            /** \brief operator == (std::vector, vcl::vect::Vector) */
            template<typename T>
            friend inline bool operator == (const std::vector<T>& lhs, const MyType& rhs)
            {
                const TScalar* rit = rhs.cbegin();
                for (auto lit = lhs.cbegin(); lit != lhs->cend() && rit != rhs.cend(); )
                    if (*lit++ != *rit++)
                        return false;
                return true;
            }

            /** \brief operator != (vcl::vect::Vector) */
            template<typename T, size_t S>
            inline bool operator != (const vcl::vect::Vector<T, S>& other)
            {
                return !(*this == other);
            }

            /** \brief operator == (std::array) */
            template<typename T, size_t S>
            inline bool operator != (const std::array<T, S>& other)
            {
                return !(*this == other);
            }

            /** \brief operator == (std::array, vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline bool operator != (const std::array<T, S>& lhs, const MyType& rhs)
            {
                return !(rhs == lhs);
            }

            /** \brief operator == (std::vector) */
            template<typename T>
            inline bool operator != (const std::vector<T>& other)
            {
                return !(*this == other);
            }

            /** \brief operator == (std::vector, vcl::vect::Vector) */
            template<typename T>
            friend inline bool operator != (const std::vector<T>& lhs, const MyType& rhs)
            {
                return !(rhs == lhs);
            }


            //---   copy()   ----------------------------------------------------
            /** \brief Copies a const vcl::vect::Vector. */
            template<typename T, size_t S>
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
            inline void copy(const std::array<T, S>& other)
            {
                auto ot = other.cbegin();
                for (TScalar* ptr = begin(); ptr != end() && ot != other.cend(); )
                    *ptr++ = clipped(*ot++);
            }

            /** \brief Copies into a std::array. */
            template<typename T, size_t S>
            friend inline void copy(std::array<T, S>&& lhs, MyType&& rhs)
            {
                TScalar p_rhs = &rhs.begin();
                for (T* p_lhs = &lhs.begin(); p_lhs != &lhs.end() && p_rhs != &rhs.end(); )
                    *p_lhs++ = T(*p_rhs++);
            }

            /** \brief Copies a const std::vector. */
            template<typename T>
            inline void copy(const std::vector<T>& other)
            {
                auto ot = other.cbegin();
                for (TScalar* ptr = begin(); ptr != this->end() && ot != other.cend(); )
                    *ptr++ = clipped(*ot++);
            }

            /** \brief Copies into a std::vector. */
            template<typename T>
            friend inline void copy(std::vector<T>&& lhs, MyType&& rhs)
            {
                TScalar p_rhs = &rhs.begin();
                for (T* p_lhs = lhs.begin(); p_lhs != lhs.end() && p_rhs != &rhs.end() + Ksize; )
                    *p_lhs++ = T(*p_rhs++);
            }


            //---   assignment operator   ---------------------------------------
            /** \brief assign operator with specified value */
            template<typename T>
            inline MyType& operator= (const T scalar_value)
            {
                fill(scalar_value);
                return *this;
            }

            /** \brief assign operator (const vcl::vect::Vector). */
            template<typename T, size_t S>
            inline MyType& operator= (vcl::vect::Vector<T, S>& other)
            {
                copy(other);
                return *this;
            }

            /** \brief assign operator (std::array). */
            template<typename T, size_t S>
            inline MyType& operator= (const std::array<T, S>& other)
            {
                copy(other);
                return *this;
            }

            /** \brief assign operator (std::vector). */
            template<typename T>
            inline MyType& operator= (const std::vector<T>& other)
            {
                copy(other);
                return *this;
            }

            //---   operator +=   -----------------------------------------------
            /** \brief += operator (reference) */
            template<typename T, size_t S>
            inline MyType& operator+= (const vcl::vect::Vector<T, S>& rhs)
            {
                add(rhs);
                return *this;
            }

            /** \brief += operator (const TScalar) */
            inline MyType& operator+= (const char value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const unsigned char value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const short value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const unsigned short value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const int value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const unsigned int value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const long value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const unsigned long value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const long long value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const unsigned long long value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const float value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const double value)
            {
                add(value);
                return *this;
            }

            inline MyType& operator+= (const long double value)
            {
                add(value);
                return *this;
            }

            /** \brief += operator (const std::array) */
            template<typename T, size_t S>
            inline MyType& operator+= (const std::array<T, S>& rhs)
            {
                add(rhs);
                return *this;
            }

            /** \brief += operator (std::array, vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline std::array<T, S>& operator+= (std::array<T, S> lhs, const MyType& rhs)
            {
                add(lhs, rhs);
                return lhs;
            }

            /** \brief += operator (const std::vector) */
            template<typename T>
            inline MyType& operator+= (const std::vector<T>& rhs)
            {
                add(rhs);
                return *this;
            }

            /** \brief += operator (std::vector, vcl::vect::Vector) */
            template<typename T>
            friend inline std::vector<T>& operator+= (std::vector<T> lhs, const MyType& rhs)
            {
                add(lhs, rhs);
                return lhs;
            }

            //---   operator +   ------------------------------------------------
            /** \brief + operator (const reference).
            * Note: optimized for chained v1+v2+v3
            */
            template<typename T, size_t S>
            friend inline MyType operator+ (MyType lhs, const vcl::vect::Vector<T, S>& rhs)
            {
                return lhs += rhs;
            }

            /** \brief + operator (const TScalar) */
            friend inline MyType operator+ (MyType lhs, const char value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const unsigned char value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const short value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const unsigned short value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const int value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const unsigned int value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const long value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const unsigned long value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const long long value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const unsigned long long value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const float value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const double value)
            {
                return lhs += value;
            }

            friend inline MyType operator+ (MyType lhs, const long double value)
            {
                return lhs += value;
            }

            /** \brief + operator (const TScalar, vcl::vect::Vector) */
            friend inline MyType operator+ (const char value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const unsigned char value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const short value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const unsigned short value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const int value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const unsigned int value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const long value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const unsigned long value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const  long long value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const unsigned  long long value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const float value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const double value, MyType rhs)
            {
                return rhs += value;
            }

            friend inline MyType operator+ (const long double value, MyType rhs)
            {
                return rhs += value;
            }

            /** \brief + operator (const std::array) */
            template<typename T, size_t S>
            friend inline MyType operator+ (MyType lhs, const std::array<T, S>& rhs)
            {
                return lhs += rhs;
            }

            /** \brief + operator (const std::array, vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline std::array<T, S> operator+ (std::array<T, S> lhs, MyType rhs)
            {
                return lhs += rhs;
            }

            /** \brief + operator (const std::vector) */
            template<typename T>
            friend inline MyType operator+ (MyType lhs, const std::vector<T> rhs)
            {
                return lhs += rhs;
            }

            /** \brief + operator (const std::vector, vcl::vect::Vector) */
            template<typename T>
            friend inline std::vector<T> operator+ (std::vector<T> lhs, MyType rhs)
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
            inline MyType& operator-= (const vcl::vect::Vector<T, S>& rhs)
            {
                sub(rhs);
                return *this;
            }

            /** \brief -= operator (const TScalar) */
            inline MyType& operator-= (const char value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const unsigned char value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const short value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const unsigned short value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const int value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const unsigned int value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const long value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const unsigned long value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const long long value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const unsigned long long value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const float value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const double value)
            {
                sub(value);
                return *this;
            }

            inline MyType& operator-= (const long double value)
            {
                sub(value);
                return *this;
            }

            /** \brief -= operator (const std::array) */
            template<typename T, size_t S>
            inline MyType& operator-= (const std::array<T, S>& rhs)
            {
                sub(rhs);
                return *this;
            }

            /** \brief -= operator (std::array, vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline std::array<T, S>& operator-= (std::array<T, S> lhs, const MyType& rhs)
            {
                sub(lhs, rhs);
                return lhs;
            }

            /** \brief -= operator (const std::vector) */
            template<typename T>
            inline MyType& operator-= (const std::vector<T>& rhs)
            {
                sub(rhs);
                return *this;
            }

            /** \brief -= operator (std::vector, vcl::vect::Vector) */
            template<typename T>
            friend inline std::vector<T>& operator-= (std::vector<T> lhs, const MyType& rhs)
            {
                sub(lhs, rhs);
                return lhs;
            }

            //---   operator -   ------------------------------------------------
            /** \brief + operator (const reference).
            * Note: optimized for chained v1-v2-v3
            */
            template<typename T, size_t S>
            friend inline MyType operator- (MyType lhs, const vcl::vect::Vector<T, S>& rhs)
            {
                return lhs -= rhs;
            }

            /** \brief - operator (const TScalar) */
            friend inline MyType operator- (MyType lhs, const char value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const unsigned char value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const short value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const unsigned short value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const int value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const unsigned int value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const long value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const unsigned long value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const long long value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const unsigned long long value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const float value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const double value)
            {
                return lhs -= value;
            }

            friend inline MyType operator- (MyType lhs, const long double value)
            {
                return lhs -= value;
            }

            /** \brief - operator (const TScalar, vcl::vect::Vector) */
            friend inline MyType operator- (const char value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const unsigned char value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const short value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const unsigned short value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const int value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const unsigned int value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const long value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const unsigned long value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const  long long value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const unsigned  long long value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const float value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const double value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            friend inline MyType operator- (const long double value, MyType rhs)
            {
                return MyType(value) -= rhs;
            }

            /** \brief - operator (const std::array) */
            template<typename T, size_t S>
            friend inline MyType operator- (MyType lhs, const std::array<T, S>& rhs)
            {
                return lhs -= rhs;
            }

            /** \brief - operator (const std::array, vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline std::array<T, S> operator- (std::array<T, S> lhs, MyType rhs)
            {
                return lhs -= rhs;
            }

            /** \brief - operator (const std::vector) */
            template<typename T>
            friend inline MyType operator- (MyType lhs, const std::vector<T> rhs)
            {
                return lhs -= rhs;
            }

            /** \brief - operator (const std::vector, vcl::vect::Vector) */
            template<typename T>
            friend inline std::vector<T> operator- (const std::vector<T> lhs, MyType rhs)
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
            inline MyType& operator*= (const vcl::vect::Vector<T, S>& rhs)
            {
                mul(rhs);
                return *this;
            }

            /** \brief *= operator (const TScalar) */
            inline MyType& operator*= (const char value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const unsigned char value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const short value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const unsigned short value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const int value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const unsigned int value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const long value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const unsigned long value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const long long value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const unsigned long long value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const float value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const double value)
            {
                mul(value);
                return *this;
            }

            inline MyType& operator*= (const long double value)
            {
                mul(value);
                return *this;
            }

            /** \brief *= operator (const std::array) */
            template<typename T, size_t S>
            inline MyType& operator*= (const std::array<T, S>& rhs)
            {
                mul(rhs);
                return *this;
            }

            /** \brief *= operator (std::array, vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline std::array<T, S>& operator*= (std::array<T, S>& lhs, const MyType& rhs)
            {
                mul(lhs, rhs);
                return lhs;
            }

            /** \brief *= operator (const std::vector) */
            template<typename T>
            inline MyType& operator*= (const std::vector<T>& rhs)
            {
                mul(rhs);
                return *this;
            }

            /** \brief *= operator (std::vector, vcl::vect::Vector) */
            template<typename T>
            friend inline std::vector<T>& operator*= (std::vector<T>& lhs, const MyType& rhs)
            {
                mul(lhs, rhs);
                return lhs;
            }

            //---   operator *   ------------------------------------------------
            /** \brief + operator (const reference).
            * Note: optimized for chained v1*v2*v3
            */
            template<typename T, size_t S>
            friend inline MyType operator* (MyType lhs, const vcl::vect::Vector<T, S>& rhs)
            {
                return lhs *= rhs;
            }

            /** \brief * operator (vcl::vect::Vector, const TScalar) */
            friend inline MyType operator* (MyType lhs, const char value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const unsigned char value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const short value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const unsigned short value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const int value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const unsigned int value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const long value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const unsigned long value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const long long value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const unsigned long long value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const float value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const double value)
            {
                return lhs *= value;
            }

            friend inline MyType operator* (MyType lhs, const long double value)
            {
                return lhs *= value;
            }

            /** \brief * operator (const TScalar, vcl::vect::Vector) */
            friend inline MyType operator* (const char value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const unsigned char value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const short value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const unsigned short value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const int value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const unsigned int value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const long value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const unsigned long value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const  long long value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const unsigned  long long value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const float value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const double value, MyType rhs)
            {
                return rhs *= value;
            }

            friend inline MyType operator* (const long double value, MyType rhs)
            {
                return rhs *= value;
            }

            /** \brief * operator (const std::array) */
            template<typename T, size_t S>
            friend inline MyType operator* (MyType lhs, const std::array<T, S>& rhs)
            {
                return lhs *= rhs;
            }

            /** \brief * operator (const std::array, vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline std::array<T, S> operator* (std::array<T, S> lhs, MyType rhs)
            {
                return lhs *= rhs;
            }

            /** \brief * operator (const std::vector) */
            template<typename T>
            friend inline MyType operator* (MyType lhs, const std::vector<T> rhs)
            {
                return lhs *= rhs;
            }

            /** \brief * operator (const std::vector, vcl::vect::Vector) */
            template<typename T>
            friend inline std::vector<T> operator* (std::vector<T> lhs, MyType rhs)
            {
                return lhs *= rhs;
            }


            //---   operators /=   ----------------------------------------------
            /** \brief /= operator (const reference) */
            template<typename T, size_t S>
            inline MyType& operator/= (const vcl::vect::Vector<T, S>& rhs)
            {
                div(rhs);
                return *this;
            }

            /** \brief /= operator (const TScalar) */
            inline MyType& operator/= (const char value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const unsigned char value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const short value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const unsigned short value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const int value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const unsigned int value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const long value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const unsigned long value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const long long value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const unsigned long long value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const float value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const double value)
            {
                div(value);
                return *this;
            }

            inline MyType& operator/= (const long double value)
            {
                div(value);
                return *this;
            }

            /** \brief /= operator (const std::array) */
            template<typename T, size_t S>
            inline MyType& operator/= (const std::array<T, S>& rhs)
            {
                div(rhs);
                return *this;
            }

            /** \brief /= operator (std::array, vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline std::array<T, S>& operator/= (std::array<T, S> lhs, const MyType& rhs)
            {
                div(lhs, rhs);
                return lhs;
            }

            /** \brief /= operator (const std::vector) */
            template<typename T>
            inline MyType& operator/= (const std::vector<T>& rhs)
            {
                div(rhs);
                return *this;
            }

            /** \brief /= operator (std::vector, vcl::vect::Vector) */
            template<typename T>
            friend inline std::vector<T>& operator/= (std::vector<T> lhs, const MyType& rhs)
            {
                div(lhs, rhs);
                return lhs;
            }


            //---   operator /   ------------------------------------------------
            /** \brief / operator (const reference).
            * Note: optimized for chained v1/v2/v3
            */
            template<typename T, size_t S>
            friend inline MyType operator/ (MyType lhs, const vcl::vect::Vector<T, S>& rhs)
            {
                return lhs /= rhs;
            }

            /** \brief / operator (vcl::vect::Vector, const TScalar) */
            friend inline MyType operator/ (MyType lhs, const char value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const unsigned char value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const short value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const unsigned short value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const int value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const unsigned int value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const long value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const unsigned long value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const long long value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const unsigned long long value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const float value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const double value)
            {
                return lhs /= value;
            }

            friend inline MyType operator/ (MyType lhs, const long double value)
            {
                return lhs /= value;
            }

            /** \brief / operator (const T Scalar, vcl::vect::Vector) */
            friend inline MyType operator/ (const char value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const unsigned char value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const short value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const unsigned short value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const int value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const unsigned int value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const long value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const unsigned long value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const  long long value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const unsigned  long long value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const float value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const double value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            friend inline MyType operator/ (const long double value, MyType& rhs)
            {
                return MyType(value) /= rhs;
            }

            /** \brief / operator (const std::array) */
            template<typename T, size_t S>
            friend inline MyType operator/ (MyType lhs, const std::array<T, S>& rhs)
            {
                return lhs /= rhs;
            }

            /** \brief / operator (const std::array, vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline std::array<T, S> operator/ (std::array<T, S> lhs, MyType rhs)
            {
                return lhs /= rhs;
            }

            /** \brief / operator (const std::vector) */
            template<typename T>
            friend inline MyType operator/ (MyType lhs, const std::vector<T> rhs)
            {
                return lhs /= rhs;
            }

            /** \brief / operator (const std::vector, vcl::vect::Vector) */
            template<typename T>
            friend inline std::vector<T> operator/ (const std::vector<T> lhs, MyType rhs)
            {
                return lhs /= rhs;
            }


            //---   miscelaneous   ----------------------------------------------
            /** \brief simulates an interator over vector content.
            * \sa end().
            */
            inline TScalar* begin()
            {
                return this->val;
            }

            /** \brief simulates a const interator over vector content.
            * \sa end().
            */
            inline const TScalar* cbegin() const
            {
                return this->val;
            }

            /** \brief simulates an interator over vector content.
            * \sa begin().
            */
            inline TScalar* end()
            {
                return this->val + Ksize;
            }

            /** \brief simulates a const interator over vector content.
            * \sa cbegin().
            */
            inline const TScalar* cend() const
            {
                return this->val + Ksize;
            }

            /** \brief Returns the specified value clipped - does no clipping in this base class. */
            template<typename T>
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
            inline void add(const vcl::vect::Vector<T, S>& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); )
                    *it++ += *rit++;
            }

            /** \brief inplace add operation (scalar) */
            inline void add(const char value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const unsigned char value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const short value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const unsigned short value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const int value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const unsigned int value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const unsigned long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const long long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const unsigned long long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const float value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const double value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            inline void add(const long double value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it + value);
            }

            /** \brief inplace add operation (const std::array) */
            template<typename T, size_t S>
            inline void add(const std::array<T, S>& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                    *it = clipped(*it + *rit++);
            }

            /** \brief inplace add operation (std::array, const vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline void add(std::array<T, S>& lhs, const MyType& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                    *it++ += T(*rit++);
            }

            /** \brief inplace add operation (const std::vector) */
            template<typename T>
            inline void add(const std::vector<T>& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = this->begin(); it != this->end() && rit != rhs.end(); it++)
                    *it = clipped(*it + *rit++);
            }

            /** \brief inplace add operation (std::vector, const vcl::vect::Vector) */
            template<typename T>
            friend inline void add(std::vector<T>& lhs, const MyType& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                    *it++ += T(*rit++);
            }


            //---   sub()   -----------------------------------------------------
            /** \brief inplace sub operation (const reference) */
            template<typename T, size_t S>
            inline void sub(const vcl::vect::Vector<T, S>& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); )
                    *it++ -= *rit++;
            }

            /** \brief inplace sub operation (scalar) */
            inline void sub(const char value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const unsigned char value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const short value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const unsigned short value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const int value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const unsigned int value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const unsigned long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const long long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const unsigned long long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const float value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const double value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            inline void sub(const long double value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - value);
            }

            /** \brief inplace sub operation (const std::array) */
            template<typename T, size_t S>
            inline void sub(const std::array<T, S>& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it - *rit++);
            }

            /** \brief inplace sub operation (std::array, const vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline void sub(std::array<T, S>& lhs, const MyType& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                    *it++ -= T(*rit++);
            }

            /** \brief inplace sub operation (const std::vector) */
            template<typename T>
            inline void sub(const std::vector<T>& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = this->begin(); it != this->end() && rit != rhs.end(); it++)
                    *it = clipped(*it - *rit++);
            }

            /** \brief inplace sub operation (std::vector, const vcl::vect::Vector) */
            template<typename T>
            friend inline void sub(std::vector<T>& lhs, const MyType& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = lhs.begin(); it != lhs.end() && rit != rhs.cend(); )
                    *it++ -= T(*rit++);
            }


            //---   mul()   -----------------------------------------------------
            /** \brief inplace mul operation (const reference) */
            template<typename T, size_t S>
            inline void mul(const vcl::vect::Vector<T, S>& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); )
                    *it++ *= *rit++;
            }

            /** \brief inplace mul operation (scalar) */
            inline void mul(const char value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const unsigned char value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const short value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const unsigned short value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const int value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const unsigned int value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const unsigned long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const long long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const unsigned long long value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const float value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const double value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            inline void mul(const long double value)
            {
                for (auto it = this->begin(); it != this->end(); it++)
                    *it = clipped(*it * value);
            }

            /** \brief inplace mul operation (const std::array) */
            template<typename T, size_t S>
            inline void mul(const std::array<T, S>& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++)
                    *it = clipped(*it * *rit++);
            }

            /** \brief inplace mul operation (std::array, const vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline void mul(std::array<T, S>& lhs, const MyType& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = lhs.begin(); it != this->end() && rit != rhs.cend(); )
                    *it++ *= T(*rit++);
            }

            /** \brief inplace mul operation (const std::vector) */
            template<typename T>
            inline void mul(const std::vector<T>& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = this->begin(); it != this->end() && rit != rhs.end(); it++)
                    *it = clipped(*it * *rit++);
            }

            /** \brief inplace mul operation (std::vector, const vcl::vect::Vector) */
            template<typename T>
            friend inline void mul(std::vector<T>& lhs, const MyType& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = lhs.begin(); it != this->end() && rit != rhs.cend(); )
                    *it++ *= T(*rit++);
            }


            //---   div()   -----------------------------------------------------
            /** \brief inplace div operation (const reference) */
            template<typename T, size_t S>
            inline void div(const vcl::vect::Vector<T, S>& rhs)
            {
                auto rit = rhs.cbegin();
                for (auto it = this->begin(); it != this->end() && rit != rhs.cend(); it++, rit++)
                    if (*rit != TScalar(0))
                        *it /= *rit;
            }

            /** \brief inplace div operation (scalar) */
            inline void div(const char value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const unsigned char value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const short value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const unsigned short value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const int value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const unsigned int value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const long value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const unsigned long value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const long long value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const unsigned long long value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const float value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const double value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            inline void div(const long double value)
            {
                if (value != 0)
                    for (auto ptr = this->begin(); ptr != end(); )
                        *ptr++ = clipped(*ptr / value);
            }

            /** \brief inplace div operation (const std::array) */
            template<typename T, size_t S>
            inline void div(const std::array<T, S>& rhs)
            {
                auto rit = rhs.cbegin();
                for (TScalar* ptr = begin(); ptr != end() && rit != rhs.cend(); ptr++, rit++)
                    if (*rit != T(0))
                        *ptr = clipped(*ptr / *rit);
            }

            /** \brief inplace div operation (std::array, const vcl::vect::Vector) */
            template<typename T, size_t S>
            friend inline void div(std::array<T, S>& lhs, const MyType& rhs)
            {
                TScalar* ptr = rhs.begin();
                for (auto it = lhs.begin(); it != lhs.end() && ptr != rhs.end(); it++, ptr++)
                    if (*ptr != T(0))
                        *it = clipped(*it / *ptr);
            }

            /** \brief inplace div operation (const std::vector) */
            template<typename T>
            inline void div(const std::vector<T>& rhs)
            {
                auto rit = rhs.cbegin();
                for (TScalar* ptr = begin(); ptr != this->end() && rit != rhs.cend(); ptr++, rit++)
                    if (*rit != T(0))
                        *ptr = clipped(*ptr / *rit);
            }

            /** \brief inplace div operation (std::vector, const vcl::vect::Vector) */
            template<typename T>
            friend inline void div(std::vector<T>& lhs, const MyType& rhs)
            {
                TScalar* ptr = rhs.begin();
                for (auto it = lhs.begin(); it != lhs.end() && ptr != rhs.end(); it++, ptr++)
                    if (*ptr != T(0))
                        *it = clipped(*it / *ptr);
            }

        }; // end of class Vector<typename TScalar, const size_t Ksize>

    } // end of namespace vect
} // end of namespace vcl
