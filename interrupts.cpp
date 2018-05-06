#include "interrupts.h"

void printf(char *s);

InterrupManager::GateDescriptor InterrupManager::interruptDescriptorTable[256];

void InterrupManager::SetInterruptDescriptorTableEntry(uint8 interruptNumber, uint16 codeSegmenteSelectorOffset, void (*handler)(), uint8 DescriptorPrivilegeLevel, uint8 DescriptorType)
{
    const uint8 IDT_DESC= 0x80;
    interruptDescriptorTable[interruptNumber].handleAddressLowBits = ((uint32) handler) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].handleAddressHighBits=(((uint32) handler) >> 16) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmenteSelectorOffset;
    interruptDescriptorTable[interruptNumber].access = IDT_DESC | DescriptorType | ((DescriptorPrivilegeLevel&3)<< 5);
    interruptDescriptorTable[interruptNumber].reserved=0;
}

InterrupManager::InterrupManager(GlobalDescriptorTable* gdt) : 
picMasterCommand(0x20),
picMasterData(0x21),
picSlaveCommand(0xA0),
picSlaveData(0xA1)

{
    
    uint16 CodeSegment = gdt -> CodeSegmenteSelector();
    const uint8 IDT_INT=0xE;
    
    for(uint16 i=0; i<256; i++){
        SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INT);
    }
    
    SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INT);   
    SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INT);
    
    
    picMasterCommand.Write(0x11);
    picSlaveCommand.Write(0x11);    
    
    picMasterData.Write(0x20);
    picSlaveData.Write(0x28);
 
    picMasterData.Write(0x04);
    picSlaveData.Write(0x02);
 
    picMasterData.Write(0x01);
    picSlaveData.Write(0x01);

    picMasterData.Write(0x00);
    picSlaveData.Write(0x00);
 
    
    interruptDescriptorTablePointer idt;
    idt.size = 256*sizeof(GateDescriptor)-1;
    idt.base = (uint32) interruptDescriptorTable;
    
    asm volatile("lidt %0" : : "m" (idt));
}

InterrupManager::~InterrupManager()
{
}

void InterrupManager::Activate()
{

    asm("sti");
}



uint32 InterrupManager::HandleInterrupt(uint8 interruptNumber, uint32 esp)
{
    printf("INTERRUP");
    return esp;
}




