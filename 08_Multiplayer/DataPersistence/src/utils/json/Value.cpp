#include <utils/json/Value.hpp>
#include <utils/json/Array.hpp>
#include <utils/json/Object.hpp>

namespace utils
{
    namespace json
    {

        void findAndReplace(std::string& str, const std::string& oldStr, const std::string& newStr)
        {
            size_t pos = 0;
            while ((pos = str.find(oldStr, pos)) != std::string::npos)
            {
                str.replace(pos, oldStr.length(), newStr);
                pos += newStr.length();
            }
        }

        Value::Value() : _type(TYPE_NULL)
        {
        }

        Value::Value(const Value& other) : _type(TYPE_NULL)
        {
			*this = other;
        }

        Value::~Value()
        {
            _reset();
        }

		Value::Value(const std::string& v) : v_string(new std::string(v)),_type(TYPE_STRING)
		{
            _escape();
		}

        Value::Value(const char* v) : v_string(new std::string(v)), _type(TYPE_STRING)
        {
            _escape();
        }

        Value::Value(int v) : v_int(v), _type(TYPE_INT)
        {
        }

        Value::Value(long int v) : v_int(v), _type(TYPE_INT)
        {
        }

        Value::Value(long long int v) : v_int(v), _type(TYPE_INT)
        {
        }

        Value::Value(double v) : v_float(v), _type(TYPE_FLOAT)
        {
        }

        Value::Value(long double v) : v_float(v), _type(TYPE_FLOAT)
        {
        }

        Value::Value(float v) : v_float(v), _type(TYPE_FLOAT)
        {
        }

        Value::Value(bool v) : v_bool(v), _type(TYPE_BOOL)
        {
        }

        Value::Value(const utils::json::Array& v) : v_array(new Array(v)), _type(TYPE_ARRAY)
        {
        }

        Value::Value(const utils::json::Object& v) : v_object(new Object(v)), _type(TYPE_OBJECT)
        {
        }

        Value& Value::operator=(const Value& other)
        {
			_reset();
            _type = other._type;

            switch(_type)
            {
                case Value::TYPE_STRING:
                {
                    v_string = new std::string(*other.v_string);
                }break;
                case Value::TYPE_INT:
                {
                    v_int = other.v_int;
                }break;
                case Value::TYPE_FLOAT:
                {
                    v_float = other.v_float;
                }break;
                case Value::TYPE_ARRAY:
                {
                    v_array = new Array(*other.v_array);
                }break;
                case Value::TYPE_OBJECT:
                {
                    v_object = new Object(*other.v_object);
                }break;
                case Value::TYPE_BOOL:
                {
                    v_bool = other.v_bool;
                }break;
                case Value::TYPE_NULL:
                {
                }break;
                default:
                {
                }break;
            }
            return *this;
        }

        Value& Value::operator = (const std::string& v)
        {
            _reset();
            v_string = new std::string(v);
            _type = TYPE_STRING;
            _escape();
            return *this;
        }

        Value& Value::operator=(const char* v)
        {
            _reset();
            v_string = new std::string(v);
            _type = TYPE_STRING;
            _escape();
            return *this;
        }

        Value& Value::operator=(int v)
        {
            _reset();
            v_int = v;
            _type = TYPE_INT;
            return *this;
        }
        Value& Value::operator=(long int v)
        {
            _reset();
            v_int = v;
            _type = TYPE_INT;
            return *this;
        }

        Value& Value::operator=(long long int v)
        {
            _reset();
            v_int = v;
            _type = TYPE_INT;
            return *this;
        }

        Value& Value::operator=(double d)
        {
            _reset();
            v_float = d;
            _type = TYPE_FLOAT;
            return *this;
        }

        Value& Value::operator=(long double d)
        {
            _reset();
            v_float = d;
            _type = TYPE_FLOAT;
            return *this;
        }

        Value& Value::operator=(float f)
        {
            _reset();
            v_float = f;
            _type = TYPE_FLOAT;
            return *this;
        }

        Value& Value::operator=(bool v)
        {
            _reset();
            v_bool = v;
            _type = TYPE_BOOL;
            return *this;
        }

        Value& Value::operator=(const utils::json::Array& v)
		{
            _reset();
			v_array = new Array(v);
            _type = TYPE_ARRAY;
			return *this;
		}

		Value& Value::operator=(const utils::json::Object& v)
		{
            _reset();
            v_object = new Object(v);
            _type = TYPE_OBJECT;
			return *this;
		}


        ///////// HELPERS ///////////////
		Value::Type Value::getType()const
		{
			return _type;
		}

        bool Value::isString()const
        {
            return _type == TYPE_STRING;
        }

        bool Value::isInt()const
        {
            return _type == TYPE_INT;
        }

        bool Value::isFloat()const
        {
            return _type == TYPE_FLOAT;
        }

        bool Value::isArray()const
        {
            return _type == TYPE_ARRAY;
        }

        bool Value::isObject()const
        {
            return _type == TYPE_OBJECT;
        }

