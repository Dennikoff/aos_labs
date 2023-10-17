#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char** argv) {

    //int stat(const char *file_name, struct stat *buf);
    if(argc != 2) {
        printf("Invalid number of parametres\n");
        return -1;
    }
    char* filename = argv[1];

    struct stat myStat;

    const int statRes = stat(filename, &myStat);
    if (statRes == -1) {
        perror("Error with stat!");
        return -1;
    }

    printf("Device: %d\n", myStat.st_dev); // Устройство где файл
    printf("Inode: %d\n", myStat.st_ino); // номер Index Node где хранится инфа о файле
    printf("Mode: %d\n", myStat.st_mode); // Режим доступа
    printf("Count of links: %d\n", myStat.st_nlink); // количество ссылок
    printf("UID: %d\n", myStat.st_uid); // ID пользователя создателя
    printf("GID: %d\n", myStat.st_gid); // ID группы пользователя создателя
    printf("Device type: %d\n", myStat.st_rdev); // номер сстройства, если это устройство
    printf("Size: %d\n", myStat.st_size); // размер файла
    printf("Block size: %d\n", myStat.st_blksize); // размер файла в блоках 
    printf("Blocks: %d\n", myStat.st_blocks); // предпочтительный размер файла
    printf("Last access time: %d\n", myStat.st_atime); // дата доступа
    printf("Last modify time: %d\n", myStat.st_mtime); // дата модификации (изменения внутренностей)
    printf("Last change time: %d\n", myStat.st_ctime); // дата изменения информации о файле в inode (имя, кол-во ссылок, пользователь, размер и тд)
    return 0;
}