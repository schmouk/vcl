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

#include <opencv2/core/types.hpp>

#include "vcl_concepts.h"

export module utils.colors;


//===========================================================================
namespace vcl::utils {

    //===================================================================
    /** \brief class Color: the base class for all colors.
    * 
    * This class is abstract: operator '=(const Color<T>)' is set to
    * be abstract.
    */
    export class Color
    {
    public:
        //---   constructors   ------------------------------------------
        /** \brief Empty constructor. */
        inline Color() = default;

        /** \brief Copy constructor. */
        inline Color(const Color& clr) = default;

        /** \brief Move constructor. */
        inline Color(Color&& clr) = default;


        //--- Destructor ----------------------------------------------------
        /** \brief Destructor. */
        inline ~Color() = default;


        //--- Assignment ----------------------------------------------------
        /** \brief Copy assignment. */
        inline Color& operator=(Color& other) = default;

        /** \brief Assignment by value.
        * This method MUST BE overridden in inheriting classes.
        */
        template<typename T>
            requires vcl::concepts::is_numeric<T>
        inline Color& operator=(const T& value) = delete;
    };

}