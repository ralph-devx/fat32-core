#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>


#define __SECTOR_SIZE__ 512


int main(int argc, char *argv[]) {
	char name_usb[10];
	snprintf(name_usb, sizeof(name_usb), "/dev/%s", argv[1]);
    int fd = open(name_usb, O_RDONLY);
    if (fd >= 0) {
        printf("[fd]: %d\n", fd);
        unsigned char buffer[__SECTOR_SIZE__ * 3];
        ssize_t bytes_read = read(fd, buffer, __SECTOR_SIZE__ * 3);

		if (bytes_read >= 512) {
			for (size_t i = 0; i < 16 && i < bytes_read; i++) {
				printf("%02X ", buffer[i]);
			}
			printf("\n\n=== Boot Sector and BPB Structure ===\n\n");
			printf("# %-25s %02X\n# %-25s %02X\n# %-25s %02X\n", 
				"[jmpBoot[0]]", buffer[0], 
				"[jmpBoot[1]]", buffer[1], 
				"[jmpBoot[2]]", buffer[2]
			);
			printf("# %-25s %.*s\n",	"[BS_OEMName]",		8, buffer + 3);					// строка OEM/форматировщика
			printf("# %-25s %d\n",		"[BPB_BytsPerSec]",	*(uint16_t *)&buffer[11]);		// количество байт в секторе
			printf("# %-25s %d\n",		"[BPB_SecPerClus]",	buffer[13]);					// количество секторов в кластере
	
			printf("# %-25s %d\n",		"[BPB_RsvdSecCnt]",	*(uint16_t *)&buffer[14]);		// кол-во зарезервированных секторов
			printf("# %-25s %d\n",		"[BPB_NumFATs]",	buffer[16]);					// кол-во таблиц fat
			printf("# %-25s %d\n",		"[BPB_RootEntCnt]",	*(uint16_t *)&buffer[17]);		// для fat32 должно быть 0
			printf("# %-25s %d\n",		"[BPB_TotSec16]",	*(uint16_t *)&buffer[19]);		// общий подсчёт секторов на томе. для fat32 = 0
			printf("# %-25s %02X\n",	"[BPB_Media]",		buffer[21]);					// F8 - стандартное значение для "фиксированных" (несъемных) носителей
			printf("# %-25s %d\n",		"[BPB_FATSz16]",	*(uint16_t *)&buffer[22]);		// для fat32 = 0
			printf("# %-25s %d\n",		"[BPB_SecPerTrk]",	*(uint16_t *)&buffer[24]);		// Количество секторов на дорожке для прерывания 0x13.
			printf("# %-25s %d\n",		"[BPB_NumHeads]",	*(uint16_t *)&buffer[26]);		// Количество головок для прерывания 0x13
			printf("# %-25s %u\n",		"[BPB_HiddSec]",	*(uint32_t *)&buffer[28]);		// Количество скрытых секторов, предшествующих разделу, содержащему данный том FAT
			printf("# %-25s %u\n",		"[BPB_TotSec32]",	*(uint32_t *)&buffer[32]);		// новое 32-битное общее количество секторов на томе. для fat32 не ноль

			printf("\n\n=== FAT32 Structure Starting at Offset 36 ===\n\n");
		
			printf("# %-25s %d\n",		"[BPB_FATSz32]",	*(uint32_t *)&buffer[36]);		// 32-битное значение количества секторов, занятых ОДНОЙ файловой системой FAT32
			// printf("# %-25s %d\n",		"[BPB_ExtFlags]",	*(uint16_t *)&buffer[36]);		// тут надо прям биты разбирать
			
			
		}
	}
    close(fd);
    return 0;
}


/**
 * todo:
 * байты читаются в обратном порядке (little-endian), нужно исправить
 * под исправить: написать алгоритм перестановки little-end в big-end
 */