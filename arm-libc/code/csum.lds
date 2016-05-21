/* ### START: csum.full */
/* ### START: flash.part */
SECTIONS {
	. = 0x00000000;
	.text : { 
	      * (vectors);
	      * (.text); 
	}
	.rodata : {
	      * (.rodata*);
	}
	.ARM.exidx : {
    	      * (.ARM.exidx*);
    	      * (.gnu.linkonce.armexidx.*);
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
/* ### END: bss.part */

/* ### START: heap.part */
 	. = ALIGN(8);
	heap_low = .; /* for _sbrk */
	. = . + 0x10000; /* 64kB of heap memory */
	heap_top = .; /* for _sbrk */
}
/* ### END: heap.part */
/* ### END: csum.full */
