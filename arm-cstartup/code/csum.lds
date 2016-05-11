/* ### START: csum.full */
/* ### START: flash.part */
SECTIONS {
	. = 0x00000000;
	.text : { 
	      * (vectors);
	      * (.text); 
	}
	.rodata : {
	      * (.rodata);
	}
	flash_sdata = .;
/* ### END: flash.part */

/* ### START: data.part */
	. = 0xA0000000;
	ram_sdata = .;
	.data : AT (flash_sdata) { 
	      * (.data); 
	}
	ram_edata = .;
	data_size = ram_edata - ram_sdata;
/* ### END: data.part */

/* ### START: bss.part */
	sbss = .;
	.bss : { 
	     * (.bss);
	}
	ebss = .;
	bss_size = ebss - sbss;
}
/* ### END: bss.part */
/* ### END: csum.full */
