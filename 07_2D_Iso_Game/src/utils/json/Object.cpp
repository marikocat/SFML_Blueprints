#include "utils/json/Object.hpp"
//#include <utils/json/Value.hpp>
#include <stdexcept>


namespace utils
{
    namespace json
    {

        Object::Object()
        {
        }

        std::ostream& operator<<(std::ostream& stream, const Object& self)
        {
            self._printIdent(stream,0);
            return stream;
        }

        void Object::_printIdent(std::ostream& stream, int i)const
        {
            /*if(i >0)
                stream<<"\n";
            ident(stream,i);*/
            stream<<"{\n";
            ++i;

            if(_values.size()>0)
            {
                auto begin = _values.begin();
                auto end = _values.end();

                _ident(stream,i);
                stream<<"\""<<begin->first<<"\" : ";
                begin->second._printIdent(stream,i);

                ++begin;
                while(begin!=end)
                {
                    stream<<",\n";
                    _ident(stream,i);
                    stream<<"\""<<begin->first<<"\" : ";
                    begin->second._printIdent(stream,i);
                    ++begin;
                }
            }
            --i;
            stream<<"\n";
            _ident(stream,i);
            stream<<"}";
        }

        Value& Object::operator[] (const std::string& key)
        {
            return _values[key];
        }

        const Value& Object::operator[] (const std::string& key) const
        {
           auto it = _values.find(key);
			if(it != _values.end())
			{
				return it->second;
            }

			throw std::out_of_range(std::string("Index '")+key+"' is out of range");
        }

        int Object::count(const std::string& key) const
        {
            return _values.count(key);
        }

        std::unordered_map<std::string, Value>::const_iterator Object::begin() const
        {
            return _values.begin();
        }

        std::unordered_map<std::string, Value>::const_iterator Object::end() const
        {
            return _values.end();
        }

        std::unordered_map<std::string, Value>::iterator Object::begin()
        {
            return _values.begin();
        }

        std::unordered_map<std::string, Value>::iterator Object::end()
        {
            return _values.end();
        }

        size_t Object::size() const
        {
            return _values.size();
        }

        void Object::merge(const Object& other, bool recursive, bool replace_old)
        {
            for (const auto& val : other._values)
            {
                auto it = this->_values.find(val.first);
                if (it != this->_values.end()) //has key
                {
                    if (replace_old) //replace existing value
                    {
                        if (recursive && it->second.isObject() && val.second.isObject()) //merge if both are object
                        {
                            it->second.asObject().merge(val.second.asObject(), recursive, replace_old);
                        }
                        else //else change value
                        {
                            it->second = val.second;
                        }
                    }
                }
                else //add value
                {
                    this->_values.insert(val);
                }
            }
        }


        void Object::_ident(std::ostream& out,int max)
        {
            for(int i=0;i<max;++i)
                out<<"    ";
        }

    }
}
