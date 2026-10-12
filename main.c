#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define __SECTOR_SIZE__ 512


int main() {
    int fd = open("/dev/sda1", O_RDONLY);
    if (fd > 2) {
        printf("[fd]: %d\n", fd);
        unsigned char buffer[__SECTOR_SIZE__];
        ssize_t bytes_read = read(fd, buffer, __SECTOR_SIZE__);
        for (size_t i = 0; i < 16 && i < bytes_read; i++) {
            printf("%02X\n", buffer[i]);
        }
        printf("# %.*s\n", 8, buffer + 3);				// строка OEM/форматировщика
        printf("# %d\n", buffer[12] << 8 | buffer[11]);	// количество байт в секторе
        printf("# %d\n", buffer[13]);					// количество секторов в кластере

		printf("# %d\n", buffer[14]);					// кол-во зарезервированных секторов
		printf("# %d\n", buffer[16]);					// кол-во таблиц fat
    }
    close(fd);
    return 0;
}


/**
 * todo:
 * байты читаются в обратном порядке (little-endian), нужно исправить
 * под исправить: написать алгоритм перестановки little-end в big-end
 */