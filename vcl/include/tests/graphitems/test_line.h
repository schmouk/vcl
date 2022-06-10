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
/** \brief core of test code for class vcl::vect::Vector. */
{
cout << "## graphitems.line / vcl::graphitems::LineT testing application..." << endl;

vcl::graphitems::Line line_00;
assert(line_00.start.x() == 0);
assert(line_00.start.y() == 0);
assert(line_00.end.x() == 0);
assert(line_00.end.y() == 0);

vcl::graphitems::Line_us line_us01(1, 2, 3, 4);
assert(line_us01.start.x() == 1);
assert(line_us01.start.y() == 2);
assert(line_us01.end.x() == 3);
assert(line_us01.end.y() == 4);

vcl::graphitems::Line line_02(line_us01);
assert(line_02.start.x() == 1);
assert(line_02.start.y() == 2);
assert(line_02.end.x() == 3);
assert(line_02.end.y() == 4);

vcl::graphitems::Line_b line_b03(vcl::vect::Vect4d(28.3, 37.6, 46.3, 55.99999));
assert(line_b03.start.x() == 28);
assert(line_b03.start.y() == 37);
assert(line_b03.end.x() == 46);
assert(line_b03.end.y() == 55);

vcl::graphitems::Line_c line_c04(std::vector<unsigned char>{ 3, 15, 128, 254 });
assert(line_c04.start.x() == 3);
assert(line_c04.start.y() == 15);
assert(line_c04.end.x() == 127);
assert(line_c04.end.y() == 127);

vcl::graphitems::Line_ui line_ul05(std::array<long long, 4>{ 1, 2, -3, 0x7fff'ffff'ffff'ffff});
assert(line_ul05.start.x() == 1);
assert(line_ul05.start.y() == 2);
assert(line_ul05.end.x() == 0);
assert(line_ul05.end.y() == 0xffff'ffff);

vcl::graphitems::Line_ll line_ll06(1, 2, vcl::utils::Pos_f(3.01f, 4.8));
assert(line_ll06.start.x() == 1);
assert(line_ll06.start.y() == 2);
assert(line_ll06.end.x() == 3);
assert(line_ll06.end.y() == 4);

vcl::graphitems::Line_ll line_ll07(vcl::utils::Pos_f(3.01f, 4.8), 1, 2);
assert(line_ll07.start.x() == 3);
assert(line_ll07.start.y() == 4);
assert(line_ll07.end.x() == 1);
assert(line_ll07.end.y() == 2);


vcl::graphitems::Line_us line_us08(std::make_pair(3.01f, 4.8), std::make_pair(5, 6ULL));
assert(line_us08.start.x() == 3);
assert(line_us08.start.y() == 4);
assert(line_us08.end.x() == 5);
assert(line_us08.end.y() == 6);

line_b03 = line_us01;
assert(line_b03.start.x() == 1);
assert(line_b03.start.y() == 2);
assert(line_b03.end.x() == 3);
assert(line_b03.end.y() == 4);

line_b03 = vcl::graphitems::Line(1, 2, -3, 0x7fff);
assert(line_b03.start.x() == 1);
assert(line_b03.start.y() == 2);
assert(line_b03.end.x() == 0);
assert(line_b03.end.y() == 0xff);

line_b03 = vcl::vect::Vect4s(1, 2, -3, 0x7fff);
assert(line_b03.start.x() == 1);
assert(line_b03.start.y() == 2);
assert(line_b03.end.x() == 0);
assert(line_b03.end.y() == 0xff);

std::vector<long long> vect_4ll{ 1, 2, -3, 0x7fff };
line_b03 = vect_4ll;
assert(line_b03.start.x() == 1);
assert(line_b03.start.y() == 2);
assert(line_b03.end.x() == 0);
assert(line_b03.end.y() == 0xff);

std::array<float, 5> arr_5f{ 1.1f, 2.9f, -3.f, float(0x7fff), 4096.0f };
line_b03 = arr_5f;
assert(line_b03.start.x() == 1);
assert(line_b03.start.y() == 2);
assert(line_b03.end.x() == 0);
assert(line_b03.end.y() == 0xff);

assert(line_b03 == line_b03);
assert(line_b03 != line_c04);
line_ll06 = line_b03;
assert(line_b03 == line_ll06);

++line_b03.start.x();
line_b03.end.y() -= 1;
assert(line_b03.start.x() == 2);
assert(line_b03.start.y() == 2);
assert(line_b03.end.x() == 0);
assert(line_b03.end.y() == 0xfe);

line_ll06 = arr_5f;
vcl::graphitems::Line line_s07(arr_5f);
assert(line_ll06 == line_s07);
assert(line_s07 == line_ll06);

line_ul05 = arr_5f;
assert(line_ul05 != line_ll06);
assert(line_ll06 != line_ul05);

//std::array<float, 5> arr_5f{ 1.1f, 2.9f, -3.f, float(0x7fff), 4096.0f };
line_b03 = arr_5f;
assert(line_b03.length() == sqrt((0-1) * (0-1) + ((255-2) * (255-2))));

line_b03.set_length(14);
assert(line_b03.start.x() == 1);
assert(line_b03.start.y() == 2);
assert(line_b03.end.x() == 1);
assert(line_b03.end.y() == 16);

vcl::vect::ClipVect4us v4us = (vcl::vect::ClipVect4us)line_ll06;
assert(v4us == vcl::vect::ClipVect4us(1, 2, 0, 32767));

vcl::vect::ClipVect4us v4_us = vcl::vect::ClipVect4us(line_ll06);
assert(v4us == v4_us);

vcl::vect::ClipVect4ll v4ll = (vcl::vect::ClipVect4ll)line_ll06;
assert(v4us == vcl::vect::ClipVect4us(1, 2, -3, 32767));

std::vector<float> vf = (std::vector<float>)line_ll06;
const std::vector<float> vcf{ 1, 2, -3, 32767 };
assert(vf == vcf);

std::array<float, 4> af = (std::array<float, 4>)line_ll06;
const std::array<float, 4> acf{ 1, 2, -3, 32767 };
assert(af == acf);

line_b03 = arr_5f; // 1, 2, 0, 255
line_b03.move(-1, 4);
assert(line_b03.start.x() == 0);
assert(line_b03.start.y() == 6);
assert(line_b03.end.x() == 0);
assert(line_b03.end.y() == 255);

line_b03.move(4, -1);
assert(line_b03.start.x() == 4);
assert(line_b03.start.y() == 5);
assert(line_b03.end.x() == 4);
assert(line_b03.end.y() == 254);

line_b03.move(v4us);
assert(line_b03.start.x() == 5);
assert(line_b03.start.y() == 7);
assert(line_b03.end.x() == 5);
assert(line_b03.end.y() == 255);

line_b03.end.y() -= 6;
line_b03.move(vect_4ll);
assert(line_b03.start.x() == 6);
assert(line_b03.start.y() == 9);
assert(line_b03.end.x() == 6);
assert(line_b03.end.y() == 251);

line_b03.move(arr_5f);
assert(line_b03.start.x() == 7);
assert(line_b03.start.y() == 11);
assert(line_b03.end.x() == 7);
assert(line_b03.end.y() == 253);

line_b03.move(std::make_pair(-6.1, 3ULL));
assert(line_b03.start.x() == 0);
assert(line_b03.start.y() == 14);
assert(line_b03.end.x() == 0);
assert(line_b03.end.y() == 255);

line_b03.move(vcl::utils::Offsets_ll(1,-2));
assert(line_b03.start.x() == 1);
assert(line_b03.start.y() == 12);
assert(line_b03.end.x() == 1);
assert(line_b03.end.y() == 253);

line_b03 += v4us;
assert(line_b03.start.x() == 2);
assert(line_b03.start.y() == 14);
assert(line_b03.end.x() == 2);
assert(line_b03.end.y() == 255);

line_b03 += v4ll;
assert(line_b03.start.x() == 3);
assert(line_b03.start.y() == 16);
assert(line_b03.end.x() == 3);
assert(line_b03.end.y() == 255);

line_b03 += arr_5f;
assert(line_b03.start.x() == 4);
assert(line_b03.start.y() == 18);
assert(line_b03.end.x() == 4);
assert(line_b03.end.y() == 255);

line_b03 += std::make_pair(-2.1, -3LL);
assert(line_b03.start.x() == 1);
assert(line_b03.start.y() == 15);
assert(line_b03.end.x() == 1);
assert(line_b03.end.y() == 252);

line_b03 += vcl::utils::Offsets_ll(1, -2);
assert(line_b03.start.x() == 2);
assert(line_b03.start.y() == 13);
assert(line_b03.end.x() == 2);
assert(line_b03.end.y() == 250);

line_ul05 = line_b03 + v4us;
assert(line_ul05.start.x() == 3);
assert(line_ul05.start.y() == 15);
assert(line_ul05.end.x() == 3);
assert(line_ul05.end.y() == 252);

line_ul05 = v4us + line_ul05;
assert(line_ul05.start.x() == 4);
assert(line_ul05.start.y() == 17);
assert(line_ul05.end.x() == 4);
assert(line_ul05.end.y() == 254);

line_b03.end.y() = 254;
line_ul05 = line_b03 + v4ll;
assert(line_ul05.start.x() == 3);
assert(line_ul05.start.y() == 15);
assert(line_ul05.end.x() == 3);
assert(line_ul05.end.y() == 255);

line_ul05 = line_b03 + v4ll;
assert(line_ul05.start.x() == 3);
assert(line_ul05.start.y() == 15);
assert(line_ul05.end.x() == 3);
assert(line_ul05.end.y() == 255);

line_ul05 = line_b03 + arr_5f;
assert(line_ul05.start.x() == 3);
assert(line_ul05.start.y() == 15);
assert(line_ul05.end.x() == 3);
assert(line_ul05.end.y() == 255);

line_ul05 = arr_5f + line_b03;
assert(line_ul05.start.x() == 3);
assert(line_ul05.start.y() == 15);
assert(line_ul05.end.x() == 3);
assert(line_ul05.end.y() == 255);

line_ul05 = line_b03 + std::make_pair(-2.1, -3LL);
assert(line_ul05.start.x() == 0);
assert(line_ul05.start.y() == 10);
assert(line_ul05.end.x() == 0);
assert(line_ul05.end.y() == 251);

line_ul05 = std::make_pair(2.1, 5LL) + line_b03;
assert(line_ul05.start.x() == 4);
assert(line_ul05.start.y() == 18);
assert(line_ul05.end.x() == 4);
assert(line_ul05.end.y() == 255);

line_ul05 = line_b03 + vcl::utils::Offsets_ll(1, -2);
assert(line_ul05.start.x() == 3);
assert(line_ul05.start.y() == 11);
assert(line_ul05.end.x() == 3);
assert(line_ul05.end.y() == 252);

line_ul05 = vcl::utils::Offsets_ll(1, -2) + line_ul05;
assert(line_ul05.start.x() == 4);
assert(line_ul05.start.y() == 9);
assert(line_ul05.end.x() == 4);
assert(line_ul05.end.y() == 250);


//std::array<float, 5> arr_5f{ 1.1f, 2.9f, -3.f, float(0x7fff), 4096.0f };
//line_b03{2, 13, 2, 254}
line_b03 -= vcl::vect::VectorT<long long, 3>(arr_5f);
assert(line_b03.start.x() == 1);
assert(line_b03.start.y() == 11);
assert(line_b03.end.x() == 1);
assert(line_b03.end.y() == 252);

//std::vector<long long> vect_4ll{ 1, 2, -3, 0x7fff };
line_b03 -= vect_4ll;
assert(line_b03.start.x() == 0);
assert(line_b03.start.y() == 9);
assert(line_b03.end.x() == 0);
assert(line_b03.end.y() == 250);

line_b03 -= arr_5f;
assert(line_b03.start.x() == 0);
assert(line_b03.start.y() == 6);
assert(line_b03.end.x() == 0);
assert(line_b03.end.y() == 247);

line_b03 -= std::make_pair(-5L, (short)-3);
assert(line_b03.start.x() == 5);
assert(line_b03.start.y() == 9);
assert(line_b03.end.x() == 5);
assert(line_b03.end.y() == 250);

line_b03 -= std::make_pair(3, -2);
assert(line_b03.start.x() == 2);
assert(line_b03.start.y() == 11);
assert(line_b03.end.x() == 2);
assert(line_b03.end.y() == 252);

vcl::graphitems::Line_b lb = line_b03 - vcl::vect::VectorT<long long, 3>(arr_5f);
assert(lb.start.x() == 1);
assert(lb.start.y() == 9);
assert(lb.end.x() == 1);
assert(lb.end.y() == 250);

//line_b03{2, 11, 2, 252}
lb = vcl::vect::VectorT<long long, 3>(16, 267) - line_b03;
assert(lb.start.x() == 14);
assert(lb.start.y() == 255);
assert(lb.end.x() == 14);
assert(lb.end.y() == 15);

//std::vector<long long> vect_4ll{ 1, 2, -3, 0x7fff };
lb = line_b03 - vect_4ll;
assert(lb.start.x() == 1);
assert(lb.start.y() == 9);
assert(lb.end.x() == 1);
assert(lb.end.y() == 250);

lb = std::vector<long long>{ 16, 267 } - line_b03;
assert(lb.start.x() == 14);
assert(lb.start.y() == 255);
assert(lb.end.x() == 14);
assert(lb.end.y() == 15);

//std::array<float, 5> arr_5f{ 1.1f, 2.9f, -3.f, float(0x7fff), 4096.0f };
//line_b03{2, 11, 2, 252}
lb = line_b03 - arr_5f;
assert(lb.start.x() == 0);
assert(lb.start.y() == 8);
assert(lb.end.x() == 0);
assert(lb.end.y() == 249);

lb = std::array<short, 3>{ 16, 267, -16 } - line_b03;
assert(lb.start.x() == 14);
assert(lb.start.y() == 255);
assert(lb.end.x() == 14);
assert(lb.end.y() == 15);


lb = line_b03 - std::make_pair(1, 2);
assert(lb.start.x() == 1);
assert(lb.start.y() == 9);
assert(lb.end.x() == 1);
assert(lb.end.y() == 250);

lb = std::make_pair(16.f, 267.f) - line_b03;
assert(lb.start.x() == 14);
assert(lb.start.y() == 255);
assert(lb.end.x() == 14);
assert(lb.end.y() == 15);


lb = line_b03 - vcl::utils::OffsetsT<short>(1, 2);
assert(lb.start.x() == 1);
assert(lb.start.y() == 9);
assert(lb.end.x() == 1);
assert(lb.end.y() == 250);

lb = vcl::utils::OffsetsT<float>(16.f, 267.f) - line_b03;
assert(lb.start.x() == 14);
assert(lb.start.y() == 255);
assert(lb.end.x() == 14);
assert(lb.end.y() == 15);


//line_b03{2, 11, 2, 252}
vcl::graphitems::Line_us lus(line_b03);
lus.move_at(10, 12);
assert(lus.start.x() == 10);
assert(lus.start.y() == 12);
assert(lus.end.x() == 10);
assert(lus.end.y() == 253);

lus.move_at(vcl::utils::Pos_s(-1, -1));
assert(lus.start.x() == 0);
assert(lus.start.y() == 0);
assert(lus.end.x() == 0);
assert(lus.end.y() == 241);

lus.move_at(vcl::utils::Pos_f(2, 11));
assert(lus.start.x() == 2);
assert(lus.start.y() == 11);
assert(lus.end.x() == 2);
assert(lus.end.y() == 252);

lus.move_at(vcl::vect::Vect3s(1, 2, 3));
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 1);
assert(lus.end.y() == 243);

lus.move_at(std::vector<int>{2, 11, 27});
assert(lus.start.x() == 2);
assert(lus.start.y() == 11);
assert(lus.end.x() == 2);
assert(lus.end.y() == 252);

lus.move_at(std::array<short, 3>{1, 2, 3});
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 1);
assert(lus.end.y() == 243);

lus.move_at(std::make_pair<unsigned int>(2, 11));
assert(lus.start.x() == 2);
assert(lus.start.y() == 11);
assert(lus.end.x() == 2);
assert(lus.end.y() == 252);


lus.start = vcl::utils::Pos_us(1, 2);
lus.end = vcl::utils::Pos_us(11, 22);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 11);
assert(lus.end.y() == 22);

lus.resize(2);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 12);
assert(lus.end.y() == 24);

