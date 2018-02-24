#include <stdio.h>

/* Print three stack frames, of the three callers directly above.
 */
void print_stack() {
   
    //current base pointer
    long current_rbp;
    asm("movq %%rbp, %0;" : "=r"(current_rbp));
    printf("current rbp absolute address: %p\n", (void*)current_rbp);

    //caller of print_stack
    long first_rbp;
    asm("movq (%1), %0;" : "=r"(first_rbp) : "r"(current_rbp));
    printf("first call absolute address: %p\n", (void*)first_rbp);

    //caller of caller of print_stack
    long second_rbp;
    asm("movq (%1), %0;" : "=r"(second_rbp) : "r"(first_rbp));
    printf("second call absolute address: %p\n", (void*)second_rbp);

    //new line to separate
    printf("\n");

    //Calculate size of frame
    long size_of_first_frame = first_rbp - current_rbp;
    long size_of_second_frame = second_rbp - first_rbp;
    //16 bytes taken off due to offset
    size_of_first_frame = size_of_first_frame - 16; 
    //size of frame by size of a byte
    long number_of_instructions = size_of_first_frame / 8;

    //subtracting offset from first rbp
    first_rbp = first_rbp - 16;

    // for loop to print out each instruction in second_rbp
    long volatile result;    //what is at the memory address
    long result_at = -size_of_first_frame; //where the memory address is
    printf("Total number of instructions for first stack frame: %ld\n", number_of_instructions);
    printf("Address                                 Relative Offset          Value\n");
    for (int i = 0; i < number_of_instructions; i++) {
        asm("movq (%1), %0;" : "=r"(result) : "r"(first_rbp));
        printf("%p                             %ld                     %ld\n", (void*)first_rbp, result_at, result);
        first_rbp = first_rbp - 8;    //minus 8 to traverse the memory address
        result_at = result_at + 8;      //plus 8 to show which address is being shown
    }

    //new line to separate
    printf("\n");

    //16 bytes taken off due to offset
    size_of_second_frame = size_of_second_frame - 16; 
    //size of frame by size of a byte
    number_of_instructions = size_of_second_frame / 8;

    //subtracting offset from second rbp
    second_rbp = second_rbp - 16;

    // for loop to print out each instruction in second_rbp
    result = 0;
    result_at = -size_of_second_frame; //where the memory address is
    printf("Total number of instructions for second stack frame: %ld\n", number_of_instructions);
    printf("Address                                 Relative Offset          Value\n");
    for (int i = 0; i < number_of_instructions; i++) {
        asm("movq (%1), %0;" : "=r"(result) : "r"(second_rbp));
        printf("%p                             %ld                     %ld\n", (void*)second_rbp, result_at, result);
        second_rbp = second_rbp - 8;    //minus 8 to traverse the memory address
        result_at = result_at + 8;      //plus 8 to show which address is being shown
    }

}

