/**
 * file_io.c
 * 
 * Demonstrates file input/output operations in C.
 * Topics covered:
 * - Opening and closing files (fopen, fclose)
 * - Text file I/O (fprintf, fscanf, fgets, fputs)
 * - Binary file I/O (fread, fwrite)
 * - File positioning (fseek, ftell, rewind)
 * - Error handling (ferror, feof, perror)
 * - File modes (read, write, append, binary)
 * 
 * Memory Implications:
 * - FILE* is a buffered I/O abstraction (typically 8KB buffer)
 * - Buffer reduces system calls: batch writes improve performance
 * - fflush() forces buffer write to disk
 * - fclose() automatically flushes and releases resources
 * 
 * CPU Overhead:
 * - Buffered I/O: amortized O(1) per character
 * - System calls (underlying write/read): ~100-1000 CPU cycles
 * - Disk I/O: 1-10ms latency (millions of CPU cycles)
 * - Binary I/O faster than formatted text I/O
 * 
 * RAII Pattern in C:
 * - Always pair fopen() with fclose()
 * - Use single exit point for cleanup
 * - Check FILE* != NULL before operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Windows UTF-8 console setup */
#ifdef _WIN32
#include <windows.h>
void setup_utf8_console(void) {
    SetConsoleOutputCP(CP_UTF8);
}
#else
void setup_utf8_console(void) {}
#endif

/* File names for examples */
#define TEXT_FILE "example_text.txt"
#define BINARY_FILE "example_binary.dat"
#define DATA_FILE "student_data.txt"

/**
 * Example 1: Basic text file writing
 * Demonstrates fopen, fprintf, and fclose
 */
void example_write_text_file(void) {
    printf("\n=== Example 1: Writing Text File ===\n");
    
    /* Open file for writing (creates new or overwrites existing) */
    FILE *file = fopen(TEXT_FILE, "w");
    
    /* Always check if file opened successfully */
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    
    printf("Writing to '%s'...\n", TEXT_FILE);
    
    /* Write formatted text to file */
    fprintf(file, "Hello, File I/O!\n");
    fprintf(file, "This is line 2.\n");
    fprintf(file, "Number: %d\n", 42);
    fprintf(file, "Float: %.2f\n", 3.14159);
    
    /* CRITICAL: Always close file to flush buffers and release resources */
    fclose(file);
    
    printf("File written successfully.\n");
}

/**
 * Example 2: Reading text file
 * Demonstrates fopen, fgets, and fclose
 */
void example_read_text_file(void) {
    printf("\n=== Example 2: Reading Text File ===\n");
    
    /* Open file for reading */
    FILE *file = fopen(TEXT_FILE, "r");
    
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }
    
    printf("Reading from '%s':\n", TEXT_FILE);
    printf("-----------------------------------\n");
    
    /* Read file line by line */
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer); /* fgets includes newline */
    }
    
    printf("-----------------------------------\n");
    
    /* Check if we stopped due to error or EOF */
    if (ferror(file)) {
        perror("Error reading file");
    }
    
    fclose(file);
    printf("File read successfully.\n");
}

/**
 * Example 3: Appending to file
 * Demonstrates append mode
 */
void example_append_to_file(void) {
    printf("\n=== Example 3: Appending to File ===\n");
    
    /* Open file for appending (writes at end of file) */
    FILE *file = fopen(TEXT_FILE, "a");
    
    if (file == NULL) {
        perror("Error opening file for appending");
        return;
    }
    
    printf("Appending to '%s'...\n", TEXT_FILE);
    
    /* Write additional lines */
    fprintf(file, "This line was appended.\n");
    fprintf(file, "So was this one!\n");
    
    fclose(file);
    printf("Content appended successfully.\n");
}

/**
 * Example 4: Binary file I/O
 * Demonstrates fwrite and fread for binary data
 */
void example_binary_file(void) {
    printf("\n=== Example 4: Binary File I/O ===\n");
    
    /* Data structure to save */
    struct Student {
        int id;
        char name[50];
        float gpa;
    };
    
    struct Student students[3] = {
        {101, "Alice Johnson", 3.8f},
        {102, "Bob Smith", 3.6f},
        {103, "Carol White", 3.9f}
    };
    
    /* Write binary data */
    FILE *file = fopen(BINARY_FILE, "wb"); /* 'b' for binary mode */
    
    if (file == NULL) {
        perror("Error opening binary file for writing");
        return;
    }
    
    printf("Writing binary data to '%s'...\n", BINARY_FILE);
    
    /* Write array of structures */
    size_t written = fwrite(students, sizeof(struct Student), 3, file);
    printf("Wrote %zu student records.\n", written);
    
    fclose(file);
    
    /* Read binary data back */
    file = fopen(BINARY_FILE, "rb"); /* 'b' for binary mode */
    
    if (file == NULL) {
        perror("Error opening binary file for reading");
        return;
    }
    
    printf("\nReading binary data from '%s':\n", BINARY_FILE);
    
    struct Student read_students[3];
    size_t read = fread(read_students, sizeof(struct Student), 3, file);
    
    printf("Read %zu student records:\n", read);
    for (size_t i = 0; i < read; i++) {
        printf("  ID: %d, Name: %s, GPA: %.2f\n",
               read_students[i].id,
               read_students[i].name,
               read_students[i].gpa);
    }
    
    fclose(file);
}

