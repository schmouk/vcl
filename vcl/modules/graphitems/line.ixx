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

#include <iostream>

#include <array>
#include <math.h>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include <opencv2/core/types.hpp> // to get access to cv::Rect_<_Tp> and cv::Point_<_Tp>
#include <opencv2/imgproc.hpp>    // to get access to OpenCV drawing functions

export module graphitems.line;

import utils.base_funcs;
import utils.colors;
import utils.dims;
import utils.offsets;
import utils.pos;
import utils.ranges;
import vectors.vect2;
import vectors.vect3;


//===========================================================================
namespace vcl::graphitems {

	//===================================================================
	/** \brief class LineT: the generic class for 2-D rectangles. */
	export template<typename TScalar>
		requires std::is_arithmetic_v<TScalar>
	class LineT;

	// Specializations
	/** \brief The class of lines with integer positions and dimensions (8 bits). */
	export using Line_c = LineT<char>;

	/** \brief The class of lines with unsigned integer positions and dimensions (8 bits). */
	export using Line_b = LineT<unsigned char>;

	/** \brief The class of lines with integer positions and dimensions (16 bits). */
	export using Line_s = LineT<short>;
	export using Line = Rect_s;

	/** \brief The class of lines with unsigned integer positions and dimensions (16 bits). */
	export using Line_us = LineT<unsigned short>;

	/** \brief The class of lines with integer positions and dimensions (32 bits). */
	export using Line_i = LineT<long>;

	/** \brief The class of lines with unsigned integer positions and dimensions (32 bits). */
	export using Line_ui = LineT<unsigned long>;

	/** \brief The class of lines with integer positions and dimensions (64 bits). */
	export using Line_ll = LineT<long long>;

	/** \brief The class of lines with unsigned integer positions and dimensions (64 bits). */
	export using Line_ull = LineT<unsigned long long>;

	/** \brief The class of lines with float positions and dimensions (32 bits). */
	export using Line_f = LineT<float>;

	/** \brief The class of lines with double positions and dimensions (64 bits). */
	export using Line_d = LineT<double>;

	/** \brief The class of lines with long double positions and dimensions (128 bits). */
	export using Line_ld = LineT<long double>;


	//=======================================================================
	/** \brief The generic class for lines.
	*
	* TODO: mofiy next paragraph!
	* Notice: this template class in vcl inherits from  the  OpenCV  class
	*   Rect_<_Tp>.  Meanwhile, it exposes a rather different API. Mostly:
	*   the origin of the plane is at top-left corner of screen,  while in
	*   openCV it is positionned at bottom-left corner. This means that in
	*   vcl, y_top coordinate gets a lower value than y_bottom coordinate.
	*   In OpenCV, the related values are inverted.
	*
	* Since vcl::graphitems::Rect inherits from class  cv::Rect_,  it gets
	* access  to  attributes  '.x' (left x),  '.y' (top y),  '.width'  and
	* '.height' as well as to methods '.area()', '.size()' and '.empty()'.
	*/
	template<typename TScalar>
	requires std::is_arithmetic_v<TScalar>
		class LineT
	{
	public:
		using MyType        = vcl::graphitems::LineT<TScalar>;  //!< wrapper to this class naming.
		using MyDimsType    = vcl::utils::DimsT<TScalar>;       //!< wrapper to this class specialized DimsT type.
		using MyPosType     = vcl::utils::PosT<TScalar>;        //!< wrapper to this class specialized PosT type.
		using MyOffsetsType = vcl::utils::OffsetsT<TScalar>;    //!< wrapper to this class specialized OffsetsT type.


        //---   Attributes   ------------------------------------------------
		MyPosType start, end; //!< start point and end point of this line.


        //---   Constructors   ----------------------------------------------
		/** \brief Empty constructor.
		*/
		inline LineT<TScalar>() noexcept
			: start(), end()
		{}

		/** \brief Copy constructor (const&).
		*/
		template<typename T>
		   requires std::is_arithmetic_v<T>
		inline LineT<TScalar>(const vcl::graphitems::LineT<T>& other) noexcept
			: start(other.start), end(other.end)
		{}

