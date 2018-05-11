GPPPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -ggdb3  -Wno-stack-protector -Wwrite-strings -Wno-write-strings 
ASARAMS = --32
LDPARAMS = -melf_i386
objects = obj/loader.o obj/gdt.o obj/drivers/driver.o obj/hardwarecom/port.o obj/hardwarecom/interruptstbs.o obj/hardwarecom/interrupts.o obj/drivers/keyboard.o obj/drivers/mouse.o obj/kernel.o 

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GPPPARAMS)  -c -o $@ $<
	
obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASARAMS) -o $@ $<
	
kernel.bin: linker.ld $(objects)
	mkdir -p $(@D)
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
	rm -f obj
	rm -rf iso
	rm kernel.iso
	rm kernel.bin

	
