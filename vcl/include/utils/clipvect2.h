#pragma once
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
#include <algorithm>
#include <array>
#include <compare>
#include <iostream>
#include <sstream>
#include <vector>

#include "utils/vect2.h"


//===========================================================================
namespace vcl {

    //=======================================================================
    // Forward declaration and Specializations
    template<typename TScalar, const TScalar Kmin, const TScalar Kmax> class ClipVect2;

    /** \brief The class of 2D vectors with bytes components (8 bits). */
    template<const char Kmin, const char Kmax> class ClipVect2c;

    /** \brief The class of 2D vectors with bytes components (8 bits). */
    template<const unsigned char Kmin, const unsigned char Kmax> class ClipVect2b;

    /** \brief The class of 2D vectors with short components (16 bits). */
    template<const short Kmin, const short Kmax> class ClipVect2s;

    /** \brief The class of 2D vectors with unsigned short components (16 bits). */
    template<const unsigned short Kmin, const unsigned short Kmax> class ClipVect2us;

    /** \brief The class of 2D vectors with int components (32 bits). */
    template<const int Kmin, const int Kmax> class ClipVect2i;

    /** \brief The class of 2D vectors with unsigned int components (32 bits). */
    template<const unsigned int Kmin, const unsigned int Kmax> class ClipVect2ui;

    /** \brief The class of 2D vectors with float components (32 bits). */
    template<const float Kmin, const float Kmax> class ClipVect2f;

    /** \brief The class of 2D vectors with double components (64 bits). */
    template<const double Kmin, const double Kmax> class ClipVect2d;


    //=======================================================================
    /** \brief the generic class for 2-D clipped vectors.
    *
    * \sa its specializations ClipVect2d, ClipVect2f, ClipVect2b, ClipVect2s, ClipVect2us, ClipVect2i, and ClipVect2ui.
    */
    template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
    class ClipVect2 : public Vect2<TScalar>
    {
    public:
        typedef Vect2<TScalar>                 MyBaseType; //!< shortcut to this class inherited class naming.
        typedef ClipVect2<TScalar, Kmin, Kmax> MyType;     //!< shortcut to this class naming.

        typedef TScalar MyScalarType; //!< wrapper to TScalar

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect2<TScalar, Kmin, Kmax>()
            : MyBaseType()
        {
            this->fill(this->clipped(TScalar(0)));
        }

