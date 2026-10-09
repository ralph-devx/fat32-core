#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


#define __SECTOR_SIZE__ 512


int main() {
    int fd = open("/dev/nvme0n1p1", O_RDONLY);
    if (fd > 2) {
        printf("[fd]: %d\n", fd);
        unsigned char buffer[__SECTOR_SIZE__];
        ssize_t bytes_read = read(fd, buffer, __SECTOR_SIZE__);
        for (size_t i = 0; i < 16 && i < bytes_read; i++) {
            printf("%02X\n", buffer[i]);
        }
        printf("# %d\n", buffer[14]);
    }
    close(fd);
    return 0;
}
