/* Library Definitions */
#include <msp430.h>

/* Macro Definitions */
#define rxPin BIT1
#define txPin BIT2
#define led1 BIT0
#define led2 BIT3
#define led3 BIT4
#define led4 BIT5
#define led5 BIT0
#define led6 BIT1
#define led7 BIT2
#define led8 BIT3

void main(void)
{

/* Watch Dog Timer & Clock Configurations */
 WDTCTL = WDTPW | WDTHOLD; // Disable WDT
 DCOCTL = 0;
 BCSCTL1 = CALBC1_1MHZ; // 1MHz Clock, internal RC Oscillator
 DCOCTL = CALDCO_1MHZ;

 /* GPIO Configurations */
 P1DIR |= (led1+led2+led3+led4); // P1.0, P1.3, P1.4, P1.5
 P1OUT &= ~(led1+led2+led3+led4);

 P2DIR |= (led5+led6+led7+led8); // P2.0, P2.1, P2.2, P2.3
 P2OUT &= ~(led5+led6+led7+led8);

/* USCI Configurations */
 P1SEL = (BIT1 + BIT2); // P1.1 = RXD, P1.2=TXD
 P1SEL2 = (BIT1 + BIT2);

 UCA0CTL1 |= UCSSEL_2; // SMCLK
 UCA0BR0 = 104; // 1MHz, 9600 Baud Rate
 UCA0BR1 = 0;
 UCA0MCTL = UCBRS0;
 UCA0CTL1 &= ~UCSWRST; // USCI Enable
 IE2 |= UCA0RXIE; // interrupt Enable

 __bis_SR_register(LPM0_bits + GIE); // Enable interrupts
}

/* USCI interrupt Handler Definitions*/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{

 while (!(IFG2&UCA0TXIFG));
 UCA0TXBUF = UCA0RXBUF;

 if(UCA0TXBUF=='1')
 {
     P1OUT |= (led1+led2+led3+led4);
     P2OUT |= (led5+led6+led7+led8);
 }
 else if (UCA0TXBUF=='0')
 {
     P1OUT &= ~(led1+led2+led3+led4);
     P2OUT &= ~(led5+led6+led7+led8);
 }
}
