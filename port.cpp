#include "port.h"

Port::Port(uint16 portnumber)
{
    this->portnumber = portnumber;
}
Port::~Port()
{
}

Port8Bit::Port8Bit(uint16 portnumber) : Port(portnumber)
{
    
}

uint8 Port8Bit::Read()
{
    uint8 result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}
void Port8Bit::Write(uint8 data)
{
    __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portnumber));
    
}
Port8Bit::~Port8Bit()
{
}


Port8BitSlow::Port8BitSlow(uint16 portnumber) : Port8Bit(portnumber)
{
}


void Port8BitSlow::Write(uint8 data)
{
    __asm__ volatile("outb %0, %1 \njmp 1f\n1: jmp 1f\n 1:" : : "a" (data), "Nd" (portnumber));
    
}
Port8BitSlow::~Port8BitSlow()
{
}





Port16Bit::Port16Bit(uint16 portnumber) : Port(portnumber)
{
    
}

uint8 Port16Bit::Read()
{
    uint16 result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}
void Port16Bit::Write(uint16 data)
{
    __asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (portnumber));
    
}
Port16Bit::~Port16Bit()
{
}





Port32Bit::Port32Bit (uint16 portnumber) : Port(portnumber)
{
    
}

uint8 Port32Bit::Read()
{
    uint32 result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}
void Port32Bit::Write(uint32 data)
{
    __asm__ volatile("outl %0, %1" : : "a" (data), "Nd" (portnumber));
    
}
Port32Bit::~Port32Bit()
{
}


