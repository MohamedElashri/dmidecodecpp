# Examples for `dmidecode_parser`

This folder contains example programs demonstrating how to use the `dmidecode_parser` header file. Each example highlights specific features of the parser.

## Folder Structure

```
examples/
├── example1.cpp    # Demonstrates exporting data to plain text and Markdown
├── example2.cpp    # Focuses on memory-related DMI types and Markdown export
├── example3.cpp    # Demonstrates how to extract specific key-value pairs
├── Makefile        # Automates building and running the examples
```

---

## Prerequisites

1. **C++ Compiler:** Ensure you have a C++17-compatible compiler installed (e.g., `g++` or `clang`).
2. **File Structure:** The `examples` folder should be located in the root directory of the repository containing `dmidecode_parser.h`.

---

## Building the Examples

To compile all examples, navigate to the `examples` folder and run:

```bash
make
```

This will generate the following executables:
- `example1`
- `example2`
- `example3`

---

## Running the Examples

### Run All Examples
To run all examples sequentially, use:

```bash
make run
```

### Run Individual Examples
To run a specific example, use one of the following commands:

- Run `example1`:
  ```bash
  make run_example1
  ```
- Run `example2`:
  ```bash
  make run_example2
  ```
- Run `example3`:
  ```bash
  make run_example3
  ```

---

## Cleaning Up

To remove all compiled executables, use:

```bash
make clean
```

---

## Example Outputs

### **example1**
Demonstrates exporting data to plain text and Markdown format for all DMI types.

**Sample Output:**
```
=== Export All Data to Plain Text ===
Type 0 - BIOS Information:
  Vendor: American Megatrends International, LLC.
  Version: 104
  Release Date: 05/05/2023
  ...

=== Export All Data to Markdown ===
### Type 0 - BIOS Information
| Key            | Value           |
|-----------------|-----------------|
| Vendor         | American Megatrends International, LLC. |
...
```

### **example2**
Focuses on memory-related DMI types (`Type 16` and `Type 17`) and their Markdown export.

**Sample Output:**
```
=== Export Memory Array (Type 16) to Markdown ===
### Type 16 - Physical Memory Array
| Key                     | Value                  |
|--------------------------|------------------------|
| Location                | System Board Or Motherboard |
| Use                     | System Memory          |
...

=== Export Memory Devices (Type 17) to Markdown ===
### Type 17 - Memory Device
| Key                     | Value                  |
|--------------------------|------------------------|
| Size                    | 16 GB                 |
...
```

### **example3**
Demonstrates how to extract specific key-value pairs, such as BIOS Vendor or Memory Size.

**Sample Output:**
```
=== Extract Single Values ===
BIOS Vendor: American Megatrends International, LLC.
BIOS Version: 104
BIOS Release Date: 05/05/2023
BIOS Revision: 5.24

Physical Memory Array:
  Location: System Board Or Motherboard
  Use: System Memory
  Maximum Capacity: 64 GB
...
```

---

## Troubleshooting

1. **Missing Header File:**
   Ensure `dmidecode_parser.h` exists in the parent directory of `examples`.

2. **Compilation Errors:**
   Check that your compiler supports C++17. You can update the `CXXFLAGS` in the Makefile to use your specific compiler options.

3. **Permission Issues:**
   Ensure you have execution permissions for the generated binaries:
   ```bash
   chmod +x example1 example2 example3
   ```
