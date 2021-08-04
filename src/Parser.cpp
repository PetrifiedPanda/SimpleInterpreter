#include "Parser.h"

#include <stdexcept>

#include "Error/SyntaxError.h"

Parser::Parser(const std::string& command, std::list<Token>&& tokens) : command_{command}, tokens_{std::move(tokens)}, current_token_{} {
    if (!tokens_.empty()) {
        current_token_ = std::move(*tokens_.begin());
        tokens_.pop_front();
    }
}

void Parser::next_token() {
    if (tokens_.empty())
        current_token_ = Token();
    else {
        current_token_ = std::move(*tokens_.begin());
        tokens_.pop_front();
    }
}

void Parser::accept(Token::Type expected) {
    if (current_token_.type() == expected)
        next_token();
    else
        throw SyntaxError(command_, current_token_.source_location(), expected, current_token_.type());
}

void Parser::accept_it() {
    next_token();
}

Statement* Parser::parse_sequence() {
    Statement* currentResult = nullptr;
    do {
        if (current_token_.type() == Token::SEMICOLON)
            accept_it();

        Statement* newResult = parse_command();

        if (currentResult == nullptr)
            currentResult = newResult;
        else
            currentResult = new Sequence(currentResult->source_location, currentResult, newResult);
            
    } while (current_token_.type() == Token::SEMICOLON);

    return currentResult;
}

Statement* Parser::parse_command() {
    size_t source_location = current_token_.source_location();
    switch (current_token_.type()) {

        case Token::SKIP: {
            accept_it();
            return new Skip(source_location);
        }
    
        case Token::VARNAME: {
            std::string varname = std::move(current_token_.move_spelling());
            accept_it();
            accept(Token::ASSIGN);
            ArithmeticExpression* val = parse_arithmetic_expression();
            return new Assignment(source_location, std::move(varname), val);
        }

        case Token::IF: {
            accept_it();
            BoolExpression* cond = parse_bool_expression();

            Statement* if_com = parse_single_or_compound_statement();

            Statement* else_com = nullptr;
            if (current_token_.type() == Token::ELSE) {
                accept_it();
                else_com = parse_single_or_compound_statement();
            }

            return new IfStatement(source_location, cond, if_com, else_com);
        }

        case Token::DO: {
            accept_it();
            Statement* loop_body = parse_single_or_compound_statement();
            accept(Token::WHILE);
            BoolExpression* cond = parse_bool_expression();
            return new DoWhileLoop(source_location, cond, loop_body);
        }

        case Token::FOR: {
            accept_it();
            accept(Token::LBRACKET);
            Statement* init_expr = parse_command();
            accept(Token::SEMICOLON);
            BoolExpression* cond = parse_bool_expression();
            accept(Token::SEMICOLON);
            Statement* incrExpr = parse_command();
            accept(Token::RBRACKET);

            Statement* loop_body = parse_single_or_compound_statement();
            return new ForLoop(source_location, init_expr, cond, incrExpr, loop_body);
        }

        case Token::WHILE: {
            accept_it();
            BoolExpression* cond = parse_bool_expression();
            Statement* loop_body = parse_single_or_compound_statement();
            return new WhileLoop(source_location, cond, loop_body);
        }

        case Token::PRINT: {
            accept_it();
            accept(Token::LBRACKET);
            ArithmeticExpression* to_print = parse_arithmetic_expression();
            accept(Token::RBRACKET);
            return new PrintStatement(source_location, to_print);
        }

        default:
            throw SyntaxError(command_, current_token_.source_location(), {Token::VARNAME, Token::IF, Token::WHILE, Token::PRINT}, current_token_.type());
    }
}

Statement* Parser::parse_single_or_compound_statement() {
    if (current_token_.type() == Token::LBRACE) {
        accept_it();
        Statement* seq = parse_sequence();
        accept(Token::RBRACE);
        return seq;
    } else 
        return parse_command();
}


