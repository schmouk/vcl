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
/** \brief core of test code for class vcl::vect::VectorT. */
{
    cout << "## vectors.vector / vcl::vect::VectorT testing application..." << endl;

    vcl::vect::VectorT<int, 5> v0;
    assert(v0[0] == 0);
    assert(v0[1] == 0);
    assert(v0[2] == 0);
    assert(v0[3] == 0);
    assert(v0[4] == 0);

    vcl::vect::VectorT<unsigned char, 5> v1(1LL);
    assert(v1[0] == 1);
    assert(v1[1] == 1);
    assert(v1[2] == 1);
    assert(v1[3] == 1);
    assert(v1[4] == 1);

    vcl::vect::VectorT<unsigned char, 5> v2(v1);
    assert(v2[0] == 1);
    assert(v2[1] == 1);
    assert(v2[2] == 1);
    assert(v2[3] == 1);
    assert(v2[4] == 1);

    std::vector<short> v = { 10, 11, 12, 13, 14 };
    vcl::vect::VectorT<short, 5> v31(v);
    assert(v31[0] == 10);
    assert(v31[1] == 11);
    assert(v31[2] == 12);
    assert(v31[3] == 13);
    assert(v31[4] == 14);

    //vcl::vect::VectorT<short, 5> v3(5, 10, 11, 12, 13, 14);
    vcl::vect::VectorT<short, 5> v3(10, 11, 12, 13, 14);
    assert(v3[0] == 10);
    assert(v3[1] == 11);
    assert(v3[2] == 12);
    assert(v3[3] == 13);
    assert(v3[4] == 14);

    vcl::vect::VectorT<short, 5> v4(15);
    assert(v4[0] == 15);
    assert(v4[1] == 15);
    assert(v4[2] == 15);
    assert(v4[3] == 15);
    assert(v4[4] == 15);

    v.pop_back();
    vcl::vect::VectorT<short, 5> v5(v);
    assert(v5[0] == 10);
    assert(v5[1] == 11);
    assert(v5[2] == 12);
    assert(v5[3] == 13);
    assert(v5[4] == 0);

    std::array<unsigned char, 5> arr = { 2,2,2,2,2 };
    vcl::vect::VectorT<unsigned char, 5> v6(arr);
    assert(v6[0] == 2);
    assert(v6[1] == 2);
    assert(v6[2] == 2);
    assert(v6[3] == 2);
    assert(v6[4] == 2);

    arr[4] = 3;
    v2.copy(arr);
    assert(v2[0] == 2);
    assert(v2[1] == 2);
    assert(v2[2] == 2);
    assert(v2[3] == 2);
    assert(v2[4] == 3);

    vcl::vect::VectorT<float, 5> v7;
    constexpr float V05 = (float)0.5;
    vcl::vect::VectorT<float, 5> v8(V05);
    v7 = v8;
    assert(v7[0] == V05);
    assert(v7[1] == V05);
    assert(v7[2] == V05);
    assert(v7[3] == V05);
    assert(v7[4] == V05);

    constexpr float V09 = (float)0.9;
    v8 = float(V09);
    assert(v8[0] == V09);
    assert(v8[1] == V09);
    assert(v8[2] == V09);
    assert(v8[3] == V09);
    assert(v8[4] == V09);

    vcl::vect::VectorT<short, 5> v9(v3);
    v9 += v4;
    assert(v9[0] == 25);
    assert(v9[1] == 26);
    assert(v9[2] == 27);
    assert(v9[3] == 28);
    assert(v9[4] == 29);

    v9 += (unsigned char)100;
    assert(v9[0] == 125);
    assert(v9[1] == 126);
    assert(v9[2] == 127);
    assert(v9[3] == 128);
    assert(v9[4] == 129);

    v9 += v;
    assert(v9[0] == 135);
    assert(v9[1] == 137);
    assert(v9[2] == 139);
    assert(v9[3] == 141);
    assert(v9[4] == 129);

    v9 += v4;
    assert(v9[0] == 150);
    assert(v9[1] == 152);
    assert(v9[2] == 154);
    assert(v9[3] == 156);
    assert(v9[4] == 144);

    vcl::vect::VectorT<short, 5> v10 = v3 + v4 + v9;
    assert(v10[0] == 175);
    assert(v10[1] == 178);
    assert(v10[2] == 181);
    assert(v10[3] == 184);
    assert(v10[4] == 173);

    v9 -= v4;
    assert(v9[0] == 135);
    assert(v9[1] == 137);
    assert(v9[2] == 139);
    assert(v9[3] == 141);
    assert(v9[4] == 129);

    v9 -= 100.0;
    assert(v9[0] == 35);
    assert(v9[1] == 37);
    assert(v9[2] == 39);
    assert(v9[3] == 41);
    assert(v9[4] == 29);

    std::array<short, 5> s_arr = { 2,2,2,2,2 };
    v9 += s_arr;
    assert(v9[0] == 37);
    assert(v9[1] == 39);
    assert(v9[2] == 41);
    assert(v9[3] == 43);
    assert(v9[4] == 31);

    v9 -= s_arr;
    assert(v9[0] == 35);
    assert(v9[1] == 37);
    assert(v9[2] == 39);
    assert(v9[3] == 41);
    assert(v9[4] == 29);

    v9 -= v;
    assert(v9[0] == 25);
    assert(v9[1] == 26);
    assert(v9[2] == 27);
    assert(v9[3] == 28);
    assert(v9[4] == 29);

    v9 -= v4;
    assert(v9[0] == 10);
    assert(v9[1] == 11);
    assert(v9[2] == 12);
    assert(v9[3] == 13);
    assert(v9[4] == 14);

    v10 = v3 - v4 - v9;
    assert(v10[0] == -15);
    assert(v10[1] == -15);
    assert(v10[2] == -15);
    assert(v10[3] == -15);
    assert(v10[4] == -15);

    v10 = -v10;
    assert(v10[0] == 15);
    assert(v10[1] == 15);
    assert(v10[2] == 15);
    assert(v10[3] == 15);
    assert(v10[4] == 15);

    v10 = +v9;
    assert(v10[0] == 10);
    assert(v10[1] == 11);
    assert(v10[2] == 12);
    assert(v10[3] == 13);
    assert(v10[4] == 14);


    v9 *= v4;
    assert(v9[0] == 150);
    assert(v9[1] == 165);
    assert(v9[2] == 180);
    assert(v9[3] == 195);
    assert(v9[4] == 210);

    v9 *= (unsigned long)100;
    assert(v9[0] == 15000);
    assert(v9[1] == 16500);
    assert(v9[2] == 18000);
    assert(v9[3] == 19500);
    assert(v9[4] == 21000);

    v10 *= v;
    assert(v10[0] == 100);
    assert(v10[1] == 121);
    assert(v10[2] == 144);
    assert(v10[3] == 169);
    assert(v10[4] == 14);

    v10 *= v4;
    assert(v10[0] == 15 * 100);
    assert(v10[1] == 15 * 121);
    assert(v10[2] == 15 * 144);
    assert(v10[3] == 15 * 169);
    assert(v10[4] == 15 * 14);

    v10 *= s_arr;
    assert(v10[0] == 2 * 15 * 100);
    assert(v10[1] == 2 * 15 * 121);
    assert(v10[2] == 2 * 15 * 144);
    assert(v10[3] == 2 * 15 * 169);
    assert(v10[4] == 2 * 15 * 14);

    v3 = 3.0f;
    v4 = 4.0;
    v9 = char(9);
    v10 = v3 * v4 * v9;
    assert(v10[0] == 108);
    assert(v10[1] == 108);
    assert(v10[2] == 108);
    assert(v10[3] == 108);
    assert(v10[4] == 108);

    v3 = 5.0f * v3;
    assert(v3[0] == 15);
    assert(v3[1] == 15);
    assert(v3[2] == 15);
    assert(v3[3] == 15);
    assert(v3[4] == 15);

    v3 = v4 * 2 * v3;
    assert(v3[0] == 120);
    assert(v3[1] == 120);
    assert(v3[2] == 120);
    assert(v3[3] == 120);
    assert(v3[4] == 120);


    v9 = array<short, 5>({ 15000, 16500, 18000, 19500, 21000 });
    v9 /= 100;
    assert(v9[0] == 150);
    assert(v9[1] == 165);
    assert(v9[2] == 180);
    assert(v9[3] == 195);
    assert(v9[4] == 210);

    v9 /= v4;
    assert(v9[0] == 150 / 4);
    assert(v9[1] == 165 / 4);
    assert(v9[2] == 180 / 4);
    assert(v9[3] == 195 / 4);
    assert(v9[4] == 210 / 4);

    v10 /= 9.0;
    assert(v10[0] == 12);
    assert(v10[1] == 12);
    assert(v10[2] == 12);
    assert(v10[3] == 12);
    assert(v10[4] == 12);

    v4 = v3 / v10;
    assert(v4[0] == 10);
    assert(v4[1] == 10);
    assert(v4[2] == 10);
    assert(v4[3] == 10);
    assert(v4[4] == 10);


    std::array<int, 3> arr03i{ 11, 12, 13 };
    vcl::vect::VectorT<unsigned char, 2> v02b;
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

    std::vector<unsigned short> vec03us{ 111, 121, 131 };
    v02b = vec03us;
    assert(v02b[0] == 111);
    assert(v02b[1] == 121);

    v06f = vec03us;
    v06f /= (unsigned char)100;
    assert(v06f[0] == 1.11f);
    assert(v06f[1] == 1.21f);
    assert(v06f[2] == 1.31f);
    assert(v06f[3] == 0.0f);
    assert(v06f[4] == 0.0f);
    assert(v06f[5] == 0.0f);

    //vcl::vect::VectorT<double, 7> vv7(6, 111.1, 122.2, 133.3, 144.4, 155.5, 166.6);
    vcl::vect::VectorT<double, 7> vv7(111.1, 122.2, 133.3, 144.4, 155.5, 166.6);
    assert(vv7[0] == 111.1);
    assert(vv7[1] == 122.2);
    assert(vv7[2] == 133.3);
    assert(vv7[3] == 144.4);
    assert(vv7[4] == 155.5);
    assert(vv7[5] == 166.6);
    assert(vv7[6] == 0.0);

    //vcl::vect::VectorT<double, 5> vv5(9, 111.1, 122.0, 133.0, 144.0, 155.0, 166.0, 177.0, 188.0, 199.0);
    vcl::vect::VectorT<double, 5> vv5(111.1, 122.0, 133.0, 144.0, 155.0, 166.0, 177.0, 188.0, 199.0);
    assert(vv5[0] == 111.1);
    assert(vv5[1] == 122.0);
    assert(vv5[2] == 133.0);
    assert(vv5[3] == 144.0);
    assert(vv5[4] == 155.0);

    vv5 = 0.01;
    assert(vv5[0] == 0.01);
    assert(vv5[1] == 0.01);
    assert(vv5[2] == 0.01);
    assert(vv5[3] == 0.01);
    assert(vv5[4] == 0.01);

    cout << "--- ALL TESTS PASSED ---" << endl << endl;
}