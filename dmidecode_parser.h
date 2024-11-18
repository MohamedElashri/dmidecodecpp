#ifndef DMIDECODE_PARSER_H
#define DMIDECODE_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace DMIDecodeParser {

// Represents a single key-value property or a key with a list of values
struct DMIProperty {
    std::string key;
    std::string value;             // Single value or empty
    std::vector<std::string> list; // Multi-line values or lists

    // Convert property to plain text
    std::string toPlainText() const {
        std::ostringstream os;
        os << "  " << key << ": " << value << "\n";
        for (const auto& listItem : list) {
            os << "    - " << listItem << "\n";
        }
        return os.str();
    }
};

// Represents a DMI type with a type ID, name, and list of properties
struct DMIType {
    int typeId;
    std::string typeName;
    std::vector<DMIProperty> properties;

    // Convert the entire DMI type to plain text
    std::string toPlainText() const {
        std::ostringstream os;
        os << "Type " << typeId << " - " << typeName << ":\n";
        for (const auto& property : properties) {
            os << property.toPlainText();
        }
        os << "\n"; // Add a blank line between types
        return os.str();
    }
};

class Parser {
private:
    std::map<int, std::vector<DMIType>> parsedData; // Store DMI types grouped by type ID

    // Helper function to trim whitespace from a string
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t");
        return str.substr(first, last - first + 1);
    }

    // Helper function to split a string by a delimiter
    static std::vector<std::string> splitByDelimiter(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::istringstream stream(str);
        std::string token;
        while (std::getline(stream, token, delimiter)) {
            tokens.push_back(trim(token));
        }
        return tokens;
    }

    // Detect if a line represents a list item
    static bool isListItem(const std::string& line) {
        return line.find_first_not_of(" \t") == 8; // List items are indented more deeply
    }

    // Parse a single DMI section
    DMIType parseSection(const std::vector<std::string>& lines) const {
        DMIType dmiType;
        if (lines.empty()) return dmiType;

        // Parse the handle line
        const auto& handleLine = lines[0];
        if (handleLine.find("Handle") != 0) return dmiType; // Skip invalid sections

        auto tokens = splitByDelimiter(handleLine, ',');
        if (tokens.size() >= 2) {
            dmiType.typeId = std::stoi(tokens[1].substr(9)); // Extract "DMI type"
        }

        // Parse the title line
        if (lines.size() > 1 && !lines[1].empty()) {
            dmiType.typeName = trim(lines[1]);
        } else {
            dmiType.typeName = "Unknown Type";
        }

        // Parse the properties
        DMIProperty currentProperty;
        for (size_t i = 2; i < lines.size(); ++i) {
            const auto& line = trim(lines[i]);
            if (line.empty()) continue;

            if (line.find(':') != std::string::npos) {
                // Add the previous property
                if (!currentProperty.key.empty()) {
                    dmiType.properties.push_back(currentProperty);
                }
                currentProperty = {};
                auto keyValue = splitByDelimiter(line, ':');
                currentProperty.key = keyValue[0];
                if (keyValue.size() > 1) {
                    currentProperty.value = keyValue[1];
                }
            } else if (isListItem(line)) { // List items
                currentProperty.list.push_back(line);
            } else if (!line.empty()) { // Continuation lines
                currentProperty.value += " " + line;
            }
        }
        // Add the last property
        if (!currentProperty.key.empty()) {
            dmiType.properties.push_back(currentProperty);
        }

        return dmiType;
    }

    // Parse the entire dmidecode output
    void parseOutput(const std::string& output) {
        std::istringstream stream(output);
        std::string line;
        std::vector<std::string> section;
        while (std::getline(stream, line)) {
            if (line.find("Handle") == 0) {
                if (!section.empty()) {
                    auto dmiType = parseSection(section);
                    parsedData[dmiType.typeId].push_back(dmiType);
                    section.clear();
                }
            }
            section.push_back(line);
        }
        if (!section.empty()) {
            auto dmiType = parseSection(section);
            parsedData[dmiType.typeId].push_back(dmiType);
        }
    }

public:
    // Constructor to initialize the parser with dmidecode output
    Parser(const std::string& output) {
        parseOutput(output);
    }

    // Export all data to plain text
    std::string exportAllToPlainText() const {
        std::ostringstream os;
        for (const auto& [typeId, types] : parsedData) {
            for (const auto& type : types) {
                os << type.toPlainText();
            }
        }
        return os.str();
    }

    // Export a specific type to plain text
    std::string exportTypeToPlainText(int typeId) const {
        if (parsedData.find(typeId) == parsedData.end()) {
            return "Type " + std::to_string(typeId) + " not found.\n";
        }
        std::ostringstream os;
        for (const auto& type : parsedData.at(typeId)) {
            os << type.toPlainText();
        }
        return os.str();
    }

    // Export a specific type to Markdown
    std::string exportByTypeToMarkdown(int typeId) const {
        if (parsedData.find(typeId) == parsedData.end()) {
            return "Type " + std::to_string(typeId) + " not found.\n";
        }
        std::ostringstream os;
        for (const auto& type : parsedData.at(typeId)) {
            os << exportToMarkdown(type);
        }
        return os.str();
    }

    // Helper function to export a single DMIType to Markdown
    std::string exportToMarkdown(const DMIType& type) const {
        std::ostringstream os;
        os << "### Type " << type.typeId << " - " << type.typeName << "\n\n";
        os << "| Key                              | Value                                |\n";
        os << "|-----------------------------------|--------------------------------------|\n";
        for (const auto& property : type.properties) {
            if (!property.list.empty()) {
                os << "| " << property.key << " | ";
                for (size_t i = 0; i < property.list.size(); ++i) {
                    if (i > 0) os << "                                "; // Align bullets
                    os << "- " << property.list[i] << "\n";
                }
                os << " |\n";
            } else {
                os << "| " << property.key << " | " << property.value << " |\n";
            }
        }
        os << "\n"; // Add a blank line between types
        return os.str();
    }

    // Retrieve a specific key's value
    std::string getValueByKey(int typeId, const std::string& key) const {
        if (parsedData.find(typeId) == parsedData.end()) {
            return "";
        }
        for (const auto& type : parsedData.at(typeId)) {
            for (const auto& property : type.properties) {
                if (property.key == key) {
                    return property.value;
                }
            }
        }
        return "";
    }
};

} // namespace DMIDecodeParser

#endif // DMIDECODE_PARSER_H
