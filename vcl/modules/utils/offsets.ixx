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


export module utils.offsets;

import vectors.vect2;


//===========================================================================
namespace vcl {
    namespace utils {

        //=======================================================================
        // Forward declaration
        export template<typename TScalar> class Offsets;

        // Specializations
        /** \brief The class of 2D offsets with unsigned short components (16 bits). */
        export typedef Offsets<short> Offsets_s;

        /** \brief The class of 2D offsets with unsigned int components (32 bits). */
        export typedef Offsets<int> Offsets_i;

        /** \brief The class of 2D offsets with float components (32 bits). */
        export typedef Offsets<float> Offsets_f;


        //=======================================================================
        /** \brief The generic class for 2D offsets. */
        template<typename TScalar>
        class Offsets : public vcl::vect::Vect2<TScalar>
        {
        public:
            typedef vcl::vect::Vect2<TScalar>    MyBaseType; //!< wrapper to the inherited class naming.
            typedef vcl::utils::Offsets<TScalar> MyType;     //!< wrapper to this class naming.

            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor.
            */
            inline Offsets<TScalar>()
                : MyBaseType()
            {}

            /** \brief Constructor with value.
            */
            template<typename T>
            inline Offsets<TScalar>(const T value)
                : MyBaseType(value)
            {}

            /** \brief Constructor with values.
            */
            template<typename T>
            inline Offsets<TScalar>(const T width, const T height)
                : MyBaseType(width, height)
            {}

            /** \brief Copy constructor (const&).
            */
            inline Offsets<TScalar>(const MyType& other)
                : MyBaseType()
            {
                this->copy(other);
            }

            /** \brief Copy constructor (const vcl::vect::Vector&).
            */
            template<typename T, size_t S>
            inline Offsets<TScalar>(const vcl::vect::Vector<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::array&).
            */
            template<typename T, size_t S>
            inline Offsets<TScalar>(const std::array<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::vector&).
            */
            template<typename T>
            inline Offsets<TScalar>(const std::vector<T>& vect)
                : MyBaseType(vect)
            {}

            //---  Destructor   -------------------------------------------------
            virtual inline ~Offsets<TScalar>()
            {}

            //---  Accessors/Mutators   -----------------------------------------
            /** \brief component dx mutator */
            template<typename T>
            inline TScalar dx(const T new_dx)
            {
                return (*this)[0] = new_dx;
            }

            /** \brief component dx accessor */
            inline const TScalar dx() const
            {
                return (*this)[0];
            }

            /** \brief component dy mutator */
            template<typename T>
            inline TScalar dy(const T new_dy)
            {
                return (*this)[1] = new_dy;
            }

            /** \brief component dy accessor */
            inline const TScalar dy() const
            {
                return (*this)[1];
            }

        };

    } // end of namespace utils
} // end of namespace vcl
