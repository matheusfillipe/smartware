#ifndef __SMARTWARE__MOUSE_H
#define __SMARTWARE__MOUSE_H

#include <common/types.h>
#include <hardwarecom/port.h>
#include <drivers/driver.h>
#include <hardwarecom/interrupts.h>


namespace smartware{
    namespace drivers{
    
       
      
class mouseEventHandler{
    
      
public:
    mouseEventHandler();
    
    virtual void OnActivate();
    virtual void OnKeyDown(smartware::common::uint8 button );
    virtual void OnkeyUp(smartware::common::uint8 button );
    virtual void OnMove(int x, int y);
    
    
    
};

class MouseDriver : public smartware::hardwarecom::InterruptHandler, public Driver
{
    smartware::hardwarecom::Port8Bit dataport;
    smartware::hardwarecom::Port8Bit commandport;
    
    smartware::common::uint8 buffer[3];
    smartware::common::uint8 offset;
    smartware::common::uint8 buttons;
    
    mouseEventHandler* handler;
    
public:
    MouseDriver(smartware::hardwarecom::InterruptManager* manager, mouseEventHandler* handler);
    ~MouseDriver();
    
    virtual smartware::common::uint32 HandleInterrupt(smartware::common::uint32 esp);
    virtual void Activate();

};
    
}
}


#endif
