#pragma once
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
/** \brief main for tests on class vcl::vect::Vect2T. */
{
    cout << "## vectors.vect2 / vcl::vect::Vect2T testing application..." << endl;

    vcl::vect::Vect2i v0;
    assert(v0[0] == 0);
    assert(v0[1] == 0);

    vcl::vect::Vect2b v1(1);
    assert(v1[0] == 1);
    assert(v1[1] == 1);

    vcl::vect::Vect2b v2(v1);
    assert(v2[0] == 1);
    assert(v2[1] == 1);

    std::vector<short> v = { 10, 11, 12, 13, 14 };
    vcl::vect::Vect2s v3(v);
    assert(v3[0] == 10);
    assert(v3[1] == 11);

    assert(v3.x() == 10);
    assert(v3.y() == 11);

    v3.x() = 5;
    v3.y(6);
    assert(v3.x() == 5);
    assert(v3.y() == 6);

    v3 = v;
    assert(v3[0] == 10);
    assert(v3[1] == 11);

    vcl::vect::Vect2s v4(15.0f);
    assert(v4[0] == 15);
    assert(v4[1] == 15);

    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();
    vcl::vect::Vect2T<short> v5(v);
    assert(v5[0] == 10);
    assert(v5[1] == 0);

    
    std::array<unsigned char, 2> arr = { 2,2 };
    vcl::vect::Vect2b v6(arr);
    assert(v6[0] == 2);
    assert(v6[1] == 2);

    arr[1] = 3;
    v2.copy(arr);
    assert(v2[0] == 2);
    assert(v2[1] == 3);

    vcl::vect::Vect2f v7;
    constexpr float V05 = (float)0.5;
    vcl::vect::Vect2f v8(V05);
    v7 = v8;
    assert(v7[0] == V05);
    assert(v7[1] == V05);

    constexpr float V09 = (float)0.9;
    v8 = float(V09);
    assert(v8[0] == V09);
    assert(v8[1] == V09);

    vcl::vect::Vect2s v9(v3);
    v9 += v4;
    assert(v9[0] == 25);
    assert(v9[1] == 26);

    v9 += 100;
    assert(v9[0] == 125);
    assert(v9[1] == 126);

    v9 += v;
    assert(v9[0] == 135);
    assert(v9[1] == 126);


    v9 += 15;
    assert(v9[0] == 150);
    assert(v9[1] == 141);

    vcl::vect::Vect2s v10 = v3 + v4 + v9;
    assert(v10[0] == 175);
    assert(v10[1] == 167);

    v9 -= v4;
    assert(v9[0] == 135);
    assert(v9[1] == 126);
    
    v9 -= 100;
    assert(v9[0] == 35);
    assert(v9[1] == 26);

    std::array<short, 2> s_arr = { 2,2 };
    v9 += s_arr;
    assert(v9[0] == 37);
    assert(v9[1] == 28);

    v9 -= s_arr;
    assert(v9[0] == 35);
    assert(v9[1] == 26);

    v9 -= v;
    assert(v9[0] == 25);
    assert(v9[1] == 26);

    v9 -= 15;
    assert(v9[0] == 10);
    assert(v9[1] == 11);

    v10 = v3 - v4 - v9;
    assert(v10[0] == -15);
    assert(v10[1] == -15);

    v10 = -v10;
    assert(v10[0] == 15);
    assert(v10[1] == 15);

    v10 = +v9;
    assert(v10[0] == 10);
    assert(v10[1] == 11);


    v9 *= v4;
    assert(v9[0] == 150);
    assert(v9[1] == 165);

    v9 *= 100;
    assert(v9[0] == 15000);
    assert(v9[1] == 16500);

    v10 *= v;
    assert(v10[0] == 100);
    assert(v10[1] == 11);

    v10 *= 15;
    assert(v10[0] == 15 * 100);
    assert(v10[1] == 15 * 11);

    v10 *= s_arr;
    assert(v10[0] == 2 * 15 * 100);
    assert(v10[1] == 2 * 15 * 11);

    v3 = 3;
    v4 = 4;
    v9 = 9;
    v10 = v3 * v4 * v9;
    assert(v10[0] == 108);
    assert(v10[1] == 108);
    
    v3 = 5 * v3;
    assert(v3[0] == 15);
    assert(v3[1] == 15);

    v3 = v4 * 2 * v3;
    assert(v3[0] == 120);
    assert(v3[1] == 120);

    vcl::vect::Vect2s v99(std::array<short, 2>({ 15000, 16500 }));
    v9 = v99;  // array<short, 2>({ 15000, 16500 });
    v9 /= 100;
    assert(v9[0] == 150);
    assert(v9[1] == 165);

    v9 /= v4;
    assert(v9[0] == 150 / 4);
    assert(v9[1] == 165 / 4);

    v10 /= 9;
    assert(v10[0] == 12);
    assert(v10[1] == 12);

    v4 = v3 / v10;
    assert(v4[0] == 10);
    assert(v4[1] == 10);

    std::array<int, 3> arr03i{ 11, 12, 13 };
    vcl::vect::Vect2b v02b;
    assert(v02b[0] == 0);
    assert(v02b[1] == 0);

    v02b = arr03i;
    assert(v02b[0] == 11);
    assert(v02b[1] == 12);

    vcl::vect::VectorT<float, 6> v06f;
    v06f = arr03i;
    assert(v06f[0] == 11.0f);
    assert(v06f[1] == 12.0f);
    assert(v06f[2] == 13.0f);
    assert(v06f[3] == 0.0f);
    assert(v06f[4] == 0.0f);
    assert(v06f[5] == 0.0f);

    v02b.zero();
    assert(v02b[0] == 0);
    assert(v02b[1] == 0);

    v02b = v06f;
    assert(v02b[0] == 11);
    assert(v02b[1] == 12);

    /***/

    std::vector<unsigned short> vec03us{ 111, 121, 131 };
    v02b = v06f * vec03us;
    assert(v02b[0] == 197);
    assert(v02b[1] == 172);

    v06f = vec03us;
    v06f /= (unsigned char)100;
    assert(v06f[0] == 1.11f);
    assert(v06f[1] == 1.21f);
    assert(v06f[2] == 1.31f);
    assert(v06f[3] == 0.0f);
    assert(v06f[4] == 0.0f);
    assert(v06f[5] == 0.0f);

    /***/

    cout << "--- ALL TESTS PASSED ---" << endl << endl;
}
