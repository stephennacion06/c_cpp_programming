/**
 * ex03_file_copy.c
 * 
 * Exercise: Create a file copy utility with error handling.
 * 
 * Requirements:
 * 1. Copy file content from source to destination
 * 2. Handle binary and text files
 * 3. Provide progress feedback for large files
 * 4. Handle errors gracefully (file not found, permissions, disk full)
 * 5. Verify copy was successful
 * 
 * Memory Implications:
 * - Buffer size affects performance: larger = fewer syscalls
 * - Typical: 4KB-64KB buffer (match OS page size)
 * - Trade-off: memory usage vs. I/O efficiency
 * 
 * Learning objectives:
 * - File I/O operations
 * - Error handling
 * - Buffer management
 * - System programming patterns
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Windows UTF-8 console setup */
#ifdef _WIN32
#include <windows.h>
void setup_utf8_console(void) {
    SetConsoleOutputCP(CP_UTF8);
}
#else
void setup_utf8_console(void) {}
#endif

#define BUFFER_SIZE 8192  /* 8KB buffer - good balance */

/**
 * Get file size
 */
long get_file_size(FILE *file) {
    if (file == NULL) {
        return -1;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    return size;
}

/**
 * Copy file with progress reporting
 * Returns: 0 on success, -1 on error
 */
int copy_file(const char *source_path, const char *dest_path) {
    FILE *source = NULL;
    FILE *dest = NULL;
    unsigned char *buffer = NULL;
    int result = -1;
    
    /* Allocate buffer */
    buffer = (unsigned char*)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Failed to allocate buffer\n");
        return -1;
    }
    
    /* Open source file for reading (binary mode) */
    source = fopen(source_path, "rb");
    if (source == NULL) {
        perror("Error opening source file");
        goto cleanup;
    }
    
    /* Get source file size */
    long file_size = get_file_size(source);
    if (file_size < 0) {
        fprintf(stderr, "Error: Cannot determine file size\n");
        goto cleanup;
    }
    
    printf("Source file size: %ld bytes\n", file_size);
    
    /* Open destination file for writing (binary mode) */
    dest = fopen(dest_path, "wb");
    if (dest == NULL) {
        perror("Error opening destination file");
        goto cleanup;
    }
    
    /* Copy file in chunks */
    size_t total_read = 0;
    size_t bytes_read;
    int last_percent = -1;
    
    printf("Copying");
    fflush(stdout);
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, dest);
        
        if (bytes_written != bytes_read) {
            fprintf(stderr, "\nError: Write failed\n");
            goto cleanup;
        }
        
        total_read += bytes_read;
        
        /* Show progress */
        if (file_size > 0) {
            int percent = (int)((total_read * 100) / file_size);
            if (percent != last_percent && percent % 10 == 0) {
                printf(".");
                fflush(stdout);
                last_percent = percent;
            }
        }
    }
    
    printf(" Done!\n");
    
    /* Check for read errors */
    if (ferror(source)) {
        fprintf(stderr, "Error: Read failed\n");
        goto cleanup;
    }
    
    printf("Successfully copied %zu bytes\n", total_read);
    result = 0;
    
cleanup:
    if (buffer != NULL) {
        free(buffer);
    }
    if (dest != NULL) {
        fclose(dest);
    }
    if (source != NULL) {
        fclose(source);
    }
    
    return result;
}

/**
 * Verify that two files are identical
 */
bool verify_copy(const char *file1_path, const char *file2_path) {
    FILE *file1 = fopen(file1_path, "rb");
    FILE *file2 = fopen(file2_path, "rb");
    bool identical = true;
    
    if (file1 == NULL || file2 == NULL) {
        fprintf(stderr, "Error opening files for verification\n");
        if (file1) fclose(file1);
        if (file2) fclose(file2);
        return false;
    }
    
    /* Compare file sizes first */
    long size1 = get_file_size(file1);
    long size2 = get_file_size(file2);
    
    if (size1 != size2) {
        printf("Verification failed: File sizes differ\n");
        identical = false;
        goto cleanup;
    }
    
    /* Compare contents byte by byte */
    int ch1, ch2;
    size_t position = 0;
    
    while ((ch1 = fgetc(file1)) != EOF) {
        ch2 = fgetc(file2);
        
        if (ch1 != ch2) {
            printf("Verification failed: Difference at byte %zu\n", position);
            identical = false;
            goto cleanup;
        }
        
        position++;
    }
    
    printf("Verification successful: Files are identical\n");
    
cleanup:
    fclose(file1);
    fclose(file2);
    
    return identical;
}

/**
 * Create a test file
 */
void create_test_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating test file");
        return;
    }
    
    fprintf(file, "╔════════════════════════════════════════╗\n");
    fprintf(file, "║        Test File Content               ║\n");
    fprintf(file, "╚════════════════════════════════════════╝\n\n");
    
    fprintf(file, "This is a test file for the file copy utility.\n");
    fprintf(file, "It contains multiple lines of text.\n");
    fprintf(file, "Numbers: 1234567890\n");
    fprintf(file, "Special characters: !@#$%%^&*()_+-={}[]|\\:;\"'<>,.?/\n");
    fprintf(file, "Unicode: α β γ δ ε\n");
    
    /* Write some binary data */
    for (int i = 0; i < 256; i++) {
        fputc(i, file);
    }
    
    fclose(file);
    printf("Created test file: %s\n", filename);
}

/**
 * Main function
 */
int main(int argc, char *argv[]) {
    setup_utf8_console();
    
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║           File Copy Utility                                ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    /* Handle command-line arguments */
    if (argc == 3) {
        /* Copy user-specified files */
        const char *source = argv[1];
        const char *dest = argv[2];
        
        printf("Copying '%s' to '%s'\n", source, dest);
        
        if (copy_file(source, dest) == 0) {
            printf("\nVerifying copy...\n");
            verify_copy(source, dest);
        }
    } else {
        /* Demo mode: create test file and copy it */
        printf("Usage: %s <source> <destination>\n\n", argv[0]);
        printf("Running demo mode...\n\n");
        
        const char *test_file = "test_source.txt";
        const char *copy_file_path = "test_copy.txt";
        
        /* Create test file */
        create_test_file(test_file);
        
        printf("\n");
        
        /* Copy file */
        if (copy_file(test_file, copy_file_path) == 0) {
            printf("\nVerifying copy...\n");
            verify_copy(test_file, copy_file_path);
        }
        
        /* Clean up */
        printf("\nCleaning up test files...\n");
        remove(test_file);
        remove(copy_file_path);
        printf("Demo completed.\n");
    }
    
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ Performance Notes:                                         ║\n");
    printf("║ - Buffer size: 8KB (good for most files)                  ║\n");
    printf("║ - Larger buffers: fewer syscalls, more memory             ║\n");
    printf("║ - Binary mode: prevents line ending conversion            ║\n");
    printf("║ - Always verify critical copies                           ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    return 0;
}
