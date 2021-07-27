#include "Tokenizer.h"

#include <stdexcept>
#include <map>
#include <cctype>

// Maps reserved words to Token type
const std::map<std::string, Token::Type> reserved_words = {
    {"true", Token::TRUE},
    {"false", Token::FALSE},
    {"else", Token::ELSE},
    {"<=", Token::LEQ},
    {"<", Token::LT},
    {">=", Token::GEQ},
    {"<=", Token::GT},
    {"not", Token::NOT},
    {"and", Token::AND},
    {"&&", Token::AND},
    {"or", Token::OR},
    {"||", Token::OR},
    {"skip", Token::SKIP},
    {"if", Token::IF},
    {"do", Token::DO},
    {"while", Token::WHILE},
    {"for", Token::FOR},
    {"print", Token::PRINT},
    {"input", Token::INPUT}
};

Token parse_multi_char_token(const std::string& text, size_t start);

std::list<Token> tokenize(const std::string& text) {
    std::list<Token> result;
    size_t i = 0;
    size_t size = text.size();
    bool no_incr = false;
    while (i < size) {
        switch (text[i]) {
            case ' ': {
                while (i + 1 < size && text[i + 1] == ' ')
                    ++i;
                break;
            }
            case '(': {
                result.emplace_back("(", Token::LBRACKET, i);
                break;
            }
            case ')': {
                result.emplace_back(")", Token::RBRACKET, i);
                break;
            }
            case '+': {
                result.emplace_back("+", Token::ADD, i);
                break;
            }
            case '-': {
                result.emplace_back("-", Token::SUB, i);
                break;
            }
            case '*': {
                result.emplace_back("*", Token::MUL, i);
                break;
            }
            case '/': {
                result.emplace_back("/", Token::DIV, i);
                break;
            }
            case '!': {
                if (i + 1 < text.size() && text[i + 1] == '=') {
                    result.emplace_back("!=", Token::NEQ, i);
                    ++i;
                } else {
                    result.emplace_back("!", Token::NOT, i);
                }
                break;
            }
            case ';': {
                result.emplace_back(";", Token::SEMICOLON, i);
                break;
            }
            case '{': {
                result.emplace_back("{", Token::LBRACE, i);
                break;
            }
            case '}': {
                result.emplace_back("}", Token::RBRACE, i);
                break;
            }
            case '=': {
                if (i + 1 < text.size() && text[i + 1] == '=') {
                    result.emplace_back("==", Token::EQ, i);
                    ++i;
                } else
                    result.emplace_back("=", Token::ASSIGN, i);
                break;
            }
            default: {
                Token token = parse_multi_char_token(text, i);
                i += token.spelling().size();
                result.push_back(std::move(token));
                no_incr = true;
                break;
            }
        }

        if (no_incr)
            no_incr = false;
        else
            ++i;
    }

    return result;
}

bool all_digits(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c))
            return false;
    }
    return true;
}  

bool is_single_char_token(char c) {
    return c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == ';' || c == ':' || c == ' ';
}

Token parse_multi_char_token(const std::string& text, size_t start) {
    size_t end = start;
    while (end < text.size() && !is_single_char_token(text[end]))
        ++end;

    std::string spelling = text.substr(start, end - start);

    Token::Type type;
    if (reserved_words.count(spelling) != 0)
        type = reserved_words.at(spelling);
    else if (all_digits(spelling))
        type = Token::NUM;
    else
        type = Token::VARNAME; // TODO: Better name checking for varnames

    return Token(std::move(spelling), type, start);
}