        /** \brief Constructor with value.
        */
        inline ClipVect2<TScalar, Kmin, Kmax>(const char value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        inline ClipVect2<TScalar, Kmin, Kmax>(const unsigned char value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        inline ClipVect2<TScalar, Kmin, Kmax>(const short value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        inline ClipVect2<TScalar, Kmin, Kmax>(const unsigned short value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }
        inline ClipVect2<TScalar, Kmin, Kmax>(const int value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        inline ClipVect2<TScalar, Kmin, Kmax>(const unsigned int value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }
        inline ClipVect2<TScalar, Kmin, Kmax>(const long value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        inline ClipVect2<TScalar, Kmin, Kmax>(const unsigned long value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        inline ClipVect2<TScalar, Kmin, Kmax>(const long long value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        inline ClipVect2<TScalar, Kmin, Kmax>(const unsigned long long value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }
        inline ClipVect2<TScalar, Kmin, Kmax>(const float value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        inline ClipVect2<TScalar, Kmin, Kmax>(const double value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }
        inline ClipVect2<TScalar, Kmin, Kmax>(const long double value)
            : MyBaseType()
        {
            this->fill(this->clipped(value));
        }

        /** \brief Copy constructor (const vcl::Vector&).
        */
        template<typename T, size_t S>
        inline ClipVect2<TScalar, Kmin, Kmax>(const vcl::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline ClipVect2<TScalar, Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline ClipVect2<TScalar, Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2<TScalar, Kmin, Kmax>()
        {}

        //---   miscelaneous   ----------------------------------------------
        /** \brief Returns the specified value clipped. */
        template<typename T>
        inline const TScalar clipped(const T value) const
        {
            return std::clamp(value, T(Kmin), T(Kmax)); // c++17
        }

        //---   Components accessors   --------------------------------------
        /** \brief component x mutator */
        template<typename T>
        inline TScalar x(const T new_x)
        {
            return (*this)[0] = this->clipped(new_x);
        }

        /** \brief component x accessor */
        inline const TScalar x() const
        {
            return (*this)[0];
        }

        /** \brief component y mutator */
        template<typename T>
        inline TScalar y(const T new_y)
        {
            return (*this)[1] = this->clipped(new_y);
        }

        /** \brief component y accessor */
        inline const TScalar y() const
        {
            return (*this)[1];
        }
    };


    //=======================================================================
    /** \brief The class of 2D vectors with char components (8 bits). */
    template<const char Kmin = -128, const char Kmax = 127>
    class ClipVect2c : public ClipVect2<char, Kmin, Kmax>
    {
    public:
        typedef ClipVect2<char, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef ClipVect2c<Kmin, Kmax>      MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect2c<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
        inline ClipVect2c<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        inline ClipVect2c<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::Vector&).
        */
        template<typename T, size_t S>
        inline ClipVect2c<Kmin, Kmax>(const vcl::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline ClipVect2c<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline ClipVect2c<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2c<Kmin, Kmax>()
        {}
    };

    //=======================================================================
    /** \brief The class of 2D vectors with bytes components (8 bits). */
    template<const unsigned char Kmin = 0, const unsigned char Kmax = 255>
    class ClipVect2b : public ClipVect2<unsigned char, Kmin, Kmax>
    {
    public:
        typedef ClipVect2<unsigned char, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef ClipVect2b<Kmin, Kmax>               MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect2b<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
        inline ClipVect2b<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        inline ClipVect2b<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::Vector&).
        */
        template<typename T, size_t S>
        inline ClipVect2b<Kmin, Kmax>(const vcl::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline ClipVect2b<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline ClipVect2b<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2b<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 2D vectors with short components (16 bits). */
    template<const short Kmin = -32768, const short Kmax = 32767>
    class ClipVect2s : public ClipVect2<short, Kmin, Kmax>
    {
    public:
        typedef ClipVect2<short, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef ClipVect2s<Kmin, Kmax>       MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect2s<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
        inline ClipVect2s<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        inline ClipVect2s<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::Vector&).
        */
        template<typename T, size_t S>
        inline ClipVect2s<Kmin, Kmax>(const vcl::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline ClipVect2s<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline ClipVect2s<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2s<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 2D vectors with unsigned short components (16 bits). */
    template<const unsigned short Kmin = 0, const unsigned short Kmax = 65535>
    class ClipVect2us : public ClipVect2<unsigned short, Kmin, Kmax>
    {
    public:
        typedef ClipVect2<unsigned short, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef ClipVect2us<Kmin, Kmax>               MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect2us<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
        inline ClipVect2us<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        inline ClipVect2us<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::Vector&).
        */
        template<typename T, size_t S>
        inline ClipVect2us<Kmin, Kmax>(const vcl::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline ClipVect2us<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline ClipVect2us<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2us<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 2D vectors with int components (32 bits). */
    template<const int Kmin = -2147483648, const int Kmax = 2147483647>
    class ClipVect2i : public ClipVect2<int, Kmin, Kmax>
    {
    public:
        typedef ClipVect2<int, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef ClipVect2i<Kmin, Kmax>     MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect2i<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
        inline ClipVect2i<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        inline ClipVect2i<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::Vector&).
        */
        template<typename T, size_t S>
        inline ClipVect2i<Kmin, Kmax>(const vcl::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline ClipVect2i<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline ClipVect2i<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2i<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 2D vectors with unsigned int components (32 bits). */
    template<const unsigned int Kmin = 0, const unsigned int Kmax = 4294967295>
    class ClipVect2ui : public ClipVect2<unsigned int, Kmin, Kmax>
    {
    public:
        typedef ClipVect2<unsigned int, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef ClipVect2ui<Kmin, Kmax>             MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect2ui<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
        inline ClipVect2ui<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        inline ClipVect2ui<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::Vector&).
        */
        template<typename T, size_t S>
        inline ClipVect2ui<Kmin, Kmax>(const vcl::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline ClipVect2ui<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline ClipVect2ui<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2ui<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 2D vectors with float components (32 bits). */
    template<const float Kmin = 0.0f, const float Kmax = 1.0f>
    class ClipVect2f : public ClipVect2<float, Kmin, Kmax>
    {
    public:
        typedef ClipVect2<float, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef ClipVect2f<Kmin, Kmax>       MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect2f<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
        inline ClipVect2f<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        inline ClipVect2f<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::Vector&).
        */
        template<typename T, size_t S>
        inline ClipVect2f<Kmin, Kmax>(const vcl::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline ClipVect2f<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline ClipVect2f<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2f<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 2D vectors with double components (64 bits). */
    template<const double Kmin = 0.0, const double Kmax = 1.0>
    class ClipVect2d : public ClipVect2<double, Kmin, Kmax>
    {
    public:
        typedef ClipVect2<double, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef ClipVect2d<Kmin, Kmax>        MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect2d<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
        inline ClipVect2d<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        inline ClipVect2d<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::Vector&).
        */
        template<typename T, size_t S>
        inline ClipVect2d<Kmin, Kmax>(const vcl::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline ClipVect2d<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline ClipVect2d<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect2d<Kmin, Kmax>()
        {}
    };

} // end of namespace vcl
