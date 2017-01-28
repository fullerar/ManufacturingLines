# ManufacturingLines

This is a four phase project defined as follows:
- Phase1:
  -Simply just a model for a finite state machine that represents the process a factory might go through once an order has been receieved. This version will work under the assumption that there is only one "manufacturing line" in the factory.

- Phase2:
    - uses the same finite state machine but this time the model is implemented with mutli-threads. This version will work under the assumption that there are five "manufacturing lines" in the factory, each represented by an individual thread.
 
- Phase3: 
    - uses the same finite state machine but this time the model is implemented with multi-processes. This version will work under the assumption that there are five "manufacturing lines" in the factory, each represented by an individual process, a process that represents the current state, and a process that supervises the shared memory in order to achieve concurrency.
    
- Phase4:
    - uses the same finite state machine but this time the model is implemented with multi-processes but this time, distributed over different machines, with no shared memory.
