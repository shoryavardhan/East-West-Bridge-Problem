
#include  <iostream.h>
#include  "ThreadClass.h"
#include  "bridge-Thrd.h"
#include  "bridge-mon.h"


BridgeMonitor::BridgeMonitor(char* Name): Monitor(Name, HOARE) 
{
     VehicleCount = 0;             // no vehicle on bridge
     Waiting[0] = Waiting[1] = 0;  // no vehicle waiting
     Names[0] = "EastWest";
     Names[1] = "WestEast";
     WaitingLine[0] = new Condition(Names[0]); // East->West waiting line
     WaitingLine[1] = new Condition(Names[1]); // West->East waiting line
};


int  BridgeMonitor::isSafe(int Direction)
{
     if (VehicleCount == 0)        // if no vehicle on bridge  
          return  TRUE;            // it is safe to cross            
     else if ((VehicleCount < MAX_VEHICLE) && (CurrentDirection == Direction))
          return  TRUE;            // if < max count in the same direction 
     else
          return  FALSE;           // otherwise, do not proceed
}


void  BridgeMonitor::ArriveBridge(int Direction)
{
     MonitorBegin();               
     if (!isSafe(Direction)) {     // is it safe to be on the bridge
          Waiting[Direction]++;    // no, wait at the bridge   
          WaitingLine[Direction]->Wait(); // block this vehicle
          Waiting[Direction]--;    // released
     }
     VehicleCount++;               // go on bridge             
     CurrentDirection = Direction; // set direction            
     MonitorEnd();                 // release monitor          
}


void  BridgeMonitor::ExitBridge(int Direction)
{
     MonitorBegin();                    // lock the monitor  
     VehicleCount--;                    // one vehicle exits        
     if (VehicleCount > 0) {            // have vehicles on bridge? 
          WaitingLine[Direction]->Signal(); // release the same direction
     }
     else {                             // no vehicle on bridge
          if (Waiting[1-Direction] != 0)    // opposite direction non-empty?
               WaitingLine[1-Direction]->Signal();  // release one of them
          else                          // release the same direction
               WaitingLine[Direction]->Signal();
     }
     MonitorEnd();                      
}

