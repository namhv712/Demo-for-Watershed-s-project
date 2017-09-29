/** @file iopin.h
*
* @brief This file include interrupt service routine for buttons.
* 
* @par
* COPYRIGHT NOTICE: (c) 2017 MANDEVICES GROUP, HUST.
*/
#ifndef _INTFUNC_H
#define _INTFUNC_H

#ifdef __cplusplus
extern “C” {
#endif
/******************************************************************************
INCLUDES
******************************************************************************/
#include<mbed.h>
#include<iopin.h>
/******************************************************************************
GLOBAL VARIABLES
******************************************************************************/
uint8_t g_mode=0;
Timeout g_time_out_s;
time_t g_time_1_s; //chuc nang ?
time_t g_time_2_s; // chuc nang?
InterruptIn g_setting_button(set);
InterruptIn g_selecting_button(select);
bool g_timer_on_1_=true; //
bool  g_timer_on_2_=true;//
/******************************************************************************
* DESCRIPTION: the timeout service routine, when timeout reset mode to switch back the main menu
* @author:
* Nguyen Ba Dat - Member of MANDEVICES GROUP
* @version: v1.0.0
* @param:
* NONE
* @return: NONE
* @see:
* .../lib/IO/interruptfunc.h
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
void set_mode_when_timeout() 
{
    g_mode=0;
}

/******************************************************************************
* DESCRIPTION: the Interrupt service routine of fall interrupt when press the select button
* @author:
* Nguyen Ba Dat - Member of MANDEVICES GROUP
* @version: v1.0.0
* @param:
* NONE
* @return: NONE
* @see:
* .../lib/IO/interruptfunc.h
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
static void fall_select_btn_isr()
{
    g_button_select.disable_irq();
    g_time_out_s.attach(&set_mode_when_timeout, 15);
    wait_ms(20);
    g_mode++;
    if(g_mode >= 3) 
    {
        g_mode=0;
    }
  
    press_button.enable_irq();
}
/******************************************************************************
* DESCRIPTION: the Interrupt service routine of fall interrupt when press the set button
* @author:
* Nguyen Ba Dat - Member of MANDEVICES GROUP
* @version: v1.0.0
* @param:
* NONE
* @return: NONE
* @see:
* .../lib/IO/interruptfunc.h
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
static void fall_set_btn_isr() 
{
    btn_Set.disable_irq();
    timeout.attach(&attimeout, 15);
    wait_ms(20);
    if(mode == 1)
    {
        timerOn1=!timerOn1; 
        time1=time(NULL);
    }
  
    if(mode == 2) 
    { 
        timerOn2=!timerOn2; 
        time1=time(NULL);
    }
  
    btn_Set.enable_irq();
}
/******************************************************************************
* DESCRIPTION: the Interrupt service routine of rise interrupt when press the set button
* @author:
* Nguyen Ba Dat - Member of MANDEVICES GROUP
* @version: v1.0.0
* @param:
* NONE
* @return: NONE
* @see:
* .../lib/IO/interruptfunc.h
* @todo:
* NONE
* @bug:
* NONE
******************************************************************************/
static void rise_set_btn_isr()
{
    btn_Set.disable_irq();
    timeout.attach(&attimeout, 15);
    wait_ms(20);
    if((mode == 1) || (mode == 2))
    {
        time2=time(NULL);
    }
  
    if((time2-time1) >= 2)
    {
        set_time(0); 
        if(mode == 1) 
        {
            timerOn1 =! timerOn1; 
            if(mode == 2) 
            {
              timerOn2 =! timerOn2;
            }
        }
    }
  
    btn_Set.enable_irq();
}
#endif /* _INTFUNC_H */
