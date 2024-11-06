#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

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
    std::vector<char> buffer {};
    for (int index = 0; index < content.length(); index ++) {
        char character = content.at(index);
        if (std::isalpha(character)) {
            buffer.push_back(character);
        }
    }
    return {};
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

    tokenize(content);

    return EXIT_SUCCESS;
}
