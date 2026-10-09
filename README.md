# fat32-core


## Полезные инспектирующие диски команды:

```Bash
# выводит список всех блочных устройств (дисков и разделов) в виде дерева:
> lsblk

NAME        MAJ:MIN RM   SIZE RO TYPE  MOUNTPOINTS
sda           8:0    1  58.2G  0 disk  
└─sda1        8:1    1  58.2G  0 part  /run/media/ralph/STORE N GO
zram0       252:0    0  31.2G  0 disk  [SWAP]
nvme0n1     259:0    0   1.8T  0 disk  
├─nvme0n1p1 259:1    0     2G  0 part  /boot
└─nvme0n1p2 259:2    0   1.8T  0 part  
  └─root    253:0    0   1.8T  0 crypt /var/log
                                       /var/cache/pacman/pkg
                                       /home
                                       /
nvme1n1     259:3    0 476.9G  0 disk  
├─nvme1n1p1 259:4    0   100M  0 part  
├─nvme1n1p2 259:5    0    16M  0 part  
├─nvme1n1p3 259:6    0 476.3G  0 part  
└─nvme1n1p4 259:7    0   558M  0 part 
```

*Чтобы увидеть дополнительную информацию о типах файловых систем и метриках, добавьте флаг -f или -a.*

```Bash
# показывает уже примонтированные файловые системы и сколько свободного места на них осталось (в человекочитаемом формате):
> df -h

Filesystem        Size  Used Avail Use% Mounted on
dev                16G     0   16G   0% /dev
run                16G  1.8M   16G   1% /run
efivarfs          256K   97K  155K  39% /sys/firmware/efi/efivars
/dev/mapper/root  1.9T  393G  1.5T  22% /
tmpfs              16G   18M   16G   1% /dev/shm
none              1.0M     0  1.0M   0% /run/credentials/systemd-journald.service
none              1.0M     0  1.0M   0% /run/credentials/systemd-resolved.service
tmpfs              16G   47M   16G   1% /tmp
/dev/mapper/root  1.9T  393G  1.5T  22% /home
/dev/mapper/root  1.9T  393G  1.5T  22% /var/cache/pacman/pkg
/dev/mapper/root  1.9T  393G  1.5T  22% /var/log
/dev/nvme0n1p1    2.0G  422M  1.6G  21% /boot
tmpfs             3.2G  864K  3.2G   1% /run/user/1000
/dev/sda1          59G  128K   59G   1% /run/media/ralph/STORE N GO
```

```Bash
# выводит подробную информацию о физических дисках, их разделах и разметке (требуются права администратора):
> sudo fdisk -l

Disk /dev/sda: 58.2 GiB, 62495129600 bytes, 122060800 sectors
Disk model: STORE N GO      
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x0551ac51

Device     Boot Start       End   Sectors  Size Id Type
/dev/sda1  *       64 122060799 122060736 58.2G  b W95 FAT32
```

```Bash
# или ls -l /dev/nvme* — показывает список подключенных SATA/USB-дисков или NVMe-накопителей напрямую из системного каталога устройств:
> ls -l /dev/sd*

Permissions Size User Date Modified Name
brw-rw----   8,0 root  9 Oct 06:08  󰡯 /dev/sda
brw-rw----   8,1 root  9 Oct 06:08  󰡯 /dev/sda1
```

```Bash
# показывает UUID, метки (LABEL) и типы файловых систем для всех разделов:
> sudo blkid

/dev/nvme0n1p1: UUID="4E82-A16F" BLOCK_SIZE="512" TYPE="vfat" PARTUUID="f4216e7c-edd6-4205-aa04-0d541cb257c7"
/dev/nvme0n1p2: UUID="285c9407-f865-4f9a-a077-8554784dee3d" TYPE="crypto_LUKS" PARTUUID="1b17fe64-5720-4323-aec7-26ead9058080"
/dev/nvme1n1p4: BLOCK_SIZE="512" UUID="5C2C8EAA2C8E7F30" TYPE="ntfs" PARTUUID="f1c606d0-f257-469f-9285-3ea53d930fa1"
/dev/nvme1n1p3: LABEL="SYSTEM" BLOCK_SIZE="512" UUID="F47EF1217EF0DCF4" TYPE="ntfs" PARTLABEL="Basic data partition" PARTUUID="14042256-1967-4ea1-9d02-1585db7f3d43"
/dev/nvme1n1p1: UUID="CAE5-7A56" BLOCK_SIZE="512" TYPE="vfat" PARTLABEL="EFI system partition" PARTUUID="964b578f-e2a8-4970-a2b5-a7428cdf312e"
/dev/mapper/root: UUID="4c012154-f9cd-40f5-9c72-d0d4bc0c118a" UUID_SUB="cd4a333e-93ad-4c0a-872b-e476133c33a6" BLOCK_SIZE="4096" TYPE="btrfs"
/dev/nvme1n1p2: PARTLABEL="Microsoft reserved partition" PARTUUID="de73b82c-af74-452e-ac5a-12c3687608c6"
/dev/sda1: LABEL_FATBOOT="DISK_IMG" LABEL="STORE N GO" UUID="0551-AC51" BLOCK_SIZE="512" TYPE="vfat" PARTUUID="0551ac51-01"
/dev/zram0: LABEL="zram0" UUID="9d9ad46c-8590-4dd2-a5f1-f2146fc9226a" TYPE="swap"
```
