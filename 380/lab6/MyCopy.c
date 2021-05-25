 /*

 * Andrew Virts
 * CS380
 * Lab6 -- Memory Mapping
 * Due date: 4/3/2020
 
 */
 
 /*
 *******************************************************************************
 * INCLUDE DIRECTIVES
 *******************************************************************************
 */

 #include <unistd.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <sys/mman.h>
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>


int
main (int argc, char* argv[])
{

    if (argc != 3) {
        printf("Sir/Ma'am, can you please make sure you're entering 3 arguments, and use lots of hand sanitizer! :-)\n");
        exit(1);
    }

    int file1 = open(argv[1], O_RDONLY);
    int file2 = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    struct stat filesize;
    fstat(file1, &filesize);
    ftruncate(file2, filesize.st_size);

    void* map1 = mmap(NULL, filesize.st_size, PROT_READ, MAP_SHARED, file1, 0);
    void* map2 = mmap(NULL, filesize.st_size, PROT_WRITE, MAP_SHARED, file2, 0);
    memcpy(map2, map1, filesize.st_size);

    munmap(map1, filesize.st_size);
    munmap(map2, filesize.st_size);

    close(file1);
    close(file2);

}