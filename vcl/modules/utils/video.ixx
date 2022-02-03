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

#include <sstream>
#include <stdexcept>
#include <string>

export module utils.video;


//===========================================================================
namespace vcl {
    namespace utils {

        //===================================================================
        // Forward declaration
        export template<const unsigned short FPS> class Timecode;

        // Specializations
        export typedef Timecode<24> Timecode24fps; //!< 24 frames per second timecode (cinema)
        export typedef Timecode<25> Timecode25fps; //!< 25 frames per second timecode (TV - DVB)
        export typedef Timecode<30> Timecode30fps; //!< ~30 frames per second timecode (TV - ATSC/ISDB)


        //-----------------------------------------------------------------------
        /** \brief The class of timecodes.
        */
        template<const unsigned short FPS>
        class Timecode
        {
        public:

            typedef unsigned char CompT; //!< the internal type of timecode components

            CompT hh, mm, ss, ff; //!< the four components of every timecode HH:MM:SS:FF

            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor.
            */
            inline Timecode<FPS>()
                : hh(0), mm(0), ss(0), ff(0), m_error(false)
            {}

            /** \brief Constructor with a single value).
            */
            template<typename T>
            inline Timecode<FPS>(const T value)
                : hh(0), mm(0), ss(0), ff(0), m_error(false)
            {
                prvt_set(double(value));
                if (m_error)
                    throw std::invalid_argument("too big value for Timecode constructor argument");
            }

            /** \brief Constructor with four filling values).
            */
            inline Timecode<FPS>(const CompT hr, const CompT mn, const CompT sc, const CompT fr)
                : hh(hr), mm(mn), ss(sc), ff(fr), m_error(false)
            {
                if (m_error)
                    throw std::invalid_argument("invalid value for Timecode constructor arguments");
            }

            /** \brief Move constructor.
            */
            template<const unsigned short F>
            inline Timecode<FPS>(const Timecode<F>& other)
                : hh(0), mm(0), ss(0), ff(0), m_error(other.m_error)
            {
                if (m_error)
                    throw std::invalid_argument("invalid timecode value passed as Timecode constructor argument");
                else
                    prvt_set((double)other);
            }

            /** \brief Constructor from char*.
            */
            inline Timecode<FPS>(const char* tc_chr)
                : hh(0), mm(0), ss(0), ff(0), m_error(false)
            {
                prvt_set(std::string(tc_chr));
                if (m_error)
                    throw std::invalid_argument("invalid c_string content passed as Timecode constructor argument");
            }

            /** \brief Constructor from string.
            */
            inline Timecode<FPS>(const std::string& tc_str)
                : hh(0), mm(0), ss(0), ff(0), m_error(false)
            {
                prvt_set(tc_str);
                if (m_error)
                    throw std::invalid_argument("invalid string content passed as Timecode constructor argument");
            }

            //---   Cast operations   -------------------------------------------
            /** \brief long(): returns the frames count related to this timecode value.
            */
            inline operator long()
            {
                return long(FPS * (3600 * hh + 60 * mm + ss) + ff);
            }

            /** \brief const long(): returns the frames count related to this timecode value.
            */
            inline operator const long()
            {
                return (const long)(FPS * (3600 * hh + 60 * mm + ss) + ff);
            }

            /** \brief unsigned long(): returns the frames count related to this timecode value.
            */
            inline operator unsigned long()
            {
                return (unsigned long)(FPS * (3600 * hh + 60 * mm + ss) + ff);
            }

            /** \brief const unsigned long(): returns the frames count related to this timecode value.
            */
            inline operator const unsigned long()
            {
                return (const unsigned long)(FPS * (3600 * hh + 60 * mm + ss) + ff);
            }

            /** \brief float(): returns the time related to this timecode value, expressed in fractional seconds.
            */
            inline operator float()
            {
                return 3600.0f * hh + 60.0f * mm + (float)ss + (float)ff / (float)FPS;
            }

            /** \brief double(): returns the time related to this timecode value, expressed in fractional seconds.
            */
            inline operator double()
            {
                return 3600.0 * hh + 60.0 * mm + (double)ss + (double)ff / (double)FPS;
            }


        private:
            typedef vcl::utils::Timecode<FPS> MyType; //<! wrapper to this class naming.
            bool m_error; //!< error status of this timecode
            
            /** \brief Internally sets this timecode (double fractional seconds).
            */
            void prvt_set(const double fract_sec)
            {
                if (fract_sec <= 0)
                    hh = mm = ss = ff = CompT(0);
                else {
                    hh = CompT(fract_sec / 3600.0);
                    mm = CompT((unsigned long)(fract_sec / 60.0) % 60);
                    ss = CompT((unsigned long)(fract_sec) % 60);
                    ff = CompT(FPS * (fract_sec - (unsigned long)fract_sec));
                    if (hh > 99)
                        prvt_set_error();
                }
            }

            /** \brief Internally sets this timecode (const string&).
            */
            void prvt_set(const std::string& fract_sec)
            {
                std::stringstream sstr(fract_sec);
                try {
                    sstr >> hh >> ':' >> mm >> ':' >> ss >> ':' >> ff;
                    prvt_check();
                }
                catch (...) {
                    prvt_set_error();
                }
            }

            /** \brief Internally checks for the correctness of this timecode .
            */
            inline const bool prvt_check()
            {
                if (0 <= hh && hh <= 99 && 0 <= mm && mm < 60 && 0 <= ss && ss < 60 && 0 <= ff && ff < FPS)
                    prvt_clr_error();
                else
                    prvt_set_error();
            }

            /** \brief clears the internal error state  */
            inline void prvt_clr_error()
            {
                m_error = false;
            }

            /** \brief sets the internal error state to true */
            inline void prvt_set_error()
            {
                m_error = true;
            }

        };

    } // end of namespace vect
} // end of namespace vcl
