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
module Utils;


//===========================================================================
#include <array>
#include <compare>
//#include <vector>


//===========================================================================
namespace vcl {

    //-----------------------------------------------------------------------
    // forward declarations.
    template<typename TScalar, const size_t Ksize> class Vector;

    /*
    template<typename TScalar> class Vec2;   // 2 coordinates vectors
    template<typename TScalar> class Vec3;   // 3 coordinates vectors
    template<typename TScalar> class Vec4;   // 4 coordinates vectors
    */


    //-----------------------------------------------------------------------
    /** \brief the generic class for vectors.
    */
    template<typename TScalar, const size_t Ksize>
    class Vector : public std::array<TScalar, Ksize>
    {
    public:
        typedef std::array<TScalar, Ksize> MyBaseType; //<! shortcut to this class inherited class naming.
        typedef Vector<TScalar, Ksize>     MyType;     //<! shortcut to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Constructor with a filling value (defaults to 0).
        * All components of this vector are set to a same specified value.
        */
        inline Vector<TScalar, Ksize>(const TScalar value = TScalar(0))
            : MyBaseType()
        {
            fill(value);
        }

        /** \brief Copy constructor (const).
        */
        inline Vector<TScalar, Ksize>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor.
        */
        inline Vector<TScalar, Ksize>(MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Constructor with specified const std::vector.
        */
        ///inline Vector<TScalar, Ksize>(const std::vector<TScalar>& vect)
        ///    : MyBaseType()
        ///{
        ///    copy(vect);
        ///}
        ///
        ////** \brief Constructor with specified std::vector.
        ///*/
        ///inline Vector<TScalar, Ksize>(std::vector<TScalar>& vect)
        ///    : MyBaseType()
        ///{
        ///    copy(vect);
        ///}

        /** \brief Constructor with specified const buffer.
        */
        inline Vector<TScalar, Ksize>(const TScalar buffer[Ksize])
            : MyBaseType()
        {
            copy(buffer);
        }

        /** \brief Constructor with specified buffer.
        */
        inline Vector<TScalar, Ksize>(TScalar buffer[Ksize])
            : MyBaseType()
        {
            copy(buffer);
        }

        //---  Destructor   -------------------------------------------------
        inline ~Vector<TScalar, Ksize>()
        {}

        //---   copy()   ----------------------------------------------------
        /** \brief Copies a const vcl::Vector. */
        inline void copy(const MyType& other)
        {
            for (TScalar* it = this->begin(), ot = other.cbegin(); it != this->end(); )
                *it++ = *ot++;
        }

        /** \brief Copies a vcl::Vector. */
        inline void copy(MyType& other)
        {
            for (TScalar* it = this->begin(), ot = other.begin(); it != this->end(); )
                *it++ = *ot++;
        }

        ////** \brief Copies a const std::vector. */
        ///inline void copy(const std::vector<TScalar>& other)
        ///{
        ///    TScalar* it = this->begin();
        ///    for (TScalar** ot = other.cbegin(); it != this->end && ot != other.end(); )
        ///        *it++ = *ot++;
        ///    // checks for length of other < length of this
        ///    while (it != this->end())
        ///        *it++ = TScalar(0);
        ///}
        ///
        ////** \brief Copies a std::vector. */
        ///inline void copy(std::vector<TScalar>& other)
        ///{
        ///    TScalar* it = this->begin();
        ///    for (TScalar** ot = other.begin(); it != this->end && ot != other.end(); )
        ///        *it++ = *ot++;
        ///    // checks for length of other < length of this
        ///    while (it != this->end())
        ///        *it++ = TScalar(0);
        ///}

        /** \brief Copies a const buffer. */
        inline void copy(const TScalar buffer[Ksize])
        {
            for (TScalar* it = this->begin(), b = buffer; it != this->end(); )
                *it++ = *b++;
        }

        /** \brief Copies a buffer. */
        inline void copy(TScalar buffer[Ksize])
        {
            for (TScalar* it = this->begin(), b = buffer; it != this->end(); )
                *it++ = *b++;
        }

        //---   assignment operator   ---------------------------------------
        /** \brief assign operator with specified value */
        inline MyType& operator= (const TScalar value)
        {
            fill(value);
            return *this;
        }

        /** \brief assign operator (const vcl::Vector). */
        inline MyType& operator= (const MyType& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (vcl::Vector). */
        inline MyType& operator= (MyType& other)
        {
            copy(other);
            return *this;
        }

        /** \brief assign operator (const buffer). */
        inline MyType& operator= (const TScalar buffer[Ksize])
        {
            copy(buffer);
            return *this;
        }

        /** \brief assign operator (buffer). */
        inline MyType& operator= (TScalar buffer[Ksize])
        {
            copy(buffer);
            return *this;
        }

        //---   operators += and  +   ---------------------------------------
        /** \brief += operator (const reference) */
        inline MyType& operator+= (const MyType& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (reference) */
        inline MyType& operator+= (MyType& rhs)
        {
            add(rhs);
            return *this;
        }

        /** \brief += operator (const TScalar) */
        inline MyType& operator+= (const TScalar value)
        {
            add(value);
            return *this;
        }

        ////** \brief += operator (const std::vector) */
        ///inline MyType& operator+= (const std::vector<TScalar>& rhs)
        ///{
        ///    add(rhs);
        ///    return *this;
        ///}
        ///
        ////** \brief += operator (std::vector) */
        ///inline MyType& operator+= (std::vector<TScalar>& rhs)
        ///{
        ///    add(rhs);
        ///    return *this;
        ///}

        /** \brief += operator (const buffer) */
        inline MyType& operator+= (const TScalar buffer[Ksize])
        {
            add(buffer);
            return *this;
        }

        /** \brief += operator (buffer) */
        inline MyType& operator+= (TScalar buffer[Ksize])
        {
            add(buffer);
            return *this;
        }

        /** \brief + operator (const reference).
        * Note: optimized for chained v1+v2+v3
        */
        friend inline MyType operator+ (MyType lhs, const MyType& rhs)
        {
            lhs.add(rhs);
            return lhs;
        }

        /** \brief + operator (reference).
        * Note: optimized for chained v1+v2+v3
        */
        friend inline MyType operator+ (MyType lhs, MyType& rhs)
        {
            lhs.add(rhs);
            return lhs;
        }

        /** \brief + operator (const TScalar) */
        friend inline MyType operator+ (MyType lhs, const TScalar value)
        {
            MyType vec(lhs);
            vec.add(value);
            return vec;
        }

        /** \brief + operator (const TScalar, vcl::Vector) */
        friend inline MyType operator+ (const TScalar value, MyType rhs)
        {
            return rhs + value;
        }

        /** \brief + operator (const buffer) */
        friend inline MyType& operator+ (MyType lhs, const TScalar buffer[Ksize])
        {
            lhs.add(buffer);
            return lhs;
        }

        /** \brief + operator (const buffer, vcl::Vector) */
        friend inline MyType& operator+ (const TScalar buffer[Ksize], MyType rhs)
        {
            MyType vec(rhs);
            vec.add(buffer);
            return vec;
        }

        //---   operators -= and  -   ---------------------------------------
        /** \brief -= operator (const reference) */
        inline MyType& operator-= (const MyType& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (reference) */
        inline MyType& operator-= (MyType& rhs)
        {
            sub(rhs);
            return *this;
        }

        /** \brief -= operator (const TScalar) */
        inline MyType& operator-= (const TScalar value)
        {
            sub(value);
            return *this;
        }

        ////** \brief -= operator (const std::vector) */
        ///inline MyType& operator-= (const std::vector<TScalar>& rhs)
        ///{
        ///    sub(rhs);
        ///    return *this;
        ///}
        ///
        ////** \brief -= operator (std::vector) */
        ///inline MyType& operator-= (std::vector<TScalar>& rhs)
        ///{
        ///    sub(rhs);
        ///    return *this;
        ///}

        /** \brief -= operator (const buffer) */
        inline MyType& operator-= (const TScalar buffer[Ksize])
        {
            sub(buffer);
            return *this;
        }

        /** \brief -= operator (buffer) */
        inline MyType& operator-= (TScalar buffer[Ksize])
        {
            sub(buffer);
            return *this;
        }

        /** \brief - operator (const reference).
        * Note: optimized for chained v1+v2+v3
        */
        friend inline MyType operator- (MyType lhs, const MyType& rhs)
        {
            lhs.sub(rhs);
            return lhs;
        }

        /** \brief - operator (reference).
        * Note: optimized for chained v1-v2-v3
        */
        friend inline MyType operator- (MyType lhs, MyType& rhs)
        {
            lhs.sub(rhs);
            return lhs;
        }

        /** \brief - operator (const TScalar) */
        friend inline MyType operator- (MyType lhs, const TScalar value)
        {
            MyType vec(lhs);
            vec.sub(value);
            return vec;
        }

        /** \brief - operator (const TScalar, vcl::Vector) */
        friend inline MyType operator- (const TScalar value, MyType rhs)
        {
            return rhs - value;
        }

        /** \brief - operator (const buffer) */
        friend inline MyType& operator- (MyType lhs, const TScalar buffer[Ksize])
        {
            lhs.sub(buffer);
            return lhs;
        }

        /** \brief - operator (const buffer, vcl::Vector) */
        friend inline MyType& operator- (const TScalar buffer[Ksize], MyType rhs)
        {
            MyType vec(rhs);
            vec.sub(buffer);
            return vec;
        }

        //---   miscelaneous   ----------------------------------------------
        /** \brief Sets all components with value 0.
        * \sa method fill.
        */
        inline void zero()
        {
            fill(TScalar(0));
        }

    protected:
        //---   add()   -----------------------------------------------------
        /** \brief inplace add operation (const reference) */
        inline void add(const MyType& rhs)
        {
            for (TScalar* it = this->begin(), rit = rhs.cbegin(); it != this->end(); )
                *it++ += *rit++;
        }

        /** \brief inplace add operation (reference) */
        inline void add(MyType& rhs)
        {
            for (TScalar* it = this->begin(), rit = rhs.begin(); it != this->end(); )
                *it++ += *rit++;
        }

        /** \brief inplace add operation (reference) */
        inline void add(const TScalar value)
        {
            for (TScalar* it = this->begin(), rhs = rhs.begin(); it != this->end(); )
                *it++ += value;
        }

        ////** \brief inplace add operation (const std::vector) */
        ///inline void add(const std::vector<TScalar>& rhs)
        ///{
        ///    for (TScalar* it = this->begin(), rit = rhs.cbegin(); it != this->end() && rit != rhs.end(); )
        ///        *it++ += *rit++;
        ///}
        ///
        ////** \brief inplace add operation (std::vector) */
        ///inline void add(std::vector<TScalar>& rhs)
        ///{
        ///    for (TScalar* it = this->begin(), rit = rhs.begin(); it != this->end() && rit != rhs.end(); )
        ///        *it++ += *rit++;
        ///}

        /** \brief inplace add operation (const buffer) */
        inline void add(const TScalar buffer[Ksize])
        {
            for (TScalar* it = this->begin(), b = buffer; it != this->end(); )
                *it++ += *b++;
        }

        /** \brief inplace add operation (buffer) */
        inline void add(TScalar buffer[Ksize])
        {
            for (TScalar* it = this->begin(), b = buffer; it != this->end(); )
                *it++ += *b++;
        }

        //---   sub()   -----------------------------------------------------
        /** \brief inplace add operation (const reference) */
        inline void sub(const MyType& rhs)
        {
            for (TScalar* it = this->begin(), rit = rhs.cbegin(); it != this->end(); )
                *it++ -= *rit++;
        }

        /** \brief inplace add operation (reference) */
        inline void sub(MyType& rhs)
        {
            for (TScalar* it = this->begin(), rit = rhs.begin(); it != this->end(); )
                *it++ -= *rit++;
        }

        /** \brief inplace add operation (reference) */
        inline void sub(const TScalar value)
        {
            for (TScalar* it = this->begin(), rhs = rhs.begin(); it != this->end(); )
                *it++ -= value;
        }

        ////** \brief inplace add operation (const std::vector) */
        ///inline void sub(const std::vector<TScalar>& rhs)
        ///{
        ///    for (TScalar* it = this->begin(), rit = rhs.cbegin(); it != this->end() && rit != rhs.end(); )
        ///        *it++ -= *rit++;
        ///}
        ///
        ////** \brief inplace add operation (std::vector) */
        ///inline void sub(std::vector<TScalar>& rhs)
        ///{
        ///    for (TScalar* it = this->begin(), rit = rhs.begin(); it != this->end() && rit != rhs.end(); )
        ///        *it++ -= *rit++;
        ///}

        /** \brief inplace add operation (const buffer) */
        inline void sub(const TScalar buffer[Ksize])
        {
            for (TScalar* it = this->begin(), b = buffer; it != this->end(); )
                *it++ -= *b++;
        }

        /** \brief inplace add operation (buffer) */
        inline void sub(TScalar buffer[Ksize])
        {
            for (TScalar* it = this->begin(), b = buffer; it != this->end(); )
                *it++ -= *b++;
        }

    };



    //export template<typename TScalar> class Vec2;   // 2 coordinates vectors
    //export template<typename TScalar> class Vec3;   // 3 coordinates vectors
    //export template<typename TScalar> class Vec4;   // 4 coordinates vectors

} // end of namespace vcl