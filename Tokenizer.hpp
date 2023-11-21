#pragma once

#include "Parser.hpp"
#include <iostream>

namespace parser
{
    enum class TokenType
    {
        WHITESPACE,
        IDENTIFIER,
        TYPE,
        INTEGER_LITERAL,
        STRING_LITERAL,
        POTENTIAL_DOUBLE,
        DOUBLE_LITERAL,
        OPERATOR,
        ESCAPE_SEQUENCE,
        POTENTIAL_COMMENT,
        COMMENT
    };

    static const char* tokenTypeStrings[] = {
        "WHITESPACE",
        "IDENTIFIER",
        "TYPE",
        "INTEGER_LITERAL",
        "STRING_LITERAL",
        "POTENTIAL_DOUBLE",
        "DOUBLE_LITERAL",
        "OPERATOR",
        "ESCAPE_SEQUENCE",
        "POTENTIAL_COMMENT",
        "COMMENT" 
    };

    struct Token
    {
    public:
        TokenType m_TokenType;
        std::string m_Data;
        std::size_t m_LineNumber{ 0 };
        std::size_t m_CharNumber{ 0 };

    public:
        void DebugPrint();
        Token() = default;
    };

    class Tokenizer
    {
    private:
        void EndToken(Token& token, std::vector<Token>& tokens);

    public:
        std::vector<Token> Tokenize(const std::string& inProgram);
    };
}