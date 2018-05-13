#ifndef PERIPHERALCOMPONENTINTERCONNECONTROLLER_H
#define PERIPHERALCOMPONENTINTERCONNECONTROLLER_H

#include <common/types.h>
#include <hardwarecom/port.h>
#include <hardwarecom/interrupts.h>
#include <drivers/driver.h>
/**
 * @todo write docs
 */

namespace smartware{
    namespace hardwarecom{
        
        class PeripheralComponentInterconneDeviceDescriptor{
        public:
            common::uint32 portBase;
            common::uint32 interrupt;
            
            
         common::uint16 bus;
         common::uint16  device;
         
         common::uint16 function;
         
         
         common::uint16   vendor_id;
         common::uint16   device_id;
         common::uint8   class_id;
         common::uint8   subclass_id;
         common::uint8   interface_id;
         
         common::uint8 revision;
         
         PeripheralComponentInterconneDeviceDescriptor();
         ~PeripheralComponentInterconneDeviceDescriptor();
         
         
        };
        
        
class PeripheralComponentInterconneController
{
       
        Port32Bit dataPort;
     Port32Bit commandPort;
public:
    /**
     * Default constructor
     */
    PeripheralComponentInterconneController();

    /**
     * Destructor
     */
    ~PeripheralComponentInterconneController();

    
    common::uint32 Read(common::uint16 bus, common::uint16 device, uint16 function, common::uint32 registerOffiset);
   void Write(common::uint16 bus, common::uint16 device, uint16 function, common::uint32 registerOffiset, common::uint32 value);   
   bool DeviceHasFunctions(common::uint16 bus, common::uint16 device);   
   
   void SelectDrivers(smartware::drivers::DriverManager* driverManager);
   
   PeripheralComponentInterconneDeviceDescriptor GetDeviceDescriptor(common::uint16 bus, common::uint16 device, uint16 function);
};

    }
    
}

#endif // PERIPHERALCOMPONENTINTERCONNECONTROLLER_H