lus.end = vcl::utils::Pos_us(1, 22);
lus.resize(2);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 1);
assert(lus.end.y() == 24);

lus.end = vcl::utils::Pos_us(11, 2);
lus.resize(2);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 13);
assert(lus.end.y() == 2);

lus.end = vcl::utils::Pos_us(11, 22);
lus.resize(2);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 12);
assert(lus.end.y() == 24);

lus.end = vcl::utils::Pos_us(11, 22);
lus.resize(-2.0f);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 10);
assert(lus.end.y() == 20);

lus.end = vcl::utils::Pos_us(11, 22);
lus += (unsigned short)4;
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 13);
assert(lus.end.y() == 26);

lus -= (unsigned short)4;
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 11);
assert(lus.end.y() == 22);

vcl::graphitems::Line_s ls = lus + 2.0;
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 12);
assert(ls.end.y() == 24);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 11);
assert(lus.end.y() == 22);

ls = -4 + lus;
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 9);
assert(ls.end.y() == 18);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 11);
assert(lus.end.y() == 22);

ls = lus - -3.9f;
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 13);
assert(ls.end.y() == 25);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 11);
assert(lus.end.y() == 22);


ls = lus;  // 1, 2, 11, 22
ls.scale(1.5);
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 16);
assert(ls.end.y() == 32);

