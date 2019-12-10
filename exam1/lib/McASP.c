/***********************************************************
* 	
*	McASP Module
*                              
*	File Name : McASP.c 
*	Date Created :
*	Last modified :
*
************************************************************/

#include "McASP.h"

CSL_McaspRegsOvly mcaspRegs = (CSL_McaspRegsOvly)(CSL_MCASP_0_CTRL_REGS);

void ConfigMcASP( Uint16 slot_size, Uint16 slot_num, Uint16 buf_sel, Uint16 rcv_int, Uint16 xmt_int )
{
	mcaspRegs->GBLCTL  = 0;       				// reset
	mcaspRegs->RSTAT = 0x7;
	mcaspRegs->XSTAT = 0x7;
    while( mcaspRegs->GBLCTL != 0 );

	/*********************************************************************/
	/*                            RX                                     */
	/*********************************************************************/	 
				
	if(slot_size == MCASP_16BIT)
	{
		mcaspRegs->RMASK    = 0x0000ffff;
    	mcaspRegs->RFMT		= 0x0000C070; 		// MSB, slot size=16, 0bit-delay, no pad, DMA bus
		CSL_FINS( mcaspRegs->RFMT, MCASP_RFMT_RPBIT, 15 );
	}
	else if(slot_size == MCASP_20BIT)
	{
		mcaspRegs->RMASK    = 0x000fffff;
    	mcaspRegs->RFMT		= 0x0000C090; 		// MSB, slot size=20, 0bit-delay, no pad, DMA bus
		CSL_FINS( mcaspRegs->RFMT, MCASP_RFMT_RPBIT, 19 );
	}
	else if(slot_size == MCASP_24BIT)
	{
		mcaspRegs->RMASK    = 0x00ffffff;
    	mcaspRegs->RFMT		= 0x0000C0B0; 		// MSB, slot size=24, 0bit-delay, no pad, DMA bus
		CSL_FINS( mcaspRegs->RFMT, MCASP_RFMT_RPBIT, 23 );
	}
	else if(slot_size == MCASP_32BIT)
	{
		mcaspRegs->RMASK    = 0xffffffff; 		// no padding used
    	mcaspRegs->RFMT		= 0x000080F0; 		// MSB, slot size=32, 0bit-delay, no pad, DMA bus
	}

	if( buf_sel == CFG )
		CSL_FINST( mcaspRegs->RFMT, MCASP_RFMT_RBUSEL, VBUS );	//  CFG bus
	
    mcaspRegs->ACLKRCTL   = 0x00000020; 		// falling, clk mode don't care (TX sync)
    mcaspRegs->AHCLKRCTL  = 0x00000000; 		// clk mode don't care (TX sync)

    if( rcv_int )
		mcaspRegs->RINTCTL = 0x00000020; 		// RDATA INT
	else
		mcaspRegs->RINTCTL = 0x00000000;		// not used

    mcaspRegs->RCLKCHK    = 0x00FF0008; 		// 255-MAX 0-MIN, div-by-256

	if( slot_num == MCASP_1SLOT )
	{
		mcaspRegs->AFSRCTL    = 0x00000002; 	// burst, bit, active high, fsync mode don't care (TX sync)
		mcaspRegs->RTDM       = 0x00000001; 	// slot 0
	}
	else if( slot_num == MCASP_2SLOT )
	{
		mcaspRegs->AFSRCTL    = 0x00000102; 	// 2-slot TDM, bit, active high, fsync mode don't care (TX sync)
		mcaspRegs->RTDM       = 0x00000003; 	// slot 0 & 1
	}

	/*********************************************************************/
	/*                            TX                                     */
	/*********************************************************************/	

    mcaspRegs->XMASK      = 0xffffffff; 		// no padding used

	if(slot_size == MCASP_16BIT)
    	mcaspRegs->XFMT		= 0x00008074; 		// MSB, slot size=16, rotate=16, 0bit-delay, no pad, DMA bus
	else if(slot_size == MCASP_20BIT)
    	mcaspRegs->XFMT		= 0x00008095; 		// MSB, slot size=20, rotate=20, 0bit-delay, no pad, DMA bus
	else if(slot_size == MCASP_24BIT)
    	mcaspRegs->XFMT		= 0x000080B6; 		// MSB, slot size=24, rotate=24, 0bit-delay, no pad, DMA bus
	else if(slot_size == MCASP_32BIT)
    	mcaspRegs->XFMT		= 0x000080F0; 		// MSB, slot size=32, rotate=0, 0bit-delay, no pad, DMA bus

	if( buf_sel == CFG )
		CSL_FINST( mcaspRegs->XFMT, MCASP_XFMT_XBUSEL, VBUS );	//  CFG bus


    mcaspRegs->ACLKXCTL   = 0x00000000; 		// rising, external clk, sync
    mcaspRegs->AHCLKXCTL  = 0x00008000; 		// internal clk

    if( xmt_int )
		mcaspRegs->XINTCTL    = 0x00000020; 	// XDATA int
	else
    	mcaspRegs->XINTCTL    = 0x00000000; 	// not used

    mcaspRegs->XCLKCHK    = 0x00FF0008; 		// 255-MAX 0-MIN, div-by-256

	if( slot_num == MCASP_1SLOT )
	{
		mcaspRegs->AFSXCTL    = 0x00000000; 	// burst, bit, active high, external fsync
		mcaspRegs->XTDM       = 0x00000001; 	// Slots 0
	}
	else if( slot_num == MCASP_2SLOT )
	{
		mcaspRegs->AFSXCTL    = 0x00000100; 	// 2-slot TDM, bit, active high, external fsync
		mcaspRegs->XTDM       = 0x00000003; 	// Slot 0 and Slot 1
	}
   
    mcaspRegs->PFUNC      = 0;          		// all MCASPs
    mcaspRegs->PDIR       = 0x00002000;			// all inputs except AXR0[13]

    mcaspRegs->SRCTL13    = 0x000D;				// AXR0[13] --> AIC DIN
    mcaspRegs->SRCTL14    = 0x000E;				// AXR0[14] <-- AIC DOUT

    mcaspRegs->DITCTL     = 0x00000000; 		// not used
    mcaspRegs->DLBCTL     = 0x00000000; 		// not used
    mcaspRegs->AMUTE      = 0x00000000; 		// not used
    
}


