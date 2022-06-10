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
cout << "## utils.dims / vcl::utils::DimsT testing application..." << endl;

vcl::utils::Dims_f d0f;
assert(d0f[0] == 0.0);
assert(d0f[1] == 0.0);
assert(d0f.area() == 0.0);

vcl::utils::DimsT<float> d08f(0.8);
assert(d08f.width() == 0.8f);
assert(d08f.height() == 0.8f);
d08f.y(d08f.y() + 0.25f);
assert(d08f.height() == 1.05f);
assert(d08f.area() == 1.05f * 0.8f);

std::vector<unsigned short> v = { 10, 11, 12, 13, 14 };
vcl::utils::Dims_us d3s(v);
assert(d3s[0] == 10);
assert(d3s[1] == 11);

assert(d3s.x() == 10);
assert(d3s.y() == 11);
assert(d3s.width() == 10);
assert(d3s.height() == 11);

/*** /
* 
d3s.width(5);
d3s.height(6);
assert(d3s.x() == 5);
assert(d3s.y() == 6);

d3s = v;
assert(d3s[0] == 10);
assert(d3s[1] == 11);

vcl::utils::Dims_us d4s(15);
assert(d4s[0] == 15);
assert(d4s[1] == 15);

v.pop_back();
v.pop_back();
v.pop_back();
v.pop_back();
vcl::utils::Dims_ui d5s(v);
assert(d5s.x() == 10);
assert(d5s.height() == 0);
assert(d5s.area() == 0.0);

std::array<unsigned char, 2> arr = { 2,2 };
vcl::utils::Dims_us d6us(arr);
assert(d6us[0] == 2);
assert(d6us[1] == 2);

arr[1] = 3;
d3s.copy(arr);
assert(d3s[0] == 2);
assert(d3s[1] == 3);

vcl::utils::Dims_us d9s(d3s + 8);
d9s += d4s;
assert(d9s[0] == 25);
assert(d9s[1] == 26);

d9s += 100;
assert(d9s[0] == 125);
assert(d9s[1] == 126);

d9s += v;
assert(d9s[0] == 135);
assert(d9s[1] == 126);

d9s += 15;
assert(d9s[0] == 150);
assert(d9s[1] == 141);

d3s += 8.0;
vcl::utils::Dims_us d10s = d3s + d4s + d9s;
assert(d10s.width() == 175);
assert(d10s.y() == 167);

d9s -= d4s;
assert(d9s[0] == 135);
assert(d9s[1] == 126);

d9s -= 100;
assert(d9s[0] == 35);
assert(d9s[1] == 26);
assert(d9s.area() == 910);

d9s *= 1.5;
assert(d9s.width() == 52);
assert(d9s.height() == 39);
assert(d9s.area() == 2028);

d9s /= 2;
assert(d9s.width() == 26);
assert(d9s.height() == 19);
assert(d9s.area() == 494);

vcl::utils::DimsT<float> d11f(0.2, 0.1);
assert(d11f.area() == 0.2f * 0.1f);
assert(d11f == d11f);
assert(!(d11f != d11f));

assert(d9s != d10s);
assert(! (d9s == d10s));
assert(d9s <= d10s);
assert(d9s < d10s);
assert(d10s >= d9s);
assert(d10s > d9s);
assert(d11f < d9s);

/***/

cout << "--- ALL TESTS PASSED ---" << endl << endl;
}
