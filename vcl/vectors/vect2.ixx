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
#include <vector>

export module vectors.vect2;

import vectors.vector;


//===========================================================================
namespace vcl {

    //-----------------------------------------------------------------------
        // Forward declaration and Specializations
        export template<typename TScalar> class Vect2;

        /** \brief The class of 2D vectors with double components (64 bits). */
        export typedef Vect2<double> Vect2d;

        /** \brief The class of 2D vectors with float components (32 bits). */
        export typedef Vect2<float> Vect2f;

        /** \brief The class of 2D vectors with bytes components (8 bits). */
        export typedef Vect2<unsigned char> Vect2b;

        /** \brief The class of 2D vectors with short components (16 bits). */
        export typedef Vect2<short> Vect2s;

        /** \brief The class of 2D vectors with unsigned short components (16 bits). */
        export typedef Vect2<unsigned short> Vect2us;

        /** \brief The class of 2D vectors with int components (32 bits). */
        export typedef Vect2<int> Vect2i;

        /** \brief The class of 2D vectors with unsigned int components (32 bits). */
        export typedef Vect2<unsigned int> Vect2ui;


        //-----------------------------------------------------------------------
        /** \brief the generic class for 2-D vectors.
        *
        * \sa its specializations Vect2d, Vect2f, Vect2b, Vect2s, Vect2us, Vect2i, and Vect2ui.
        */
        template<typename TScalar>
        class Vect2 : public vcl::Vector<TScalar, 2>
        {
        public:
            typedef vcl::Vector<TScalar, 2> MyBaseType; //<! wrapper to the inherited class naming.
            typedef vcl::Vect2<TScalar>     MyType;     //<! wrapper to this class naming.


            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor (components default to 0).
            */
            inline Vect2<TScalar>()
                : MyBaseType()
            {}

            /** \brief Constructor with a filling value.
            */
            template<typename T>
            inline Vect2<TScalar>(const T value)
                : MyBaseType(value)
            {}

            /** \brief Copy constructor (const&).
            */
            template<typename T, size_t S>
            inline Vect2<TScalar>(const vcl::Vector<T, S>& other)
                : MyBaseType(other)
            {}

            /** \brief Copy constructor (const std::array&).
            */
            template<typename T, size_t S>
            inline Vect2<TScalar>(const std::array<T, S>& arr)
                : MyBaseType(arr)
            {}

            /** \brief Copy constructor (const std::vector&).
            */
            template<typename T>
            inline Vect2<TScalar>(const std::vector<T>& vect)
                : MyBaseType(vect)
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
            inline TScalar y(const T new_y)
            {
                return (*this)[1] = this->clipped(new_y);
            }
        };

} // end of namespace vcl
