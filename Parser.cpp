#include "Parser.h"

#include <stdexcept>

#include "Error/SyntaxError.h"

std::string test = "FNSOFDSOKF";

Parser::Parser() : command_(test), tokens_(), currentToken_() {}

Parser::Parser(const std::string& command, std::list<Token>&& tokens) : command_(command), tokens_(std::move(tokens)), currentToken_() {
    if (!tokens_.empty()) {
        currentToken_ = std::move(*tokens_.begin());
        tokens_.pop_front();
    }
}

void Parser::nextToken() {
    if (tokens_.empty())
        currentToken_ = Token();
    else {
        currentToken_ = std::move(*tokens_.begin());
        tokens_.pop_front();
    }
}

void Parser::accept(Token::Type expected) {
    if (currentToken_.type() == expected)
        nextToken();
    else
        throw SyntaxError(command_, currentToken_.sourceLocation(), expected, currentToken_.type());
}

void Parser::acceptIt() {
    nextToken();
}

Command* Parser::parseSequence() {
    Command* currentResult = nullptr;
    do {
        if (currentToken_.type() == Token::SEMICOLON)
            acceptIt();

        Command* newResult = parseCommand();

        if (currentResult == nullptr)
            currentResult = newResult;
        else
            currentResult = new Sequence(currentResult->sourceLocation, currentResult, newResult);
            
    } while (currentToken_.type() == Token::SEMICOLON);

    return currentResult;
}

Command* Parser::parseCommand() {
    size_t sourceLocation = currentToken_.sourceLocation();
    switch (currentToken_.type()) {

        case Token::SKIP: {
            acceptIt();
            return new Skip(sourceLocation);
        }
    
        case Token::VARNAME: {
            std::string varname = std::move(currentToken_.moveSpelling());
            acceptIt();
            accept(Token::ASSIGN);
            ArithmeticExpression* val = parseArithmeticExpression();
            return new Assignment(sourceLocation, std::move(varname), val);
        }

        case Token::IF: {
            acceptIt();
            BoolExpression* cond = parseBoolExpression();

            Command* ifCom = parseSingleOrCompoundStatement();

            Command* elseCom = nullptr;
            if (currentToken_.type() == Token::ELSE) {
                acceptIt();
                elseCom = parseSingleOrCompoundStatement();
            }

            return new IfStatement(sourceLocation, cond, ifCom, elseCom);
        }

        case Token::DO: {
            acceptIt();
            Command* loopBody = parseSingleOrCompoundStatement();
            accept(Token::WHILE);
            BoolExpression* cond = parseBoolExpression();
            return new DoWhileLoop(sourceLocation, cond, loopBody);
        }

        case Token::FOR: {
            acceptIt();
            accept(Token::LBRACKET);
            Command* initExpr = parseCommand();
            accept(Token::SEMICOLON);
            BoolExpression* cond = parseBoolExpression();
            accept(Token::SEMICOLON);
            Command* incrExpr = parseCommand();
            accept(Token::RBRACKET);

            Command* loopBody = parseSingleOrCompoundStatement();
            return new ForLoop(sourceLocation, initExpr, cond, incrExpr, loopBody);
        }

        case Token::WHILE: {
            acceptIt();
            BoolExpression* cond = parseBoolExpression();
            Command* loopBody = parseSingleOrCompoundStatement();
            return new WhileLoop(sourceLocation, cond, loopBody);
        }

        case Token::PRINT: {
            acceptIt();
            accept(Token::LBRACKET);
            ArithmeticExpression* toPrint = parseArithmeticExpression();
            accept(Token::RBRACKET);
            return new PrintStatement(sourceLocation, toPrint);
        }

        default:
            throw SyntaxError(command_, currentToken_.sourceLocation(), {Token::VARNAME, Token::IF, Token::WHILE, Token::PRINT}, currentToken_.type());
    }
}

Command* Parser::parseSingleOrCompoundStatement() {
    if (currentToken_.type() == Token::LBRACE) {
        acceptIt();
        Command* seq = parseSequence();
        accept(Token::RBRACE);
        return seq;
    } else 
        return parseCommand();
}


