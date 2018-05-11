#ifndef __SMARTWARE__KEYBOARD_H
#define __SMARTWARE__KEYBOARD_H

#include <common/types.h>
#include <hardwarecom/port.h>
#include <hardwarecom/interrupts.h>
#include <drivers/driver.h>




namespace smartware{
    namespace drivers{
        
      

     
        
class keyboardEventHandler{

public:
    keyboardEventHandler();
    
    virtual void OnKeyDown(char );
    virtual void OnkeyUp(char );
    
    
    
};

class KeyboardDriver : smartware::hardwarecom::InterruptHandler, public Driver
{
    smartware::hardwarecom::Port8Bit dataport;
    smartware::hardwarecom::Port8Bit commandport;
    keyboardEventHandler* handler;

    
public:
    KeyboardDriver(smartware::hardwarecom::InterruptManager* manager, keyboardEventHandler *handler);
    ~KeyboardDriver();
    
    virtual smartware::common::uint32 HandleInterrupt(smartware::common::uint32 esp);
    virtual void Activate();
};
    }
}


#endif
