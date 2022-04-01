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
#include <vector>
#include "vcl_concepts.h"

export module vectors.clipvect3;

import vectors.vector;
import vectors.vect3;


//===========================================================================
namespace vcl::vect {

    //=======================================================================
    // Forward declaration and Specializations
    export template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
        requires vcl::concepts::is_numeric<TScalar>
    class ClipVect3;

    /** \brief The class of 3D vectors with bytes components (8 bits). */
    export template<const char Kmin, const char Kmax> class ClipVect3c;

    /** \brief The class of 3D vectors with bytes components (8 bits). */
    export template<const unsigned char Kmin, const unsigned char Kmax> class ClipVect3b;

    /** \brief The class of 3D vectors with short components (16 bits). */
    export template<const short Kmin, const short Kmax> class ClipVect3s;

    /** \brief The class of 3D vectors with unsigned short components (16 bits). */
    export template<const unsigned short Kmin, const unsigned short Kmax> class ClipVect3us;

    /** \brief The class of 3D vectors with long int components (32 bits). */
    export template<const long Kmin, const long Kmax> class ClipVect3i;

    /** \brief The class of 3D vectors with unsigned long int components (32 bits). */
    export template<const unsigned long Kmin, const unsigned long Kmax> class ClipVect3ui;

    /** \brief The class of 3D vectors with float components (32 bits). */
    export template<const float Kmin, const float Kmax> class ClipVect3f;

    /** \brief The class of 3D vectors with double components (64 bits). */
    export template<const double Kmin, const double Kmax> class ClipVect3d;


    //=======================================================================
    /** \brief the generic class for 3-D clipped vectors.
    *
    * \sa its specializations ClipVect3d, ClipVect3f, ClipVect3b, ClipVect3s, ClipVect3us, ClipVect3i, and ClipVect3ui.
    */
    template<typename TScalar, const TScalar Kmin, const TScalar Kmax>
        requires vcl::concepts::is_numeric<TScalar>
    class ClipVect3 : public vcl::vect::Vect3<TScalar>
    {
    public:
        typedef vcl::vect::Vect3<TScalar>                 MyBaseType; //!< shortcut to this class inherited class naming.
        typedef vcl::vect::ClipVect3<TScalar, Kmin, Kmax> MyType;     //!< shortcut to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect3<TScalar, Kmin, Kmax>()
            : MyBaseType()
        {
            this->fill(this->clipped(TScalar(0)));
        }

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3<TScalar, Kmin, Kmax>(const T value)
            : MyBaseType()
        {
            this->fill<T>(this->clipped(value));
        }

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T> && vcl::concepts::is_numeric<U> && vcl::concepts::is_numeric<V>
        inline ClipVect3<TScalar, Kmin, Kmax>(const T x_, const U y_, const V z_ = T(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
        }

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3<TScalar, Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}


        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3<TScalar, Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3<TScalar, Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        /** \brief Copy constructor (const std::pair&).
        */
        template<typename T, typename U>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>
        inline ClipVect3<TScalar, Kmin, Kmax>(const std::pair<T, U>& pair)
            : MyBaseType(pair)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect3<TScalar, Kmin, Kmax>()
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

        /** \brief component z accessor */
        inline const TScalar z() const
        {
            return (*this)[2];
        }

        /** \brief component z mutator */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline TScalar z(const T new_z)
        {
            return (*this)[2] = this->clipped(new_z);
        }

        //---   miscelaneous   ----------------------------------------------
        /** \brief Returns the specified value clipped. */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline const TScalar clipped(const T value) const
        {
            return std::clamp(value, T(Kmin), T(Kmax)); // c++17
        }
    };


    //=======================================================================
    /** \brief The class of 3D vectors with char components (8 bits). */
    template<const char Kmin = -128, const char Kmax = 127>
    class ClipVect3c : public vcl::vect::ClipVect3<char, Kmin, Kmax>
    {
    public:
        typedef vcl::vect::ClipVect3<char, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::vect::ClipVect3c<Kmin, Kmax>      MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect3c<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
        inline ClipVect3c<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>&& vcl::concepts::is_numeric<V>
        inline ClipVect3c<Kmin, Kmax>(const T x_, const U y_, const V z_ = T(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
        }

        /** \brief Copy constructor (const&).
        */
        inline ClipVect3c<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3c<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3c<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3c<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3c<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect3c<Kmin, Kmax>()
        {}
    };

