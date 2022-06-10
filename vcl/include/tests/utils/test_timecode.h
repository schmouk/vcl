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

cout << "## utils.timecode / vcl::utils::Timecode testing application..." << endl;

vcl::utils::Timecode<24> t0;
assert(string(t0) == "00:00:00:00"s);

vcl::utils::Timecode25fps ta25(62);
assert(string(ta25) == "00:01:02:00"s);

vcl::utils::Timecode25fps tb25(62.601);
assert(string(tb25) == "00:01:02:15"s);

tb25 += 12;
assert(string(tb25) == "00:01:03:02"s);

vcl::utils::Timecode30fps tc30(tb25 - 12);
assert(string(tc30) == "00:01:02:18"s);

t0 = tb25 - 12;
assert(string(t0) == "00:01:02:14"s);

vcl::utils::Timecode25fps td25 = tb25 - t0;
assert(string(td25) == "00:00:00:12"s);

assert(string(td25++) == "00:00:00:12"s);
assert(string(++td25) == "00:00:00:14"s);

assert(string(--td25) == "00:00:00:13"s);
assert(string(td25--) == "00:00:00:13"s);
assert(string(td25) == "00:00:00:12"s);

assert(td25 == tb25 - t0);
assert(td25 < tb25);
assert(tb25 > td25);
assert(tb25 != td25);

cout << "--- ALL TESTS PASSED ---" << endl << endl;
