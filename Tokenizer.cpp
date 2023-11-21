#include "Parser.hpp"

namespace parser
{
    std::vector<Token> Tokenizer::Tokenize(const std::string& inProgram)
    {
        std::vector<Token> tokens;
        Token currentToken = Token();
        currentToken.m_TokenType = TokenType::WHITESPACE;
        currentToken.m_LineNumber = 1;
        currentToken.m_CharNumber = 0;

        for (char ch : inProgram)
        {
            ++currentToken.m_CharNumber;

            if (currentToken.m_TokenType == TokenType::ESCAPE_SEQUENCE)
            {
                switch (ch)
                {
                case 'n':
                    currentToken.m_Data.append(1, '\n');
                    break;

                case 't':
                    currentToken.m_Data.append(1, '\t');
                    break;

                case '\\':
                    currentToken.m_Data.append(1, '\\');
                    break;

                default:
                    exit(EXIT_FAILURE);
                    break;
                }

                currentToken.m_TokenType = TokenType::STRING_LITERAL;
                continue;
            }
            else if (currentToken.m_TokenType == TokenType::POTENTIAL_COMMENT && ch != '/')
            {
                currentToken.m_TokenType = TokenType::OPERATOR;
                EndToken(currentToken, tokens);
                continue;
            }

            switch (ch)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (currentToken.m_TokenType == TokenType::WHITESPACE)
                {
                    currentToken.m_TokenType = TokenType::INTEGER_LITERAL;
                    currentToken.m_Data.append(1, ch);
                }
                else
                    currentToken.m_Data.append(1, ch);
                break;

            case '.':
                if (currentToken.m_TokenType == TokenType::WHITESPACE)
                {
                    currentToken.m_TokenType = TokenType::POTENTIAL_DOUBLE;
                    currentToken.m_Data.append(1, ch);
                }
                else if (currentToken.m_TokenType == TokenType::INTEGER_LITERAL)
                {
                    currentToken.m_TokenType = TokenType::POTENTIAL_DOUBLE;
                    currentToken.m_Data.append(1, ch);
                }
                else if (currentToken.m_TokenType == TokenType::STRING_LITERAL)
                    currentToken.m_Data.append(1, ch);
                else
                {
                    EndToken(currentToken, tokens);
                    currentToken.m_TokenType = TokenType::OPERATOR;
                    currentToken.m_Data.append(1, ch);
                    EndToken(currentToken, tokens);
                }
                break;

            case '(':
            case ')':
            case '{':
            case '}':
            case '[':
            case ']':
            case '=':
            case ';':
            case ',':
            case '+':
            case '-':
            case '*':
            case '%':
            case '&':
            case '<':
            case '>':
            case '|':
                if (currentToken.m_TokenType != TokenType::STRING_LITERAL)
                {
                    EndToken(currentToken, tokens);
                    currentToken.m_TokenType = TokenType::OPERATOR;
                    currentToken.m_Data.append(1, ch);
                    EndToken(currentToken, tokens);
                }
                else
                    currentToken.m_Data.append(1, ch);
                break;

            case ' ':
            case '\t':
                if (currentToken.m_TokenType == TokenType::STRING_LITERAL || currentToken.m_TokenType == TokenType::COMMENT)
                    currentToken.m_Data.append(1, ch);
                else
                    EndToken(currentToken, tokens);
                break;

            case '\n':
                EndToken(currentToken, tokens);
                ++currentToken.m_LineNumber;
                currentToken.m_CharNumber = 0;
                break;

            case '\\':
                if (currentToken.m_TokenType == TokenType::STRING_LITERAL)
                    currentToken.m_TokenType = TokenType::ESCAPE_SEQUENCE;
                else
                {
                    EndToken(currentToken, tokens);
                    currentToken.m_TokenType = TokenType::OPERATOR;
                    currentToken.m_Data.append(1, ch);
                    EndToken(currentToken, tokens);
                }
                break;

            case '"':
                if (currentToken.m_TokenType != TokenType::STRING_LITERAL)
                {
                    EndToken(currentToken, tokens);
                    currentToken.m_TokenType = TokenType::STRING_LITERAL;
                }
                else if (currentToken.m_TokenType == TokenType::STRING_LITERAL)
                    EndToken(currentToken, tokens);
                break;

            case '/':
                if (currentToken.m_TokenType == TokenType::STRING_LITERAL)
                    currentToken.m_Data.append(1, ch);
                else if (currentToken.m_TokenType == TokenType::POTENTIAL_COMMENT)
                {
                    currentToken.m_TokenType = TokenType::COMMENT;
                    currentToken.m_Data.erase();
                }
                else
                {
                    EndToken(currentToken, tokens);
                    currentToken.m_TokenType = TokenType::POTENTIAL_COMMENT;
                    currentToken.m_Data.append(1, ch);
                }
                break;

            default:
                if (currentToken.m_TokenType == TokenType::WHITESPACE || currentToken.m_TokenType == TokenType::INTEGER_LITERAL)
                {
                    EndToken(currentToken, tokens);
                    currentToken.m_TokenType = TokenType::IDENTIFIER;
                    currentToken.m_Data.append(1, ch);
                }
                else
                    currentToken.m_Data.append(1, ch);
                break;
            }
        }

        EndToken(currentToken, tokens);

        return tokens;
    }

    void Tokenizer::EndToken(Token& token, std::vector<Token>& tokens)
    {
        if (token.m_TokenType == TokenType::COMMENT || token.m_TokenType == TokenType::WHITESPACE)
            return;
            
        if (token.m_TokenType == TokenType::IDENTIFIER && Parser::ContainsType(token.m_Data))
            token.m_TokenType = TokenType::TYPE;

        if (token.m_TokenType == TokenType::POTENTIAL_DOUBLE)
        {
            if (token.m_Data.compare(".") == 0)
                token.m_TokenType = TokenType::OPERATOR;
            else
                token.m_TokenType = TokenType::DOUBLE_LITERAL;
        }

        tokens.push_back(token);

        token.m_TokenType = TokenType::WHITESPACE;
        token.m_Data.clear();
    }

    void Token::DebugPrint()
    {
        std::cout << "Token(" << tokenTypeStrings[(int)m_TokenType] << ", \"" << m_Data << "\" ln: " << m_LineNumber << ", " << m_CharNumber << ")" << std::endl;
    }
}