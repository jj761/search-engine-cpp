#include "tokenizer.h"
#include <cctype>

std::string normalize_quotes(const std::string &text)
{
    std::string result;

    for (size_t i = 0; i < text.size(); i++)
    {
        unsigned char c = text[i];

        // U+2019 in UTF-8 is the 3-byte sequence: 0xE2 0x80 0x99
        if (c == 0xE2 && i + 2 < text.size() &&
            static_cast<unsigned char>(text[i + 1]) == 0x80 &&
            static_cast<unsigned char>(text[i + 2]) == 0x99)
        {
            result += '\'';
            i += 2; // skip the next two bytes, they were part of this character
        }
        else
        {
            result += text[i];
        }
    }

    return result;
}

std::vector<std::string> tokenize(const std::string &text)
{
    std::string normalized = normalize_quotes(text);

    std::vector<std::string> tokens;
    std::string current;

    for (size_t i = 0; i < normalized.size(); i++)
    {
        unsigned char c = normalized[i];

        if (std::isalnum(c))
        {
            current += std::tolower(c);
        }
        else if (c == '\'' &&
                 i > 0 && std::isalnum(static_cast<unsigned char>(normalized[i - 1])) &&
                 i + 1 < normalized.size() && std::isalnum(static_cast<unsigned char>(normalized[i + 1])))
        {
            // interior apostrophe (don't, Tom's) — keep as part of the token
            current += c;
        }
        else
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current.clear();
            }
        }
    }

    if (!current.empty())
    {
        tokens.push_back(current);
    }

    return tokens;
}