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
    cout << "## graphitems.rect / vcl::graphitems::RectT testing application..." << endl;

    vcl::graphitems::Rect rect_00;
    assert(rect_00.x == 0);
    assert(rect_00.y == 0);
    assert(rect_00.width == 0);
    assert(rect_00.height == 0);

    vcl::graphitems::Rect rect_01(rect_00);
    assert(rect_01.x == 0);
    assert(rect_01.y == 0);
    assert(rect_01.width == 0);
    assert(rect_01.height == 0);

    vcl::vect::Vect4i vect4_i01(2, 21, 1, 11);
    vcl::graphitems::Rect_i rect_i01(vect4_i01);
    assert(rect_i01.x == 2);
    assert(rect_i01.y == 1);
    assert(rect_i01.width == 21 - 2 + 1);
    assert(rect_i01.height == 11 - 1 + 1);

    std::array<short, 4> arr4_s01 = {3, 31, 11, 21};
    vcl::graphitems::Rect rect_i02(arr4_s01);
    assert(rect_i02.x == 3);
    assert(rect_i02.y == 11);
    assert(rect_i02.width == 31 - 3 + 1);
    assert(rect_i02.height == 21 - 11 + 1);

    std::vector<long> v4_i01 = { 3, 31, 11, 21 };
    vcl::graphitems::Rect rect_i03(v4_i01);
    assert(rect_i03.x == 3);
    assert(rect_i03.y == 11);
    assert(rect_i03.width == 31 - 3 + 1);
    assert(rect_i03.height == 21 - 11 + 1);

    vcl::graphitems::Rect_f rect_f01(0.1, 0.9, 0.15, 0.25);
    assert(rect_f01.x == 0.1f);
    assert(rect_f01.y == 0.15f);
    assert(rect_f01.width == 0.9f - 0.1f + 1.0f);
    assert(rect_f01.height == 0.25f - 0.15f + 1.0f);

    vcl::graphitems::Rect rect_i04(111, 22, vcl::utils::Dims_ui(80, 67));
    assert(rect_i04.x == 111);
    assert(rect_i04.y == 22);
    assert(rect_i04.right_x() == 190);
    assert(rect_i04.bottom_y() == 88);

    vcl::utils::Pos_s pos_s01(-1, 2);
    vcl::utils::Dims_ui dims_ui01(80, 67);
    vcl::graphitems::Rect rect_i05(pos_s01, dims_ui01);
    assert(rect_i05.x == -1);
    assert(rect_i05.y == 2);
    assert(rect_i05.right_x() == 78);
    assert(rect_i05.bottom_y() == 68);

    vcl::graphitems::Rect rect_s06(pos_s01, vcl::utils::Pos_s(80, 67));
    assert(rect_s06.x == -1);
    assert(rect_s06.y == 2);
    assert(rect_s06.right_x() == 80);
    assert(rect_s06.bottom_y() == 67);

    vcl::graphitems::Rect rect_s07(pos_s01, 81.0f, 68.0);
    assert(rect_s07.x == -1);
    assert(rect_s07.y == 2);
    assert(rect_s07.right_x() == 79);
    assert(rect_s07.bottom_y() == 69);

    vcl::graphitems::Rect_i rect_i08(std::make_pair((unsigned long)3, 4.0f), std::make_pair((short)20, (long long)10));
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 4);
    assert(rect_i08.right_x() == 22);
    assert(rect_i08.bottom_y() == 13);

    rect_i08 = rect_s07;
    assert(rect_i08.x == -1);
    assert(rect_i08.y == 2);
    assert(rect_i08.right_x() == 79);
    assert(rect_i08.bottom_y() == 69);

    rect_i08 = rect_i04;
    assert(rect_i08.x == 111);
    assert(rect_i08.y == 22);
    assert(rect_i08.right_x() == 190);
    assert(rect_i08.bottom_y() == 88);

    //vcl::vect::Vect4i vect4_i01(2, 21, 1, 11);
    rect_s07 = vect4_i01;
    assert(rect_s07.x == 2);
    assert(rect_s07.y == 21);
    assert(rect_s07.right_x() == 2);
    assert(rect_s07.bottom_y() == 31);

    std::vector<int> v5_i01 = { 3, 31, 11, 21, -127 };
    rect_s07 = v5_i01;
    assert(rect_s07.x == 3);
    assert(rect_s07.y == 31);
    assert(rect_s07.width == 11);
    assert(rect_s07.height == 21);

    //std::array<short, 4> arr4_s01 = {3, 31, 11, 21};
    rect_s07 = arr4_s01;
    assert(rect_s07.x == 3);
    assert(rect_s07.y == 31);
    assert(rect_s07.width == 11);
    assert(rect_s07.height == 21);

    rect_i08 = rect_s07;
    assert(rect_i08 == rect_s07);
    assert(rect_s07 == rect_i08);
    assert(rect_i08 == rect_i08);
    assert(rect_i04 != rect_i08);
    assert(rect_i08 != rect_i04);
    assert(rect_f01 != rect_s07);
    assert(rect_s07 != rect_f01);

    rect_s06.left_x(11ULL);
    rect_s06.right_x((unsigned char)111);
    rect_s06.top_y(22.0f);
    rect_s06.bottom_y(123.0);
    assert(rect_s06.left_x() == 11);
    assert(rect_s06.right_x() == 111);
    assert(rect_s06.top_y() == 22);
    assert(rect_s06.bottom_y() == 123);
    assert(rect_s06.x == 11);
    assert(rect_s06.y == 22);
    assert(rect_s06.width == 101);
    assert(rect_s06.height == 102);

    // vcl::utils::Pos_s pos_s01(-1, 2);
    rect_i08.top_left(pos_s01);
    assert(rect_i08.x == -1);
    assert(rect_i08.y == 2);
    assert(rect_i08.top_left() == pos_s01);

    pos_s01 += 30;
    rect_i08.bottom_right(pos_s01);
    assert(rect_i08.width == 31);
    assert(rect_i08.height == 31);
    assert(rect_i08.bottom_right() == pos_s01);

    assert(rect_i08.center().x() == 14);
    assert(rect_i08.center().y() == 17);
    rect_i08.center(vcl::utils::PosT<char>(19, 33));
    assert(rect_i08.center().x() == 19);
    assert(rect_i08.center().y() == 33);
    assert(rect_i08.x == 4);
    assert(rect_i08.y == 18);
    assert(rect_i08.width == 31);
    assert(rect_i08.height == 31);

    // vcl::utils::Dims_ui dims_ui01(80, 67);
    rect_s06.dims(dims_ui01);
    assert(rect_s06.dims().width() == 80);
    assert(rect_s06.dims().height() == 67);
    assert(rect_s06.dims() == dims_ui01);
    assert(!(rect_s06.dims() != dims_ui01));
    assert(rect_s06.left_x() == 11);
    assert(rect_s06.right_x() == 90);
    assert(rect_s06.top_y() == 22);
    assert(rect_s06.bottom_y() == 88);
    assert(rect_s06.x == 11);
    assert(rect_s06.y == 22);
    assert(rect_s06.width == 80);
    assert(rect_s06.height == 67);

    assert(int(rect_s06) == int(80 * 67));
    assert(unsigned short(rect_s06) == (unsigned short)(80 * 67));
    assert(float(rect_s06) == float(80 * 67));

    assert(vcl::utils::PosT<long>(rect_s06) == rect_s06.top_left());
    assert(vcl::graphitems::Rect::MyPosType(rect_i08).x() == rect_i08.x);
    assert(vcl::graphitems::Rect::MyPosType(rect_i08).y() == rect_i08.y);

    assert(vcl::utils::DimsT<long>(rect_s06) == rect_s06.dims());
    assert(vcl::graphitems::Rect::MyDimsType(rect_i08).width() == rect_i08.width);
    assert(vcl::graphitems::Rect::MyDimsType(rect_i08).height() == rect_i08.height);

    // vcl::vect::Vect4i vect4_i01(2, 21, 1, 11);
    rect_s07 = vect4_i01;
    assert(vcl::vect::Vect4s(rect_s07) == vect4_i01);
    assert(vcl::vect::Vect4i(rect_s07) == vect4_i01);

    // std::vector<int> v4_i01 = { 3, 31, 11, 21 };
    rect_i08 = v4_i01;
    std::vector<long> vi = (std::vector<long>)rect_i08;
    assert(vi == v4_i01);
    assert(std::vector<long>(rect_i08) == v4_i01);

    // std::array<short, 4> arr4_s01 = {3, 31, 11, 21};
    rect_s06 = arr4_s01;
    assert((std::array<short, 4>)rect_s06 == arr4_s01);

    rect_s06.crop(0, 1, 2, 3);
    assert(rect_s06.x == 3+0);
    assert(rect_s06.y == 31 + 2);
    assert(rect_s06.width == 11 - 1);
    assert(rect_s06.height == 21 - 2 - 3);

    rect_s06 = arr4_s01;
    rect_s06.crop(4, 5);
    assert(rect_s06.x == 3 + 4);
    assert(rect_s06.y == 31 + 5);
    assert(rect_s06.width == 11 - 4 - 4);
    assert(rect_s06.height == 21 - 5 - 5);

    rect_s06 = arr4_s01;
    rect_s06.crop(3);
    assert(rect_s06.x == 3 + 3);
    assert(rect_s06.y == 31 + 3);
    assert(rect_s06.width == 11 - 3 - 3);
    assert(rect_s06.height == 21 - 3 - 3);

    // std::array<short, 4> arr4_s01 = {3, 31, 11, 21};
    rect_s06 = arr4_s01;
    rect_s06.move(1.8, 3ULL);
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 + 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06.move(vcl::utils::OffsetsT<float>(1.8, -3.7f));
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 - 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06.move(vcl::vect::Vect2f(1.8, -3.7f));
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 - 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    // std::vector<int> v5_i01 = { 3, 31, 11, 21, -127 };
    rect_s06 = arr4_s01;
    rect_s06.move(v5_i01);
    assert(rect_s06.x == 3 + 3);
    assert(rect_s06.y == 31 + 31);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06.move(arr4_s01);
    assert(rect_s06.x == 3 + 3);
    assert(rect_s06.y == 31 + 31);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06.move(std::make_pair(1.8, -3.7f));
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 - 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06 += vcl::utils::OffsetsT<float>(1.8, -3.7f);
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 - 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06 += vcl::vect::Vect2f(1.8, -3.7f);
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 - 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    // std::vector<int> v5_i01 = { 3, 31, 11, 21, -127 };
    rect_s06 = arr4_s01;
    rect_s06 += v5_i01;
    assert(rect_s06.x == 3 + 3);
    assert(rect_s06.y == 31 + 31);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06 += arr4_s01;
    assert(rect_s06.x == 3 + 3);
    assert(rect_s06.y == 31 + 31);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06 += std::make_pair(1.8, -3.7f);
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 - 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    /*******************/

    rect_s06 = arr4_s01;
    vcl::graphitems::Rect rect_s10(rect_s06 + vcl::utils::OffsetsT<float>(1.8, -3.7f));
    assert(rect_s10.x == 3 + 1);
    assert(rect_s10.y == 31 - 3);
    assert(rect_s10.width == 11);
    assert(rect_s10.height == 21);

    rect_s06 = arr4_s01;
    rect_s06 = rect_s06 + vcl::vect::Vect2f(1.8, -3.7f);
    rect_s07 = rect_s06;
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 - 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    // std::vector<int> v5_i01 = { 3, 31, 11, 21, -127 };
    rect_s06 = arr4_s01;
    rect_s06 = rect_s06 + v5_i01;
    assert(rect_s06.x == 3 + 3);
    assert(rect_s06.y == 31 + 31);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06 = rect_s06 + arr4_s01;
    assert(rect_s06.x == 3 + 3);
    assert(rect_s06.y == 31 + 31);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06 = rect_s06 + std::make_pair(1.8, -3.7f);
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 - 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    /*******************/

    rect_s06 = arr4_s01;
    vcl::graphitems::Rect rect_s11(vcl::utils::OffsetsT<float>(1.8, -3.7f) + rect_s06);
    assert(rect_s11.x == 3 + 1);
    assert(rect_s11.y == 31 - 3);
    assert(rect_s11.width == 11);
    assert(rect_s11.height == 21);

    rect_s06 = arr4_s01;
    rect_s06 = vcl::vect::Vect2f(1.8, -3.7f) + rect_s06;
    rect_s07 = rect_s06;
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 - 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    // std::vector<int> v5_i01 = { 3, 31, 11, 21, -127 };
    rect_s06 = arr4_s01;
    rect_s06 = v5_i01 + rect_s06;
    assert(rect_s06.x == 3 + 3);
    assert(rect_s06.y == 31 + 31);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06 = arr4_s01 + rect_s06;
    assert(rect_s06.x == 3 + 3);
    assert(rect_s06.y == 31 + 31);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06 = arr4_s01;
    rect_s06 = std::make_pair(1.8, -3.7f) + rect_s06;
    assert(rect_s06.x == 3 + 1);
    assert(rect_s06.y == 31 - 3);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06.move_at(3.67f, 10ULL);
    assert(rect_s06.x == 3);
    assert(rect_s06.y == 10);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    vcl::utils::PosT<char> pos_c01(19, 33);
    rect_s06.move_at(pos_c01);
    assert(rect_s06.x == 19);
    assert(rect_s06.y == 33);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06.move_at(vcl::vect::Vect3i(1, 2, 3));
    assert(rect_s06.x == 1);
    assert(rect_s06.y == 2);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    // std::vector<int> v5_i01 = { 3, 31, 11, 21, -127 };
    rect_s06.move_at(v5_i01);
    assert(rect_s06.x == 3);
    assert(rect_s06.y == 31);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    std::array<int, 3> arr3_i01{ 15, 17, 19 };
    rect_s06.move_at(arr3_i01);
    assert(rect_s06.x == 15);
    assert(rect_s06.y == 17);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    rect_s06.move_at(std::make_pair((unsigned long)3, 4.95f));
    assert(rect_s06.x == 3);
    assert(rect_s06.y == 4);
    assert(rect_s06.width == 11);
    assert(rect_s06.height == 21);

    // std::vector<int> v4_i01 = { 3, 31, 11, 21 };
    rect_i08 = v4_i01;
    rect_i08.resize(127);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 138);
    assert(rect_i08.height == 148);

    rect_i08.resize(-5.2f, -10LL);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 132);
    assert(rect_i08.height == 138);

    // vcl::utils::Dims_ui dims_ui01(80, 67);
    rect_i08.resize(dims_ui01);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 212);
    assert(rect_i08.height == 205);

    rect_i08.resize(vcl::vect::Vect2d(-100.1, -200.95));
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 111);
    assert(rect_i08.height == 4);

    //std::vector<int> v5_i01 = { 3, 31, 11, 21, -127 };
    rect_i08.resize(v5_i01);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 114);
    assert(rect_i08.height == 35);

    //std::array<int, 3> arr3_i01{ 15, 17, 19 };
    rect_i08.resize(arr3_i01);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 129);
    assert(rect_i08.height == 52);

    rect_i08.resize(std::make_pair(-3LL, -4.95f));
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 126);
    assert(rect_i08.height == 47);

    rect_i08.scale(0.5f);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 63);
    assert(rect_i08.height == 23);

    rect_i08.scale(0.41f, 2ULL);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 25);
    assert(rect_i08.height == 46);

    rect_i08.scale(vcl::vect::Vect3f(2.0, 1.1, 0.33f));
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 50);
    assert(rect_i08.height == 50);

    //std::vector<int> v5_i01 = { 3, 31, 11, 21, -127 };
    rect_i08.scale(v5_i01);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 50*3);
    assert(rect_i08.height == 50*31);

    std::array<double, 3> arr_d01{ 1.0 / 3.0, 1.0 / 31.0, 0.2 };
    rect_i08.scale(arr_d01);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 50);
    assert(rect_i08.height == 50);

    rect_i08.scale(std::make_pair(3LL, 4.95f));
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 50*3);
    assert(rect_i08.height == int(50*4.95f));

    rect_i08 *= 0.2;
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 30);
    assert(rect_i08.height == 49);  // int(52 * 4.95f) / 5);

    rect_i08 *= vcl::vect::Vect3f(2.0, 1.1, 0.33f);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 60);
    assert(rect_i08.height == 53);

    rect_i08.scale(v5_i01);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 60 * 3);
    assert(rect_i08.height == 53 * 31);

    rect_i08.scale(arr_d01);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 60);
    assert(rect_i08.height == 53);

    rect_i08.scale(std::make_pair(3LL, 4.95f));
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 60 * 3);
    assert(rect_i08.height == int(53 * 4.95f));

    rect_i08.dims(156, 257);
    vcl::graphitems::Rect_i rect_i09 = rect_i08 * 0.2;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 31);
    assert(rect_i09.height == 51);

    rect_i09 = 0.2 * rect_i08;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 31);
    assert(rect_i09.height == 51);
    assert(rect_i08.x == 3);
    assert(rect_i08.y == 31);
    assert(rect_i08.width == 156);
    assert(rect_i08.height == 257);

    //std::vector<int> v5_i01 = { 3, 31, 11, 21, -127 };
    rect_i09 = rect_i09 * v5_i01;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 31 * 3);
    assert(rect_i09.height == 51 * 31);

    rect_i09.dims(31, 51);
    rect_i09 = v5_i01 * rect_i09;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 31 * 3);
    assert(rect_i09.height == 51 * 31);

    // std::vector<int> v4_i01 = { 3, 31, 11, 21 };
    rect_i09.dims(31, 51);
    rect_i09 = rect_i09 * v4_i01;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 31 * 3);
    assert(rect_i09.height == 51 * 31);

    rect_i09.dims(31, 51);
    rect_i09 = v4_i01 * rect_i09;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 31 * 3);
    assert(rect_i09.height == 51 * 31);

    //std::array<int, 3> arr3_i01{ 15, 17, 19 };
    rect_i09.dims(31, 51);
    rect_i09 = rect_i09 * arr3_i01;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 31 * 15);
    assert(rect_i09.height == 51 * 17);

    rect_i09.dims(31, 51);
    rect_i09 = arr3_i01 * rect_i09;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 31 * 15);
    assert(rect_i09.height == 51 * 17);

    auto pair_01 = std::make_pair(3LL, 4.95f);
    rect_i09.dims(31, 51);
    rect_i09 = rect_i09 * pair_01;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 31 * 3);
    assert(rect_i09.height == int(51 * 4.95f));

    rect_i09.dims(31, 51);
    rect_i09 = pair_01 * rect_i09;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 31 * 3);
    assert(rect_i09.height == int(51 * 4.95f));

    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09.scale_from_center(1.1);
    assert(rect_i09.x == -4);
    assert(rect_i09.y == 19);
    assert(rect_i09.width == 171);
    assert(rect_i09.height == 282);

    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09.scale_from_center(0.9, 0.6f);
    assert(rect_i09.x == 11);
    assert(rect_i09.y == 82);
    assert(rect_i09.width == 140);
    assert(rect_i09.height == 154);

    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09.shrink(3ULL);
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 52);
    assert(rect_i09.height == 85);

    rect_i09.shrink(0.5, (unsigned char)2);
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 104);
    assert(rect_i09.height == 42);

    rect_i09.shrink(vcl::vect::Vect3f(1.1, 0.9, 3.45));
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 94);
    assert(rect_i09.height == 46);

    std::vector<float> vect = { 1.1f, 0.9f, 3.45f };
    rect_i09.shrink(vect);
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 85);
    assert(rect_i09.height == 51);

    std::array<double, 4> arr = { 1.1, 0.9, 3.45, 0.001 };
    rect_i09.shrink(arr);
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 77);
    assert(rect_i09.height == 56);

    // auto pair_01 = std::make_pair(3LL, 4.95f);
    rect_i09.shrink(pair_01);
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 25);
    assert(rect_i09.height == 11);

    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09 /= 3ULL;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 52);
    assert(rect_i09.height == 85);

    rect_i09.shrink(0.5, (unsigned char)2);
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 104);
    assert(rect_i09.height == 42);

    rect_i09.dims(104, 42);
    rect_i09 /= vcl::vect::Vect3f(1.1, 0.9, 3.45);
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 94);
    assert(rect_i09.height == 46);

    rect_i09 /= vect;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 85);
    assert(rect_i09.height == 51);

    rect_i09 /= arr;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 77);
    assert(rect_i09.height == 56);

    rect_i09 /= pair_01;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 25);
    assert(rect_i09.height == 11);

    vcl::graphitems::Rect rect_s12( 3, 158, 31, 287 );
    rect_i09 = rect_s12 / 3ULL;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 52);
    assert(rect_i09.height == 85);

    rect_i09.dims(104, 42);

    rect_s12.dims(104, 42);
    rect_i09 = rect_s12 / vcl::vect::Vect3f(1.1, 0.9, 3.45);
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 94);
    assert(rect_i09.height == 46);

    rect_s12 = rect_i09;
    rect_i09 = rect_s12 / vect;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 85);
    assert(rect_i09.height == 51);

    rect_s12 = rect_i09;
    rect_i09 = rect_s12 / arr;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 77);
    assert(rect_i09.height == 56);

    rect_s12 = rect_i09;
    rect_i09 = rect_s12 / pair_01;
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 31);
    assert(rect_i09.width == 25);
    assert(rect_i09.height == 11);

    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09.shrink_from_center(1.1);
    assert(rect_i09.x == 10);
    assert(rect_i09.y == 43);
    assert(rect_i09.width == 141);
    assert(rect_i09.height == 233);

    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09.shrink_from_center(1.1, 2UL);
    assert(rect_i09.x == 10);
    assert(rect_i09.y == 95);
    assert(rect_i09.width == 141);
    assert(rect_i09.height == 128);

    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09.inset(5);
    assert(rect_i09.x == 8);
    assert(rect_i09.y == 36);
    assert(rect_i09.width == 146);
    assert(rect_i09.height == 247);

    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09.inset(6ULL, 11.1);
    assert(rect_i09.x == 9);
    assert(rect_i09.y == 42);
    assert(rect_i09.width == 144);
    assert(rect_i09.height == 235);

    rect_i09.inset(vcl::utils::DimsT<short>(7, 13.3));
    assert(rect_i09.x == 16);
    assert(rect_i09.y == 55);
    assert(rect_i09.width == 130);
    assert(rect_i09.height == 209);

    rect_i09.inset(vcl::utils::OffsetsT<short>(-7, -13.3));
    assert(rect_i09.x == 9);
    assert(rect_i09.y == 42);
    assert(rect_i09.width == 144);
    assert(rect_i09.height == 235);

    // std::vector<int> v4_i01 = { 3, 31, 11, 21 };
    rect_i09.inset(v4_i01);
    assert(rect_i09.x == 12);
    assert(rect_i09.y == 73);
    assert(rect_i09.width == 138);
    assert(rect_i09.height == 173);

    //std::array<int, 3> arr3_i01{ 15, 17, 19 };
    rect_i09.inset(arr3_i01);
    assert(rect_i09.x == 27);
    assert(rect_i09.y == 90);
    assert(rect_i09.width == 108);
    assert(rect_i09.height == 139);

    rect_i09.inset(std::make_pair((short)-4, 2.9));
    assert(rect_i09.x == 23);
    assert(rect_i09.y == 92);
    assert(rect_i09.width == 116);
    assert(rect_i09.height == 135);


    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09.outset(5UL);
    assert(rect_i09.x == -2);
    assert(rect_i09.y == 26);
    assert(rect_i09.width == 166);
    assert(rect_i09.height == 267);

    rect_i09.outset(-5.0, (short)-6);
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 32);
    assert(rect_i09.width == 156);
    assert(rect_i09.height == 255);

    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09.outset(vcl::utils::Dims(5));
    assert(rect_i09.x == -2);
    assert(rect_i09.y == 26);
    assert(rect_i09.width == 166);
    assert(rect_i09.height == 267);

    rect_i09.outset(vcl::vect::Vect2s(short(-5), short(-6)));
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 32);
    assert(rect_i09.width == 156);
    assert(rect_i09.height == 255);

    rect_i09 = rect_i08; // x=3, y=31, width=156, height=257
    rect_i09.outset(std::vector<unsigned long long>{5});
    assert(rect_i09.x == -2);
    assert(rect_i09.y == 26);
    assert(rect_i09.width == 166);
    assert(rect_i09.height == 267);

    std::array<char, 2> arr_c{ -5, -6 };
    rect_i09.outset(arr_c);
    assert(rect_i09.x == 3);
    assert(rect_i09.y == 32);
    assert(rect_i09.width == 156);
    assert(rect_i09.height == 255);

    rect_i09.outset(std::make_pair(5, 6.15));
    assert(rect_i09.x == -2);
    assert(rect_i09.y == 26);
    assert(rect_i09.width == 166);
    assert(rect_i09.height == 267);

    assert(rect_i09.contains(0.0, 28ULL));
    assert(rect_i09.contains(163, 240));
    assert(!rect_i09.contains(164, 240));
    assert(!rect_i09.contains(163, 293));
    assert(!rect_i09.contains(-3, 26));
    assert(!rect_i09.contains(-2, 25));
    assert(rect_i09.contains(-2, 26));

    assert(rect_i09.contains(vcl::utils::Pos_b(4, 26)));
    assert(!rect_i09.contains(vcl::utils::Pos_s(-3, 26)));
    assert(rect_i09.contains(vcl::vect::Vect2b(4, 26)));
    assert(!rect_i09.contains(vcl::vect::Vect2s(-3, 26)));
    assert(rect_i09.contains(std::vector<short>{4, 26, -1}));
    assert(!rect_i09.contains(std::vector<short>{-3, 26, 4, 56}));
    assert(rect_i09.contains(std::array<int, 3>{4, 26, -1}));
    assert(!rect_i09.contains(std::array<long long, 4>{-3, 26, 4, 56}));
    assert(rect_i09.contains(std::make_pair((unsigned char)4, 26LL)));
    assert(!rect_i09.contains(vcl::vect::Vect2s((short)-3, 26UL)));

    rect_s10 = rect_i09 * 0.8;
    assert(rect_i09.contains(rect_s10));
    assert(rect_i09 <= rect_i09);
    assert(!(rect_i09 < rect_i09));
    assert(rect_s10 <= rect_i09);
    assert(rect_s10 < rect_i09);
    assert(rect_i09 >= rect_i09);
    assert(!(rect_i09 > rect_i09));
    assert(rect_i09 >= rect_s10);
    assert(rect_i09 > rect_s10);

    assert(!rect_s10.contains(rect_i09));
    assert(rect_i09.does_embed(rect_s10));
    assert(!rect_s10.does_embed(rect_i09));
    assert(rect_i09.does_intersect(rect_s10));
    assert(rect_s10.does_intersect(rect_i09));

    rect_s10.move(1000, 1000);
    assert(!rect_i09.does_intersect(rect_s10));
    assert(!rect_s10.does_intersect(rect_i09));
    rect_s10.move(-1000, -1000);
    assert(rect_i09.does_intersect(rect_s10));
    assert(rect_s10.does_intersect(rect_i09));

    rect_i09.move_at(10, 11);
    rect_i09.dims(30, 20);
    rect_s10.top_left(6, 5);
    rect_s10.bottom_right(32, 16);
    rect_i08 = rect_i09.intersection_rect(rect_s10);
    assert(rect_i08.x == 10);
    assert(rect_i08.y == 11);
    assert(rect_i08.width == 23);
    assert(rect_i08.height == 6);

    assert(rect_i09.intersection_rect(rect_s10) == rect_s10.intersection_rect(rect_i09));
    
    rect_i09.move(100, 1000);
    rect_i08 = rect_i09.intersection_rect(rect_s10);
    assert(rect_i08.x == 0);
    assert(rect_i08.y == 0);
    assert(rect_i08.width == 0);
    assert(rect_i08.height == 0);

    rect_i09.move_at(10, 11);
    rect_i09.dims(30, 20);
    rect_s10.top_left(6, 5);
    rect_s10.bottom_right(32, 16);
    rect_i08 = rect_i09 & rect_s10;
    assert(rect_i08.x == 10);
    assert(rect_i08.y == 11);
    assert(rect_i08.width == 23);
    assert(rect_i08.height == 6);

    rect_i08 = rect_i09 + rect_s10;
    assert(rect_i08.x == 6);
    assert(rect_i08.y == 5);
    assert(rect_i08.width == 34);
    assert(rect_i08.height == 26);

    rect_i08 = rect_i09 | rect_s10;
    assert(rect_i08.x == 6);
    assert(rect_i08.y == 5);
    assert(rect_i08.width == 34);
    assert(rect_i08.height == 26);

    rect_i09.x += 30;

    rect_i08 = rect_i09 + rect_s10;
    assert(rect_i08.x == 6);
    assert(rect_i08.y == 5);
    assert(rect_i08.width == 64);
    assert(rect_i08.height == 26);

    rect_i08 = rect_i09 | rect_s10;
    assert(rect_i08.x == 40);
    assert(rect_i08.y == 11);
    assert(rect_i08.width == 30);
    assert(rect_i08.height == 20);
    cout << "--- ALL TESTS PASSED ---" << endl << endl;
}