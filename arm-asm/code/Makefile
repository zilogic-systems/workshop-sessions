%.o: %.s
	arm-none-eabi-as -o $@ $<

%.elf: %.o
	arm-none-eabi-ld -Ttext=0x0 -o $@ $<

%.bin: %.elf
	arm-none-eabi-objcopy -O binary $< $@

%-flash.bin: %.bin
	dd if=/dev/zero of=$@ bs=4096 count=4096
	dd if=$< of=$@ bs=4096 conv=notrunc

clean:
	rm -f *.o
	rm -f *.elf
	rm -f *.bin