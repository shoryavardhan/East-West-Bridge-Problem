An east-west bridge is shared between east cars and west cars. Each car is a process. We want the following to hold:
1. Multiple cars: More than one car can on the bridge as long as they are all going in the same direction (east or west).
2. No starvation: A car that attempts to cross the bridge eventually does so provided no car stays forever in the bridge.
3. No busy waiting.
This problem is like the readers-writers problem except that multiple writes can be ongoing at the same time.
This problem is like the readers-writers problem except that multiple writes can be ongoing at the same time.