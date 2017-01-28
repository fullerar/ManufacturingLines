# ManufacturingLines

- Some things to note: 
  - These programs were made on/for a Linux based machine. Some functions used are deprecated on Mac OS and will cause warnings/errors if you try to compile them.
  - Each Phase contains a makefile for the corresponding phase.
  - Each Phase is intended to be used through the command line.
  




This is a four phase project defined as follows:
- Phase1:
  - Finite state machine that represents the process a factory might go through once an order has been receieved. This version will work under the assumption that there is only one "manufacturing line" in the factory.

- Phase2:
  - uses the same finite state machine but this time the model is implemented with mutli-threads. This version will work under the assumption that there are five "manufacturing lines" in the factory, each represented by an individual thread.
 
- Phase3: 
  - uses the same finite state machine but this time the model is implemented with multi-processes. This version will work under the assumption that there are five "manufacturing lines" in the factory, each represented by an individual process, a process that represents the current state, and a process that supervises the shared memory in order to achieve concurrency.
    
- Phase4:
  - uses the same finite state machine but this time the model is implemented with multi-processes but this time, distributed over different machines, with no shared memory.
