🎵 MP3 Tag Reader & Editor

A C-based MP3 Tag Reader and Editor that allows users to view and modify ID3 metadata (Title, Artist, Album, Year, Genre, and Comment) directly from the command line.

This project demonstrates practical concepts of file handling, structures, endianness conversion, and command-line argument processing in C — making it a great example of low-level file manipulation and data parsing.

✨ Features

🔍 View MP3 file information and verify ID3 headers

✏️ Edit song details like title, artist, and album directly from terminal

⚙️ Safe editing using a temporary file system

🧰 Color-coded CLI output for better readability

❌ Error handling for invalid files or arguments

💡 Skills Demonstrated

Binary file handling in C

Structs and pointers

Byte-order (Big Endian ↔ Little Endian) conversion

Modular programming with multiple .c and .h files

User-friendly terminal interface

🧪 Example Usage
./a.out -v song.mp3           # View tags
./a.out -e -t "New Title" song.mp3   # Edit title
./a.out -h                    # Help menu
