# Report

1. Linking Rule in Makefile $(TARGET): $(OBJECTS) means: “build the program named in $(TARGET) by linking all the object files listed in $(OBJECTS).”
It just collects .o files into one executable.
A rule that links against a library also mentions the library flags, e.g. -lmystr or libmystr.a. That tells the linker to also pull code from a library file in addition to your object files.
2. Git Tag

A tag is a named pointer to a specific commit. It is used to mark important points like “v1.0”.

    -Lightweight (simple) tag: just a name pointing to a commit.

    -Annotated tag: also stores the author, date, and a message. It is like a real “release note” inside Git.

Tags make it easy to go back to, or build, a particular version later.
3. Purpose of a GitHub Release

Creating a Release on GitHub publishes a tagged version with extra information (title, notes).
Attaching binaries (like your compiled client) lets other people download and run the program without building it themselves.
4. Makefile Part 2 vs Part 3

In Part 2 the Makefile probably just built object files and linked them into an executable.
In Part 3 new variables (like LIBNAME or ARFLAGS) and new rules were added to:
    -combine object files into a static library (.a file),
    -then link that library into the executable.
So the key difference: Part 3 introduces variables and rules to create and use a library, not just separate .o files.
5. Purpose of ar and ranlib
    ar = “archiver” – it packs multiple .o files into one .a static library file.
    ranlib = updates the library’s symbol index so the linker can quickly find functions inside the .a.
    On some systems ar already updates the index; on others you need ranlib right after.

6. Symbols in nm Output
If you run nm client_static, you usually see the symbols (like mystrlen) inside the executable.
That means the code from the library got physically copied into the program at build time.
This is how static linking works: the needed code is included in the final binary.
7. Position-Independent Code (-fPIC)
-fPIC tells the compiler to generate machine code that can run no matter where in memory it is loaded.
Shared libraries (.so files) can be placed at different addresses at runtime, so they must be built as PIC to work correctly.
8. File Size: Static vs Dynamic
A statically linked executable is bigger because it contains full copies of all library code inside it.
A dynamically linked executable is smaller because it only holds references; the code stays in a shared .so file loaded at runtime.
9. LD_LIBRARY_PATH
This environment variable lists extra folders where the system’s dynamic loader should look for shared libraries.
If your library isn’t in a standard system path (like /usr/lib), you must set LD_LIBRARY_PATH so your program can find it.
This shows that the OS loader, not your program, is responsible for locating and loading shared libraries before the program starts running.

