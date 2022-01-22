/**
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
/** \brief module Utils
*
* Exports all utilities stuff.
*/
export module Utils;

namespace vcl {
    // Vectors
    export template<typename TScalar, const int Ksize> class Vector;
    export template<typename TScalar> class Vec2;   // 2 coordinates vectors
    export template<typename TScalar> class Vec3;   // 3 coordinates vectors
    export template<typename TScalar> class Vec4;   // 4 coordinates vectors

    export class Vec2d;     // Vec2<double>         - 64 bits
    export class Vec2f;     // Vec2<float>          - 32 bits
    export class Vec2ui;    // Vec2<unsigned int>   - 32 bits
    export class Vec2us;    // Vec2<unsigned short> - 16 bits
    export class Vec2b;     // Vec2<unsigned char>  -  8 bits

    export class Vec3d;     // Vec3<double>         - 64 bits
    export class Vec3f;     // Vec3<float>          - 32 bits
    export class Vec3ui;    // Vec3<unsigned int>   - 32 bits
    export class Vec3us;    // Vec3<unsigned short> - 16 bits
    export class Vec3b;     // Vec<unsigned char>   -  8 bits

    export class Vec4d;     // Vec4<double>         - 64 bits
    export class Vec4f;     // Vec4<float>          - 32 bits
    export class Vec4ui;    // Vec4<unsigned int>   - 32 bits
    export class Vec4us;    // Vec4<unsigned short> - 16 bits
    export class Vec4b;     // Vec4<unsigned char>  -  8 bits

    // Matrices
    export template<typename TScalar> class Matrix;
    export template<typename TScalar> class Mat2;   // 2 dimensions matrices

    export class Mat2d;     // Mat2<double>         - 64 bits
    export class Mat2f;     // Mat2<float>          - 32 bits
    export class Mat2ui;    // Mat2<unsigned int>   - 32 bits
    export class Mat2us;    // Mat2<unsigned short> - 16 bits
    export class Mat2b;     // Mat2<unsigned char>  -  8 bits

} // end of namespace vcl