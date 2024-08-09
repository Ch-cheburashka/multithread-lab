# Multithread-Lab

Multithread-Lab is a multi-threaded C++ application that generates SHA-256 hashes for random strings and writes valid hashes (ending with "0000") to a file. It demonstrates the use of multi-threading, thread-safe queues, and signal handling.

## Features

- **Random String Generation**: Generates random strings of varying lengths.
- **SHA-256 Hashing**: Computes SHA-256 hashes using the PicoSHA2 library.
- **Hash Validation**: Checks if hashes end with "0000".
- **Multi-threaded**: Uses multiple threads to generate hashes concurrently.
- **File Writing**: Periodically writes valid hashes to a specified file.
- **Graceful Termination**: Handles termination signals to stop the program cleanly.