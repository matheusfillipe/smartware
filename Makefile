GPPPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -ggdb3  -Wno-stack-protector -Wwrite-strings -Wno-write-strings 
ASARAMS = --32
LDPARAMS = -melf_i386
objects = obj/loader.o obj/gdt.o obj/drivers/driver.o obj/common/console.o obj/hardwarecom/port.o obj/hardwarecom/interruptstbs.o obj/hardwarecom/interrupts.o obj/hardwarecom/pci.o obj/drivers/keyboard.o obj/drivers/mouse.o obj/kernel.o 
 

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GPPPARAMS)  -c -o $@ $<
	
obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASARAMS) -o $@ $<
	
kernel.bin: linker.ld $(objects)
	mkdir -p $(@D)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

qemu: kernel.bin
	qemu-system-x86_64 -kernel $< -s
	
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
	#(killall VirtualBox; sleep 1) || true
	
	VBoxHeadless  --startvm "SmartWare" -v on --settingspw 123 &
	krdc vnc://127.0.0.1:3389
	VBoxManage controlvm SmartWare poweroff soft
	#Comment the lines above and uncomment this in case you need
	#VirtualBox  --startvm "SmartWare"

	
.PHONY: clean
clean:
	rm -rf obj
	rm -rf iso
	rm kernel.iso
	rm kernel.bin

	
