#include <fstream>
#include <sstream>
#include "Parser.hpp"

using namespace parser;

int main()
{
    std::cout << std::endl << std::endl;

    std::stringstream stream;
    std::fstream file = std::fstream("Test.mh", std::ios::in);
    stream << file.rdbuf();
    std::string contents = stream.str();

    std::cout << contents << std::endl << std::endl;
    std::cout << "-----------------------------------------------" << std::endl << std::endl;

    Tokenizer tokenizer = Tokenizer();
    auto tokens = tokenizer.Tokenize(contents);

    for (auto token : tokens)
        token.DebugPrint();

    std::cout << std::endl << std::endl;
    std::cout << "-----------------------------------------------" << std::endl << std::endl;

    Parser parser = Parser();
    parser.Parse(tokens);

    std::cout << std::endl << std::endl;

    return EXIT_SUCCESS;
}