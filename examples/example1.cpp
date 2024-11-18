#include "../dmidecode_parser.h"
#include <iostream>

int main() {
    // Example dmidecode output
    std::string dmidecodeOutput = R"(
# dmidecode 3.3
Getting SMBIOS data from sysfs.
SMBIOS 3.4.0 present.
Handle 0x0000, DMI type 0, 26 bytes
BIOS Information
        Vendor: American Megatrends International, LLC.
        Version: 104
        Release Date: 05/05/2023
        Address: 0xF0000
        Runtime Size: 64 kB
        ROM Size: 0 MB
        Characteristics:
                PCI is supported
                BIOS is upgradeable
                BIOS shadowing is allowed
                Boot from CD is supported
                Selectable boot is supported
                BIOS ROM is socketed
                EDD is supported
                ACPI is supported
                BIOS boot specification is supported
                Targeted content distribution is supported
                UEFI is supported
        BIOS Revision: 5.24
        Firmware Revision: 1.3

Handle 0x0007, DMI type 13, 22 bytes
BIOS Language Information
        Language Description Format: Long
        Installable Languages: 1
                en|US|iso8859-1
        Currently Installed Language: en|US|iso8859-1
    )";

    // Initialize the parser with dmidecode output
    DMIDecodeParser::Parser parser(dmidecodeOutput);

    // Test: Export all data to plain text
    std::cout << "\n=== Export All Data to Plain Text ===\n";
    std::cout << parser.exportAllToPlainText() << "\n";

    // Test: Export Type 0 (BIOS Information) to plain text
    std::cout << "\n=== Export Type 0 (BIOS Information) to Plain Text ===\n";
    std::cout << parser.exportTypeToPlainText(0) << "\n";

    // Test: Export Type 13 (BIOS Language Information) to plain text
    std::cout << "\n=== Export Type 13 (BIOS Language Information) to Plain Text ===\n";
    std::cout << parser.exportTypeToPlainText(13) << "\n";

    // Test: Retrieve specific keys
    std::cout << "\n=== Retrieve Specific Keys ===\n";
    std::cout << "BIOS Vendor: " << parser.getValueByKey(0, "Vendor") << "\n";
    std::cout << "BIOS Version: " << parser.getValueByKey(0, "Version") << "\n";
    std::cout << "BIOS Language Format: " << parser.getValueByKey(13, "Language Description Format") << "\n";
    std::cout << "Currently Installed Language: " << parser.getValueByKey(13, "Currently Installed Language") << "\n";

    return 0;
}
