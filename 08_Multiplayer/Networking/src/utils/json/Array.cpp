#include <utils/json/Array.hpp>

namespace utils
{
    namespace json
    {
        Array::Array()
        {
        }

        std::ostream& operator<<(std::ostream& stream, const Array& self)
        {
            self._printIdent(stream,0);
            return stream;
        }

        void Array::_printIdent(std::ostream& stream, int i)const
        {
            stream<<"[";
            if(_values.size()>0)
            {
                std::list<Value>::const_iterator begin = _values.begin();
                std::list<Value>::const_iterator end = _values.end();
                begin->_printIdent(stream,i);
                ++begin;
                while(begin!=end)
                {
                    stream<<",";
                    begin->_printIdent(stream,i);
                    ++begin;
                }
            }
            stream<<"]";
        }

        std::list<Value>::const_iterator Array::begin() const
        {
            return _values.begin();
        }

        std::list<Value>::const_iterator Array::end() const
        {
            return _values.end();
        }

        std::list<Value>::iterator Array::begin()
        {
            return _values.begin();
        }

        std::list<Value>::iterator Array::end()
        {
            return _values.end();
        }

        size_t Array::size()const
        {
            return _values.size();
        }

        std::list<Value>& Array::data()
        {
            return _values;
        }

        const std::list<Value>& Array::data() const
        {
            return _values;
        }

    }
}
