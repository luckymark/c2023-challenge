project(class)

add_executable(struct struct/main.c)

add_executable(pop pop/main.c)

add_executable(choose choose/main.c)

add_executable(insert insert/main.c)

add_executable(stack stack/main.c)

add_executable(others_1 others_1/main.c)

add_executable(reverse_bolan_SeqLink reverse_bolan_SeqLink/main.c
        reverse_bolan_SeqLink/SeqList.c
        reverse_bolan_SeqLink/SeqList.h)

add_executable(list list/main.c)

add_executable(queue queue/main.c
        queue/Queue.c
        queue/Queue.h)
