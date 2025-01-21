#include <xc.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/uart2.h"
#include <libpic30.h>
#define FCY 4000000UL

#include <stdint.h>

#include <stdint.h>

void UART2_to_UART1_Transfer(void) {
    // Wait for data to be available in UART2 receive buffer
    while (!U2STAbits.URXDA) {
        // Wait until UART2 has received data
    }

    // Read the received byte from UART2
    uint8_t received_data = U2RXREG;

    // Wait until UART1 is ready to transmit
    while (U1STAbits.UTXBF) {
        // Wait for UART1 Transmit Buffer to become empty
    }

    // Write the received byte to UART1 Transmit Register
    U1TXREG = received_data;
}



void delay_ms(unsigned int milliseconds) {
    unsigned long cycles = (FCY / 1000) * milliseconds; // Total instruction cycles
    while (cycles > 0) {
        Nop(); // No Operation: Keeps the CPU busy for one cycle
        cycles--;
    }
}

void sendATCommand(const char *command) {
    // Iterate through the string until the null terminator
    while (*command != '\0') {
        UART2_Write(*command);  // Send each byte to UART2
        command++;  // Move to the next character
    }
}

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    char myData[] = "AT\r\n";
    SYSTEM_Initialize();
    char myData2 ;

    while (1)
    {
         
        delay_ms(50);
        sendATCommand(myData);
        
       
       
           
          // Check if data is available in the RX register
        UART2_to_UART1_Transfer();  // Write to UART1
          // End loop when newline is received
                
        
            
                
    }

    return 1;
}
/**
 End of Filefile:mcc_generated_files/uart2.c; rxQueue
*/