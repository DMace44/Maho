#include "Parser.hpp"
#include "Tokenizer.hpp"

namespace parser
{
    std::optional<Token> Parser::ExpectOperator(const std::string& name)
    {
        auto returnToken = m_currentToken;
        ++m_currentToken;

        if (returnToken == m_endToken)
            return std::nullopt;

        if (returnToken->m_TokenType != TokenType::OPERATOR)
            return std::nullopt;

        if (!name.empty() && returnToken->m_Data != name)
            return std::nullopt;

        return *returnToken;
    }

    std::optional<Token> Parser::ExpectIdentifier(const std::string& name)
    {
        auto returnToken = m_currentToken;
        ++m_currentToken;

        if (returnToken == m_endToken)
            return std::nullopt;

        if (returnToken->m_TokenType != TokenType::IDENTIFIER)
            return std::nullopt;

        if (!name.empty() && returnToken->m_Data != name)
            return std::nullopt;

        return *returnToken;
    }

    void Parser::Parse(std::vector<Token>& tokens)
    {
        m_currentToken = tokens.begin();
        m_endToken = tokens.end();

        while (m_currentToken != m_endToken)
        {
            auto possibleType = ExpectIdentifier();

            if (possibleType.has_value())
            {
                auto possibleName = ExpectIdentifier();

                if (possibleName.has_value())
                {
                    auto possibleOperator = ExpectOperator("(");

                    if (possibleOperator.has_value())
                    {
                        std::cout << "A Function! : " << possibleType->m_Data << " " << possibleName->m_Data << std::endl;
                        exit(EXIT_SUCCESS);
                    }
                }
            }
        }
    }

    
    Parser::Parser()
    {
        typeTable["int"] = Type("Integer32", TypeDeclaration::STRUCTURE);
        typeTable["string"] = Type("String", TypeDeclaration::CLASS);
    }
}