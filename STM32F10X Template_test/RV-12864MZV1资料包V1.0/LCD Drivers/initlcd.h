	send_cmd(0xe2);	 //软复位
	delayms(10);
	send_cmd(0xa0);  //列扫描顺序：从左到右
	send_cmd(0xc8);  //行扫描顺序：从下到上，c0从上到下
	send_cmd(0xa2);	 //设置偏压比1/9
	send_cmd(0x2f);	 //控制电源
	send_cmd(0x25);	 //粗调对比度
	send_cmd(0x81);  //微调对比度,进入微调对比度命令
	send_cmd(0x19);  //设置电压的参数RR值(对比度请修改此值，调浓增大此值，反之调淡)
	send_cmd(0x40);  //起始行：第一行开始
	send_cmd(0xaf);  //开显示
