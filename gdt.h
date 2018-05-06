#ifndef __GDT_H
#define __GDT_H

    #include "types.h"   
    class GlobalDescriptorTable{
    public:
       class SegmentDescriptor {
           
       private:
           uint16 limit_lo;
           uint16 base_lo;
           uint8 base_hi;
           uint8 type;
           uint8 flags_limit_hi;
           uint8 base_vhi;
           
       public:
           SegmentDescriptor(uint32 base, uint32 limit, uint8 type);
           uint32 Base();
           uint32 Limit();
           
    } __attribute__((packed));
        
    
    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector;
    SegmentDescriptor codeSegmenteSelector;
    SegmentDescriptor dataSegmenteSelector;
    
    public:
         GlobalDescriptorTable();
        ~GlobalDescriptorTable();
        
        uint16 CodeSegmenteSelector();
        uint16 DataSegmenteSelector();
        
        
    };
    
#endif
