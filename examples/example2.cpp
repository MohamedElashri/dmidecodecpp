#include "../dmidecode_parser.h"
#include <iostream>

int main() {
    // Realistic dmidecode output focusing on memory
    std::string dmidecodeOutput = R"(
# dmidecode 3.3
Getting SMBIOS data from sysfs.
SMBIOS 3.4.0 present.
Handle 0x0010, DMI type 16, 23 bytes
Physical Memory Array
        Location: System Board Or Motherboard
        Use: System Memory
        Error Correction Type: None
        Maximum Capacity: 64 GB
        Error Information Handle: 0x000F
        Number Of Devices: 2

Handle 0x0013, DMI type 17, 92 bytes
Memory Device
        Array Handle: 0x0010
        Error Information Handle: 0x0012
        Total Width: 64 bits
        Data Width: 64 bits
        Size: 16 GB
        Form Factor: SODIMM
        Set: None
        Locator: DIMM 0
        Bank Locator: P0 CHANNEL A
        Type: DDR5
        Type Detail: Synchronous Unbuffered (Unregistered)
        Speed: 4800 MT/s
        Manufacturer: Unknown
        Serial Number: E7998573
        Asset Tag: Not Specified
        Part Number: CT16G48C40S5.M8A1
        Rank: 1
        Configured Memory Speed: 4800 MT/s
        Minimum Voltage: 1.1 V
        Maximum Voltage: 1.1 V
        Configured Voltage: 1.1 V
        Memory Technology: DRAM
        Memory Operating Mode Capability: Volatile memory
        Firmware Version: Unknown
        Module Manufacturer ID: Bank 6, Hex 0x9B
        Module Product ID: Unknown
        Memory Subsystem Controller Manufacturer ID: Unknown
        Memory Subsystem Controller Product ID: Unknown
        Non-Volatile Size: None
        Volatile Size: 16 GB
        Cache Size: None
        Logical Size: None

Handle 0x0016, DMI type 17, 92 bytes
Memory Device
        Array Handle: 0x0010
        Error Information Handle: 0x0015
        Total Width: 64 bits
        Data Width: 64 bits
        Size: 16 GB
        Form Factor: SODIMM
        Set: None
        Locator: DIMM 0
        Bank Locator: P0 CHANNEL B
        Type: DDR5
        Type Detail: Synchronous Unbuffered (Unregistered)
        Speed: 4800 MT/s
        Manufacturer: Unknown
        Serial Number: E7998574
        Asset Tag: Not Specified
        Part Number: CT16G48C40S5.M8A1
        Rank: 1
        Configured Memory Speed: 4800 MT/s
        Minimum Voltage: 1.1 V
        Maximum Voltage: 1.1 V
        Configured Voltage: 1.1 V
        Memory Technology: DRAM
        Memory Operating Mode Capability: Volatile memory
        Firmware Version: Unknown
        Module Manufacturer ID: Bank 6, Hex 0x9B
        Module Product ID: Unknown
        Memory Subsystem Controller Manufacturer ID: Unknown
        Memory Subsystem Controller Product ID: Unknown
        Non-Volatile Size: None
        Volatile Size: 16 GB
        Cache Size: None
        Logical Size: None
    )";

    // Initialize the parser
    DMIDecodeParser::Parser parser(dmidecodeOutput);

    // Test: Export memory-related data to Markdown
    std::cout << "\n=== Export Memory Array (Type 16) to Markdown ===\n";
    std::cout << parser.exportByTypeToMarkdown(16) << "\n";

    std::cout << "\n=== Export Memory Devices (Type 17) to Markdown ===\n";
    std::cout << parser.exportByTypeToMarkdown(17) << "\n";

    // Test: Retrieve specific memory-related keys
    std::cout << "\n=== Retrieve Specific Memory Keys ===\n";
    std::cout << "Maximum Capacity (Type 16): " << parser.getValueByKey(16, "Maximum Capacity") << "\n";
    std::cout << "Number Of Devices (Type 16): " << parser.getValueByKey(16, "Number Of Devices") << "\n";
    std::cout << "Size of First Memory Device (Type 17): " << parser.getValueByKey(17, "Size") << "\n";
    std::cout << "Type of First Memory Device (Type 17): " << parser.getValueByKey(17, "Type") << "\n";

    return 0;
}
