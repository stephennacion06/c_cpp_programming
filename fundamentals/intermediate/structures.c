/**
 * Structures (struct) - User-Defined Types
 * 
 * Demonstrates structures in C:
 * - Structure declaration and definition
 * - Structure initialization (designated initializers)
 * - Accessing members (. and -> operators)
 * - Nested structures
 * - Structures and functions
 * - typedef for cleaner syntax
 * - Struct alignment and padding
 * 
 * Structures group related data under a single name,
 * forming the foundation of object-oriented concepts in C.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Structure declarations

// Basic structure - Student record
struct Student {
    int id;
    char name[50];
    float gpa;
    bool is_enrolled;
};

// Structure with typedef - cleaner syntax
typedef struct {
    int x;
    int y;
} Point;

// Nested structures - Rect with two Points
typedef struct {
    Point top_left;
    Point bottom_right;
} Rect;

// Complex structure - Employee with nested address
typedef struct {
    char street[100];
    char city[50];
    char state[20];
    int zip_code;
} Address;

typedef struct {
    int employee_id;
    char name[50];
    float salary;
    Address address;  // Nested structure
} Employee;

// Linked structure - each node points to next
typedef struct Node {
    int data;
    struct Node* next;  // Self-referential structure
} Node;

// Function declarations
void demonstrate_basics(void);
void demonstrate_initialization(void);
void demonstrate_nested(void);
void demonstrate_functions(void);
void demonstrate_memory_layout(void);
void print_student(struct Student s);
void update_salary(Employee* emp, float new_salary);
int calculate_area(Rect rect);

int main(void) {
#ifdef _WIN32
    // Enable UTF-8 output on Windows console
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IOFBF, 1000);
#endif

    printf("========================================\n");
    printf("     STRUCTURES (struct) TUTORIAL      \n");
    printf("========================================\n\n");

    demonstrate_basics();
    demonstrate_initialization();
    demonstrate_nested();
    demonstrate_functions();
    demonstrate_memory_layout();

    printf("========================================\n");
    printf("     ALL DEMONSTRATIONS COMPLETED      \n");
    printf("========================================\n");

    return 0;
}

/**
 * Structure Basics
 * Declaration, definition, and member access
 */
void demonstrate_basics(void) {
    printf("========================================\n");
    printf("1. STRUCTURE BASICS\n");
    printf("========================================\n\n");

    // Creating and initializing a structure
    struct Student student1;
    student1.id = 1001;
    strcpy(student1.name, "Alice Johnson");
    student1.gpa = 3.85f;
    student1.is_enrolled = true;

    printf("Student Record:\n");
    printf("  ID: %d\n", student1.id);
    printf("  Name: %s\n", student1.name);
    printf("  GPA: %.2f\n", student1.gpa);
    printf("  Enrolled: %s\n\n", student1.is_enrolled ? "Yes" : "No");

    // Using typedef for cleaner syntax
    Point p1;
    p1.x = 10;
    p1.y = 20;

    printf("Point Structure (with typedef):\n");
    printf("  Coordinates: (%d, %d)\n", p1.x, p1.y);
    printf("  Size: %zu bytes\n\n", sizeof(Point));
}

/**
 * Structure Initialization Methods
 * Demonstrates different ways to initialize structures
 */
void demonstrate_initialization(void) {
    printf("========================================\n");
    printf("2. INITIALIZATION METHODS\n");
    printf("========================================\n\n");

    // Method 1: Member-by-member
    printf("Method 1: Member-by-member\n");
    struct Student s1;
    s1.id = 2001;
    strcpy(s1.name, "Bob Smith");
    s1.gpa = 3.50f;
    s1.is_enrolled = true;
    print_student(s1);

    // Method 2: Initialize at declaration (order matters)
    printf("\nMethod 2: Ordered initialization\n");
    struct Student s2 = {2002, "Carol Davis", 3.92f, true};
    print_student(s2);

    // Method 3: Designated initializers (C99+) - Best Practice
    printf("\nMethod 3: Designated initializers (recommended)\n");
    struct Student s3 = {
        .id = 2003,
        .name = "David Lee",
        .gpa = 3.75f,
        .is_enrolled = false
    };
    print_student(s3);

    // Method 4: Partial initialization (rest defaults to 0)
    printf("\nMethod 4: Partial initialization\n");
    struct Student s4 = {.id = 2004, .name = "Eve Martin"};
    print_student(s4);

    // Copy structures
    printf("\nStructure Copy:\n");
    struct Student s5 = s2;  // Memberwise copy
    printf("  Copied s2 to s5: %s (ID: %d)\n\n", s5.name, s5.id);
}

/**
 * Nested Structures
 * Structures containing other structures
 */
