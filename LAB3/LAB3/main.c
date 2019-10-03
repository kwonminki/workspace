/*
 *  ======== main.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/LoggerBuf.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/cfg/global.h>


/*
 *  ======== main ========
 */
Int main()
{ 
    System_printf("LAB3 - Hello SYS/BIOS\n");
    Log_info0("Log info0");
    Log_info1("Log info1 %d", 100);
    LoggerBuf_flush( logger0 );

    return(0);
}
