#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>


int main(void) {
    int d = 0;
    char *source_f = "a";
    char *dir = "dir1";
    FILE *f;
    char symlink_elem[3];
    if (mkdir(dir, 0700) == -1) {
        perror("mkdir failed");
        return 1;
    }
    f = fopen(source_f, "w");
    fclose(f);

    for (; d < 1000; ++d) {
            char e = 'a' + d;
            snprintf(symlink_elem, 3, "%c%c", e, e);
            symlink(source_f, symlink_elem);
            if (fopen(symlink_elem, "r") == NULL) {
                printf("Достигнутая глубина рекурсии: %d\n", d);
                break;
            }
            printf("Текущая глубина рекурсии: %d\n", d + 1);
    }

    for (int i = 0; i < d; ++i) {
            char e = 'a' + i;
            snprintf(symlink_elem, 3, "%c%c", e, e);
            unlink(symlink_elem);
    }
    unlink(source_f);
    rmdir(dir);
    return 0;
}