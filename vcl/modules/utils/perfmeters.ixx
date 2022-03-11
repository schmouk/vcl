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
module;

#include <chrono>
#include <format>
#include <sstream>
#include <string>

export module utils.perfmeters;


//===========================================================================
namespace vcl::utils {

    //===================================================================
    /** the class of time performance evaluators.
    */
    export class PerfMeter
    {
    public:
        /** \brief Empty constructor.
        */
        inline PerfMeter()
            : prvt_start(std::chrono::steady_clock::now())
        {}

        /** \brief Copy constructor.
        */
        inline PerfMeter(const PerfMeter& other)
            : prvt_start(other.prvt_start)
        {}

        /** \brief Move constructor.
        */
        inline PerfMeter(PerfMeter&& other)
            : prvt_start(other.prvt_start)
        {}

        /** \brief internally sets the starting point.
        */
        inline void start()
        {
            prvt_start = std::chrono::steady_clock::now();
        }

        /** \brief gets measured duration in fractional milliseconds.
        */
        inline const double get_elapsed_ms()
        {
            return get_elapsed_s() * 1000.0;
        }

        /** \brief gets measured duration in fractional seconds.
        */
        inline const double get_elapsed_s()
        {
            return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - prvt_start).count();
        }

    private:
        std::chrono::steady_clock::time_point prvt_start;

    };

}
