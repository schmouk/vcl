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
#include <type_traits>
#include <vector>

export module utils.ranges;


//===========================================================================
namespace vcl::utils {

//---------------------------------------------------------------------------
#define IN_RANGE(x,a,b)    ((a) <= (x) && (x) <= (b))
#define IN_RANGE_01(x,a,b) ((a) <  (x) && (x) <= (b))
#define IN_RANGE_10(x,a,b) ((a) <= (x) && (x) <  (b))
#define IN_RANGE_00(x,a,b) ((a) <  (x) && (x) <  (b))

    export bool IN_RANGE;
    export bool IN_RANGE_01;
    export bool IN_RANGE_10;
    export bool IN_RANGE_00;


    export template<typename TScalar>
        requires std::is_arithmetic_v<TScalar>
    inline const bool in_range_ii(const TScalar x, const TScalar Kmin, const TScalar Kmax)
    {
        return Kmin <= x && x <= Kmax;
    }


    export template<typename TScalar>
        requires std::is_arithmetic_v<TScalar>
    inline const bool in_range_io(const TScalar x, const TScalar Kmin, const TScalar Kmax)
    {
        return Kmin <= x && x < Kmax;
    }


    export template<typename TScalar>
        requires std::is_arithmetic_v<TScalar>
    inline const bool in_range_oi(const TScalar x, const TScalar Kmin, const TScalar Kmax)
    {
        return Kmin < x && x <= Kmax;
    }


    export template<typename TScalar>
        requires std::is_arithmetic_v<TScalar>
    inline const bool in_range_oo(const TScalar x, const TScalar Kmin, const TScalar Kmax)
    {
        return Kmin < x && x < Kmax;
    }


    export template<typename TScalar>
        requires std::is_arithmetic_v<TScalar>
    inline const bool in_range(const TScalar x, const TScalar Kmin, const TScalar Kmax)
    {
        return in_range_ii(x, Kmin, Kmax);
    }

}
