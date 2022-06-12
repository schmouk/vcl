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
/** \brief main for tests on class vcl::utils::PerfMeter. */

cout << "## utils.perfmeters / vcl::utils::PerfMeter testing application..." << endl;

vcl::utils::PerfMeter perf0;
std::this_thread::sleep_for(std::chrono::milliseconds(150));
assert( (vcl::utils::in_range_ii<double>(perf0.get_elapsed_ms(), 150.0, 167.0)) );
cout << perf0.get_elapsed_ms() << std::endl;

std::this_thread::sleep_for(std::chrono::milliseconds(150));
assert((vcl::utils::in_range_ii<double>(perf0.get_elapsed_ms(), 300, 300 + 33)));
cout << perf0.get_elapsed_ms() << std::endl;


perf0.start();
std::this_thread::sleep_for(std::chrono::milliseconds(127));
assert((vcl::utils::in_range_ii<double>(perf0.get_elapsed_ms(), 127, 127 + 17.0)));
cout << perf0.get_elapsed_ms() << std::endl;


cout << "--- ALL TESTS PASSED ---" << endl << endl;
