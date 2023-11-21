#pragma once

#include "Type.hpp"
#include "Tokenizer.hpp"
#include <optional>

namespace parser
{
    static std::map<const std::string, Type> typeTable;

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
        void Parse(std::vector<Token>& tokens);
        static bool ContainsType(const std::string& name)
        {
            typeTable["int"] = Type("Integer32", TypeDeclaration::STRUCTURE);
            typeTable["string"] = Type("String", TypeDeclaration::CLASS);
            typeTable["Console"] = Type("Console", TypeDeclaration::CLASS);
            return typeTable.find(name) != typeTable.end();
        }
    };
}