		/** \brief Constructor (4-D vcl::vector positions).
		* Notice: order of coordinates in vector: start.x, start.y, end.x, end.y.
		*/
		template<typename T>
			requires std::is_arithmetic_v<T>
		inline explicit LineT<TScalar>(const vcl::vect::Vect4T<T>& vect) noexcept
			: start(vect[0], vect[1]), end(vect[2], vect[3])
		{}

		/** \brief Copy constructor (const std::vector&).
		* Notice: order of coordinates in vector: start.x, start.y, end.x, end.y.
		*/
		template<typename T>
			requires std::is_arithmetic_v<T>
		explicit LineT<TScalar>(const std::vector<T>& vect) noexcept(false)
			: start(), end()
		{
			const size_t S = vect.size();
			if (vect.size() < 4) {
				throw std::invalid_argument("vectors used for lines construction must contain at least 4 components.");
			}
			else {
				start.x = TScalar(vect[0]);
				start.y = TScalar(vect[1]);
				end.x = TScalar(vect[2]);
				end.y = TScalar(vect[3]);
			}
		}

		/** \brief Copy constructor (const std::array&).
		* Notice: order of coordinates in array: start.x, start.y, end.x, end.y.
		*/
		template<typename T, size_t S>
		    requires std::is_arithmetic_v<T>
		explicit LineT<TScalar>(const std::array<T, S>& arr) noexcept(false)
			: start(), end()
		{
			if (S < 4) {
				throw std::invalid_argument("arrays used for lines construction must contain at least 4 components.");
			}
			else {
				start.x = TScalar(arr[0]);
				start.y = TScalar(arr[1]);
				end.x = TScalar(arr[2]);
				end.y = TScalar(arr[3]);
			}
		}

		/** \brief Constructor (4 scalar border positions).
		*/
		template<typename T, typename U, typename V, typename W>
		    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V> && std::is_arithmetic_v<W>
		inline explicit LineT<TScalar>(const T start_x, const U start_y, const V end_x, const W end_y) noexcept
			: start(start_x, start_y), end(end_x, end_y)
		{}

		/** \brief Constructor (2 scalar start position + 1 end position).
		*/
		template<typename T, typename U, typename V>
		    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
		inline explicit LineT<TScalar>(const T start_x, const U start_y, const vcl::utils::PosT<V>& end) noexcept
			: MyBaseType(start_x, start_y, end.x(), end.y())
		{}


		/** \brief Constructor (1 start position + 2 scalar end position).
		*/
		template<typename T, typename U, typename V>
		    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
		inline explicit LineT<TScalar>(const vcl::utils::PosT<T>& top_left, const U end_x, const V end_y) noexcept
			: MyBaseType(start.x(), start.y(), end_x, end_y)
		{}

		/** \brief Constructor (std::pair<>, std::pair<>).
		*/
		template<typename T, typename U, typename V, typename W>
		    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V> && std::is_arithmetic_v<W>
		inline explicit LineT<TScalar>(const std::pair<T, U>& start, const std::pair<V, W>& end) noexcept
			: MyBaseType(start.first, start.second, end.first, end.second)
		{}


		//---   Destructor   ------------------------------------------------
		virtual inline ~LineT<TScalar>() noexcept
		{}