/**
 * Example 5: File positioning
 * Demonstrates fseek, ftell, and rewind
 */
void example_file_positioning(void) {
    printf("\n=== Example 5: File Positioning ===\n");
    
    /* Create a file with known content */
    FILE *file = fopen("position_test.txt", "w");
    if (file == NULL) {
        perror("Error creating position test file");
        return;
    }
    
    fprintf(file, "0123456789ABCDEFGHIJ");
    fclose(file);
    
    /* Reopen for reading */
    file = fopen("position_test.txt", "r");
    if (file == NULL) {
        perror("Error opening position test file");
        return;
    }
    
    /* Read first character */
    printf("Position at start: %ld\n", ftell(file));
    char c = fgetc(file);
    printf("Read: '%c'\n", c);
    printf("Position after read: %ld\n", ftell(file));
    
    /* Seek to position 10 from start */
    fseek(file, 10, SEEK_SET);
    printf("\nSeeked to position 10 (SEEK_SET)\n");
    printf("Position: %ld\n", ftell(file));
    c = fgetc(file);
    printf("Read: '%c'\n", c);
    
    /* Seek 5 positions forward from current */
    fseek(file, 5, SEEK_CUR);
    printf("\nSeeked 5 positions forward (SEEK_CUR)\n");
    printf("Position: %ld\n", ftell(file));
    c = fgetc(file);
    printf("Read: '%c'\n", c);
    
    /* Seek to 5 positions before end */
    fseek(file, -5, SEEK_END);
    printf("\nSeeked to -5 from end (SEEK_END)\n");
    printf("Position: %ld\n", ftell(file));
    c = fgetc(file);
    printf("Read: '%c'\n", c);
    
    /* Rewind to beginning */
    rewind(file);
    printf("\nRewound to start\n");
    printf("Position: %ld\n", ftell(file));
    c = fgetc(file);
    printf("Read: '%c'\n", c);
    
    fclose(file);
    
    /* Clean up test file */
    remove("position_test.txt");
}

/**
 * Example 6: Formatted input with fscanf
 * Demonstrates reading structured data from text file
 */
void example_formatted_input(void) {
    printf("\n=== Example 6: Formatted Input ===\n");
    
    /* Create a data file */
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL) {
        perror("Error creating data file");
        return;
    }
    
    /* Write structured data */
    fprintf(file, "Alice 25 85.5\n");
    fprintf(file, "Bob 30 90.0\n");
    fprintf(file, "Carol 28 88.5\n");
    fclose(file);
    
    printf("Created data file '%s'\n\n", DATA_FILE);
    
    /* Read structured data */
    file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        perror("Error opening data file");
        return;
    }
    
    printf("Reading formatted data:\n");
    printf("%-10s %-5s %-7s\n", "Name", "Age", "Score");
    printf("----------------------------\n");
    
    char name[50];
    int age;
    float score;
    
    /* Read until EOF or error */
    while (fscanf(file, "%49s %d %f", name, &age, &score) == 3) {
        printf("%-10s %-5d %-7.1f\n", name, age, score);
    }
    
    fclose(file);
}

/**
 * Example 7: Error handling and file existence check
 * Demonstrates robust file operations
 */
void example_error_handling(void) {
    printf("\n=== Example 7: Error Handling ===\n");
    
    /* Try to open non-existent file */
    FILE *file = fopen("nonexistent.txt", "r");
    
    if (file == NULL) {
        printf("Expected error: ");
        perror("Opening nonexistent.txt");
        printf("This is normal - file doesn't exist.\n");
    }
    
    /* Create and test file operations */
    file = fopen("error_test.txt", "w");
    if (file == NULL) {
        perror("Error creating test file");
        return;
    }
    
    /* Demonstrate ferror and clearerr */
    fprintf(file, "Test content\n");
    
    if (ferror(file)) {
        printf("Error detected during write.\n");
        clearerr(file); /* Clear error flag */
    } else {
        printf("Write successful, no errors.\n");
    }
    
    fclose(file);
    
    /* Clean up */
    remove("error_test.txt");
}

/**
 * Example 8: File modes summary
 * Educational example showing different open modes
 */
