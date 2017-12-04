使用reStructuredText工具编写自己的学习笔记，可下载于本地使用网页查看

Windows下sphinx+reStructuredText的配置参考链接：http://www.th7.cn/system/win/201501/81743.shtml

烧写ubunut最小系统用的指令：

拷贝镜像到“platform-tools”文件夹下
1.进入uboot模式

上电，启动开发板，超级终端中，按“回车”键（一上电就按），进入uboot模式

2.分区命令，超级终端中，输入命令：

fdisk -c 0

3.格式化命令，超级终端中输入命令：

fatformat mmc 0:1

ext3format mmc 0:2

ext3format mmc 0:3

ext3format mmc 0:4

4.连接命令，超级终端中输入命令：

fastboot




烧写命令，在windows命令行输入:

1.烧写uboot命令（不建议烧写，已经有了）：

fastboot.exe flash bootloader u-boot-iTOP-4412.bin

2.烧写zImage内核命令：

fastboot.exe flash kernel zImage


3.输入烧写ramdisk 命令:

fastboot.exe flash ramdisk ramdisk-uboot.img

4.输入烧写system 文件系统命令:

fastboot.exe flash system system.img

输入擦除命令：

fastboot -w

输入重启开发板命令：

fastboot reboot

