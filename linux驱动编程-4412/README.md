– 查看总线的命令

	#ls /sys/bus/

– 查看设备号的命令

	#cat /proc/devices

– 查看杂项设备号的命令

	#cat /proc/misc

/***************************************内核的编译、将新生成的内核文件写入4412*********************************************/

自己的ubunut内核源码文件夹为：虚拟机中的文件夹名称为：iTop4412_Kernel_3.0 (.config 文件为 config_for_linux_scp_elite    linux系统)

修改好内核之后，切换到内核目录文件夹 

	make zImage

编译完成之后，zImage文件在：

	arch/arm/boot/zImage 一般编译完成会提示生成的文件夹的位置的


写入4412：


1.将生成的zImage文件传入到platform-tools文件夹 准备烧写

2.进入到超级终端，打开4412，输入指令

这个地方一定要注意：打开4412的时候，一定要进入到uboot模式（即开机后立马按回车键），先连接otg线，在使用fastboot命令，不然的话，就会出现连接不上otg。如果开机4412进入到了

文件系统模式（开机没有任何人为的动作，一直进去了），此时fastboot指令也不起作用了，在此时，你去插上otg线，在电脑的设备管理器中，显示不了该设备，出现unknown device，其实

并不是gdb驱动的问题，往往我们就搞错了，一个非常好的检测gdb驱动的方法就是直接连接一个android手机，然后在设备管理器中看有没有该设备。

	fastboot

3.进入到platform-tools文件夹使用OTG：输入：

	fastboot.exe flash kernel zImage

4. 输入擦除命令：

	fastboot -w

5. 输入重启开发板命令：

	fastboot reboot

6.就可以进入到超级终端中 在/dev目录下查看驱动了

	


/************************************注册设备******************************************************/


– 注册设备。将设备结构体放到平台文件中，会自动注册设备，不用去调用注册设备的函数。

	vim arch/arm/mach-exynos/mach-itop4412.c 

添加代码：

	#ifdef CONFIG_HELLO_CTL  

	struct platform_device s3c_device_hello_ctl = {

        .name = "hello",

        .id            = -1,

	}

	#endif

之后还是在这个文件里将上面写的这个写入到列表里面：

	#ifdef CONFIG_HELLO_CTL	

        &s3c_device_hello_ctl,

	#endif

– 在Kconfig文件中添加编译HELLO设备的宏定义

	这个可以看/drivers/char下面的Kconfig文件    （生成一个HELLO的话，首先在这个文件里面写，仿led的就好了，之
	后就可以在menuconfig看到了）

        在确认一下使用make menuconfig来查看

– 配置menuconfig中的HELLO宏定义，生成新的.config文件

– 生成新的zImage

/**************************************************************************************************/