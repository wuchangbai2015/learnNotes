void Lcd_Address(u16 page,u16 column)
{
	column=column-0x01;
	send_cmd(0xb0+page-1);   /*设置页地址*/ //1-8
	send_cmd(0x10+(column>>4&0x0f));	/*设置列地址的高4位*///0-128
	send_cmd(column&0x0f);	/*设置列地址的低4位*/	
}	

