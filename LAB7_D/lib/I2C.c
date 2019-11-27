/***********************************************************
*
*	I2C Module
*
*	File Name : i2c.c
*	Date Created :
*	Last modified :
*
************************************************************/

#include <I2C.h>

static CSL_I2cRegsOvly i2c0Regs = (CSL_I2cRegsOvly)(CSL_I2C_0_REGS);

void I2C_Init(Uint16 sclk)
{
	Uint32 icclk = (4000/sclk) - 5;

	i2c0Regs->ICMDR   = CSL_FMKT(I2C_ICMDR_MST, MASTER_MODE);	// reset I2C
	i2c0Regs->ICIMR = CSL_I2C_ICIMR_RESETVAL;
	i2c0Regs->ICSTR = i2c0Regs->ICSTR;							// clear ICSTR

	i2c0Regs->ICPSC   = 2;               						// prescale for I2C internal, (24MH/3)=8MHz
	i2c0Regs->ICCLKL  = icclk;               					// clk low for (scl_clk)kHz
	i2c0Regs->ICCLKH  = icclk;               					// clk high for (scl_clk)kHz
}


void I2C_Write( Uint16 i2c_addr, Uint8* data, Uint16 len)//, Uint16 stop )
{
    Int32 i;

    i2c0Regs->ICCNT = len;
    i2c0Regs->ICSAR = i2c_addr;         								// I2C slave address
    i2c0Regs->ICMDR =  CSL_FMKT(I2C_ICMDR_MST, MASTER_MODE) 			// master mode
               		| CSL_FMKT(I2C_ICMDR_FREE, TRUE)
					| CSL_FMKT(I2C_ICMDR_TRX, TX_MODE)					// tx mode
					| CSL_FMKT(I2C_ICMDR_IRS, ENABLE);					// out of reset

	CSL_FINST(i2c0Regs->ICMDR, I2C_ICMDR_STT, SET);						// start condition

    for ( i = 0 ; i < len ; i++ )
    {
    	i2c0Regs->ICDXR = data[i];            							// write
        while( CSL_FEXT(i2c0Regs->ICSTR, I2C_ICSTR_ICXRDY) != 1 );		// wait for TX ready
    }

	CSL_FINST(i2c0Regs->ICMDR, I2C_ICMDR_STP, SET);
	while(CSL_FEXT(i2c0Regs->ICMDR, I2C_ICMDR_MST) == 1);
}


void I2C_Read( Uint16 i2c_addr, Uint8* data, Uint16 len )
{
    Int32 i;

    i2c0Regs->ICCNT = len;
    i2c0Regs->ICSAR = i2c_addr;         								// I2C slave address
	i2c0Regs->ICMDR =  CSL_FMKT(I2C_ICMDR_MST, MASTER_MODE) 			// master mode
               		| CSL_FMKT(I2C_ICMDR_FREE, TRUE)
					| CSL_FMKT(I2C_ICMDR_TRX, RX_MODE)					// rx mode
			   		| CSL_FMKT(I2C_ICMDR_IRS, ENABLE); 					// out of reset

	while( CSL_FEXT(i2c0Regs->ICSTR, I2C_ICSTR_BB) != 0 );				// wait for bus ready
	CSL_FINST(i2c0Regs->ICMDR, I2C_ICMDR_STT, SET);						// enable start

    for ( i = 0 ; i < len ; i++ )
    {
		while( CSL_FEXT(i2c0Regs->ICSTR, I2C_ICSTR_ICRRDY) != 1 );		// wait for RX ready
        data[i] = i2c0Regs->ICDRR;            							// read
    }

    CSL_FINST(i2c0Regs->ICMDR, I2C_ICMDR_STP, SET);
   	while(CSL_FEXT(i2c0Regs->ICMDR, I2C_ICMDR_MST) == 1);
}