ls = lus;  // 1, 2, 11, 22
ls.scale(0.67);
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 8);
assert(ls.end.y() == 15);

ls = lus;  // 1, 2, 11, 22
ls *= 1.5;
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 16);
assert(ls.end.y() == 32);

ls = lus * 0.667;
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 8);
assert(ls.end.y() == 15);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 11);
assert(lus.end.y() == 22);

ls = 1.5 * lus;
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 16);
assert(ls.end.y() == 32);
assert(lus.start.x() == 1);
assert(lus.start.y() == 2);
assert(lus.end.x() == 11);
assert(lus.end.y() == 22);

ls = lus;  // 1, 2, 11, 22
ls.scale_from_center(2.1);
assert(ls.start.x() == -9);
assert(ls.start.y() == -19);
assert(ls.end.x() == 12);
assert(ls.end.y() == 23);


ls = lus;  // 1, 2, 11, 22
ls.shrink(1.5f);
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 8);
assert(ls.end.y() == 15);

ls.shrink(0.67);
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 11);
assert(ls.end.y() == 21);

ls = lus;  // 1, 2, 11, 22
ls /= 1.5f;
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 8);
assert(ls.end.y() == 15);

ls = lus / 0.67;
assert(ls.start.x() == 1);
assert(ls.start.y() == 2);
assert(ls.end.x() == 16);
assert(ls.end.y() == 32);


ls = lus;  // 1, 2, 11, 22
ls.shrink_from_center(0.47619f);  // 1.0 / 2.1);
assert(ls.start.x() == -9);
assert(ls.start.y() == -19);
assert(ls.end.x() == 12);
assert(ls.end.y() == 23);








cout << "--- ALL TESTS PASSED ---" << endl << endl;
}