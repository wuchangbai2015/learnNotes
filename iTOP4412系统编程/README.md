一.使用ubuntu实现交叉编译

编译指令为： 

  	arm-none-linux-gnueabi-gcc -o helloword helloworld.c -static 

/****************************************************************************************/

二.烧写ubunut最小系统用的指令：

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

/****************************************************************************************/

三. 代码的加载和运行

u盘拷贝在ubunut下面交叉编译后的代码后挂载到4412上

  	mount /dev/sda1 /mnt/disk/

卸载 

  	umount /mnt/disk/

/****************************************************************************************/

四.设置某一个程序或者其他东西成开机就运行

将helloword文件先拷贝在一个目录下：

  	cp -r /mut/disk /bin

  	vim /etc/init.d/rcS

将helloword文件写在rcs的最后面

  	/bin/helloword &

/****************************************************************************************/

五.tftp服务器的搭建，主要用来给4412传程序，便于调试

4412的ip地址：

  	cat /etc/eth0-setting  

要使TFTP来传递一些简单的文件，4412和ubuntu pc机在需在同一个网段


tftp文件中的/var/tftpboot是服务器的目录（在ubuntu中）需把编译好的二进制文件cp到这里


TFTP传输应用程序：

在4412板子上：

  	tftp -g -l helloworld -r helloworld + 服务器的ip

例如：  

  	cd /bin

  	tftp -g -l helloword -r helloword 192.168.1.104 （192.168.1.104 是ubuntu pc 的ip）

运行：
  
  	chmod 777 helloword 

  	./helloword


/****************************************************************************************/



