# ManufacturingLines

Some things to note: 
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



Usage notes:
- In Terminal, cd into the correct directory and perform the following in order:
  - To compile all files:
    - make
  - To start the program: 
    - ./driver
- NOTE:
  - The default starting state is ACCEPTING
  - Each state has different entry/exit functions that will be displayed in terminal. These statements do not actually represent anything happening in the code, they are simply there to abstractly represent what might actually be happening in a real manufacturing line. For example, when you enter the MANUFACTURING state, the terminal will display "Lines are running." And when you exit from the MANUFACTURING state, the terminal will display "Lines are not running."
  - Certain states will only respond to certain keys. The machine will not change state if a key is entered out of order. The possible keys to be entered for each state are as follows:
    - ACCEPTING => O
    - PROCESSING => V,I
    - MANUFACTURING => C,F
    - SHIPPING => R,L
    - You may enter X at any time
- Key explanations:
  - 'X' => exits the driver
  - 'O' => tells the machine that an order has been recieved. State switches to PROCESSING and now waits for either a valid or invalid payment.
  - 'I' => tells the machine that an invalid payment has been recieved. The state remains in PROCESSING until either a valid payment is given or 3 invalid attempts are given. Upon the latter, the state is returned to ACCEPTING and you must start over.
  - 'V' => tells the machine that a valid payment has been recieved. State switches to MANUFACTURING and now waits for confirmation that the manufacturing was either completed or failed.
  - 'F' => tells the machine that the manufacturing lines failed to produce the product. State returns to ACCEPTING and you must start over.
  - 'C' => tells the machine that the manufacturing lines completed the product. State switches to SHIPPING and waits for either confirmation that the customer received the product, or that it was lost in transit.
  - 'L' => tells the machine that the product was lost in transit. State returns to ACCEPTING and you must start over.
  - 'R' => tells the machine that the product was delivered to the customer. State returns to ACCEPTING and waits for a new order.
