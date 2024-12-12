#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <unordered_map>

// Types de jetons constituant le langage.
enum class TokenType {
    retourner,
    entier,
    si,
    sinon_si,
    sinon,
    tant_que,
    alors,
    fonction,
    point_virgule,
};

// Structure représentant un jeton.
struct Token {
    TokenType type;
    std::optional<std::string> value;
};

/**
 * Transforme une chaîne de caractères en une liste de jetons.
 * @param content Chaîne de caractères à transformer en jetons.
 * @return Un vecteur de jetons.
 */
std::vector<Token> tokenize(const std::string& content) {
    std::vector<Token> tokens;
    std::string buffer;
    std::unordered_map<std::string, TokenType> tokenMap = {
        {"si", TokenType::si},
        {"sinon_si", TokenType::sinon_si},
        {"sinon", TokenType::sinon},
        {"tant_que", TokenType::tant_que},
        {"alors", TokenType::alors},
        {"fonction", TokenType::fonction},
        // {";", TokenType::point_virgule},
        {"retourner", TokenType::retourner}
    };

    for (int index = 0; index < content.length(); index++) {
        char character = content.at(index);

        // Ignore spaces.
        if (std::isspace(character)) {
            continue;
        }

        // If the character is a letter, read the complete word.
        if (std::isalpha(character)) {
            buffer.push_back(character);
            index++;
            while (index < content.length() && std::isalpha(content.at(index))) {
                buffer.push_back(content.at(index));
                index++;
            }
            index--;
        }

        // If the character is a digit, read the complete number.
        if (std::isdigit(character)) {
            if (!buffer.empty()) {
                if (auto iterator = tokenMap.find(buffer); iterator != tokenMap.end()) {
                    tokens.push_back({iterator->second, std::nullopt});
                    buffer.clear();
                } else {
                    std::cerr << "Erreur: jeton inconnu " << buffer << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            buffer.push_back(character);
            index++;
            while (index < content.length() && std::isdigit(content.at(index))) {
                buffer.push_back(content.at(index));
                index++;
            }
            index--;
            tokens.push_back({TokenType::entier, buffer});
            buffer.clear();
            continue;
        }

        if (character == ';') {
            tokens.push_back({TokenType::point_virgule, std::nullopt});
            continue;
        }

        if (auto iterator = tokenMap.find(buffer); iterator != tokenMap.end()) {
            tokens.push_back({iterator->second, std::nullopt});
            buffer.clear();
        } else if (!buffer.empty()) {
            std::cerr << "Erreur: jeton inconnu " << buffer << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}

std::string tokens_to_asm(const std::vector<Token>& tokens) {
    std::string output = "global _start\nglobal _main\n_main: jmp _start\n_start:\n";
    for (int index = 0; index < tokens.size(); index ++) {
        const Token& token = tokens.at(index);
        if (token.type == TokenType::retourner) {
            if (index + 1 < tokens.size() && tokens.at(index + 1).type == TokenType::entier) {
                if (index + 2 < tokens.size() && tokens.at(index + 2).type == TokenType::point_virgule) {
                    output += "    mov rax, 60\n";
                    output += "    mov rdi, " + tokens.at(index + 1).value.value() + "\n";
                    output += "    syscall\n";
                    index += 2;
                } else {
                    std::cerr << "Erreur: point-virgule manquant après l'entier" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    return output;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Nombre d'arguments incorrects. Vous devriez utiliser..." << std::endl;
        std::cerr << "frs <input.frs>" << std::endl;
        return EXIT_FAILURE;
    }

    // Ouvre le fichier spécifié en argument en mode lecture et extrait son contenu en chaîne de caractères.
    std::string content;
    {
        std::fstream input(argv[1], std::ios::in);
        if (!input.is_open()) {
            std::cerr << "Impossible d'ouvrir le fichier " << argv[1] << std::endl;
            return EXIT_FAILURE;
        }
        std::stringstream stream;
        stream << input.rdbuf();
        content = stream.str();
    }
    std::cout << content << std::endl;

    // Tokenize the content.
    std::vector<Token> tokens = tokenize(content);

    {
        std::fstream file("output.asm", std::ios::out);
        file << tokens_to_asm(tokens);
    }

    system("nasm -f elf64 output.asm");
    system("ld -o output output.o");

    return EXIT_SUCCESS;
}
