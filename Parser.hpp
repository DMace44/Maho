#pragma once

#include "Tokenizer.hpp"
#include "Type.hpp"
#include <optional>

namespace parser
{
    std::map<std::string, Type> typeTable{};

    class Parser
    {
    private:
        std::vector<Token>::iterator m_currentToken{};
        std::vector<Token>::iterator m_endToken{};
    private:
        //std::optional<Token> ExpectTypeDeclaration(const std::string& name = std::string());
        std::optional<Token> ExpectOperator(const std::string& name = std::string());
        std::optional<Token> ExpectIdentifier(const std::string& name = std::string());
    public:
        Parser();
        void Parse(std::vector<Token>& tokens);
        static std::optional<Type> GetType(const std::string& name)
        {
            return typeTable[name];
        }
    };
}