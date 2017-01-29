/*
Names: Laura VanDyke and Andrew Fuller
TermProject-Phase1
Date: Octorber 11, 2015
*/
#ifndef hardware_h
#define hardware_h

#include "state.h"


typedef enum
{
   FAIL,
   LOST,
   DONE
}  stats;

typedef enum
{
   DISPATCH,
   SHUT_DOWN
}  factory_line;

typedef enum
{
   WARRANTY,
   REFUND
}  delivery;

// Events
typedef enum
{
   ORDER_RCVD,
   INVALID_PYMNT,
   VALID_PYMNT,
   MANUF_FAILED,
   MANUF_COMPLETED,
   LOST_PACKAGE,
   RECEIVED
}  event;

// Functions for controlling the manuf lines
void set_Factory_Line(factory_line value);

// Functions for shipping results
void set_Shipping_Result(delivery value);

void updateStats(stats value);
void charge_Client();
state_t* increment_Attempts();
void resetAttempts();
void getAddress();


#endif
