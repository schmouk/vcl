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

#include <array>
#include <cassert>
#include <chrono>
#include <format>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;


import vectors.vector;
import vectors.vect2;
import vectors.vect3;
import vectors.vect4;
import vectors.clipvect2;
import vectors.clipvect3;
import vectors.clipvect4;
import vectors.clipvector;
import utils.pos;
import utils.dims;
import utils.offsets;
import utils.ranges;
import utils.timecodes;
import utils.perfmeters;
import graphitems.rect;
import graphitems.line;

//#include "tests/test_opencv.h"

/** \brief main for tests on modules. */
int main()
{
    std::cout << ">>>>>>>>>>   TESTS SEQUENCE STARTED   <<<<<<<<<<\n\n\n";

    vcl::utils::PerfMeter perfm;

#include "tests/vectors/test_vect2.h"
#include "tests/vectors/test_vect3.h"
#include "tests/vectors/test_vect4.h"
#include "tests/vectors/test_clipvect2.h"
#include "tests/vectors/test_clipvect3.h"
#include "tests/vectors/test_clipvect4.h"
#include "tests/vectors/test_clipvector.h"

#include "tests/utils/test_pos.h"
#include "tests/utils/test_dims.h"
#include "tests/utils/test_offsets.h"
#include "tests/utils/test_timecode.h"
#include "tests/utils/test_perfmeters.h"

#include "tests/graphitems/test_rect.h"

#include "tests/graphitems/test_line.h"

    std::string processing_time = std::format("{:.1f} ms\n\n", perfm.get_elapsed_ms());

    std::cout << "\n  >>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<";
    std::cout << "\n  >>>>>>>>>>   Everything went FINE   <<<<<<<<<<";
    std::cout << "\n  >>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cout << "Processing time: " << processing_time;

    return 0;
}