		//---   Assignment   ------------------------------------------------
		/** \brief Copy assign operator (const vcl::graphitems::LineT<>&).
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& operator= (vcl::graphitems::LineT<T>& other) noexcept
		{
			start = other.start;
			end = other.end;
			return *this;
		}

		/** \brief Move assign operator (const vcl::graphitems::LineT<>&&).
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		MyType& operator= (vcl::graphitems::LineT<T>&& other) noexcept
		{
			start = other.start;
			end = other.end;
			return *this;
		}

		/** \brief assign operator (const vcl::vect::Vect4T<>).
		* The vector components are: {start_x, start_y, end_x, end_y}.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		MyType& operator= (vcl::vect::Vect4T<T>& other) noexcept
		{
			start.x(TScalar(vect[0]));
			start.y(TScalar(vect[1]));
			end.x(TScalar(vect[2]));
			end.y(TScalar(vect[3]));
			return *this;
		}

		/** \brief assign operator (const std::vector<>).
		* The vector components must be: {start_x, start_y, end_x, end_y}.
		* At least four components must be provided. If more than 4
		* of them are provided, the next ones are ignored.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		MyType& operator= (std::vector<T>& vect) noexcept(false)
		{
			if (vect.size() < 4) {
				throw std::invalid_argument("vectors used for lines assignment must contain at least 4 components.");
				return *this;
			}
			else {
				start.x(TScalar(vect[0]));
				start.y(TScalar(vect[1]));
				end.x(TScalar(vect[2]));
				end.y(TScalar(vect[3]));
			}
			return *this;
		}

		/** \brief assign operator (const std::array<>).
		* The array components must be: {start_x, start_y, end_x, end_y}.
		* At least four components must be provided. If more than 4
		* of them are provided, the next ones are ignored.
		*/
		template<typename T, const size_t S>
		    requires std::is_arithmetic_v<T>
		MyType& operator= (std::array<T, S>& arr) noexcept(false)
		{
			if (S < 4) {
				throw std::invalid_argument("arrays used for lines assignment must contain at least 4 components.");
				return *this;
			}
			else {
				start.x(TScalar(arr[0]));
				start.y(TScalar(arr[1]));
				end.x(TScalar(arr[2]));
				end.y(TScalar(arr[3]));
			}
			return *this;
		}


		//---   Comparisons   -----------------------------------------------
		/** \brief Equality between lines. */
		template<typename T = TScalar>
		    requires std::is_arithmetic_v<T>
		inline const bool operator== (const vcl::graphitems::LineT<T>& other) const noexcept
		{
			return start == other.start && end == other.end;
		}

		/** \brief Inequality between rectangles. */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline const bool operator != (const vcl::graphitems::LineT<T>& other) const noexcept
		{
			return !(*this == other);
		}


		//---   Accessors / Mutators   --------------------------------------
		/** \brief start.x position accessor. */
		inline const TScalar start_x() const noexcept
		{
			return start.x();
		}

		/** \brief start.x position mutator. */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline void end_x(const T& new_start_x) noexcept
		{
			start.x(new_start_x);
		}

		/** \brief start.y position accessor. */
		inline const TScalar start_y() const noexcept
		{
			return start.y();
		}

		/** \brief start.y position mutator. */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline void start_y(const T& new_start_y) noexcept
		{
			start.y(new_start_y);
		}

		/** \brief end.x position accessor. */
		inline const TScalar end_x() const noexcept
		{
			return end.x();
		}

		/** \brief end.x position mutator. */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline void end_x(const T& new_end_x) noexcept
		{
			end.x(new_end_x);
		}

		/** \brief end.y position accessor. */
		inline const TScalar end_y() const noexcept
		{
			return end.y();
		}

		/** \brief end.y position mutator. */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline void end_y(const T& new_end_y) noexcept
		{
			end.y(new_end_y);
		}


		//---   Miscelaneous   ----------------------------------------------
		/** \brief Returns the length of this line, maybe rounded to the nearest integral value. */
		const TScalar length() const noexcept
		{
			if (std::is_integral_v<TScalar>) {
				const long long dx = (long long)start.x - (long long)end.x;
				const long long dy = (long long)start.y - (long long)end.y;
				return TScalar(round(sqrt(dx * dx + dy * dy)));
			}
			else {
				const TScalar dx = start.x - end.x;
				const TScalar dy = start.y - end.y;
				return sqrt(dx * dx + dy * dy);
			}
		}

		//---   Casting operators   -----------------------------------------
		/** \brief casting operator to vcl::vect::Vect4T<T>.
		* Returns a 4-components vcl::vect::Vect4T (start.x, start.y, nd.x, end.y).
		*/
		template<typename T = TScalar>
		    requires std::is_arithmetic_v<T>
		inline operator vcl::vect::Vect4T<T>() noexcept
		{
			return vcl::vect::Vect4T<T>(start.x(), start.y(), end.x(), end.y());
		}

