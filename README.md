# CProwler 🕵️‍♂

C implementation of PyProwler (A project of mine) - a lightweight network packet analyzer.

## Quick Start

### Linux

```bash
gcc main.c -o packet_analyzer
sudo ./packet_analyzer
```

### macOS


Install dependencies
```bash
brew install libpcap
```
```bash
Compile and run
gcc main.c -o packet_analyzer -lpcap
sudo ./packet_analyzer
```

## Features
- Real-time packet capture
- Ethernet frame analysis
- MAC address decoding
- Protocol identification

## Requirements
- Root/sudo privileges
- GCC compiler
- libpcap (macOS only)

## Output Example

Ethernet Frame:
Destination: AA:BB:CC:DD:EE:FF
Source: 11:22:33:44:55:66
Type: 0x0800

Press `Ctrl+C` to stop capturing.

## Security Note
Requires root privileges. Use responsibly.










