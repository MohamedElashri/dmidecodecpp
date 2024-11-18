#include "../dmidecode_parser.h"
#include <iostream>

int main() {
    // Example dmidecode output with multiple sections and properties
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

Handle 0x0010, DMI type 16, 23 bytes
Physical Memory Array
        Location: System Board Or Motherboard
        Use: System Memory
        Error Correction Type: None
        Maximum Capacity: 64 GB
        Number Of Devices: 2

Handle 0x0013, DMI type 17, 92 bytes
Memory Device
        Size: 16 GB
        Type: DDR5
        Speed: 4800 MT/s
        Manufacturer: Unknown
        Serial Number: E7998573
    )";

    // Initialize the parser
    DMIDecodeParser::Parser parser(dmidecodeOutput);

    // Extract single values
    std::cout << "=== Extract Single Values ===\n";

    // Example 1: BIOS Information
    std::string biosVendor = parser.getValueByKey(0, "Vendor");
    std::string biosVersion = parser.getValueByKey(0, "Version");
    std::string biosReleaseDate = parser.getValueByKey(0, "Release Date");
    std::string biosRevision = parser.getValueByKey(0, "BIOS Revision");

    std::cout << "BIOS Vendor: " << biosVendor << "\n";
    std::cout << "BIOS Version: " << biosVersion << "\n";
    std::cout << "BIOS Release Date: " << biosReleaseDate << "\n";
    std::cout << "BIOS Revision: " << biosRevision << "\n";

    // Example 2: Physical Memory Array
    std::string memoryLocation = parser.getValueByKey(16, "Location");
    std::string memoryUse = parser.getValueByKey(16, "Use");
    std::string memoryMaxCapacity = parser.getValueByKey(16, "Maximum Capacity");
    std::string memoryDevices = parser.getValueByKey(16, "Number Of Devices");

    std::cout << "\nPhysical Memory Array:\n";
    std::cout << "  Location: " << memoryLocation << "\n";
    std::cout << "  Use: " << memoryUse << "\n";
    std::cout << "  Maximum Capacity: " << memoryMaxCapacity << "\n";
    std::cout << "  Number Of Devices: " << memoryDevices << "\n";

    // Example 3: Memory Device
    std::string memorySize = parser.getValueByKey(17, "Size");
    std::string memoryType = parser.getValueByKey(17, "Type");
    std::string memorySpeed = parser.getValueByKey(17, "Speed");
    std::string memoryManufacturer = parser.getValueByKey(17, "Manufacturer");
    std::string memorySerialNumber = parser.getValueByKey(17, "Serial Number");

    std::cout << "\nMemory Device:\n";
    std::cout << "  Size: " << memorySize << "\n";
    std::cout << "  Type: " << memoryType << "\n";
    std::cout << "  Speed: " << memorySpeed << "\n";
    std::cout << "  Manufacturer: " << memoryManufacturer << "\n";
    std::cout << "  Serial Number: " << memorySerialNumber << "\n";

    // Example 4: Key not found
    std::string nonExistentKey = parser.getValueByKey(0, "Non-Existent Key");
    if (nonExistentKey.empty()) {
        std::cout << "\nKey not found: Non-Existent Key\n";
    } else {
        std::cout << "\nNon-Existent Key: " << nonExistentKey << "\n";
    }

    return 0;
}
