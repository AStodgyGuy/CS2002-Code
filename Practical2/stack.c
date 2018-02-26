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

    //calller of caller of caller of print_stack
    long third_rbp;
    asm("movq (%1), %0;" : "=r"(third_rbp) : "r"(second_rbp));
    printf("third call absolute address: %p\n", (void*)third_rbp);

    //new line to separate
    printf("\n");

    //number of frames to print
    int number_of_frames = 3;
    //Calculate size of each frame
    long size_of_frame, number_of_instructions, working_rbp;
    //for loop to print out three stack frames
    for (int i = 0; i < number_of_frames; i++) {
        //first frame
        if (i == 0) {
            working_rbp = first_rbp;
            size_of_frame = first_rbp - current_rbp;
        //second frame
        } else if (i == 1) {
            working_rbp = second_rbp;
            size_of_frame = second_rbp - first_rbp;
        //third frame
        } else if (i == 2) {
            working_rbp = third_rbp;
            size_of_frame = third_rbp - second_rbp;
        }
        //subtracting top padding
        working_rbp = working_rbp - sizeof(working_rbp);
        //subtracting bottom padding
        size_of_frame = size_of_frame - sizeof(working_rbp);
        //size of frame divded by size of a byte to get number of instructions
        number_of_instructions = size_of_frame / sizeof(working_rbp);

        //print
        printf("Address\t\tRelative Offset\t\tValue\n");
        long result;    //what is at the memory address
        long result_at = -sizeof(working_rbp); //where the memory address is
        for (int j = 0; j < number_of_instructions; j++) {
            asm("movq (%1), %0;" : "=r"(result) : "r"(working_rbp));
            //pointers at these locations
            if (result_at == -8 || result_at == -40) {
                printf("%p\t\t%ld\t\t%p\n", (void*)working_rbp, result_at, (void*)result);
            } else {
                printf("%p\t\t%ld\t\t%ld\n", (void*)working_rbp, result_at, result);
            }
            working_rbp = working_rbp - sizeof(working_rbp);    //minus 8 to traverse the memory address
            result_at = result_at - sizeof(working_rbp);      //plus 8 to show which address is being shown
        }
        //new line to separate
        printf("\n");
    }    
}