void demonstrate_nested(void) {
    printf("========================================\n");
    printf("3. NESTED STRUCTURES\n");
    printf("========================================\n\n");

    // Rect with nested Points
    Rect rect = {
        .top_left = {.x = 0, .y = 10},
        .bottom_right = {.x = 20, .y = 0}
    };

    printf("Rectangle:\n");
    printf("  Top-left: (%d, %d)\n", rect.top_left.x, rect.top_left.y);
    printf("  Bottom-right: (%d, %d)\n", rect.bottom_right.x, rect.bottom_right.y);
    printf("  Width: %d\n", rect.bottom_right.x - rect.top_left.x);
    printf("  Height: %d\n", rect.top_left.y - rect.bottom_right.y);
    printf("  Area: %d\n\n", calculate_area(rect));

    // Employee with nested Address
    Employee emp = {
        .employee_id = 12345,
        .name = "Frank Wilson",
        .salary = 75000.0f,
        .address = {
            .street = "123 Main St",
            .city = "Springfield",
            .state = "IL",
            .zip_code = 62701
        }
    };

    printf("Employee Record:\n");
    printf("  ID: %d\n", emp.employee_id);
    printf("  Name: %s\n", emp.name);
    printf("  Salary: $%.2f\n", emp.salary);
    printf("  Address:\n");
    printf("    %s\n", emp.address.street);
    printf("    %s, %s %d\n\n", 
           emp.address.city, emp.address.state, emp.address.zip_code);
}

/**
 * Structures and Functions
 * Passing structures to functions (by value and by pointer)
 */
void demonstrate_functions(void) {
    printf("========================================\n");
    printf("4. STRUCTURES AND FUNCTIONS\n");
    printf("========================================\n\n");

    Employee emp = {
        .employee_id = 67890,
        .name = "Grace Taylor",
        .salary = 65000.0f,
        .address = {"456 Oak Ave", "Chicago", "IL", 60601}
    };

    printf("Original salary: $%.2f\n", emp.salary);
    
    // Pass by pointer to modify (efficient for large structures)
    update_salary(&emp, 72000.0f);
    printf("After raise: $%.2f\n\n", emp.salary);

    // Array of structures
    printf("Array of Structures:\n");
    Point points[] = {
        {0, 0},
        {10, 5},
        {20, 10},
        {30, 15}
    };

    printf("  Path coordinates:\n");
    for (int i = 0; i < 4; i++) {
        printf("    Point %d: (%d, %d)\n", i, points[i].x, points[i].y);
    }
    printf("\n");

    // Pointer to structure (-> operator)
    printf("Pointer to Structure:\n");
    Employee* ptr = &emp;
    printf("  Using arrow operator: ptr->name = %s\n", ptr->name);
    printf("  Equivalent to: (*ptr).name = %s\n\n", (*ptr).name);
}

/**
 * Structure Memory Layout
 * Demonstrates padding and alignment
 */
void demonstrate_memory_layout(void) {
    printf("========================================\n");
    printf("5. MEMORY LAYOUT & ALIGNMENT\n");
    printf("========================================\n\n");

    // Structures with padding
    typedef struct {
        char a;      // 1 byte
        // 3 bytes padding
        int b;       // 4 bytes
        char c;      // 1 byte
        // 3 bytes padding
    } PaddedStruct;

    typedef struct {
        char a;      // 1 byte
        char c;      // 1 byte
        // 2 bytes padding
        int b;       // 4 bytes
    } OptimizedStruct;

    printf("Structure Sizes (alignment matters):\n");
    printf("  sizeof(char) = %zu byte\n", sizeof(char));
    printf("  sizeof(int) = %zu bytes\n", sizeof(int));
    printf("  sizeof(float) = %zu bytes\n\n", sizeof(float));

    printf("PaddedStruct { char, int, char }:\n");
    printf("  Expected: 1 + 4 + 1 = 6 bytes\n");
    printf("  Actual: %zu bytes (padding added)\n\n", sizeof(PaddedStruct));

    printf("OptimizedStruct { char, char, int }:\n");
    printf("  Actual: %zu bytes (better packing)\n\n", sizeof(OptimizedStruct));

    printf("Real Structure Sizes:\n");
    printf("  sizeof(Student) = %zu bytes\n", sizeof(struct Student));
    printf("  sizeof(Point) = %zu bytes\n", sizeof(Point));
    printf("  sizeof(Employee) = %zu bytes\n", sizeof(Employee));
    printf("  sizeof(Node) = %zu bytes\n\n", sizeof(Node));

    printf("Best Practices:\n");
    printf("  • Order members by size (largest first) for efficiency\n");
    printf("  • Use pointers for large structures in functions\n");
    printf("  • Consider cache line alignment for performance\n");
    printf("  • Use designated initializers for clarity\n\n");
}

/**
 * Helper Functions
 */

void print_student(struct Student s) {
    printf("  ID: %d | Name: %s | GPA: %.2f | Enrolled: %s\n",
           s.id, s.name, s.gpa, s.is_enrolled ? "Yes" : "No");
}

void update_salary(Employee* emp, float new_salary) {
    emp->salary = new_salary;
}

int calculate_area(Rect rect) {
    int width = rect.bottom_right.x - rect.top_left.x;
    int height = rect.top_left.y - rect.bottom_right.y;
    return width * height;
}
