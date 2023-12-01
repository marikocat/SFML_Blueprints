%{
    /* Implementation of yyFlexScanner */
    #include <utils/json/Scanner.hpp>
    #include <utils/log.hpp>

    /* typedef to make the returns for the tokens shorter */
    typedef utils::json::Parser::token token;
    int json_line_no = 1;
    std::string json_buffer;

    /* define yyterminate as this instead of NULL */
    //#define yyterminate() return token::T_END;

    /* msvc2010 requires that we exclude this header file. */
    #define YY_NO_UNISTD_H
%}

%option c++
%option yyclass="Scanner"
%option nodefault
%option noyywrap
%option prefix="UtilsJson"
%option debug
%x STRING_BEGIN

%%

\n {
    ++json_line_no;
    //return token::T_EOL;
}

"[" {
    return token::T_SQUARE_BRACKET_L;
}

"]" {
    return token::T_SQUARE_BRACKET_R;
}

"{" {
    return token::T_CURLY_BRACKET_L;
}

"}" {
    return token::T_CURLY_BRACKET_R;
}

"," {
    return token::T_COMMA;
}

":" {
    return token::T_COLON;
}

[ \t]  {
}

[-+]?[0-9]+  {
    yylval->v_int = ::atoi(yytext);
    return token::T_NUMBER_I;
}

[-+]?[0-9]*\.?[0-9]*([eE][-+]?[0-9]+)?  {
    yylval->v_float = atof(yytext);
    return token::T_NUMBER_F;
}

true {
    yylval->v_bool = true;
    return token::T_BOOLEAN;
}
false {
    yylval->v_bool = false;
    return token::T_BOOLEAN;
}

null {
    return token::T_NULL;
}

\" {
	json_buffer.clear();
	BEGIN STRING_BEGIN;
}

<STRING_BEGIN>\" {
	yylval->v_string = new std::string(json_buffer);
	BEGIN 0;
	return token::T_DOUBLE_QUOTED_STRING;
}

<STRING_BEGIN>\\\" {
	json_buffer.push_back('"');
}

<STRING_BEGIN>\\\\ {
	json_buffer.push_back('\\');
}

<STRING_BEGIN>\\\/ {
	json_buffer.push_back('/');
}

<STRING_BEGIN>\\b {
	json_buffer.push_back('\b');
}

<STRING_BEGIN>\\f {
	json_buffer.push_back('\f');
}

<STRING_BEGIN>\\n {
	json_buffer.push_back('\n');
}

<STRING_BEGIN>\\r {
	json_buffer.push_back('\r');
}

<STRING_BEGIN>\\t {
	json_buffer.push_back('\t');
}

<STRING_BEGIN>\\u[a-fA-F0-9][a-fA-F0-9][a-fA-F0-9][a-fA-F0-9] {
	//TODO NOT SUPPORTED
}

<STRING_BEGIN>[^\"] { 
	json_buffer.push_back(yytext[0]);
}

. {
    utils::log::error("JSON Parser","line",json_line_no,": what is that <",yytext,"> ?");
}

