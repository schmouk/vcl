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
/** \brief interface module Utils.
*
* Exports all utilities stuff.
*/
export module Utils;

namespace vcl {

    /*
    // Matrices
    export template<typename T> class Matrix;
    */

    // Vectors
    export template<typename TScalar, const size_t Ksize> class Vector;
    /*
    export template<typename TScalar, const int Ksize> class ClippedVector;

    export template<typename TScalar> class Vec2;   // 2 coordinates vectors
    export template<typename TScalar> class Vec3;   // 3 coordinates vectors
    export template<typename TScalar> class Vec4;   // 4 coordinates vectors

    export typedef Vec2<double>             Vec2d;  //!< 2D vectors, 64 bits components
    export typedef Vec2<float>              Vec2f;  //!< 2D vectors, 32 bits components
    export typedef Vec2<unsigned int>       Vec2i;  //!< 2D vectors, 32 bits components
    export typedef Vec2<unsigned short>     Vec2s;  //!< 2D vectors, 16 bits components
    export typedef Vec2<unsigned char>      Vec2b;  //!< 2D vectors,  8 bits components

    export typedef Vec3<double>             Vec3d;  //!< 3D vectors, 64 bits components
    export typedef Vec3<float>              Vec3f;  //!< 3D vectors, 32 bits components
    export typedef Vec3<unsigned int>       Vec3i;  //!< 3D vectors, 32 bits components
    export typedef Vec3<unsigned short>     Vec3s;  //!< 3D vectors, 16 bits components
    export typedef Vec3<unsigned char>      Vec3b;  //!< 3D vectors,  8 bits components

    export typedef Vec4<double>             Vec4d;  //!< 4D vectors, 64 bits components
    export typedef Vec4<float>              Vec4f;  //!< 4D vectors, 32 bits components
    export typedef Vec4<unsigned int>       Vec4i;  //!< 4D vectors, 32 bits components
    export typedef Vec4<unsigned short>     Vec4s;  //!< 4D vectors, 16 bits components
    export typedef Vec4<unsigned char>      Vec4b;  //!< 4D vectors,  8 bits components
    */

} // end of namespace vcl