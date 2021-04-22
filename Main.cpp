#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>

#include "Tokenizer.h"
#include "Parser.h"
#include "Visitor.h"

#include "Error/InterpreterError.h"

int main(int argc, char** argv) {
    if (argc > 1) {
        std::ifstream stream(argv[1]);
        std::string command;

        State state;
        int line_count = 1;
        while (std::getline(stream, command)) {
            std::list<Token> tokens = tokenize(command);
            Parser parser(command, std::move(tokens));
            try {
                std::unique_ptr<Statement> com(parser.parse_sequence());
                Visitor visitor(command, state);
                com->visit(visitor);
                com->execute(state);
            } catch (InterpreterError& err) {
                std::cerr << "Error on line " << line_count << "\n";
                std::cerr << err.what() << "\n";
                break;
            }
            ++line_count;
        }
    }
    else {
        State state;
        while (true) {
            std::cout << "> ";
            std::string command;
            std::getline(std::cin, command);

            if (!command.empty()) {
                std::list<Token> tokens = tokenize(command);
                Parser parser(command, std::move(tokens));
                try {
                    std::unique_ptr<Statement> com(parser.parse_sequence());
                    Visitor visitor(command, state);
                    com->visit(visitor);
                    com->execute(state);
                } catch (InterpreterError& err) {
                    std::cerr << err.what() << "\n";
                }
            }
        }
    }
}