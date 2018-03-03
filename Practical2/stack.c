#include <stdio.h>

/* Print three stack frames, of the three callers directly above.
 */
void print_stack() {
   
    //current base pointer
    long current_rbp;
    asm("movq %%rbp, %0;" : "=r"(current_rbp));
    printf("Current rbp absolute address: %p\n\n", (void*)current_rbp);

    //number of frames to print
    int number_of_frames = 3;
    //Calculate size of each frame
    long size_of_frame, number_of_instructions, working_rbp, first_rbp, second_rbp, third_rbp;
    //for loop to print out three stack frames
    for (int i = 0; i < number_of_frames; i++) {
        //first frame
        if (i == 0) {
            //caller of print_stack
            asm("movq (%1), %0;" : "=r"(first_rbp) : "r"(current_rbp));
            printf("First call absolute address: %p\n", (void*)first_rbp);
            working_rbp = first_rbp;
            size_of_frame = first_rbp - current_rbp;
        //second frame
        } else if (i == 1) {
            //caller of caller of print_stack
            asm("movq (%1), %0;" : "=r"(second_rbp) : "r"(first_rbp));
            printf("Second call absolute address: %p\n", (void*)second_rbp);
            working_rbp = second_rbp;
            size_of_frame = second_rbp - first_rbp;
        //third frame
        } else if (i == 2) {
            //calller of caller of caller of print_stack
            asm("movq (%1), %0;" : "=r"(third_rbp) : "r"(second_rbp));
            printf("Third call absolute address: %p\n", (void*)third_rbp);
            working_rbp = third_rbp;
            size_of_frame = third_rbp - second_rbp;
        }
        
        //size of frame divded by size of a byte to get number of instructions
        number_of_instructions = size_of_frame / sizeof(working_rbp);

        //print
        printf("Address\t\t Relative Offset      Value\n");
        long result;    //what is at the memory address
        long result_at = 0; //where the memory address is relative to rbp
        for (int j = 0; j < number_of_instructions; j++) {
            asm("movq (%1), %0;" : "=r"(result) : "r"(working_rbp));
            //pointers at locations -8, -40 and -72
            if (result_at == 0 || result_at == -8 || result_at == -40 || result_at == -72) {
                printf("%p\t|\t%ld\t|\t%p\n", (void*)working_rbp, result_at, (void*)result);
            } else {
                printf("%p\t|\t%ld\t|\t%ld\n", (void*)working_rbp, result_at, result);
            }
            working_rbp = working_rbp - sizeof(working_rbp);    //minus 8 to traverse the memory address
            result_at = result_at - sizeof(working_rbp);      //plus 8 to show which address is being shown
        }
        //new line to separate
        printf("\n");
    }    
}
