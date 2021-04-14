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
        int lineCount = 1;
        while (std::getline(stream, command)) {
            std::list<Token> tokens = tokenize(command);
            Parser parser(command, std::move(tokens));
            try {
                std::unique_ptr<Statement> com(parser.parseSequence());
                Visitor visitor(command, state);
                com->visit(visitor);
                com->execute(state);
            } catch (InterpreterError& err) {
                std::cerr << "Error on line " << lineCount << "\n";
                std::cerr << err.what() << "\n";
                break;
            }
            ++lineCount;
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
                    std::unique_ptr<Statement> com(parser.parseSequence());
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