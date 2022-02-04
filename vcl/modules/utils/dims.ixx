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


export module utils.dims;

import vectors.vect2;


//===========================================================================
namespace vcl {
    namespace utils {

        //=======================================================================
        // Forward declaration
        export template<typename TScalar> class Dims;

        // Specializations
        /** \brief The class of 2D dimensions with unsigned short components (16 bits). */
        export typedef Dims<unsigned short> Dims_us;

        /** \brief The class of 2D dimensions with unsigned long int components (32 bits). */
        export typedef Dims<unsigned long> Dims_ui;

        /** \brief The class of 2D dimensions with float components (32 bits). */
        export typedef Dims<float> Dims_f;


        //=======================================================================
        /** \brief The generic class for 2D dimensions. */
        template<typename TScalar>
        class Dims : public vcl::vect::Vect2<TScalar>
        {
        public:
            typedef vcl::vect::Vect2<TScalar> MyBaseType; //!< wrapper to the inherited class naming.
            typedef vcl::utils::Dims<TScalar> MyType;     //!< wrapper to this class naming.

            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor.
            */
            inline Dims<TScalar>()
                : MyBaseType()
            {}

            /** \brief Constructor with value.
            */
            template<typename T>
            inline Dims<TScalar>(const T value)
                : MyBaseType(value)
            {}

            /** \brief Constructor with values.
            */
            template<typename T>
            inline Dims<TScalar>(const T width, const T height)
                : MyBaseType(width, height)
            {}

            /** \brief Copy constructor (const&).
            */
            inline Dims<TScalar>(const MyType& other)
                : MyBaseType()
            {
                this->copy(other);
            }

            /** \brief Copy constructor (const vcl::vect::Vector&).
            */
            template<typename T, size_t S>
            inline Dims<TScalar>(const vcl::vect::Vector<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::array&).
            */
            template<typename T, size_t S>
            inline Dims<TScalar>(const std::array<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::vector&).
            */
            template<typename T>
            inline Dims<TScalar>(const std::vector<T>& vect)
                : MyBaseType(vect)
            {}

            //---  Destructor   -------------------------------------------------
            virtual inline ~Dims<TScalar>()
            {}

            //---  Accessors/Mutators   -----------------------------------------
            /** \brief component width mutator */
            template<typename T>
            inline TScalar width(const T new_width)
            {
                return (*this)[0] = new_width;
            }

            /** \brief component width accessor */
            inline const TScalar width() const
            {
                return (*this)[0];
            }

            /** \brief component height mutator */
            template<typename T>
            inline TScalar height(const T new_height)
            {
                return (*this)[1] = new_height;
            }

            /** \brief component height accessor */
            inline const TScalar height() const
            {
                return (*this)[1];
            }

            //---  Miscelaneous   ----------------------------------------------
            /** \brief returns the ratio of width / height */
            inline const double ratio_wh() const
            {
                return double(width()) / double(height());
            }

            /** \brief returns the surface related to the dimensions */
            inline const TScalar surface() const
            {
                return width() * height();  // caution: may overflow...
            }

            /** \brief operator == */
            inline bool operator== (const MyType& other)
            {
                return surface() == other.surface();
            }

            /** \brief operator != */
            inline bool operator!= (const MyType& other)
            {
                return surface() != other.surface();
            }

            /** \brief operator < */
            inline bool operator< (const MyType& other)
            {
                return surface() < other.surface();
            }

            /** \brief operator <= */
            inline bool operator<= (const MyType& other)
            {
                return surface() <= other.surface();
            }

            /** \brief operator > */
            inline bool operator> (const MyType& other)
            {
                return surface() > other.surface();
            }

            /** \brief operator >= */
            inline bool operator>= (const MyType& other)
            {
                return surface() >= other.surface();
            }

        };

    } // end of namespace utils
} // end of namespace vcl