ArithmeticExpression* Parser::parseArithmeticExpression() {
    size_t sourceLocation = currentToken_.sourceLocation();
    switch (currentToken_.type()) {
        case Token::NUM: {
            int value = atoi(currentToken_.spelling().c_str());
            acceptIt();
            return new NumericLiteral(sourceLocation, value);
        }

        case Token::VARNAME: {
            std::string varname = std::move(currentToken_.moveSpelling());
            acceptIt();
            return new VariableRef(sourceLocation, std::move(varname));
        }
        
        case Token::LBRACKET: {
            acceptIt();
            ArithmeticExpression* left = parseArithmeticExpression();
            ABinaryOperation::ArithOp op;
            switch (currentToken_.type()) {
                case Token::ADD:
                    acceptIt();
                    op = ABinaryOperation::ADD;
                    break;

                case Token::SUB:
                    acceptIt();
                    op = ABinaryOperation::SUB;
                    break;

                case Token::MUL:
                    acceptIt();
                    op = ABinaryOperation::MUL;
                    break;
                
                case Token::DIV:
                    acceptIt();
                    op = ABinaryOperation::DIV;
                    break;

                default:
                    throw SyntaxError(command_, currentToken_.sourceLocation(), {Token::ADD, Token::SUB, Token::MUL, Token::DIV}, currentToken_.type());
            }
            ArithmeticExpression* right = parseArithmeticExpression();
            accept(Token::RBRACKET);
            return new ABinaryOperation(sourceLocation, left, right, op);
        }
        
        default:
            throw SyntaxError(command_, currentToken_.sourceLocation(), {Token::NUM, Token::VARNAME, Token::LBRACKET}, currentToken_.type());
            break;

    }
}

BoolExpression* Parser::parseBoolExpression() {
    size_t sourceLocation = currentToken_.sourceLocation();
    switch (currentToken_.type()) {
        case Token::TRUE:
            acceptIt();
            return new BoolLiteral(sourceLocation, true);

        case Token::FALSE:
            acceptIt();
            return new BoolLiteral(sourceLocation, false);
        
        case Token::NOT:
            acceptIt();
            return new Negation(sourceLocation, parseBoolExpression());

        case Token::LBRACKET:
            acceptIt();
            if (nextIsLogicalOp()) {
                BoolExpression* left = parseBoolExpression();
                BBinaryOperation::LogOp op;
                if (currentToken_.type() == Token::AND) {
                    acceptIt();
                    op = BBinaryOperation::AND;
                } else {
                    accept(Token::OR);
                    op = BBinaryOperation::OR;
                }
                BoolExpression* right = parseBoolExpression();
                accept(Token::RBRACKET);
                return new BBinaryOperation(sourceLocation, left, right, op);
            } else {
                ArithmeticExpression* left = parseArithmeticExpression();
                Comparision::CompOp op;
                if (currentToken_.type() == Token::EQ) {
                    acceptIt();
                    op = Comparision::EQ;
                } else {
                    accept(Token::LEQ);
                    op = Comparision::LEQ;
                }
                ArithmeticExpression* right = parseArithmeticExpression();
                accept(Token::RBRACKET);
                return new Comparision(sourceLocation, left, right, op);
            }

        default:
            throw SyntaxError(command_, currentToken_.sourceLocation(), {Token::TRUE, Token::FALSE, Token::NOT, Token::LBRACKET}, currentToken_.type());
    }
}

// Determines whether the current bracket was for a logical operator or a comparision when parsing a BoolExpression
bool Parser::nextIsLogicalOp() const {
    // Catch case where there are no brackets
    if (currentToken_.type() == Token::TRUE || currentToken_.type() == Token::FALSE)
        return true;
    else if (currentToken_.type() == Token::VARNAME || currentToken_.type() == Token::NUM)
        return false;

    int openingBracketCount = 1; // currentToken_.type() must be LBRACKET
    size_t lastOpenedBracket = -1;

    auto it = tokens_.begin();

    while (it != tokens_.end() && it->type() != Token::RBRACKET) {
        if (it->type() == Token::LBRACKET) {
            lastOpenedBracket = it->sourceLocation();
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
            throw SyntaxError(command_, it->sourceLocation(), {Token::AND, Token::OR, Token::EQ, Token::LEQ}, it->type());
    } else 
        throw InterpreterError(command_, lastOpenedBracket, "Opening Bracket has no corresponding closing bracket");
}