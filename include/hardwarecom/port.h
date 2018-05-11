#ifndef __SMARTWARE__PORT
#define __SMARTWARE__PORT

    #include <common/types.h>
    
    using namespace smartware::common;
    
namespace smartware{
    namespace hardwarecom{
        


    class Port
    {
    protected:
        uint16 portnumber;
        Port ( uint16 portnumber )        ;
        ~Port();

    };
    
    class Port8Bit : public Port
    {
    public:

        Port8Bit ( uint16 portnumber );
        ~Port8Bit();
        virtual void Write ( uint8 data );
        virtual uint8 Read();


    };
    class Port8BitSlow : public Port8Bit
    {
    public:

        Port8BitSlow ( uint16 portnumber );
        ~Port8BitSlow();
        virtual void Write ( uint8 data );



    };
    class Port16Bit : public Port
    {
    public:

        Port16Bit ( uint16 portnumber );
        ~Port16Bit();
        virtual void Write ( uint16 data );
        virtual uint8 Read();


    };
    class Port32Bit : public Port
    {
    public:

        Port32Bit ( uint16 portnumber );
        ~Port32Bit();
        virtual void Write ( uint32 data );
        virtual uint8 Read();


    };
    }
}
#endif
