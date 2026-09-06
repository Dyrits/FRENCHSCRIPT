#pragma once

#include <string>

class Tokenizer {
    public:
        inline Tokenizer(const std::string& source) : source_(std::move(source)) {} 

        std::vector<Token> tokenize tokenize() {}
        
    private:
        const std::string source_;
};