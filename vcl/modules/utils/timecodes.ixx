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

#include <format>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

export module utils.timecodes;

import utils.ranges;


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

        
        // not to be used out of this module scope
        std::map<std::string, std::string> _TC_ERR_TXT = {
            {"TC001", "too big value for Timecode constructor argument"},
            {"TC002", "invalid value for Timecode constructor arguments"},
            {"TC003", "invalid timecode value passed as Timecode constructor argument"},
            {"TC004", "invalid c_string content passed as Timecode constructor argument"}
        };


        //-----------------------------------------------------------------------
        /** \brief The class of timecodes.
        */
        template<const unsigned short FPS>
        class Timecode
        {
        public:

            typedef Timecode<FPS>   MyType;     //<! wrapper to this class naming.
            typedef unsigned char   CompT;      //!< the internal type of timecode components.
            typedef float           FrameTime;  //!< the internal type for fractional seconds time related to timecodes.
            typedef unsigned long   FrameIndex; //!< the internal type for frames index.

            CompT hh, mm, ss, ff;        //!< the four components of every timecode HH:MM:SS:FF.
            bool b_error;                //!< error status of this timecode.


            //---   constructors   ----------------------------------------------
            /** \brief Empty constructor.
            */
            inline Timecode<FPS>()
                : hh(0), mm(0), ss(0), ff(0), b_error(false)
            {}

            /** \brief Constructor with a single value.
            */
            template<typename T>
            inline Timecode<FPS>(const T value)
                : hh(0), mm(0), ss(0), ff(0), b_error(false)
            {
                prvt_set(Timecode::FrameTime(value));
                if (b_error)
                    throw std::invalid_argument(_TC_ERR_TXT["TC001"]);
            }

            /** \brief Constructor with four filling values.
            */
            inline Timecode<FPS>(const CompT hr, const CompT mn, const CompT sc, const CompT fr)
                : hh(hr), mm(mn), ss(sc), ff(fr), b_error(false)
            {
                if (b_error)
                    throw std::invalid_argument(_TC_ERR_TXT["TC002"]);
            }

            /** \brief Copy constructor.
            */
            template<const unsigned short F>
            inline Timecode<FPS>(const vcl::utils::Timecode<F>& other)
                : hh(0), mm(0), ss(0), ff(0), b_error(other.b_error)
            {
                if (b_error)
                    throw std::invalid_argument(_TC_ERR_TXT["TC003"]);
                else
                    prvt_set(other);
            }

            /** \brief Move constructor.
            */
            template<const unsigned short F>
            inline Timecode<FPS>(vcl::utils::Timecode<F>&& other)
                : hh(0), mm(0), ss(0), ff(0), b_error(other.b_error)
            {
                if (b_error)
                    throw std::invalid_argument(_TC_ERR_TXT["TC003"]);
                else
                    prvt_set(other);
            }

            /** \brief Constructor from char*.
            */
            inline Timecode<FPS>(const char* tc_chr)
                : hh(0), mm(0), ss(0), ff(0), b_error(false)
            {
                prvt_set(std::string(tc_chr));
                if (b_error)
                    throw std::invalid_argument(_TC_ERR_TXT["TC004"]);
            }

            /** \brief Constructor from string.
            */
            inline Timecode<FPS>(const std::string& tc_str)
                : hh(0), mm(0), ss(0), ff(0), b_error(false)
            {
                prvt_set(tc_str);
                if (b_error)
                    throw std::invalid_argument(_TC_ERR_TXT["TC003"]);
            }


            //---   Cast operations   -------------------------------------------
            /** \brief long(): returns the frames count related to this timecode value.
            /** Returns the time (i.e. fractional seconds) related to this timecode.
            */
            const Timecode::FrameTime frame_s() const
            {
                constexpr Timecode::FrameTime eps = Timecode::FrameTime(1e-5f);
                return Timecode::FrameTime(3600.0f * hh + 60.0f * mm + (float)ss + (float)ff / (float)FPS + kEPS);
            }

            /** Returns the frame index related to this timecode.
            */
            const Timecode::FrameIndex frame_index()  const
            {
                return (const Timecode::FrameIndex)(FPS * (3600 * hh + 60 * mm + ss) + ff);
            }

            /** \brief operator string&
            */
            inline operator std::string()
            {
                return std::format("{:02d}:{:02d}:{:02d}:{:02d}", hh, mm, ss, ff);
            }


            //---   Increment operator ++   ---------------------------------
            /** \brief Pre-increment operator.
            */
            inline MyType& operator++()
            {
                *this += 1;
                return *this;
            }

            /** \brief Post-increment operator.
            */
            MyType operator++(int)
            {
                *this += 1;
                return *this - 1;
            }


            //---   Decrement operator --   ---------------------------------
            /** \brief Pre-decrement operator.
            */
            inline MyType& operator--()
            {
                *this -= 1;
                return *this;
            }

            /** \brief Post-decrement operator.
            */
            MyType operator--(int)
            {
                *this -= 1;
                return *this + 1;
            }


            //---   Operator +=   -------------------------------------------
            /* \brief operator += (const &)
            */
            template<const unsigned short F>
            MyType& operator +=(const vcl::utils::Timecode<F>& rhs)
            {
                prvt_set(this->frame_s() + rhs.frame_s());
                return *this;
            }

            /* \brief operator += (const char) on frames count
            */
            MyType& operator += (const char offset)
            {
                prvt_set(this->frame_index() + FrameIndex(offset));
                return *this;
            }

            /* \brief operator += (const unsigned char) on frames count
            */
            MyType& operator += (const unsigned char offset)
            {
                prvt_set(this->frame_index() + FrameIndex(offset));
                return *this;
            }

            /* \brief operator += (const short) on frames count
            */
            MyType& operator += (const short offset)
            {
                prvt_set(this->frame_index() + FrameIndex(offset));
                return *this;
            }

            /* \brief operator += (const unsigned short) on frames count
            */
            MyType& operator += (const unsigned short offset)
            {
                prvt_set(this->frame_index() + FrameIndex(offset));
                return *this;
            }

            /* \brief operator += (const int) on frames count
            */
            MyType& operator += (const int offset)
            {
                prvt_set(this->frame_index() + FrameIndex(offset));
                return *this;
            }

            /* \brief operator += (const unsigned int) on frames count
            */
            MyType& operator += (const unsigned int offset)
            {
                prvt_set(this->frame_index() + FrameIndex(offset));
                return *this;
            }

            /* \brief operator += (const long) on frames count
            */
            MyType& operator += (const long offset)
            {
                prvt_set(this->frame_index() + FrameIndex(offset));
                return *this;
            }

            /* \brief operator += (const unsigned long) on frames count
            */
            MyType& operator += (const unsigned long offset)
            {
                prvt_set(this->frame_index() + FrameIndex(offset));
                return *this;
            }

            /* \brief operator += (const long long) on frames count
            */
            MyType& operator += (const long long offset)
            {
                prvt_set(this->frame_index() + FrameIndex(offset));
                return *this;
            }

            /* \brief operator += (const unsigned long long) on frames count
            */
            MyType& operator += (const unsigned long long offset)
            {
                prvt_set(this->frame_index() + FrameIndex(offset));
                return *this;
            }

            /* \brief operator += (const float) on frames times
            */
            MyType& operator += (const float offset)
            {
                prvt_set(this->frame_s() + FrameTime(offset));
                return *this;
            }

            /* \brief operator += (const double) on frames times
            */
            MyType& operator += (const double offset)
            {
                prvt_set(this->frame_s() + FrameTime(offset));
                return *this;
            }


            //---   Operator +   --------------------------------------------
            /* \brief operator + (const &)
            */
            template<const unsigned short F>
            friend inline MyType operator+ (MyType lhs, const vcl::utils::Timecode<F>& rhs)
            {
                return lhs += rhs;
            }

            /** \brief + operator (const TScalar) */
            friend inline MyType operator+ (MyType lhs, const char offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const char offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const unsigned char offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const unsigned char offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const short offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const short offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const unsigned short offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const unsigned short offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const int offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const int offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const unsigned int offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const unsigned int offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const long offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const long offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const unsigned long offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const unsigned long offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const long long offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const long long offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const unsigned long long offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const unsigned long long offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const float offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const float offset, MyType rhs)
            {
                return rhs += offset;
            }

            friend inline MyType operator+ (MyType lhs, const double offset)
            {
                return lhs += offset;
            }

            friend inline MyType operator+ (const double offset, MyType rhs)
            {
                return rhs += offset;
            }


            //---   Operator -=   -------------------------------------------
            /* \brief operator -= (const &)
            */
            template<const unsigned short F>
            MyType& operator -= (const vcl::utils::Timecode<F>& rhs)
            {
                prvt_set(this->frame_s() - rhs.frame_s());
                return *this;
            }

            /* \brief operator -= (const char) on frames count
            */
            MyType& operator -= (const char offset)
            {
                prvt_set(this->frame_index() - FrameIndex(offset));
                return *this;
            }

            /* \brief operator -= (const unsigned char) on frames count
            */
            MyType& operator -= (const unsigned char offset)
            {
                prvt_set(this->frame_index() - FrameIndex(offset));
                return *this;
            }

            /* \brief operator -= (const short) on frames count
            */
            MyType& operator -=(const short offset)
            {
                prvt_set(this->frame_index() - FrameIndex(offset));
                return *this;
            }

            /* \brief operator -= (const unsigned short) on frames count
            */
            MyType& operator -= (const unsigned short offset)
            {
                prvt_set(this->frame_index() - FrameIndex(offset));
                return *this;
            }

            /* \brief operator -= (const int) on frames count
            */
            MyType& operator -= (const int offset)
            {
                prvt_set(this->frame_index() - FrameIndex(offset));
                return *this;
            }

            /* \brief operator -= (const unsigned int) on frames count
            */
            MyType& operator -= (const unsigned int offset)
            {
                prvt_set(this->frame_index() - FrameIndex(offset));
                return *this;
            }

            /* \brief operator -= (const long) on frames count
            */
            MyType& operator -= (const long offset)
            {
                prvt_set(this->frame_index() - FrameIndex(offset));
                return *this;
            }

            /* \brief operator -= (const unsigned long) on frames count
            */
            MyType& operator -= (const unsigned long offset)
            {
                prvt_set(this->frame_index() - FrameIndex(offset));
                return *this;
            }

            /* \brief operator -= (const long long) on frames count
            */
            MyType& operator -= (const long long offset)
            {
                prvt_set(this->frame_index() - FrameIndex(offset));
                return *this;
            }

            /* \brief operator -= (const unsigned long long) on frames count
            */
            MyType& operator -= (const unsigned long long offset)
            {
                prvt_set(this->frame_index() - FrameIndex(offset));
                return *this;
            }

            /* \brief operator -= (const float) on frames times
            */
            MyType& operator -= (const float offset)
            {
                prvt_set(this->frame_s() - FrameTime(offset));
                return *this;
            }

            /* \brief operator -= (const double) on frames times
            */
            MyType& operator -= (const double offset)
            {
                prvt_set(this->frame_s() - FrameTime(offset));
                return *this;
            }


            //---   Operator -   --------------------------------------------
            /* \brief operator - (const &)
            */
            template<const unsigned short F>
            friend inline MyType operator- (MyType lhs, const vcl::utils::Timecode<F>& rhs)
            {
                return lhs -= rhs;
            }

            /** \brief - operator (const TScalar) */
            friend inline MyType operator- (MyType lhs, const char offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const char offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const unsigned char offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const unsigned char offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const short offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const short offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const unsigned short offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const unsigned short offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const int offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const int offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const unsigned int offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const unsigned int offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const long offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const long offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const unsigned long offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const unsigned long offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const long long offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const long long offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const unsigned long long offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const unsigned long long offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const float offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const float offset, MyType rhs)
            {
                return rhs -= offset;
            }

            friend inline MyType operator- (MyType lhs, const double offset)
            {
                return lhs -= offset;
            }

            friend inline MyType operator- (const double offset, MyType rhs)
            {
                return rhs -= offset;
            }


            //---   Comparison Operators   ----------------------------------
            /** operator < */
            template<const unsigned short F>
            inline bool operator < (const vcl::utils::Timecode<F>& rhs)
            {
                return frame_s() < rhs.frame_s();
            }

            /** operator <= */
            template<const unsigned short F>
            inline bool operator <= (const vcl::utils::Timecode<F>& rhs)
            {
                return frame_s() < rhs.frame_s() || *this == rhs;
            }

            /** operator > */
            template<const unsigned short F>
            inline bool operator > (const vcl::utils::Timecode<F>& rhs)
            {
                return frame_s() > rhs.frame_s();
            }

            /** operator >= */
            template<const unsigned short F>
            inline bool operator >= (const vcl::utils::Timecode<F>& rhs)
            {
                return frame_s() > rhs.frame_s() || *this == rhs;
            }

            /** operator == */
            template<const unsigned short F>
            inline bool operator == (const vcl::utils::Timecode<F>& rhs)
            {
                constexpr FrameTime EPS = 1e-4f;
                return vcl::utils::in_range_ii<FrameTime, -EPS, EPS>(this->frame_s() - rhs.frame_s());
            }

            /** operator != */
            template<const unsigned short F>
            inline bool operator != (const vcl::utils::Timecode<F>& rhs)
            {
                return !(*this == rhs);
            }


        private:

            static inline Timecode::FrameTime kEPS = Timecode::FrameTime(1e-5);

            static std::string m_ERR_TXT[];

            /** \brief Internally sets this timecode (const FrameIndex).
            */
            inline void prvt_set(const Timecode::FrameIndex index)
            {
                prvt_set(Timecode::FrameTime(index) / Timecode::FrameTime(FPS));
            }

            /** \brief Internally sets this timecode (const FrameTime fractional seconds).
            */
            void prvt_set(const Timecode::FrameTime fract_sec)
            {
                if (fract_sec <= 0)
                    hh = mm = ss = ff = CompT(0);
                else {
                    hh = CompT(fract_sec / 3600.0);
                    mm = CompT((unsigned long)(fract_sec / 60.0) % 60);
                    ss = CompT((unsigned long)(fract_sec) % 60);
                    ff = CompT(FPS * (fract_sec - (unsigned long)fract_sec + kEPS));
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

            /** \brief Internally sets this timecode (const&).
            */
            template<const unsigned short F>
            void prvt_set(const Timecode<F>& other)
            {
                if (other.b_error)
                    throw std::invalid_argument("invalid timecode value passed as Timecode argument");
                else {
                    prvt_set(other.frame_s());
                }
            }

            /** \brief Internally checks for the correctness of this timecode .
            */
            inline const bool prvt_check()
            {
                //if (0 <= hh && hh <= 99 && 0 <= mm && mm < 60 && 0 <= ss && ss < 60 && 0 <= ff && ff < FPS)
                if (vcl::utils::in_range_ii<CompT, 0, 99>(hh) &&
                        vcl::utils::in_range_io<CompT, 0, 60>(mm) &&
                        vcl::utils::in_range_ii<CompT, 0, 59>(ss) &&
                        vcl::utils::in_range_io<CompT, 0, FPS>(ff))
                    prvt_clr_error();
                else
                    prvt_set_error();
            }

            /** \brief clears the internal error state  */
            inline void prvt_clr_error()
            {
                b_error = false;
            }

            /** \brief sets the internal error state to true */
            inline void prvt_set_error()
            {
                b_error = true;
            }

        };

    } // end of namespace utils
} // end of namespace vcl
