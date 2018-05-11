#ifndef __SMARTWARE__DRIVER_H
#define __SMARTWARE__DRIVER_H

/**
 * @todo write docs
 * 
 * 
 */

namespace smartware{
    
    namespace drivers{

class Driver
{
public:
   Driver();
   ~Driver();
    
    virtual void Activate();
    virtual int Reset();
    virtual void Deactivate();
};

class DriverManager{
  
private:
    Driver* drivers[255];
    int numDrivers;
    
public:
    void AddDriver(Driver*);
    DriverManager();
    ~DriverManager();
    void ActivateAll();
    
    
    
};
    }
}

#endif // DRIVER_H
