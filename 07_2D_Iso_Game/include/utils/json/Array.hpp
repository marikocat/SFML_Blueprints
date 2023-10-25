#ifndef UTILS_JSON_ARRAY_HPP
#define UTILS_JSON_ARRAY_HPP

#include "Value.hpp"
#include <list>
#include <iostream>

namespace utils
{
    class Parser;

    namespace json ///< namespace for json objects
    {
        /**
         * \brief class to manage the special Array value
         * Internally stored as a list. Operator [] is not allowed
         */
        class Array
        {
		    public:
                /**
                \brief iterator type
                */
		        typedef std::list<Value>::iterator iterator;

                /**
                \brief const iterator type
                */
		        typedef std::list<Value>::const_iterator const_iterator;

                /**
                \brief constructor
                */
                explicit Array();

                friend std::ostream& operator<<(std::ostream& stream, const Array& self); //< output as json

                /**
                \brief begin iterator
                */
                std::list<Value>::const_iterator begin() const;

                /**
                \brief end iterator
                */
                std::list<Value>::const_iterator end() const;

                /**
                \brief begin iterator
                */
                std::list<Value>::iterator begin();

                /**
                \brief end iterator
                */
                std::list<Value>::iterator end();


                size_t size() const; //< return the size (number of elements)

                std::list<Value>& data(); //return the internal container
                const std::list<Value>& data() const;//return the internal container

            private:
                friend class Value;
                friend class ::utils::json::Parser;

                void _printIdent(std::ostream& out,int i)const;

                std::list<Value> _values;

        };
    }
}
#endif
