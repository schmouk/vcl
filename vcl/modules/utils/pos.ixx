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


export module utils.pos;

import vectors.clipvect2;


//===========================================================================
namespace vcl {
    namespace utils {

        //=======================================================================
        /** \brief class Pos: the generic class for 2-D clipped positions. */
        export template<typename TScalar, const size_t Kmin, const size_t Kmax>
        using Pos = vcl::vect::ClipVect2<TScalar, Kmin, Kmax>;


        //=======================================================================
        // Forward declaration and Specializations
        /** \brief The class of 2D positions with short components (16 bits). */
        export template<const short Kmin, const short Kmax> class Pos_s;

        /** \brief The class of 2D positions with unsigned short components (16 bits). */
        export template<const unsigned short Kmin, const unsigned short Kmax> class Pos_us;

        /** \brief The class of 2D positions with long int components (32 bits). */
        export template<const long Kmin, const long Kmax > class Pos_i;

        /** \brief The class of 2D positions with unsigned long int components (32 bits). */
        export template<const unsigned long Kmin, const unsigned long Kmax> class Pos_ui;

        /** \brief The class of 2D positions with float components (32 bits). */
        export template<const float Kmin, const float Kmax> class Pos_f;

        /** \brief The class of 2D positions with double components (64 bits). */
        export template<const double Kmin, const double Kmax> class Pos_d;


        //=======================================================================
        /** \brief The class of 2D positions with short components (16 bits). */
        template<const short Kmin = -32768, const short Kmax = 32767>
        class Pos_s : public vcl::vect::ClipVect2s<Kmin, Kmax>
        {
        public:
            typedef vcl::vect::ClipVect2s<Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
            typedef vcl::utils::Pos_s<Kmin, Kmax>     MyType;     //!< wrapper to this class naming.


            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor.
            */
            inline Pos_s<Kmin, Kmax>()
                : MyBaseType()
            {}

            /** \brief Constructor with value.
            */
            template<typename T>
            inline Pos_s<Kmin, Kmax>(const T value)
                : MyBaseType(value)
            {}

            /** \brief Constructor with values.
            */
            template<typename T>
            inline Pos_s<Kmin, Kmax>(const T x, const T y)
                : MyBaseType(x, y)
            {}

            /** \brief Copy constructor (const&).
            */
            inline Pos_s<Kmin, Kmax>(const MyType& other)
                : MyBaseType()
            {
                this->copy(other);
            }

            /** \brief Copy constructor (const vcl::vect::Vector&).
            */
            template<typename T, size_t S>
            inline Pos_s<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Move constructor (const vcl::vect::Vector&&).
            */
            template<typename T, size_t S>
            inline Pos_s<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::array&).
            */
            template<typename T, size_t S>
            inline Pos_s<Kmin, Kmax>(const std::array<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::vector&).
            */
            template<typename T>
            inline Pos_s<Kmin, Kmax>(const std::vector<T>& vect)
                : MyBaseType(vect)
            {}

            //---  Destructor   -------------------------------------------------
            virtual inline ~Pos_s<Kmin, Kmax>()
            {}

            //---   origin   ----------------------------------------------------
            /* \brief returns the origin position (short).
            */
            static inline MyType origin()
            {
                return MyType();
            }
        };

        export vcl::utils::Pos_s Pos_Origin_s;


        //=======================================================================
        /** \brief The class of 2D positions with unsigned short components (16 bits). */
        template<const unsigned short Kmin = 0, const unsigned short Kmax = 65535>
        class Pos_us : public vcl::vect::ClipVect2us<Kmin, Kmax>
        {
        public:
            typedef vcl::vect::ClipVect2us<Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
            typedef vcl::utils::Pos_us<Kmin, Kmax>     MyType;     //!< wrapper to this class naming.

            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor.
            */
            inline Pos_us<Kmin, Kmax>()
                : MyBaseType()
            {}

            /** \brief Constructor with value.
            */
            template<typename T>
            inline Pos_us<Kmin, Kmax>(const T value)
                : MyBaseType(value)
            {}

            /** \brief Constructor with values.
            */
            template<typename T>
            inline Pos_us<Kmin, Kmax>(const T x, const T y)
                : MyBaseType(x, y)
            {}

            /** \brief Copy constructor (const&).
            */
            inline Pos_us<Kmin, Kmax>(const MyType& other)
                : MyBaseType()
            {
                this->copy(other);
            }

