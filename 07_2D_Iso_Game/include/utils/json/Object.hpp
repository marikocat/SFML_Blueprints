#ifndef UTILS_JSON_OBJECT_HPP
#define UTILS_JSON_OBJECT_HPP

#include "Value.hpp"
#include <unordered_map>
#include <iostream>

namespace utils
{
    class Parser;
    namespace json
    {
        /**
         * \brief a class to manage JSon objects
         * Stored as std::map
         */
        class Object
        {
            public:
                explicit Object();

                friend std::ostream& operator<<(std::ostream& stream, const Object& self); //< output as json

                /**
                 * \return the Value with key key
                 * Note a new one is create if key does't exist
                 */
                Value& operator[] (const std::string& key);

                /**
                 * \return the Value with key key
                 * Note make a error is key is not valid
                 */
                const Value& operator[] (const std::string& key) const;

                /**
                 * \return the count of items with key name
                 */
                int count(const std::string& key) const;

                /**
                \brief begin iterator
                */
                std::unordered_map<std::string, Value>::const_iterator begin() const;

                /**
                \brief end iterator
                */
                std::unordered_map<std::string, Value>::const_iterator end() const;

                /**
                \brief begin iterator
                */
                std::unordered_map<std::string, Value>::iterator begin();

                /**
                \brief end iterator
                */
                std::unordered_map<std::string, Value>::iterator end();


                size_t size() const; //< return the object size

                /**
                \brief merge other object into this
                \param other object to merge
                \param recursive recursivly merge
                \param replace_old replace original value by other value
                */
                void merge(const Object& other, bool recursive = true, bool replace_old = false);

            private:
                friend class ::utils::json::Parser;
                friend class Value;

                std::unordered_map<std::string,Value> _values;

                static void _ident(std::ostream& out,int);

                void _printIdent(std::ostream& out,int i)const;

        };
    }
}
#endif
