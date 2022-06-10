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

cout << "## utils.pos / vcl::utils::Pos testing application..." << endl;


const vcl::utils::Pos_s my_pos_Origin_s = vcl::utils::Pos_s::origin();
assert(my_pos_Origin_s.x() == 0);
assert(my_pos_Origin_s.y() == 0);

assert(vcl::utils::Pos_s::origin().x() == 0);
assert(vcl::utils::Pos_s::origin().y() == 0);
assert(vcl::utils::Pos_us::origin().x() == 0);
assert(vcl::utils::Pos_us::origin().y() == 0);
assert(vcl::utils::Pos_i::origin().x() == 0);
assert(vcl::utils::Pos_i::origin().y() == 0);
assert(vcl::utils::Pos_ui::origin().x() == 0);
assert(vcl::utils::Pos_ui::origin().y() == 0);
assert(vcl::utils::Pos_f::origin().x() == 0);
assert(vcl::utils::Pos_f::origin().y() == 0);

/***/

vcl::utils::PosT<unsigned char> pos;
assert(pos[0] == 0);
assert(pos[1] == 0);

vcl::utils::Pos_f p0f;
assert(p0f[0] == 0.0f);
assert(p0f[1] == 0.0f);


vcl::utils::PosT<float> p08f(0.8f);
assert(p08f[0] == 0.8f);
assert(p08f[1] == 0.8f);
p08f.y(p08f.y() + 0.25);
assert(p08f[1] == 1.05f);

vcl::utils::Pos_us p0i;
assert(p0i[0] == 0);
assert(p0i[1] == 0);

vcl::utils::Pos_s p1s(32768);
assert(p1s[0] == 32767);
assert(p1s[1] == 32767);

vcl::utils::Pos_s p2us(p1s);
assert(p2us[0] == 32767);
assert(p2us[1] == 32767);

p2us -= 32767;
assert(p2us[0] == 0);
assert(p2us[1] == 0);

p2us += 1;
assert(p2us[0] == 1);
assert(p2us[1] == 1);

std::vector<short> v = { 10, 11, 12, 13, 14 };
vcl::utils::Pos_s p3s(v);
assert(p3s[0] == 10);
assert(p3s[1] == 11);

assert(p3s.x() == 10);
assert(p3s.y() == 11);

p3s.x(5);
p3s.y(6);
assert(p3s.x() == 5);
assert(p3s.y() == 6);

p3s = v;
assert(p3s[0] == 10);
assert(p3s[1] == 11);


vcl::utils::Pos_s p4s(15);
assert(p4s[0] == 15);
assert(p4s[1] == 15);

v.pop_back();
v.pop_back();
v.pop_back();
v.pop_back();
vcl::utils::Pos_s p5s(v);
assert(p5s[0] == 10);
assert(p5s[1] == 0);

std::array<unsigned char, 2> arr = { 2,2 };
vcl::utils::Pos_us p6us(arr);
assert(p6us[0] == 2);
assert(p6us[1] == 2);

arr[1] = 3;
p3s.copy(arr);
assert(p3s[0] == 2);
assert(p3s[1] == 3);

vcl::utils::Pos_f p7f;
constexpr float p05 = 0.5f;
vcl::utils::Pos_f p8f(p05);
p7f = p8f;
assert(p7f[0] == p05);
assert(p7f[1] == p05);

constexpr float k09f = (float)0.9;
p8f = float(k09f);
assert(p8f[0] == k09f);
assert(p8f[1] == k09f);

vcl::utils::Pos_s p9s(p3s + 8);
p9s += p4s;
assert(p9s[0] == 25);
assert(p9s[1] == 26);

p9s += 100;
assert(p9s[0] == 125);
assert(p9s[1] == 126);

p9s += v;
assert(p9s[0] == 135);
assert(p9s[1] == 126);

p9s += 15;
assert(p9s[0] == 150);
assert(p9s[1] == 141);

p3s += 8.0;
vcl::utils::Pos_s p10s = p3s + p4s + p9s;
assert(p10s[0] == 175);
assert(p10s[1] == 167);

p9s -= p4s;
assert(p9s[0] == 135);
assert(p9s[1] == 126);


p9s -= 100;
assert(p9s[0] == 35);
assert(p9s[1] == 26);

std::array<short, 2> s_arr = { 2,2 };
p9s += s_arr;
assert(p9s[0] == 37);
assert(p9s[1] == 28);

p9s -= s_arr;
assert(p9s[0] == 35);
assert(p9s[1] == 26);

p9s -= v;
assert(p9s[0] == 25);
assert(p9s[1] == 26);

p9s -= 15;
assert(p9s[0] == 10);
assert(p9s[1] == 11);

p10s = p3s - p4s - p9s;
assert(p10s[0] == -15);
assert(p10s[1] == -15);

p10s = -p10s;
assert(p10s[0] == 15);
assert(p10s[1] == 15);

p10s = +p9s;
assert(p10s[0] == 10);
assert(p10s[1] == 11);

p9s *= p4s;
assert(p9s[0] == 150);
assert(p9s[1] == 165);

p9s *= 100;
assert(p9s[0] == 15000);
assert(p9s[1] == 16500);

p10s *= v;
assert(p10s[0] == 100);
assert(p10s[1] == 11);

p10s *= 15;
assert(p10s[0] == 15 * 100);
assert(p10s[1] == 15 * 11);

p10s *= s_arr;
assert(p10s[0] == 2 * 15 * 100);
assert(p10s[1] == 2 * 15 * 11);

p3s = 3;
p4s = 4;
p9s = 9;
p10s = p3s * p4s * p9s;
assert(p10s[0] == 108);
assert(p10s[1] == 108);

p3s = 5 * p3s;
assert(p3s[0] == 15);
assert(p3s[1] == 15);

p3s = p4s * 2 * p3s;
assert(p3s[0] == 120);
assert(p3s[1] == 120);

vcl::utils::Pos_s p99s(array<short, 2>({ 15000, 16500 }));
p9s = p99s;  // array<short, 2>({ 15000, 16500 });
p9s /= 100;
assert(p9s[0] == 150);
assert(p9s[1] == 165);

p9s /= p4s;
assert(p9s[0] == 150 / 4);
assert(p9s[1] == 165 / 4);

p10s /= 9;
assert(p10s[0] == 12);
assert(p10s[1] == 12);

p4s = p3s / p10s;
assert(p4s[0] == 10);
assert(p4s[1] == 10);

p4s = 15 * p4s;
assert(p4s[0] == 150);
assert(p4s[1] == 150);

p4s /= 15;
assert(p4s[0] == 10);
assert(p4s[1] == 10);

p9s = std::array<short, 2>({ 1, 2 });
p9s = 15 / p9s;
assert(p9s[0] == 15);
assert(p9s[1] == 7);

assert(p9s == p9s);
assert(p4s != p9s);

cout << "--- ALL TESTS PASSED ---" << endl << endl;
