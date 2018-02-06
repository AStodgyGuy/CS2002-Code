# If you just type 'make', the first rule is run
# so in this file, 'make stage1' is the same as 'make'.
stage1 : pado.h print_pado.c recursive_pado.c
	gcc -o stage1 recursive_pado.c print_pado.c

# Second stage
# 'make stage2'
stage2 : pado.h print_pado.c iterative_pado.c
	gcc -o stage2 iterative_pado.c print_pado.c

# Third stage
# 'make stage3'
stage3 : pado.h personalised.c second_main.c
	gcc -o stage3 personalised.c second_main.c

# If you put no dependencies, like this rule, then
# the rule is always run.
clean :
	rm stage1 stage2 stage3