		/** \brief casting operator to std::vector<T>.
		* Returns a 4-components std::vector (start.x, start.y, nd.x, end.y).
		*/
		template<typename T = TScalar>
		    requires std::is_arithmetic_v<T>
		operator std::vector<T>() noexcept
		{
			std::vector<T> v;
			v.push_back(T(start.x()));
			v.push_back(T(start.y()));
			v.push_back(T(end.x());
			v.push_back(T(end.y()));
			return v;
		}

		/** \brief casting operator to std::array<T, 4>.
		* Returns a 4-components std::array (start.x, start.y, nd.x, end.y).
		*/
		template<typename T = TScalar>
		    requires std::is_arithmetic_v<T>
		inline operator std::array<T, 4>() noexcept
		{
			std::array<T, 4> arr{ T(start.x()), T(start.y()), T(end.x()), T(end.y()) };
			return arr;
		}


		//---   Moving   ----------------------------------------------------
		/** \brief Moves this line according to specified offset (2 scalars). */
		template<typename T, typename U>
		    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
		inline MyType& move(const T dx, const U dy) noexcept
		{
			return move(MyOffsetsType(dx, dy));
		}

		/** \brief Moves this line according to specified offset (vcl::vect::VectorT). */
		template<typename T, const size_t Ksize>
		    requires std::is_arithmetic_v<T>
		inline MyType& move(const vcl::vect::VectorT<T, Ksize>& offset) noexcept(false)
		{
			if (Ksize < 2) {
				throw std::invalid_argument("vectors used to move lines must contain at least 2 components.");
				return *this;
			}
			else {
				return move(MyOffsetsType(offset));
			}
		}

		/** \brief Moves this line with specified offset (std::vector). */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& move(const std::vector<T>& offset) noexcept(false)
		{
			if (offset.size() < 2) {
				throw std::invalid_argument("vectors used to move lines must contain at least 2 components.");
				return *this;
			}
			else {
				return move(MyOffsetsType(offset));
			}
		}

		/** \brief Moves this line with specified offset (std::array). */
		template<typename T, const size_t S>
		    requires std::is_arithmetic_v<T>
		inline MyType& move(const std::array<T, S>& offset) noexcept(false)
		{
			if (S < 2) {
				throw std::invalid_argument("arrays used to move lines must contain at least 2 components.");
				return *this;
			}
			else {
				return move(MyOffsetsType(offset));
			}
		}

		/** \brief Moves this line with specified offset (std::pair). */
		template<typename T, typename U>
		    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
		inline MyType& move(const std::pair<T, U>& offset) noexcept
		{
				return move(MyOffsetsType(offset));
		}

		/** \brief Moves this line according to specified offset (vcl::utils::Offset). */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& move(const vcl::utils::OffsetsT<T>& offset) noexcept
		{
			start += offset;
			end += offset;
			return *this;
		}

		/** \brief Moves this line according to specified offset (vcl::vect::VectorT). */
		template<typename T, const size_t Ksize>
		    requires std::is_arithmetic_v<T>
		inline MyType& operator += (const vcl::vect::VectorT<T, Ksize>& offset) noexcept
		{
			return move(offset);
		}

		/** \brief Moves this line according to specified offset (std::vector). */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& operator += (const std::vector<T>& offset) noexcept
		{
			return move(offset);
		}

		/** \brief Moves this line according to specified offset (std::array). */
		template<typename T, const size_t S>
		    requires std::is_arithmetic_v<T>
		inline MyType& operator += (const std::array<T, S>& offset) noexcept
		{
			return move(offset);
		}

		/** \brief Moves this line according to specified offset (std::pair). */
		template<typename T, typename U>
		    requires std::is_arithmetic_v<T> &&  std::is_arithmetic_v<U>
		inline MyType& operator += (const std::pair<T, U>& offset) noexcept
		{
			return move(offset);
		}

		/** \brief Moves this line according to specified offset (vcl::vect::VectorT). */
		template<typename T, const size_t Ksize>
		    requires std::is_arithmetic_v<T>
		inline friend MyType operator + (MyType line, const vcl::vect::VectorT<T, Ksize>& offset) noexcept
		{
			return line += offset;
		}

		/** \brief Moves this line according to specified offset (vcl::vect::VectorT). */
		template<typename T, const size_t Ksize>
		    requires std::is_arithmetic_v<T>
		inline friend MyType operator + (const vcl::vect::VectorT<T, Ksize>& offset, MyType line) noexcept
		{
			return line += offset;
		}

		/** \brief Moves this line according to specified offset (std::vector). */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline friend MyType operator + (MyType line, const std::vector<T>& offset) noexcept
		{
			return line += offset;
		}

		/** \brief Moves this line according to specified offset (std::vector). */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline friend MyType operator + (const std::vector<T>& offset, MyType line) noexcept
		{
			return line += offset;
		}

		/** \brief Moves this line according to specified offset (std::array). */
		template<typename T, const size_t S>
		    requires std::is_arithmetic_v<T>
		inline friend MyType operator + (MyType line, const std::array<T, S>& offset) noexcept
		{
			return line += offset;
		}

		/** \brief Moves this line according to specified offset (std::array). */
		template<typename T, const size_t S>
		    requires std::is_arithmetic_v<T>
		inline friend MyType operator + (const std::array<T, S>& offset, MyType line) noexcept
		{
			return line += offset;
		}

		/** \brief Moves this line according to specified offset (std::pair). */
		template<typename T, typename U>
		    requires std::is_arithmetic_v<T> &&  std::is_arithmetic_v<U>
		inline friend MyType operator + (MyType line, const std::pair<T, U>& offset) noexcept
		{
			return line += offset;
		}

		/** \brief Moves this line according to specified offset (std::pair). */
		template<typename T, typename U>
     		requires std::is_arithmetic_v<T> &&  std::is_arithmetic_v<U>
		inline friend MyType operator + (const std::pair<T, U>& offset, MyType line) noexcept
		{
			return line += offset;
		}

		/** \brief Moves this line according to specified offset (vcl::graphitems::LineT, vcl::utils::Offset). */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline friend MyType operator + (MyType line, const vcl::utils::OffsetsT<T>& offset) noexcept
		{
			return line += offset;
		}

		/** \brief Moves this line according to specified offset (vcl::utils::Offset, vcl::graphitems::LineT). */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline friend MyType operator + (const vcl::utils::OffsetsT<T>& offset, MyType line) noexcept
		{
			return line += offset;
		}


		//---   Moving at   -------------------------------------------------
		/** \brief Moves ending points of this line to specified position (2 scalars). */
		template<typename T, typename U>
		    requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
		inline MyType& move_at(const T new_start_x, const U new_start_y) noexcept
		{
			if (std::is_integral_v<T>) {
				const MyOffsetType offset((long long)new_start_x - (long long)start.x,
										  (long long)new_start_y - (long long)start.y);
				return move(offset);
			}
			else {
				const MyOffsetType offset(new_start_x - start.x, new_start_y - start.y);
				return move(offset);
			}
		}

		/** \brief Moves ending points of this line to specified position (vcl::utils::PosT). */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& move_at(const vcl::utils::PosT<T>& new_pos) noexcept
		{
			return move_at(new_pos.x(), new_pos.y());
		}

		/** \brief Moves ending points of this line to specified position (vcl::vect::VectorT). */
		template<typename T, const size_t Ksize>
		    requires std::is_arithmetic_v<T>
		inline MyType& move_at(const vcl::vect::VectorT<T, Ksize>& new_pos) noexcept(false)
		{
			if (Ksize < 2) {
				throw std::invalid_argument("vectors used to move lines must contain at least 2 components.");
				return *this;
			}
			else
				return move_at(new_pos[0], new_pos[1]);
		}

		/** \brief Moves ending points of this line to specified position (std::vector). */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& move_at(const std::vector<T>& new_pos)
		{
			if (new_pos.size() < 2) {
				throw std::invalid_argument("vectors used to move lines must contain at least 2 components.");
				return *this;
			}
			else
				return move_at(new_pos[0], new_pos[1]);
		}

		/** \brief Moves ending points of this line to specified position (std::array). */
		template<typename T, const size_t S>
		    requires std::is_arithmetic_v<T>
		inline MyType& move_at(const std::array<T, S>& new_pos)
		{
				if (S < 2) {
					throw std::invalid_argument("arrays used to move lines must contain at least 2 components.");
					return *this;
				}
				else
					return move_at(new_pos[0], new_pos[1]);
			}

		/** \brief Moves ending points of this line to specified position (std::pair). */
		template<typename T, typename U>
		    requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
		inline MyType& move_at(const std::pair<T, U>& new_pos) noexcept
		{
			return move_at(new_pos.first, new_pos.second);
		}


		//---   Resizing   --------------------------------------------------
		/** \brief Resizes this line (1 scalar parameter).
		* Negative values for argument 'incr' decrease the length of the line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		MyType& resize(const T& incr) noexcept
		{
			if (start.x() == end.x()) {
				end += MyOffsetsType(0, incr);
			}
			else if (start.y() == end.y()) {
				end += MyOffsetsType(incr, 0);
			}
			else {
				if (std::is_integral_v<TScalar>) {
					const double dx = double(start.x()) - double(end.x());
					const double dy = double(start.y()) - double(end.y());
					const double new_length = double(length() + incr);
					end = MyPosType(round(dx * new_length / dy + start.x()),
									round(dy * new_length / dx + start.y()));
				}
				else {
					const TScalar dx = start.x() - end.x();
					const TScalar dy = start.y() - end.y();
					const TScalar new_length = length() + incr;
					end = MyPosType(round(dx * new_length / dy) + start.x(),
									round(dy * new_length / dx) + start.y());
				}
			}
			return *this;
		}

		/** \brief Resizes this line (operator +=, 1 scalar parameter).
		* Negative values for argument 'incr' decrease the length of the line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& operator+= (const T& incr) noexcept
		{
			return resize(incr);
		}

		/** \brief Resizes this line (operator -=, 1 scalar parameter).
		* Negative values for argument 'incr' increase the length of the line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& operator-= (const T& incr) noexcept
		{
			return resize(-incr);
		}

		/** \brief Resizes this line (operator +, 1 line + 1 scalar parameter).
		* Negative values for argument 'incr' decrease the length of the line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		friend inline MyType& operator+ (MyType line, const T& incr) noexcept
		{
			return line += incr;
		}

		/** \brief Resizes this line (operator +, 1 scalar parameter + 1 line).
		* Negative values for argument 'incr' decrease the length of the line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		friend inline MyType& operator+ (const T& incr, MyType line) noexcept
		{
			return line += incr;
		}

		/** \brief Resizes this line (operator +, 1 line + 1 scalar parameter).
		* Negative values for argument 'incr' increase the length of the line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		friend inline MyType& operator- (MyType line, const T& incr) noexcept
		{
			return line -= incr;
		}

		/** \brief Resizes this line (operator +, 1 scalar parameter + 1 line).
		* Negative values for argument 'incr' increase the length of the line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		friend inline MyType& operator+ (const T& incr, MyType line) noexcept
		{
			return line -= incr;
		}


		//---   Scaling   ---------------------------------------------------
		/** \brief Resizes this line according to a scaling factor.
		* Factors less than 1 reduce the size of this line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& scale(const T& factor) noexcept
		{
			return resize(length() * (factor - 1));
		}

		/** \brief Resizes this line according to a scaling factor.
		* Factors less than 1 reduce the size of this line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& operator *= (const T& factor) noexcept
		{
			return scale(factor);
		}

		/** \brief Resizing operator * (const TScalar) */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		friend inline MyType operator * (MyType line, const T factor) noexcept
		{
			return line *= factor;
		}

		/** \brief Resizing operator * (const TScalar, vcl::graphitems::LineT<>) */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		friend inline MyType operator * (const T factor, MyType line) noexcept
		{
			return line *= factor;
		}

		/** \brief Scales this line from its center (1 scalar factor).
		* Scales this line from its center as  the  origin
		* of the scaling. As such, modifies the top-left corner
		* position.
		* Values less than 1.0 shrink this line.
		* \sa \c shrink_from_center() and \c scale()
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& scale_from_center(const T factor) noexcept
		{
			const TScalar prev_length = length();
			scale(factor);
			return move(0.5 * (prev_length - length()));
		}


		//---   Shrinking   -------------------------------------------------
		/** \brief Resizes this line according to a reducing factor.
		* Factors less than 1 augment the size of this line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& shrink(const T factor) noexcept(false)
		{
			if (factor == T(0))
				throw std::invalid_argument("reducing factors cannot be zero");
			else
				this *= 1.0 / double(factor);
			return *this;
		}

		/** \brief Resizes this line according to a reducing factor.
		* Factors less than 1 augment the size of this line.
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& operator /= (const T& factor) noexcept(false)
		{
			return shrink(factor);
		}

		/** \brief Shrinking operator / (const TScalar) */
		template<typename T>
		    requires std::is_arithmetic_v<T>
		friend inline MyType operator / (MyType line, const T factor) noexcept(false)
		{
			return line /= factor;
		}

		/** \brief Shrinks this line from its center (1 scalar factor).
		* Shrinks this line from its center as the  origin
		* of the scaling. As such, modifies the top-left corner
		* position.
		* Values less than 1.0 augment this line.
		* \sa \c scale_from_center() and \c skrink()
		*/
		template<typename T>
		    requires std::is_arithmetic_v<T>
		inline MyType& shrink_from_center(const T& factor) noexcept(false)
		{
			const TScalar prev_length = length();
			shrink(factor);
			return move(0.5 * (prev_length - length()));
		}


		//---   Drawing   ---------------------------------------------------
		/** \brief Draws this line in a specified frame (whole arguments provided). */
		inline void draw(cv::Mat&                 frame,
						 const vcl::utils::Color& border_color,
						 const int                border_thickness,
						 const cv::LineTypes      border_type)
		{
			prvt_last_color = border_color;
			prvt_last_thickness = border_thickness;
			prvt_last_type = border_type;
			draw(frame);
		}

		/** \brief Draws this line in a specified frame (use previous border_color again). */
		inline void draw(cv::Mat&            frame,
			             const int           border_thickness,
			             const cv::LineTypes border_type)
		{
			prvt_last_thickness = border_thickness;
			prvt_last_type = border_type;
			draw(frame);
		}

		/** \brief Draws this line in a specified frame (use previous border_thickness again). */
		inline void draw(cv::Mat&                 frame,
			             const vcl::utils::Color& border_color,
			             const cv::LineTypes      border_type)
		{
			prvt_last_color = border_color;
			prvt_last_type = border_type;
			draw(frame);
		}

		/** \brief Draws this line in a specified frame (use previous border_type again). */
		inline void draw(cv::Mat& frame,
			             const vcl::utils::Color& border_color,
			             const int                border_thickness)
		{
			prvt_last_color = border_color;
			prvt_last_thickness = border_thickness;
			draw(frame);
		}

		/** \brief Draws this line in a specified frame (use previous border_color and _thickness again). */
		inline void draw(cv::Mat& frame, const cv::LineTypes border_type)
		{
			prvt_last_type = border_type;
			draw(frame);
		}

		/** \brief Draws this line in a specified frame (use previous border_color and _type again). */
		inline void draw(cv::Mat& frame, const int border_thickness)
		{
			prvt_last_thickness = border_thickness;
			draw(frame);
		}

		/** \brief Draws this line in a specified frame (use previous border_thickness and _ttype again). */
		inline void draw(cv::Mat& frame, const vcl::utils::Color& border_color)
		{
			prvt_last_color = border_color;
			draw(frame);
		}


		/** \brief Draws this line in a specified frame (use all previous specifiers again).
		* CAUTION: while first calling method  'draw()'  on  a  line,
		*       color  MUST BE specified. Not doing so may lead to the not
		*       display of the line in the frame  or  may  result  to
		*       unpredictable color used for the display of the line.
		*/
		inline void draw(cv::Mat& frame)
		{
			cv::line(
				frame,
				cv::Point_<TScalar>(start),
				cv::Point_<TScalar>(end),
				prvt_last_color,
				prvt_last_thickness,
				prvt_last_type,
				0  // notice: in vcl, the number of fractional bits in the point coordinates is forced to zero.  
			);
		}


	private:
		vcl::utils::Color prvt_last_color{};
		int               prvt_last_thickness{ 1 };
		cv::LineTypes     prvt_last_type{ cv::LINE_8 };
	};

}
