GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -ggdb3 
ASARAMS = --32
LDPARAMS = -melf_i386
objects = loader.o gdt.o port.o interruptstbs.o interrupts.o kernel.o

%.o: %.cpp
	gcc $(GPPPARAMS)  -c -o $@ $<
	
%.o: %.s
	as $(ASARAMS) -o $@ $<
	
kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)
	
kernel.iso: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "my Operating system"{' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso
	rm -rf iso

run: kernel.iso
	(killall VirtualBox; sleep 1) || true
	VirtualBox --startvm "SmartWare" &
	
	
.PHONY: clean
clean:
	rm $(objects)
	rm -rf iso
	rm kernel.iso
	rm kernel.bin

	