void InitMcASP( Uint16 rcv_xmt, Uint16 buf_sel )
{
	volatile Uint32 dummy;

    if( rcv_xmt == TRANSMIT )
    	mcaspRegs->XSTAT = 0x0000ffff;
	else
    	mcaspRegs->RSTAT = 0x0000ffff;

	if( rcv_xmt == TRANSMIT )
	{
		mcaspRegs->XGBLCTL |= CSL_MCASP_XGBLCTL_XSRCLR_MASK;                 		// serializer
    	while ( ( mcaspRegs->XGBLCTL & CSL_MCASP_XGBLCTL_XSRCLR_MASK ) == 0 );
	}
	else
	{
    	mcaspRegs->RGBLCTL |= CSL_MCASP_RGBLCTL_RSRCLR_MASK;                   		// serializer
    	while ( ( mcaspRegs->RGBLCTL & CSL_MCASP_RGBLCTL_RSRCLR_MASK ) == 0 );
	}

    if( rcv_xmt == TRANSMIT )
	{
		if( buf_sel == CFG )
    		mcaspRegs->XBUF13 = 0;
		else
			MCASP_0_DATA = 0;
	}		
	else
	{
		if( buf_sel == CFG )
    		dummy = mcaspRegs->RBUF14;
		else
			dummy = MCASP_0_DATA;
	}	

	if( rcv_xmt == TRANSMIT )
	{
		mcaspRegs->XGBLCTL |= CSL_MCASP_XGBLCTL_XSMRST_MASK;                       	// state-machine
    	while ( ( mcaspRegs->XGBLCTL & CSL_MCASP_XGBLCTL_XSMRST_MASK ) == 0 );
	}
	else
	{
    	mcaspRegs->RGBLCTL |= CSL_MCASP_RGBLCTL_RSMRST_MASK;                    	// state-machine
    	while ( ( mcaspRegs->RGBLCTL & CSL_MCASP_RGBLCTL_RSMRST_MASK ) == 0 );
	}

    if( rcv_xmt == TRANSMIT )
	{
    	mcaspRegs->XGBLCTL |= CSL_MCASP_XGBLCTL_XFRST_MASK;                   		// frame sync
    	while ( ( mcaspRegs->XGBLCTL & CSL_MCASP_XGBLCTL_XFRST_MASK ) == 0 );
/*
		while( ! ( mcaspRegs->SRCTL11 & 0x10 ) );  									// wait for TX empty
    	if( buf_sel == CFG )
    		mcaspRegs->XBUF11 = 0;
		else
			MCASP_0_DATA = 0;
*/
	}
	else
	{
    	mcaspRegs->RGBLCTL |= CSL_MCASP_RGBLCTL_RFRST_MASK;                 		// frame sync
    	while ( ( mcaspRegs->RGBLCTL & CSL_MCASP_RGBLCTL_RFRST_MASK ) == 0 );
	}
}


void GlobalResetMcASP( void )
{
    mcaspRegs->GBLCTL = 0;
	while( mcaspRegs->GBLCTL != 0 );
}


void RResetMcASP( void )
{
	 mcaspRegs->RGBLCTL = 0;
	 while( (mcaspRegs->RGBLCTL & 0x00FF) != 0 );
}


void XResetMcASP( void )
{
	 mcaspRegs->XGBLCTL = 0;
	 while( (mcaspRegs->XGBLCTL & 0x0FF00) != 0 );
}
	


