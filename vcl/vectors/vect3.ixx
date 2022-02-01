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

export module vectors.vect3;

import vectors.vector;


//===========================================================================
namespace vcl {
    //-----------------------------------------------------------------------
    // Forward declaration and Specializations
    export template<typename TScalar> class Vect3;

    /** \brief The class of 3D vectors with double components (64 bits). */
    export typedef Vect3<double> Vect3d;

    /** \brief The class of 3D vectors with float components (32 bits). */
    export typedef Vect3<float> Vect3f;

    /** \brief The class of 3D vectors with bytes components (8 bits). */
    export typedef Vect3<unsigned char> Vect3b;

    /** \brief The class of 3D vectors with short components (16 bits). */
    export typedef Vect3<short> Vect3s;

    /** \brief The class of 3D vectors with unsigned short components (16 bits). */
    export typedef Vect3<unsigned short> Vect3us;

    /** \brief The class of 3D vectors with int components (32 bits). */
    export typedef Vect3<int> Vect3i;

    /** \brief The class of 3D vectors with unsigned int components (32 bits). */
    export typedef Vect3<unsigned int> Vect3ui;


    //-----------------------------------------------------------------------
    /** \brief the generic class for 3-D vectors.
    *
    * \sa its specializations Vect3d, Vect3f, Vect3b, Vect3s, Vect3us, Vect3i, and Vect3ui.
    */
    template<typename TScalar>
    class Vect3 : public vcl::Vector<TScalar, 3>
    {
    public:
        typedef vcl::Vector<TScalar, 3> MyBaseType; //<! wrapper to the inherited class naming.
        typedef vcl::Vect3<TScalar>     MyType;     //<! wrapper to this class naming.


        //---   constructors   ----------------------------------------------
        /** \brief Empty constructor (components default to 0).
        */
        inline Vect3<TScalar>()
            : MyBaseType()
        {}

        /** \brief Constructor with a filling value.
        */
        template<typename T>
        inline Vect3<TScalar>(const T value)
            : MyBaseType(value)
        {}

        /** \brief Copy constructor (const&).
        */
        template<typename T, size_t S>
        inline Vect3<TScalar>(const vcl::Vector<T, S>& other)
            : MyBaseType(other)
        {}

        /** \brief Copy constructor (const std::array&).
        */
        template<typename T, size_t S>
        inline Vect3<TScalar>(const std::array<T, S>& arr)
            : MyBaseType(arr)
        {}

        /** \brief Copy constructor (const std::vector&).
        */
        template<typename T>
        inline Vect3<TScalar>(const std::vector<T>& vect)
            : MyBaseType(vect)
        {}

        //---  Destructor   -------------------------------------------------
        virtual inline ~Vect3<TScalar>()
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

        /** \brief component z accessor */
        inline const TScalar z() const
        {
            return (*this)[2];
        }

        /** \brief component z mutator */
        template<typename T>
        inline TScalar z(const T new_z)
        {
            return (*this)[2] = this->clipped(new_z);
        }
    };

} // end of namespace vcl