    //=======================================================================
    /** \brief The class of 3D vectors with bytes components (8 bits). */
    template<const unsigned char Kmin = 0, const unsigned char Kmax = 255>
    class ClipVect3b : public vcl::vect::ClipVect3<unsigned char, Kmin, Kmax>
    {
    public:
        typedef vcl::vect::ClipVect3<unsigned char, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::vect::ClipVect3b<Kmin, Kmax>               MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect3b<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3b<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>&& vcl::concepts::is_numeric<V>
        inline ClipVect3b<Kmin, Kmax>(const T x_, const U y_, const V z_ = T(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
        }

        /** \brief Copy constructor (const&).
        */
        inline ClipVect3b<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3b<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3b<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3b<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3b<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect3b<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 3D vectors with short components (16 bits). */
    template<const short Kmin = -32768, const short Kmax = 32767>
    class ClipVect3s : public vcl::vect::ClipVect3<short, Kmin, Kmax>
    {
    public:
        typedef vcl::vect::ClipVect3<short, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::vect::ClipVect3s<Kmin, Kmax>       MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect3s<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3s<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>&& vcl::concepts::is_numeric<V>
        inline ClipVect3s<Kmin, Kmax>(const T x_, const U y_, const V z_ = T(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
        }

        /** \brief Copy constructor (const&).
        */
        inline ClipVect3s<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3s<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3s<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3s<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3s<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect3s<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 3D vectors with unsigned short components (16 bits). */
    template<const unsigned short Kmin = 0, const unsigned short Kmax = 65535>
    class ClipVect3us : public vcl::vect::ClipVect3<unsigned short, Kmin, Kmax>
    {
    public:
        typedef vcl::vect::ClipVect3<unsigned short, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::vect::ClipVect3us<Kmin, Kmax>               MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect3us<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3us<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>&& vcl::concepts::is_numeric<V>
        inline ClipVect3us<Kmin, Kmax>(const T x_, const U y_, const V z_ = T(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
        }

        /** \brief Copy constructor (const&).
        */
        inline ClipVect3us<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3us<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3us<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3us<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3us<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect3us<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 3D vectors with long int components (32 bits). */
    template<const long Kmin = -2147483648, const long Kmax = 2147483647>
    class ClipVect3i : public vcl::vect::ClipVect3<long, Kmin, Kmax>
    {
    public:
        typedef vcl::vect::ClipVect3<long, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::vect::ClipVect3i<Kmin, Kmax>      MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect3i<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3i<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>&& vcl::concepts::is_numeric<V>
        inline ClipVect3i<Kmin, Kmax>(const T x_, const U y_, const V z_ = T(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
        }

        /** \brief Copy constructor (const&).
        */
        inline ClipVect3i<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3i<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3i<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3i<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3i<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect3i<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 3D vectors with unsigned long int components (32 bits). */
    template<const unsigned long Kmin = 0, const unsigned long Kmax = 4294967295>
    class ClipVect3ui : public vcl::vect::ClipVect3<unsigned long, Kmin, Kmax>
    {
    public:
        typedef vcl::vect::ClipVect3<unsigned long, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::vect::ClipVect3ui<Kmin, Kmax>              MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect3ui<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3ui<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>&& vcl::concepts::is_numeric<V>
        inline ClipVect3ui<Kmin, Kmax>(const T x_, const U y_, const V z_ = T(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
        }

        /** \brief Copy constructor (const&).
        */
        inline ClipVect3ui<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3ui<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3ui<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3ui<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3ui<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect3ui<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 3D vectors with float components (32 bits). */
    template<const float Kmin = 0.0f, const float Kmax = 1.0f>
    class ClipVect3f : public vcl::vect::ClipVect3<float, Kmin, Kmax>
    {
    public:
        typedef vcl::vect::ClipVect3<float, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::vect::ClipVect3f<Kmin, Kmax>       MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect3f<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3f<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>&& vcl::concepts::is_numeric<V>
        inline ClipVect3f<Kmin, Kmax>(const T x_, const U y_, const V z_ = T(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
        }

        /** \brief Copy constructor (const&).
        */
        inline ClipVect3f<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3f<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3f<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3f<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3f<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect3f<Kmin, Kmax>()
        {}
    };


    //=======================================================================
    /** \brief The class of 3D vectors with double components (64 bits). */
    template<const double Kmin = 0.0, const double Kmax = 1.0>
    class ClipVect3d : public vcl::vect::ClipVect3<double, Kmin, Kmax>
    {
    public:
        typedef vcl::vect::ClipVect3<double, Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
        typedef vcl::vect::ClipVect3d<Kmin, Kmax>        MyType;     //!< wrapper to this class naming.

        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor.
        */
        inline ClipVect3d<Kmin, Kmax>()
            : MyBaseType()
        {}

        /** \brief Constructor with value.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3d<Kmin, Kmax>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Constructor with values.
        */
        template<typename T, typename U, typename V>
            requires vcl::concepts::is_numeric<T>&& vcl::concepts::is_numeric<U>&& vcl::concepts::is_numeric<V>
        inline ClipVect3d<Kmin, Kmax>(const T x_, const U y_, const V z_ = T(0))
            : MyBaseType()
        {
            x(x_);
            y(y_);
            z(z_);
        }

        /** \brief Copy constructor (const&).
        */
        inline ClipVect3d<Kmin, Kmax>(const MyType& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const vcl::vect::Vector&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3d<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Move constructor (&&).
        */
        template<typename T, const size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3d<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3d<Kmin, Kmax>(const std::array<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline ClipVect3d<Kmin, Kmax>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~ClipVect3d<Kmin, Kmax>()
        {}
    };

}
