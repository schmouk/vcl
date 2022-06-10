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
/** \brief main for tests on class vcl::utils::Pos. */
{
cout << "## utils.offsets / vcl::utils::Offsets testing application..." << endl;

vcl::utils::Offsets_f o0f;
assert(o0f[0] == 0.0);
assert(o0f[1] == 0.0);

vcl::utils::OffsetsT<float> o08f(0.8);
assert(o08f.dx() == 0.8f);
assert(o08f.dy() == 0.8f);
o08f.y(o08f.y() + 0.25f);
assert(o08f.dy() == 1.05f);

std::vector<short> v = { 10, 11, 12, 13, 14 };
vcl::utils::Offsets_s o3s(v);
assert(o3s[0] == 10);
assert(o3s[1] == 11);

assert(o3s.x() == 10);
assert(o3s.y() == 11);
assert(o3s.dx() == 10);
assert(o3s.dy() == 11);

o3s.dx(5);
o3s.dy(6);
assert(o3s.x() == 5);
assert(o3s.y() == 6);

o3s = v;
assert(o3s[0] == 10);
assert(o3s[1] == 11);

vcl::utils::Offsets_s o4s(15);
assert(o4s[0] == 15);
assert(o4s[1] == 15);

v.pop_back();
v.pop_back();
v.pop_back();
v.pop_back();
vcl::utils::Offsets_i o5s(v);
assert(o5s.x() == 10);
assert(o5s.dy() == 0);

std::array<unsigned char, 2> arr = { 2,2 };
vcl::utils::Offsets_s o6us(arr);
assert(o6us[0] == 2);
assert(o6us[1] == 2);

arr[1] = 3;
o3s.copy(arr);
assert(o3s[0] == 2);
assert(o3s[1] == 3);

vcl::utils::Offsets_s o9s(o3s + 8);
o9s += o4s;
assert(o9s[0] == 25);
assert(o9s[1] == 26);

o9s += 100;
assert(o9s[0] == 125);
assert(o9s[1] == 126);

o9s += v;
assert(o9s[0] == 135);
assert(o9s[1] == 126);

o9s += 15;
assert(o9s[0] == 150);
assert(o9s[1] == 141);

o3s += 8.0;
vcl::utils::Offsets_s o10s = o3s + o4s + o9s;
assert(o10s.dx() == 175);
assert(o10s.y() == 167);

o9s -= o4s;
assert(o9s[0] == 135);
assert(o9s[1] == 126);

o9s -= 100;
assert(o9s[0] == 35);
assert(o9s[1] == 26);

o9s *= 1.5;
assert(o9s.dx() == 52);
assert(o9s.dy() == 39);

o9s /= 2;
assert(o9s.dx() == 26);
assert(o9s.dy() == 19);

vcl::utils::OffsetsT<float> o11f(0.2, 0.1);
assert(o11f == o11f);
assert(!(o11f != o11f));

cout << "--- ALL TESTS PASSED ---" << endl << endl;
}
