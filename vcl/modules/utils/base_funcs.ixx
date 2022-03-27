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

export module utils.base_funcs;



//===========================================================================
namespace vcl::utils {
    
    /** \brief Returns the max of two objects.
    * Notice: types T and U must be comparable, i.e. the operator '>'
    * must have been defined between these two types.
    */
    export template<typename T, typename U>
    inline auto max(const T& a, const U& b)
    {
        return (a > b) ? a : b;
    }

    /** \brief Returns the min of two objects.
    * Notice: types T and U must be comparable, i.e. the operator '<'
    * must have been defined between these two types.
    */
    export template<typename T, typename U>
    inline auto min(const T& a, const U& b)
    {
        return (a < b) ? a : b;  // return vcl::utils::max(b, a); would fit also...
    }
}