            /** \brief Copy constructor (const vcl::vect::Vector&).
            */
            template<typename T, size_t S>
            inline Pos_us<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Move constructor (const vcl::vect::Vector&&).
            */
            template<typename T, size_t S>
            inline Pos_us<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::array&).
            */
            template<typename T, size_t S>
            inline Pos_us<Kmin, Kmax>(const std::array<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::vector&).
            */
            template<typename T>
            inline Pos_us<Kmin, Kmax>(const std::vector<T>& vect)
                : MyBaseType(vect)
            {}

            //---  Destructor   -------------------------------------------------
            virtual inline ~Pos_us<Kmin, Kmax>()
            {}

            //---   origin   ----------------------------------------------------
            /* \brief returns the origin position (unsigned short).
            */
            inline MyType& origin()
            {
                return MyType();
            }
        };

        export vcl::utils::Pos_us Pos_Origin_us;


        //=======================================================================
        /** \brief The class of 2D positions with longint components (32 bits). */
        template<const long Kmin = -2147483648, const long Kmax = 2147483647>
        class Pos_i : public vcl::vect::ClipVect2i<Kmin, Kmax>
        {
        public:
            typedef vcl::vect::ClipVect2i<Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
            typedef vcl::utils::Pos_i<Kmin, Kmax>     MyType;     //!< wrapper to this class naming.

            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor.
            */
            inline Pos_i<Kmin, Kmax>()
                : MyBaseType()
            {}

            /** \brief Constructor with value.
            */
            template<typename T>
            inline Pos_i<Kmin, Kmax>(const T value)
                : MyBaseType(value)
            {}

            /** \brief Constructor with values.
            */
            template<typename T>
            inline Pos_i<Kmin, Kmax>(const T x, const T y)
                : MyBaseType(x, y)
            {}

            /** \brief Copy constructor (const&).
            */
            inline Pos_i<Kmin, Kmax>(const MyType& other)
                : MyBaseType()
            {
                this->copy(other);
            }

            /** \brief Copy constructor (const vcl::vect::Vector&).
            */
            template<typename T, size_t S>
            inline Pos_i<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Move constructor (const vcl::vect::Vector&&).
            */
            template<typename T, size_t S>
            inline Pos_i<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::array&).
            */
            template<typename T, size_t S>
            inline Pos_i<Kmin, Kmax>(const std::array<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::vector&).
            */
            template<typename T>
            inline Pos_i<Kmin, Kmax>(const std::vector<T>& vect)
                : MyBaseType(vect)
            {}

            //---  Destructor   -------------------------------------------------
            virtual inline ~Pos_i<Kmin, Kmax>()
            {}

            //---   origin   ----------------------------------------------------
            /* \brief returns the origin position (long).
            */
            inline MyType& origin()
            {
                return MyType();
            }
        };

        export vcl::utils::Pos_i Pos_Origin_i;


        //=======================================================================
        /** \brief The class of 2D positions with unsigned long int components (32 bits). */
        template<const unsigned long Kmin = 0, const unsigned long Kmax = 4294967295>
        class Pos_ui : public vcl::vect::ClipVect2ui<Kmin, Kmax>
        {
        public:
            typedef vcl::vect::ClipVect2ui<Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
            typedef vcl::utils::Pos_ui<Kmin, Kmax>     MyType;     //!< wrapper to this class naming.

            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor.
            */
            inline Pos_ui<Kmin, Kmax>()
                : MyBaseType()
            {}

            /** \brief Constructor with value.
            */
            template<typename T>
            inline Pos_ui<Kmin, Kmax>(const T value)
                : MyBaseType(value)
            {}

            /** \brief Constructor with values.
            */
            template<typename T>
            inline Pos_ui<Kmin, Kmax>(const T x, const T y)
                : MyBaseType(x, y)
            {}

            /** \brief Copy constructor (const&).
            */
            inline Pos_ui<Kmin, Kmax>(const MyType& other)
                : MyBaseType()
            {
                this->copy(other);
            }

            /** \brief Copy constructor (const vcl::vect::Vector&).
            */
            template<typename T, size_t S>
            inline Pos_ui<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Move constructor (const vcl::vect::Vector&&).
            */
            template<typename T, size_t S>
            inline Pos_ui<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::array&).
            */
            template<typename T, size_t S>
            inline Pos_ui<Kmin, Kmax>(const std::array<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::vector&).
            */
            template<typename T>
            inline Pos_ui<Kmin, Kmax>(const std::vector<T>& vect)
                : MyBaseType(vect)
            {}

            //---  Destructor   -------------------------------------------------
            virtual inline ~Pos_ui<Kmin, Kmax>()
            {}

            //---   origin   ----------------------------------------------------
            /* \brief returns the origin position (unsigned long).
            */
            inline MyType& origin()
            {
                return MyType();
            }
        };

        export vcl::utils::Pos_ui Pos_Origin_ui;


        //=======================================================================
        /** \brief The class of 2D positions with float components (32 bits).
        *
        * This class of positions relates to proportional positions, relative
        * to the size of graphical component, a texture or a frame.
        */
        template<const float Kmin = 0.0f, const float Kmax = 1.0f>
        class Pos_f : public vcl::vect::ClipVect2f<Kmin, Kmax>
        {
        public:
            typedef vcl::vect::ClipVect2f<Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
            typedef vcl::utils::Pos_f<Kmin, Kmax>     MyType;     //!< wrapper to this class naming.

            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor.
            */
            inline Pos_f<Kmin, Kmax>()
                : MyBaseType()
            {}

            /** \brief Constructor with value.
            */
            template<typename T>
            inline Pos_f<Kmin, Kmax>(const T value)
                : MyBaseType(value)
            {}

            /** \brief Constructor with values.
            */
            template<typename T>
            inline Pos_f<Kmin, Kmax>(const T x, const T y)
                : MyBaseType(x, y)
            {}

            /** \brief Copy constructor (const&).
            */
            inline Pos_f<Kmin, Kmax>(const MyType& other)
                : MyBaseType()
            {
                this->copy(other);
            }

            /** \brief Copy constructor (const vcl::vect::Vector&).
            */
            template<typename T, size_t S>
            inline Pos_f<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Move constructor (const vcl::vect::Vector&&).
            */
            template<typename T, size_t S>
            inline Pos_f<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::array&).
            */
            template<typename T, size_t S>
            inline Pos_f<Kmin, Kmax>(const std::array<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::vector&).
            */
            template<typename T>
            inline Pos_f<Kmin, Kmax>(const std::vector<T>& vect)
                : MyBaseType(vect)
            {}

            //---  Destructor   -------------------------------------------------
            virtual inline ~Pos_f<Kmin, Kmax>()
            {}

            //---   origin   ----------------------------------------------------
            /* \brief returns the origin position (float).
            */
            inline MyType& origin()
            {
                return MyType();
            }
        };

        export vcl::utils::Pos_f Pos_Origin_f;


        //=======================================================================
        /** \brief The class of 2D positions with double components (64 bits).
        *
        * This class of positions relates to proportional positions, relative
        * to the size of graphical component, a texture or a frame.
        */
        template<const double Kmin = 0.0, const double Kmax = 1.0>
        class Pos_d : public vcl::vect::ClipVect2d<Kmin, Kmax>
        {
        public:
            typedef vcl::vect::ClipVect2d<Kmin, Kmax> MyBaseType; //!< wrapper to the inherited class naming.
            typedef vcl::utils::Pos_d<Kmin, Kmax>     MyType;     //!< wrapper to this class naming.

            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor.
            */
            inline Pos_d<Kmin, Kmax>()
                : MyBaseType()
            {}

            /** \brief Constructor with value.
            */
            template<typename T>
            inline Pos_d<Kmin, Kmax>(const T value)
                : MyBaseType(value)
            {}

            /** \brief Constructor with values.
            */
            template<typename T>
            inline Pos_d<Kmin, Kmax>(const T x, const T y)
                : MyBaseType(x, y)
            {}

            /** \brief Copy constructor (const&).
            */
            inline Pos_d<Kmin, Kmax>(const MyType& other)
                : MyBaseType()
            {
                this->copy(other);
            }

            /** \brief Copy constructor (const vcl::vect::Vector&).
            */
            template<typename T, size_t S>
            inline Pos_d<Kmin, Kmax>(const vcl::vect::Vector<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Move constructor (const vcl::vect::Vector&&).
            */
            template<typename T, size_t S>
            inline Pos_d<Kmin, Kmax>(vcl::vect::Vector<T, S>&& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::array&).
            */
            template<typename T, size_t S>
            inline Pos_d<Kmin, Kmax>(const std::array<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::vector&).
            */
            template<typename T>
            inline Pos_d<Kmin, Kmax>(const std::vector<T>& vect)
                : MyBaseType(vect)
            {}

            //---  Destructor   -------------------------------------------------
            virtual inline ~Pos_d<Kmin, Kmax>()
            {}

            //---   origin   ----------------------------------------------------
            /* \brief returns the origin position (float).
            */
            inline MyType& origin()
            {
                return MyType();
            }
        };

        export vcl::utils::Pos_d Pos_Origin_d;

    } // end of namespace utils
} // end of namespace vcl