void example_file_modes(void) {
    printf("\n=== Example 8: File Modes Summary ===\n");
    
    printf("Text File Modes:\n");
    printf("  'r'  - Read only (file must exist)\n");
    printf("  'w'  - Write only (creates/truncates file)\n");
    printf("  'a'  - Append (creates if not exists)\n");
    printf("  'r+' - Read and write (file must exist)\n");
    printf("  'w+' - Read and write (creates/truncates)\n");
    printf("  'a+' - Read and append (creates if not exists)\n");
    printf("\n");
    
    printf("Binary File Modes (add 'b'):\n");
    printf("  'rb', 'wb', 'ab', 'rb+', 'wb+', 'ab+'\n");
    printf("\n");
    
    printf("Platform Differences:\n");
    printf("  Windows: Text mode converts \\r\\n <-> \\n\n");
    printf("  Linux/Unix: Text and binary modes are same\n");
    printf("  Best practice: Always use 'b' for binary files\n");
}

/**
 * Example 9: Proper cleanup pattern with multiple files
 */
int example_multiple_files(void) {
    printf("\n=== Example 9: Multiple Files Pattern ===\n");
    
    FILE *input = NULL;
    FILE *output = NULL;
    int result = 0;
    
    /* Open input file */
    input = fopen(TEXT_FILE, "r");
    if (input == NULL) {
        perror("Error opening input file");
        result = -1;
        goto cleanup;
    }
    printf("Opened input file: %s\n", TEXT_FILE);
    
    /* Open output file */
    output = fopen("copy_of_text.txt", "w");
    if (output == NULL) {
        perror("Error opening output file");
        result = -1;
        goto cleanup;
    }
    printf("Opened output file: copy_of_text.txt\n");
    
    /* Copy content */
    char buffer[256];
    int lines = 0;
    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        fputs(buffer, output);
        lines++;
    }
    
    printf("Copied %d lines successfully.\n", lines);
    result = 0;
    
cleanup:
    /* Single cleanup point */
    if (output != NULL) {
        fclose(output);
        printf("Closed output file.\n");
    }
    if (input != NULL) {
        fclose(input);
        printf("Closed input file.\n");
    }
    
    /* Clean up copied file */
    if (result == 0) {
        remove("copy_of_text.txt");
    }
    
    return result;
}

/**
 * Cleanup function to remove example files
 */
void cleanup_example_files(void) {
    remove(TEXT_FILE);
    remove(BINARY_FILE);
    remove(DATA_FILE);
}

/**
 * Main function demonstrating all examples
 */
int main(void) {
    setup_utf8_console();
    
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║           File I/O Operations in C                        ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    printf("\nFile I/O Functions:\n");
    printf("Opening/Closing:\n");
    printf("  fopen(name, mode) - Open file, returns FILE*\n");
    printf("  fclose(file)      - Close file, flush buffers\n");
    printf("\n");
    
    printf("Text I/O:\n");
    printf("  fprintf/fscanf    - Formatted text I/O\n");
    printf("  fgets/fputs       - Line-based I/O\n");
    printf("  fgetc/fputc       - Character I/O\n");
    printf("\n");
    
    printf("Binary I/O:\n");
    printf("  fread(ptr, size, count, file)  - Read binary data\n");
    printf("  fwrite(ptr, size, count, file) - Write binary data\n");
    printf("\n");
    
    printf("Positioning:\n");
    printf("  fseek(file, offset, whence) - Move file position\n");
    printf("  ftell(file)                  - Get current position\n");
    printf("  rewind(file)                 - Reset to start\n");
    printf("\n");
    
    printf("Error Handling:\n");
    printf("  ferror(file)  - Check for errors\n");
    printf("  feof(file)    - Check for end-of-file\n");
    printf("  clearerr()    - Clear error flags\n");
    printf("  perror(msg)   - Print error message\n");
    
    /* Run all examples */
    example_write_text_file();
    example_read_text_file();
    example_append_to_file();
    example_read_text_file(); /* Show appended content */
    example_binary_file();
    example_file_positioning();
    example_formatted_input();
    example_error_handling();
    example_file_modes();
    example_multiple_files();
    
    /* Clean up all example files */
    cleanup_example_files();
    printf("\nCleaned up all example files.\n");
    
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ Key Takeaways:                                             ║\n");
    printf("║ 1. Always check if fopen() returns NULL                   ║\n");
    printf("║ 2. Always fclose() to flush buffers and free resources    ║\n");
    printf("║ 3. Use 'b' flag for binary files (portability)            ║\n");
    printf("║ 4. Check ferror() and feof() after reads                  ║\n");
    printf("║ 5. Buffered I/O is faster than unbuffered                 ║\n");
    printf("║ 6. Binary I/O is faster than text I/O                     ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    return 0;
}
