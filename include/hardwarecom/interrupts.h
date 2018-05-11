
#ifndef __SMARTWARE__INTERRUPTMANAGER_H
#define __SMARTWARE__INTERRUPTMANAGER_H

    #include <gdt.h>
    #include <common/types.h>

#include <hardwarecom/port.h>

 



 
    
namespace smartware{
    namespace hardwarecom{
       

        
   class InterruptManager;
    
    class InterruptHandler{
        
    protected:
        smartware::common::uint8  interruptNumber;
        InterruptManager*  interruptManager;
        
        InterruptHandler(smartware::common::uint8 interruptNumber, InterruptManager* interruptManager);
        ~InterruptHandler();
        
    public:
        virtual smartware::common::uint32 HandleInterrupt(smartware::common::uint32 esp);
        
        
    };
    
    

    class InterruptManager
    {
       friend class InterruptHandler;
        protected:
            
            
            static InterruptManager* ActiveInterruptManager;
            InterruptHandler* handles[256];

            struct GateDescriptor
            {
                smartware::common::uint16 handlerAddressLowBits;
                smartware::common::uint16 gdt_codeSegmentSelector;
                smartware::common::uint8 reserved;
                smartware::common::uint8 access;
                smartware::common::uint16 handlerAddressHighBits;
            } __attribute__((packed));

            static GateDescriptor interruptDescriptorTable[256];

            struct InterruptDescriptorTablePointer
            {
                smartware::common::uint16 size;
                smartware::common::uint32 base;
            } __attribute__((packed));

            smartware::common::uint16 hardwareInterruptOffset;
            //static InterruptManager* ActiveInterruptManager;
            static void SetInterruptDescriptorTableEntry(smartware::common::uint8 interrupt,
                smartware::common::uint16 codeSegmentSelectorOffset, void (*handler)(),
                smartware::common::uint8 DescriptorPrivilegeLevel, smartware::common::uint8 DescriptorType);


            static void InterruptIgnore();

            static void HandleInterruptRequest0x00();
            static void HandleInterruptRequest0x01();
            static void HandleInterruptRequest0x02();
            static void HandleInterruptRequest0x03();
            static void HandleInterruptRequest0x04();
            static void HandleInterruptRequest0x05();
            static void HandleInterruptRequest0x06();
            static void HandleInterruptRequest0x07();
            static void HandleInterruptRequest0x08();
            static void HandleInterruptRequest0x09();
            static void HandleInterruptRequest0x0A();
            static void HandleInterruptRequest0x0B();
            static void HandleInterruptRequest0x0C();
            static void HandleInterruptRequest0x0D();
            static void HandleInterruptRequest0x0E();
            static void HandleInterruptRequest0x0F();
            static void HandleInterruptRequest0x31();

            static void HandleException0x00();
            static void HandleException0x01();
            static void HandleException0x02();
            static void HandleException0x03();
            static void HandleException0x04();
            static void HandleException0x05();
            static void HandleException0x06();
            static void HandleException0x07();
            static void HandleException0x08();
            static void HandleException0x09();
            static void HandleException0x0A();
            static void HandleException0x0B();
            static void HandleException0x0C();
            static void HandleException0x0D();
            static void HandleException0x0E();
            static void HandleException0x0F();
            static void HandleException0x10();
            static void HandleException0x11();
            static void HandleException0x12();
            static void HandleException0x13();

            static smartware::common::uint32 HandleInterrupt(smartware::common::uint8 interrupt, smartware::common::uint32 esp);
            smartware::common::uint32 DoHandleInterrupt(smartware::common::uint8 interrupt, smartware::common::uint32 esp);

           Port8BitSlow programmableInterruptControllerMasterCommandPort;
           Port8BitSlow programmableInterruptControllerMasterDataPort;
           Port8BitSlow programmableInterruptControllerSlaveCommandPort;
           Port8BitSlow programmableInterruptControllerSlaveDataPort;

        public:
            InterruptManager(smartware::common::uint16 hardwareInterruptOffset, GlobalDescriptorTable* globalDescriptorTable);
            ~InterruptManager();
            smartware::common::uint16 HardwareInterruptOffset();
            void Activate();
            void Deactivate();
    };
    }
}
#endif
