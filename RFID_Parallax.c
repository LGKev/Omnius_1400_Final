int a[] = [Start Sentinel |Byte 1|Byte 2|Byte 3|Byte 4|Byte 5|Byte 6|Byte 7|Byte 8|Byte 9|Byte 10| Stop Sentinel];

BSET(PCICR,PCIE2);        // pin change interrupt control register pcie2
BSET(PCMSK2,PCINT18);    // enable pin change interrupt for PCINT18 (PD2)
BSET(SREG,7);            // Set SREG I-bit

// this is the interrupt
ISR(PCINT2_vect){
if (BCHK(PIND,RFID_IN))	// Start bit goes low
return;
uint8_t	bit = 0;
TunedDelay(CENTER_DELAY);		// Center on start bit
for (uint8_t x = 0; x < 8; x++)	{
TunedDelay(INTRABIT_DELAY);	// skip a bit, brother...
if (BCHK(PIND,RFID_IN))
BSET(bit,x);
else
BCLR(bit,x);
}
TunedDelay(INTRABIT_DELAY);		// skip stop bit
RFID_tag[rxIdx] = bit;
++rxIdx;
if (rxIdx == 12)
bDataReady = 1;
}