        bool Value::isBool()const
        {
            return _type == TYPE_BOOL;
        }

        bool Value::isNull()const
        {
            return _type == TYPE_NULL;
        }

        long double& Value::asFloat()
        {
            if (isFloat() == false)
            {
                throw std::logic_error("Value is not a Float");
            }

            return v_float;
        }

        const long double& Value::asFloat()const
        {
            if (isFloat() == false)
            {
                throw std::logic_error("Value is not a Float");
            }

            return v_float;
        }

        long long int& Value::asInt()
        {
            if (isInt() == false)
            {
                throw std::logic_error("Value is not a Int");
            }

            return v_int;
        }

        const long long int& Value::asInt()const
        {
            if (isInt() == false)
            {
                throw std::logic_error("Value is not a Int");
            }

            return v_int;
        }

        bool& Value::asBool()
        {
            if (isBool() == false)
            {
                throw std::logic_error("Value is not a Bool");
            }

            return v_bool;
        }

        const bool& Value::asBool()const
        {
            if (isBool() == false)
            {
                throw std::logic_error("Value is not a Bool");
            }

            return v_bool;
        }

        std::string Value::asString()const
        {
            if (isString() == false)
            {
                throw std::logic_error("Value is not a String");
            }

            std::string result = *v_string;

            findAndReplace(result, "\\\"", "\"");
            findAndReplace(result, "\\\\","\\");

            return result;
        }

        Object& Value::asObject()
        {
            if (isObject() == false)
            {
                throw std::logic_error("Value is not a Object");
            }

            return *v_object;
        }

        const Object& Value::asObject()const
        {
            if (isObject() == false)
            {
                throw std::logic_error("Value is not a Object");
            }

            return *v_object;
        }

        Array& Value::asArray()
        {
            if (isArray() == false)
            {
                throw std::logic_error("Value is not a Array");
            }

            return *v_array;
        }

        const Array& Value::asArray()const
        {
            if (isArray() == false)
            {
                throw std::logic_error("Value is not a Array");
            }

            return *v_array;
        }

		void Value::_printIdent(std::ostream& out)const
		{
			_printIdent(out,0);
		}

        std::ostream& operator<<(std::ostream& stream, const Value& self)
        {
            switch(self._type)
            {
                case Value::TYPE_STRING:
                {
                    stream << "\"" << *self.v_string << "\"";
                }break;
                case Value::TYPE_INT:
                {
                    stream << self.v_int;
                }break;
                case Value::TYPE_FLOAT:
                {
                    stream << self.v_float;
                }break;
                case Value::TYPE_ARRAY:
                {
                    stream << *self.v_array;
                }break;
                case Value::TYPE_OBJECT:
                {
                    stream << *self.v_object;
                }break;
                case Value::TYPE_BOOL:
                {
                    stream << (self.v_bool ? "true" : "false");
                }break;
                case Value::TYPE_NULL:
                {
                    stream << "TYPE_NULL";
                }break;
                default:
                {
                    stream << "UNKNOW TYPE";
                }break;
            }
            return stream;
        }

        ///////////////////// PRIVATE //////////////////////

        Value::Value(std::string* v) : v_string(v), _type(TYPE_STRING)
        {
            _escape();
        }

        Value::Value(Array* v) : v_array(v), _type(TYPE_ARRAY)
        {
        }

        Value::Value(Object* v) : v_object(v), _type(TYPE_OBJECT)
        {
        }

        void Value::_printIdent(std::ostream& stream, int i)const
        {
            switch(_type)
            {
                case Value::TYPE_STRING:
                {
                    stream << "\"" << *v_string << "\"";
                }break;
                case Value::TYPE_INT:
                {
                    stream << v_int;
                }break;
                case Value::TYPE_FLOAT:
                {
                    stream << v_float;
                }break;
                case Value::TYPE_ARRAY:
                {
                    v_array->_printIdent(stream, i);
                }break;
                case Value::TYPE_OBJECT:
                {
                    v_object->_printIdent(stream, i);
                }break;
                case Value::TYPE_BOOL:
                {
                    stream << (v_bool ? "true" : "false");
                }break;
                case Value::TYPE_NULL:
                {
                    stream << "null";
                }break;
                default:
                {
                    stream << "UNKNOW TYPE";
                }break;
            }
        }

		void Value::_reset()
		{
			switch(_type)
            {
                case Value::TYPE_STRING:
                {
                    delete v_string;
                    v_string = NULL;
                }break;
                case Value::TYPE_ARRAY:
                {
                    delete v_array;
                    v_array = NULL;
                }break;
                case Value::TYPE_OBJECT:
                {
                    delete v_object;
                    v_object = NULL;
                }break;
                default:
                {
                    break;
                }
            }
            _type = TYPE_NULL;
		}

        void Value::_escape()
        {
            findAndReplace(*v_string, "\\", "\\\\");
            findAndReplace(*v_string,"\"","\\\"");
        }
    }
}
