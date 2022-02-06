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

#include <new>


export module matrices.matrix;

import utils.dims;


//===========================================================================
namespace vcl {
    namespace mat {

        //-----------------------------------------------------------------------
        /** \brief the generic class for 2-D matrices.
        */
        export template<typename TComp> class Mat
        {
        public:

            typedef vcl::mat::Mat<TComp>    MyType; //<! wrapper to this class naming.
            typedef unsigned long           TSize;  //<! the internal type for width and height values.
            typedef vcl::utils::Dims<TSize> TDims;  //<! the internal type for dimensions.

            //---   constructors   ----------------------------------------------
            /** \brief Constructor with width, height and default filling value.
            */
            inline Mat<TComp>(const TSize width, const TSize height)
                : m_dims(width, height), prvt_data(NULL)
            {
                prvt_create(m_dims);
                fill(TComp());
            }

            /** \brief Constructor with width, height and specified value.
            */
            inline Mat<TComp>(const TSize width, const TSize height, const TComp value)
                : m_dims(width, height), prvt_data(NULL)
            {
                prvt_create(m_dims);
                fill(value);
            }

            /** \brief Constructor with width, height and reference to specified value.
            */
            inline Mat<TComp>(const TSize width, const TSize height, const TComp& value)
                : m_dims(width, height), prvt_data(NULL)
            {
                prvt_create(m_dims);
                fill(value);
            }

            /** \brief Constructor with dims and default filling value.
            */
            inline Mat<TComp>(const TDims& dims)
                : m_dims(width, height), prvt_data(NULL)
            {
                prvt_create(m_dims);
                fill(TComp());
            }

            /** \brief Constructor with dims and specified value.
            */
            inline Mat<TComp>(const TDims& dims, const TComp value)
                : m_dims(width, height), prvt_data(NULL)
            {
                prvt_create(m_dims);
                fill(value);
            }

            /** \brief Constructor with dims and reference to specified value.
            */
            inline Mat<TComp>(const TDims& dims, const TComp& value)
                : m_dims(width, height), prvt_data(NULL)
            {
                prvt_create(m_dims);
                fill(value);
            }

            /** \brief Move constructor.
            */
            inline Mat<TComp>(const Mat<TComp>& other)
                : m_dims(other.m_dims), prvt_data(NULL)
            {
                prvt_create(m_dims);
                copy(other);
            }

            //---  Destructor   -------------------------------------------------
            virtual inline ~Mat<TComp>()
            {
                if (prvt_data != NULL)
                    delete[] prvt_data;
            }

            //---   Dimensions accessors   --------------------------------------
            /** \brief wrapper to this matrix height.
            */
            inline const TSize height() const
            {
                return m_dims.height();
            }

            /** \brief wrapper to this matrix width.
            */
            inline const TSize width() const
            {
                return m_dims.width();
            }

            //---   miscelaneous   ----------------------------------------------
            /** \brief returns true if things are fine with this matrix, or false otherwise. */
            const bool is_ok() const
            {
                return prvt_data != NULL;
            }

            //---   copy()   ----------------------------------------------------
            /** \brief Copies a const vcl::mat::Mat.
            */
            template<typename T>
            inline void copy(const vcl::mat::Mat<T>& other)
            {
                auto ot = other.cbegin();
                for (auto it = this->begin(); it != this->end() && ot != other.cend(); )
                    *it++ = clipped(*ot++);
            }

            //---   Assignment operator =   -------------------------------------
            /** \brief = operator (const reference) */
            template<typename T, size_t S>
            inline MyType& operator= (const vcl::vect::Vector<T, S>& rhs)
            {
                // TODO:
                return *this;
            }

            /** \brief = operator (const TComp) */
            inline MyType& operator= (const char value)
            {
                // TODO:
                return *this;
            }

            /** \brief = operator (const std::array) */
            template<typename T, size_t S>
            inline MyType& operator= (const std::array<T, S>& rhs)
            {
                // TODO:
                return *this;
            }

            /** \brief = operator (const std::vector) */
            template<typename T>
            inline MyType& operator= (const std::vector<T>& rhs)
            {
                // TODO:
                return *this;
            }


        protected:
            vcl::utils::Dims<size_t> m_dims; //!< the dimensions of this matrix.


        private:
            TComp** prvt_data;
            std::vector<TComp*> prvt_rows;

            /** \brief creates the data storage for this matrix. */
            void prvt_create(const vcl::utils::Dims<TSize> dims)
            {
                prvt_data = new(std::nothrow) TComp[dims.surface()];
                prvt_rows.resize(dims.height());
                TComp* ptr = prvt_data;
                for (auto it = prvt_rows.begin(); it != prvt_rows.end(); it++, ptr += sizeof(TComp))
                    *it++ = ptr;
            }

        }; // end of class Mat<typename TComp>

    } // end of namespace mat
} // end of namespace vcl
