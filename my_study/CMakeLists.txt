project(my_study)

add_executable(static_list static_list/main.c
        static_list/SeqList.c
        static_list/SeqList.h)
add_executable(delete_duplicates delete_duplicates/main.c)
add_executable(packed_array packed_array/main.c)
add_executable(my_list my_list/s_list.c
        my_list/s_list.h
        my_list/main.c)
