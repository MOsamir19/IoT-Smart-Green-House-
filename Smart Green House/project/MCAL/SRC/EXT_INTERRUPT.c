
/*
 * EXT_INTERRUPT.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 
#include "EXT_INTERRUPT.h"

void (*ptr_CallList[4])(void);

void GLobal_Int_Flag(GLobal_Int_state state)
{
	switch(state)
	{
		case GLobal_closed:
		CLEARBIT(SREG,7);
		break;
		case Global_open:
		SETBIT(SREG,7);
		break;
	}
}
void EXT_Init(INT_NUM  intNUM, INT_STATE intSTATE)
{
	
	switch(intNUM)
	{
	case INT_NUM_0 :
	  switch(intSTATE)
    	{
	    	case INT_STATE_FALLING:
		      CLEARBIT(EICRA,ISC00);
		      SETBIT(EICRA,ISC01);
	    	break;
	    	case INT_STATE_RISING:
	    	    SETBIT(EICRA,ISC00);
	     	    SETBIT(EICRA,ISC01);
    		break;
    	 }
		 
	break;
	case INT_NUM_1 :
	     switch(intSTATE)
	     {
		     case INT_STATE_FALLING:
		      CLEARBIT(EICRA,ISC10);
		      SETBIT(EICRA,ISC11);
		     break;
		     case INT_STATE_RISING:
		      SETBIT(EICRA,ISC10);
		      SETBIT(EICRA,ISC11);
		     break;
	     }
	break;
	
	case INT_NUM_2 :
	       switch(intSTATE)
	       {
		       case INT_STATE_FALLING:
		        CLEARBIT(EICRA,ISC20);
		        SETBIT(EICRA,ISC21);
		       break;
		       case INT_STATE_RISING:
		        SETBIT(EICRA,ISC20);
		        SETBIT(EICRA,ISC21);
		       break;
	       }
	break;
	case INT_NUM_3 :
	     switch(intSTATE)
	     {
		     case INT_STATE_FALLING:
		      CLEARBIT(EICRA,ISC30);
		      SETBIT(EICRA,ISC31);
		     break;
		     case INT_STATE_RISING:
		      SETBIT(EICRA,ISC30);
		      SETBIT(EICRA,ISC31);
		     break;
	     }
	break;
	}
	SETBIT(EIMSK,intNUM);
}

void EXT_Disable(INT_NUM intNUM)
{
	CLEARBIT(EIMSK,intNUM);
}
void EXT_CallSetup(INT_NUM intNUM, void (*ptr_CallBack_Fun)(void))
{
	ptr_CallList[intNUM]= ptr_CallBack_Fun;
}


ISR(INT0_vect)
{
	ptr_CallList[INT_NUM_0]();
}
ISR(INT1_vect)
{
	ptr_CallList[INT_NUM_1]();
}
ISR(INT2_vect)
{
	ptr_CallList[INT_NUM_2]();
}
ISR(INT3_vect)
{
	ptr_CallList[INT_NUM_3]();
}