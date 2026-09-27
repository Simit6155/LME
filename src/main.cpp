#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <cctype>

#include "generation.h"
#include "parser.h"
#include "tokenization.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Incorrect usage. Correct usage is..." << std::endl;
        std::cerr << "Luna <input.lme>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents;

    {
        std::stringstream contents_stream;

        std::fstream input(argv[1], std::ios::in);

        if (!input) {
            std::cerr << "Could not open input file: "
                      << argv[1] << std::endl;
            return EXIT_FAILURE;
        }

        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(std::move(tokens));
    std::optional<node::NodeExit> tree = parser.parse();

    if (!tree.has_value()) {
        std::cerr << "No exit statement found" << std::endl;
        return EXIT_FAILURE;
    }

    {
        std::fstream file("out.asm", std::ios::out);

        if (!file) {
            std::cerr << "Could not create out.asm" << std::endl;
            return EXIT_FAILURE;
        }

        Generator generator(tree.value());
        file << generator.generate();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}
