#include "../include/hardwarecom/pci.h"

using namespace smartware::common;
using namespace smartware::hardwarecom;

smartware::hardwarecom::PeripheralComponentInterconneDeviceDescriptor::PeripheralComponentInterconneDeviceDescriptor()
{
}

smartware::hardwarecom::PeripheralComponentInterconneDeviceDescriptor::~PeripheralComponentInterconneDeviceDescriptor()
{
}


PeripheralComponentInterconneController::PeripheralComponentInterconneController(): dataPort(0xCFC), commandPort(0xCF8)
{

}

PeripheralComponentInterconneController::~PeripheralComponentInterconneController()
{

}

smartware::common::uint32 smartware::hardwarecom::PeripheralComponentInterconneController::Read(common::uint16 bus, common::uint16 device, smartware::common::uint16 function, common::uint32 registerOffiset)
{
    uint32 id = 
    0x1 << 31
    |((bus & 0xFF) << 16)
    |((device & 0x1F) <<11)
    |((function & 0x07) <<8)
    |(registerOffiset & 0xFC);
    
    commandPort.Write(id);
    uint32 result = dataPort.Read();
    
    return result >> (8* (registerOffiset % 4));
}

void smartware::hardwarecom::PeripheralComponentInterconneController::Write(common::uint16 bus, common::uint16 device, smartware::common::uint16 function, common::uint32 registerOffiset, common::uint32 value)
{
    uint32 id = 
    0x1 << 31
    |((bus & 0xFF) << 16)
    |((device & 0x1F) <<11)
    |((function & 0x07) <<8)
    |(registerOffiset & 0xFC);
    commandPort.Write(id);
    dataPort.Write(value);
}


bool smartware::hardwarecom::PeripheralComponentInterconneController::DeviceHasFunctions(common::uint16 bus, common::uint16 device)
{
    return Read(bus, device, 0, 0x0E) & (1<<7);
}

void printf(char* str);
void printHex(uint8);

void smartware::hardwarecom::PeripheralComponentInterconneController::SelectDrivers(smartware::drivers::DriverManager* driverManager)
{
    for(int bus =0; bus<8; bus++){
        for(int device =0; device < 32; device++){
            int numFunctions = DeviceHasFunctions( bus, device) ? 8 : 1;
            for(int function =0; function < numFunctions; function++){
                PeripheralComponentInterconneDeviceDescriptor dev = GetDeviceDescriptor(bus, device, function);
                
                if(dev.vendor_id == 0x0000 || dev.vendor_id == 0xFFFF)
                    break;
                printf("PCI BUS ");
                printHex(bus & 0xFF);
                
                printf("Device: ");
                printHex(device & 0xFF);
  
                
               printf(" , Function: ");
                printHex(function & 0xFF);
  
                
               printf(" , Vendor: ");
                printHex((dev.vendor_id & 0xFF00) >> 8);
                 printHex(dev.vendor_id & 0xFF);
                 
                printf(" , Device: ");
                printHex((dev.device_id & 0xFF00) >> 8);
                 printHex(dev.device_id & 0xFF);
                 
                 printf("\n");
                
            
                
                
 
                
            }
        }
    }
}


smartware::hardwarecom::PeripheralComponentInterconneDeviceDescriptor smartware::hardwarecom::PeripheralComponentInterconneController::GetDeviceDescriptor(common::uint16 bus, common::uint16 device, smartware::common::uint16 function)
{
    PeripheralComponentInterconneDeviceDescriptor result;
    result.bus=bus;
    result.device=device;
    result.function=function;
    
    result.vendor_id=Read(bus, device, function, 0x00);
     result.device_id=Read(bus, device, function, 0x02);
     result.class_id=Read(bus, device, function, 0x0b);
     result.subclass_id=Read(bus, device, function, 0x0a);
     result.interface_id=Read(bus, device, function, 0x09);
     result.revision=Read(bus, device, function, 0x08);
     result.interrupt=Read(bus, device, function, 0x3c);
     
     return result;
}