ArithmeticExpression* Parser::parse_arithmetic_expression() {
    size_t source_location = current_token_.source_location();
    switch (current_token_.type()) {
        case Token::NUM: {
            int value = atoi(current_token_.spelling().c_str());
            accept_it();
            return new NumericLiteral(source_location, value);
        }

        case Token::VARNAME: {
            std::string varname = std::move(current_token_.move_spelling());
            accept_it();
            return new VariableRef(source_location, std::move(varname));
        }
        
        case Token::LBRACKET: {
            accept_it();
            ArithmeticExpression* left = parse_arithmetic_expression();
            ABinaryOperation::ArithOp op;
            switch (current_token_.type()) {
                case Token::ADD:
                    accept_it();
                    op = ABinaryOperation::ADD;
                    break;

                case Token::SUB:
                    accept_it();
                    op = ABinaryOperation::SUB;
                    break;

                case Token::MUL:
                    accept_it();
                    op = ABinaryOperation::MUL;
                    break;
                
                case Token::DIV:
                    accept_it();
                    op = ABinaryOperation::DIV;
                    break;

                default:
                    throw SyntaxError(command_, current_token_.source_location(), {Token::ADD, Token::SUB, Token::MUL, Token::DIV}, current_token_.type());
            }
            ArithmeticExpression* right = parse_arithmetic_expression();
            accept(Token::RBRACKET);
            return new ABinaryOperation(source_location, left, right, op);
        }

        case Token::INPUT: {
            accept_it();
            accept(Token::LBRACKET);
            accept(Token::RBRACKET);
            return new InputCommand(source_location);
        }
        
        default:
            throw SyntaxError(command_, current_token_.source_location(), {Token::NUM, Token::VARNAME, Token::LBRACKET}, current_token_.type());
            break;

    }
}

BoolExpression* Parser::parse_bool_expression() {
    size_t source_location = current_token_.source_location();
    switch (current_token_.type()) {
        case Token::TRUE:
            accept_it();
            return new BoolLiteral(source_location, true);

        case Token::FALSE:
            accept_it();
            return new BoolLiteral(source_location, false);
        
        case Token::NOT:
            accept_it();
            return new Negation(source_location, parse_bool_expression());

        case Token::LBRACKET:
            accept_it();
            if (next_is_logical_op()) {
                BoolExpression* left = parse_bool_expression();
                BBinaryOperation::LogOp op;
                if (current_token_.type() == Token::AND) {
                    accept_it();
                    op = BBinaryOperation::AND;
                } else {
                    accept(Token::OR);
                    op = BBinaryOperation::OR;
                }
                BoolExpression* right = parse_bool_expression();
                accept(Token::RBRACKET);
                return new BBinaryOperation(source_location, left, right, op);
            } else {
                ArithmeticExpression* left = parse_arithmetic_expression();
                Comparision::CompOp op;
                switch (current_token_.type()) {
                    case Token::EQ: {
                        accept_it();
                        op = Comparision::EQ;
                        break;
                    } 
                    case Token::NEQ: {
                        accept_it();
                        op = Comparision::NEQ;
                        break;
                    } 
                    case Token::LEQ: {
                        accept_it();
                        op = Comparision::LEQ;
                        break;
                    } 
                    case Token::LT: {
                        accept_it();
                        op = Comparision::LT;
                        break;
                    } 
                    case Token::GEQ: {
                        accept_it();
                        op = Comparision::GEQ;
                        break;
                    } 
                    case Token::GT: {
                        accept_it();
                        op = Comparision::GT;
                        break;
                    }
                    default:
                        throw SyntaxError(command_, current_token_.source_location(), {Token::EQ, Token::NEQ, Token::LEQ, Token::LT, Token::GEQ, Token::GT}, current_token_.type());
                }
                ArithmeticExpression* right = parse_arithmetic_expression();
                accept(Token::RBRACKET);
                return new Comparision(source_location, left, right, op);
            }

        default:
            throw SyntaxError(command_, current_token_.source_location(), {Token::TRUE, Token::FALSE, Token::NOT, Token::LBRACKET}, current_token_.type());
    }
}

// Determines whether the current bracket was for a logical operator or a comparision when parsing a BoolExpression
bool Parser::next_is_logical_op() const {
    // Catch case where there are no brackets
    if (current_token_.type() == Token::TRUE || current_token_.type() == Token::FALSE)
        return true;
    else if (current_token_.type() == Token::VARNAME || current_token_.type() == Token::NUM)
        return false;

    int openingBracketCount = 1; // current_token_.type() must be LBRACKET
    size_t lastOpenedBracket = -1;

    auto it = tokens_.begin();

    while (it != tokens_.end() && it->type() != Token::RBRACKET) {
        if (it->type() == Token::LBRACKET) {
            lastOpenedBracket = it->source_location();
            ++openingBracketCount;
        }

        ++it;
    }

    while (it != tokens_.end() && openingBracketCount != 0) {
        if (it->type() == Token::RBRACKET)
            --openingBracketCount;

        ++it;
    }

    if (openingBracketCount == 0) {
        if (it->type() == Token::AND || it->type() == Token::OR)
            return true;
        else if (it->type() == Token::EQ || it->type() == Token::LEQ)
            return false;
        else
            throw SyntaxError(command_, it->source_location(), {Token::AND, Token::OR, Token::EQ, Token::LEQ}, it->type());
    } else 
        throw InterpreterError(command_, lastOpenedBracket, "Opening Bracket has no corresponding closing bracket");
}