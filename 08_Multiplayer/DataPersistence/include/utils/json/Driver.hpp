#ifndef UTILS_JSON_DRIVER_HPP
#define UTILS_JSON_DRIVER_HPP

#include <iostream>

#include <utils/json/Scanner.hpp>
#include <utils/json/Value.hpp>

#include <memory>

namespace utils
{
    /**
     * \brief namspace for json
     */
    namespace json {
        /**
         * A class that have to be use to parse json input
         */
        class Driver
        {
            public:
                /**
                 * \brief Construct a Driver from a stream
                 * \param in input stream
                 */
                Driver(std::istream& in);

                Driver(const Driver&) = delete;
                Driver& operator=(const Driver&) = delete;

                /**
                 * \brief Parse all the input (until \0)
                 */
                std::shared_ptr<Value> parse();

                /**
                 * \return true if the stream is a valid format, else, false.
                 */
                inline bool isValid()const{return _validity;}

                /**
                 * \brief Parse a input
                 * \param in The input stream to parse
                 */
                static std::shared_ptr<Value> parse(std::istream& in);

                /**
                 * \brief Parse a input
                 * \param in The input stream to parse
                 */
                static std::shared_ptr<Value> parse(const std::string& in);

                /**
                 * \brief Parse a file and return a Analyse
                 * \param filename the file name
                 * \return A Analyse tha contain all the datas parsed
                 */
                static std::shared_ptr<Value> parse_file(const std::string& filename);


                 
            private:
                friend class Parser;
                    
                Scanner _scanner; ///< The lexer
                Parser _parser; ///< The parser

                bool _validity;//< is valid
                std::shared_ptr<utils::json::Value> _value;///< the root node

        };
    }
}
#endif
