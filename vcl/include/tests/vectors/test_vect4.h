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
/** \brief main for tests on class vcl::vect::Vect4T. */
{
    cout << "## vectors.vect4 / vcl::vect::Vect4T testing application..." << endl;

    vcl::vect::Vect4i v0;
    assert(v0[0] == 0);
    assert(v0[1] == 0);
    assert(v0[2] == 0);
    assert(v0[3] == 0);

    vcl::vect::Vect4b v1(1);
    assert(v1[0] == 1);
    assert(v1[1] == 1);
    assert(v1[2] == 1);
    assert(v1[3] == 1);

    vcl::vect::Vect4b v2(v1);
    assert(v2[0] == 1);
    assert(v2[1] == 1);
    assert(v2[2] == 1);
    assert(v2[3] == 1);

    std::vector<short> v = { 10, 11, 12, 13, 14 };
    vcl::vect::Vect4 v3(v);
    assert(v3[0] == 10);
    assert(v3[1] == 11);
    assert(v3[2] == 12);
    assert(v3[3] == 13);

    assert(v3.x() == 10);
    assert(v3.y() == 11);
    assert(v3.z() == 12);
    assert(v3.w() == 13);

    v3.x(5);
    v3.y(6);
    v3.z(7);
    v3.w() = 8;
    assert(v3.x() == 5);
    assert(v3.y() == 6);
    assert(v3.z() == 7);
    assert(v3.w() == 8);

    v3 = v;
    assert(v3[0] == 10);
    assert(v3[1] == 11);
    assert(v3[2] == 12);
    assert(v3[3] == 13);


    vcl::vect::Vect4s v4(15.0);
    assert(v4[0] == 15);
    assert(v4[1] == 15);
    assert(v4[2] == 15);
    assert(v4[3] == 15);

    v.pop_back();
    v.pop_back();
    vcl::vect::Vect4T<short> v5(v);
    assert(v5[0] == 10);
    assert(v5[1] == 11);
    assert(v5[2] == 12);
    assert(v5[3] == 0);

    std::array<unsigned char, 4> arr = { 2,2,2,2 };
    vcl::vect::Vect4b v6(arr);
    assert(v6[0] == 2);
    assert(v6[1] == 2);
    assert(v6[2] == 2);
    assert(v6[3] == 2);

    arr[3] = 3;
    v2.copy(arr);
    assert(v2[0] == 2);
    assert(v2[1] == 2);
    assert(v2[2] == 2);
    assert(v2[3] == 3);

    vcl::vect::Vect4f v7;
    constexpr float V05 = (float)0.5;
    vcl::vect::Vect4f v8(V05);
    v7 = v8;
    assert(v7[0] == V05);
    assert(v7[1] == V05);
    assert(v7[2] == V05);
    assert(v7[3] == V05);

    constexpr float V09 = (float)0.9;
    v8 = float(V09);
    assert(v8[0] == V09);
    assert(v8[1] == V09);
    assert(v8[2] == V09);
    assert(v8[3] == V09);

    vcl::vect::Vect4s v9(v3);
    v9 += v4;
    assert(v9[0] == 25);
    assert(v9[1] == 26);
    assert(v9[2] == 27);
    assert(v9[3] == 28);

    v9 += 100;
    assert(v9[0] == 125);
    assert(v9[1] == 126);
    assert(v9[2] == 127);
    assert(v9[3] == 128);

    v9 += v;
    assert(v9[0] == 135);
    assert(v9[1] == 137);
    assert(v9[2] == 139);
    assert(v9[3] == 128);

    v9 += 15;
    assert(v9[0] == 150);
    assert(v9[1] == 152);
    assert(v9[2] == 154);
    assert(v9[3] == 143);

    vcl::vect::Vect4s v10 = v3 + v4 + v9;
    assert(v10[0] == 175);
    assert(v10[1] == 178);
    assert(v10[2] == 181);
    assert(v10[3] == 171);


    v9 -= v4;
    assert(v9[0] == 135);
    assert(v9[1] == 137);
    assert(v9[2] == 139);
    assert(v9[3] == 128);

    v9 -= 100;
    assert(v9[0] == 35);
    assert(v9[1] == 37);
    assert(v9[2] == 39);
    assert(v9[3] == 28);

    std::array<short, 4> s_arr = { 2,2,2,2 };
    v9 += s_arr;
    assert(v9[0] == 37);
    assert(v9[1] == 39);
    assert(v9[2] == 41);
    assert(v9[3] == 30);

    v9 -= s_arr;
    assert(v9[0] == 35);
    assert(v9[1] == 37);
    assert(v9[2] == 39);
    assert(v9[3] == 28);

    v9 -= v;
    assert(v9[0] == 25);
    assert(v9[1] == 26);
    assert(v9[2] == 27);
    assert(v9[3] == 28);

    v9 -= 15;
    assert(v9[0] == 10);
    assert(v9[1] == 11);
    assert(v9[2] == 12);
    assert(v9[3] == 13);

    v10 = v3 - v4 - v9;
    assert(v10[0] == -15);
    assert(v10[1] == -15);
    assert(v10[2] == -15);
    assert(v10[3] == -15);

    v10 = -v10;
    assert(v10[0] == 15);
    assert(v10[1] == 15);
    assert(v10[2] == 15);
    assert(v10[3] == 15);

    v10 = +v9;
    assert(v10[0] == 10);
    assert(v10[1] == 11);
    assert(v10[2] == 12);
    assert(v10[3] == 13);


    v9 *= v4;
    assert(v9[0] == 150);
    assert(v9[1] == 165);
    assert(v9[2] == 180);
    assert(v9[3] == 195);

    v9 *= 100;
    assert(v9[0] == 15000);
    assert(v9[1] == 16500);
    assert(v9[2] == 18000);
    assert(v9[3] == 19500);

    v10 *= v;
    assert(v10[0] == 100);
    assert(v10[1] == 121);
    assert(v10[2] == 144);
    assert(v10[3] == 13);

    v10 *= 15;
    assert(v10[0] == 15 * 100);
    assert(v10[1] == 15 * 121);
    assert(v10[2] == 15 * 144);
    assert(v10[3] == 15 * 13);

    v10 *= s_arr;
    assert(v10[0] == 2 * 15 * 100);
    assert(v10[1] == 2 * 15 * 121);
    assert(v10[2] == 2 * 15 * 144);
    assert(v10[3] == 2 * 15 * 13);

    v3 = 3;
    v4 = 4;
    v9 = 9;
    v10 = v3 * v4 * v9;
    assert(v10[0] == 108);
    assert(v10[1] == 108);
    assert(v10[2] == 108);
    assert(v10[3] == 108);

    v3 = 5 * v3;
    assert(v3[0] == 15);
    assert(v3[1] == 15);
    assert(v3[2] == 15);
    assert(v3[3] == 15);

    v3 = v4 * 2 * v3;
    assert(v3[0] == 120);
    assert(v3[1] == 120);
    assert(v3[2] == 120);
    assert(v3[3] == 120);

    vcl::vect::Vect4s v99(array<short, 4>({ 15000, 16500, 18000, 19500 }));
    v9 = v99;
    v9 /= 100;
    assert(v9[0] == 150);
    assert(v9[1] == 165);
    assert(v9[2] == 180);
    assert(v9[3] == 195);

    v9 /= v4;
    assert(v9[0] == 150 / 4);
    assert(v9[1] == 165 / 4);
    assert(v9[2] == 180 / 4);
    assert(v9[3] == 195 / 4);

    v10 /= 9;
    assert(v10[0] == 12);
    assert(v10[1] == 12);
    assert(v10[2] == 12);
    assert(v10[3] == 12);

    v4 = v3 / v10;
    assert(v4[0] == 10);
    assert(v4[1] == 10);
    assert(v4[2] == 10);
    assert(v4[3] == 10);

    v4 = 15.0f * v4;
    assert(v4[0] == 150);
    assert(v4[1] == 150);
    assert(v4[2] == 150);
    assert(v4[3] == 150);

    v4 /= (long long)15;
    assert(v4[0] == 10);
    assert(v4[1] == 10);
    assert(v4[2] == 10);
    assert(v4[3] == 10);

    vcl::vect::Vect4T<unsigned short> v19(std::array<short, 4>({ 1, 2, 3, 5 }));
    v9 = 15 / v19;
    assert(v9[0] == 15);
    assert(v9[1] == 7);
    assert(v9[2] == 5);
    assert(v9[3] == 3);


    cout << "--- ALL TESTS PASSED ---" << endl << endl;
}
