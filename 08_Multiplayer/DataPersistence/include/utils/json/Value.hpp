#ifndef UTILS_JSON_VALUE_HPP
#define UTILS_JSON_VALUE_HPP

#include <string>
#include <iostream>

namespace utils
{
    namespace json
    {
        class Parser;
        class Array;
        class Object;

        /**
         * \brief A class to store any JSON value
         */
        class Value
        {
            public:
                /**
                \brief a null json value
                */
                explicit Value();

                /**
                \brief copy constructor
                */
                explicit Value(const Value&);

                /**
                \destructor
                */
                ~Value();

                /**
                \brief construct a string json value
                */
                explicit Value(const std::string& v);

                /**
                \brief construct a string value
                */
                explicit Value(const char* v);

                /**
                \brief an int json value
                */
                explicit Value(int v);

                /**
                \brief
                */
                explicit Value(long int v);

                /**
                \brief construct a interger json value
                */
                explicit Value(long long int v);

                /**
                \brief construct a float json value
                */
                explicit Value(double);

                /**
                \brief construct a float json value
                */
                explicit Value(long double);

                /**
                \brief construct a float json value
                */
                explicit Value(float);

                /**
                \brizef construct a boolean json value
                */
                explicit Value(bool v);

                /**
                \brief construct from a json Array
                */
                explicit Value(const Array& v);

                /**
                \brief construct from a json Object
                */
                explicit Value(const Object& v);
                /**
                \brief copy assignement value
                */
                Value& operator=(const Value&);

                /**
                \brief set value as string
                */
                Value& operator=(const std::string& v);

                /**
                \brief set value as string
                */
                Value& operator=(const char* v);

                /**
                \brief set value as integer
                */
                Value& operator=(int v);

                /**
                \brief set value as int
                */
                Value& operator=(long int v);

                /**
                \brief set value as int
                */
                Value& operator=(long long int v);

                /**
                \brief set value as float
                */
                Value& operator=(double);

                /**
                \brief set value as float
                */
                Value& operator=(long double);

                /**
                \brief set value as float
                */
                Value& operator=(float);

                /**
                \brief set value as boolean
                */
                Value& operator=(bool v);

                /**
                \brief set value as array
                */
                Value& operator=(const Array& v);

                /**
                \brief set value as object
                */
                Value& operator=(const Object& v);

                enum Type {
                    TYPE_STRING = 0,
                    TYPE_INT,
                    TYPE_FLOAT,
                    TYPE_ARRAY,
                    TYPE_OBJECT,
                    TYPE_BOOL,
                    TYPE_NULL,
                    TYPE_UNDEFINE,
                    TYPE_SIZE
                };

                Type getType()const; //< return the value type

                /**
                \brief test if current type is TYPE_STRING
                */
                bool isString()const;

                /**
                \brief test if current type is TYPE_INT
                */
                bool isInt()const;

                /**
                \brief test if current type is TYPE_FLOAT
                */
                bool isFloat()const;

                /**
                \brief test if current type is TYPE_ARRAY
                */
                bool isArray()const;

                /**
                \brief test if current type is TYPE_OBJECT
                */
                bool isObject()const;

                /**
                \brief test if current type is TYPE_BOOL
                */
                bool isBool()const;

                /**
                \brief test if current type is TYPE_NULL
                */
                bool isNull()const;

                /**
                \brief convert json value as float.  Undefine behaviour if isFloat() is false
                */
                long double& asFloat();

                /**
                \brief convert json value as float.  Undefine behaviour if isFloat() is false
                */
                const long double& asFloat() const;

                /**
                \brief convert json value as int.  Undefine behaviour if isInt() is false
                */
                long long int& asInt();

                /**
                \brief convert json value as int.  Undefine behaviour if isInt() is false
                */
                const long long int& asInt()const;

                /**
                \brief convert json value as bool.  Undefine behaviour if isBool() is false
                */
                bool& asBool();

                /**
                \brief convert json value as bool.  Undefine behaviour if isBool() is false
                */
                const bool& asBool()const;

                /**
                \brief convert json value as string.  Undefine behaviour if isString() is false
                */
                std::string asString()const;

                /**
                \brief convert json value as object.  Undefine behaviour if isObject() is false
                */
                Object& asObject();

                /**
                \brief convert json value as object.  Undefine behaviour if isObject() is false
                */
                const Object& asObject()const;

                /**
                \brief convert json value as array.  Undefine behaviour if isArray() is false
                */
                Array& asArray();

                /**
                \brief convert json value as array.  Undefine behaviour if isArray() is false
                */
                const Array& asArray()const ;

                friend std::ostream& operator<<(std::ostream& stream, const Value& self); //< output the json

            private:
                friend class Object;
                friend class Array;
                friend class Parser;

                explicit Value(std::string* v);
                explicit Value(Array* v);
                explicit Value(Object* v);

                union
                {
                    std::string*    v_string;
                    long long int   v_int;
                    long double     v_float;
                    Array*          v_array;
                    Object*         v_object;
                    bool            v_bool;
                };

                Type _type;

                void _printIdent(std::ostream& out)const; //< print the json as human readable

                void _printIdent(std::ostream& out,int i)const; //< print the json as human readable

                void _reset(); ///< reset the object to null

                void _escape(); ///< escape the current string (replace \ by \\ and " by \\")
        };
    }
}
#endif
