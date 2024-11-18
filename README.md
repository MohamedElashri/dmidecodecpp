# DMIDecode Parser in C++

This project provides a self-contained C++ header file, `dmidecode_parser.h`, designed to parse the output of the `dmidecode` tool. The parser organizes the data into structured types and supports exporting to plain text or Markdown, as well as retrieving individual key-value pairs.

---

## Features

- Parse `dmidecode` output into structured DMI types.
- Export data as:
  - Plain text
  - Markdown tables (by type)
- Retrieve specific key-value pairs programmatically.
- Lightweight and dependency-free, implemented as a single header file.

---

## Getting Started

### **Prerequisites**
- A C++17-compatible compiler (e.g., `g++`, `clang`).

### **Installation**
Clone the repository or download the `dmidecode_parser.h` file. Include it in your C++ project:

```cpp
#include "dmidecode_parser.h"
```

---

## Usage

### **1. Parse DMIDecode Output**
The parser takes the raw output of `dmidecode` as a string. For example:

```cpp
std::string dmidecodeOutput = R"(
Handle 0x0000, DMI type 0, 26 bytes
BIOS Information
    Vendor: American Megatrends International, LLC.
    Version: 104
    Release Date: 05/05/2023
)";
DMIDecodeParser::Parser parser(dmidecodeOutput);
```

### **2. Retrieve Individual Values**
You can extract specific values using the `getValueByKey` method:

```cpp
std::string biosVendor = parser.getValueByKey(0, "Vendor");
std::string biosReleaseDate = parser.getValueByKey(0, "Release Date");

std::cout << "BIOS Vendor: " << biosVendor << "\n";
std::cout << "BIOS Release Date: " << biosReleaseDate << "\n";
```

**Output:**
```
BIOS Vendor: American Megatrends International, LLC.
BIOS Release Date: 05/05/2023
```

### **3. Export Data**
Export the parsed data to plain text or Markdown:

```cpp
// Export all data to plain text
std::cout << parser.exportAllToPlainText();

// Export all data to Markdown
std::cout << parser.exportAllToMarkdown();
```

---

## Examples

The `examples` folder contains ready-to-run examples that showcase how to use the parser.

1. **Build and Run All Examples:**
   ```bash
   cd examples
   make run
   ```

2. **Run Individual Examples:**
   - `example1`: Export parsed data to plain text and Markdown.
   - `example2`: Focus on memory-related types (`Type 16` and `Type 17`).
   - `example3`: Demonstrates retrieving individual key-value pairs.

**Navigate to the `examples` folder and refer to its [README.md](examples/README.md) for more details.**

---

## Contribution

Contributions are welcome! If you have feature requests, bug reports, or improvements, feel free to:

1. Fork the repository.
2. Submit a pull request with a clear description of your changes.

---

## License

This project is licensed under the [Apache License 2.0](LICENSE).

You are free to use, modify, and distribute this software in compliance with the license terms.

