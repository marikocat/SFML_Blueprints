#include <utils/json/Scanner.hpp>
#include <utils/log.hpp>

namespace utils
{
    namespace json
    {
        Scanner::Scanner(std::istream& in) : UtilsJsonFlexLexer(&in), yylval(nullptr)
        {
        }

        int Scanner::yylex(utils::json::Parser::semantic_type *lval)
        {
            yylval = lval;
            int result = this->yylex();
            return result;
        }

    }
}
