#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H
    #include "types.h"
    #include "port.h"
    #include "gdt.h"
    class InterrupManager{
       
    protected:
        
        struct GateDescriptor{
            uint16 handleAddressLowBits;
            uint16 gdt_codeSegmentSelector;
            uint8 reserved;
            uint8 access;
            uint16 handleAddressHighBits;
            
        } __attribute__((packet)); 
        
        static GateDescriptor interruptDescriptorTable[256];
        
        struct interruptDescriptorTablePointer{
            uint32 base;
            uint16 size;
        } __attribute__((packet));
        
        static void SetInterruptDescriptorTableEntry(
            
            uint8 interruptNumber,
            uint16 codeSegmenteSelectorOffset,
            void (*handler)(),
            uint8 DescriptorPrivilegeLevel,
            uint8 DescriptorType
                                                     
                                                    
            
        );
        
        
        
        Port8BitSlow picMasterCommand;
        Port8BitSlow picMasterData;
        Port8BitSlow picSlaveCommand;
        Port8BitSlow picSlaveData;
        
        
        
        
    public:
        
        InterrupManager ( GlobalDescriptorTable* gdt );
        ~InterrupManager();
        
        void Activate();
        
        static uint32 HandleInterrupt(uint8 interruptNumber, uint32 esp);
        
        static void IgnoreInterruptRequest();
        static void HandleInterruptRequest0x00();
        static void HandleInterruptRequest0x01();       
        
    };

    
#endif
