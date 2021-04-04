#pragma once

#include <string>

class Token {
   public:
    enum Type {
        TRUE, FALSE,
    
        LBRACKET, RBRACKET,

        ADD, SUB, MUL, DIV,
        EQ, LEQ, NOT, AND, OR,

        ASSIGN, SEMICOLON, 

        LBRACE, RBRACE,
        IF, ELSE, 
        FOR, DO, WHILE,
        PRINT, SKIP,

        VARNAME, NUM,

        INVALID
    };

   private:
    std::string spelling_;
    Type type_;
    size_t sourceLocation_;

   public:
    Token() : spelling_(""), type_(INVALID), sourceLocation_(0) {}
    Token(std::string&& spelling, Type kind) : spelling_(std::move(spelling)), type_(kind), sourceLocation_(0) {}
    Token(std::string&& spelling, Type kind, size_t sourceLocation) : spelling_(std::move(spelling)), type_(kind), sourceLocation_(sourceLocation) {}

    const std::string& spelling() const {
        return spelling_;
    }

    Type type() const {
        return type_;
    }

    size_t sourceLocation() const {
        return sourceLocation_;
    }

    std::string&& moveSpelling() {
        type_ = INVALID;
        return std::move(spelling_);
    }

    static std::string toString(Type type) {
        switch (type) {
            case TRUE:
                return "true";

            case FALSE:
                return "false";

            case LBRACKET:
                return "(";

            case RBRACKET:
                return ")";

            case ADD:
                return "+";
                
            case SUB:
                return "-";
            
            case MUL:
                return "*";
            
            case DIV:
                return "/";
            
            case EQ:
                return "eq";

            case LEQ:
                return "leq";

            case NOT:
                return "not";

            case AND:
                return "and";

            case OR:
                return "or";

            case ASSIGN:
                return "=";

            case SEMICOLON:
                return ";"; 
            
            case LBRACE:
                return "{";

            case RBRACE:
                return "}";

            case IF:
                return "if";
            
            case ELSE:
                return "else";

            case DO:
                return "do";

            case WHILE:
                return "while";

            case FOR:
                return "for";
            
            case PRINT:
                return "print";
                
            case SKIP:
                return "skip";

            case VARNAME:
                return "identifier";
                
            case NUM:
                return "numeric literal";

            case INVALID:
                return "invalid";
        }
        return "";
    }
};