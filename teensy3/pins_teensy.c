
#include "core_pins.h"
#include "pins_arduino.h"
#include "serial.h"

#if 0
// moved to pins_arduino.h
struct digital_pin_bitband_and_config_table_struct {
	volatile uint32_t *reg;
	volatile uint32_t *config;
};
const struct digital_pin_bitband_and_config_table_struct digital_pin_to_info_PGM[];

// compatibility macros
#define digitalPinToPort(pin) (pin)
#define digitalPinToBitMask(pin) (1)
#define portOutputRegister(pin) ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 0))
#define portSetRegister(pin)    ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 32))
#define portClearRegister(pin)  ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 64))
#define portToggleRegister(pin) ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 96))
#define portInputRegister(pin)  ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 128))
#define portModeRegister(pin)   ((volatile uint8_t *)(digital_pin_to_info_PGM[(pin)].reg + 160))
#define portConfigRegister(pin) ((volatile uint32_t *)(digital_pin_to_info_PGM[(pin)].config))
#endif

//#define digitalPinToTimer(P) ( pgm_read_byte( digital_pin_to_timer_PGM + (P) ) )
//#define analogInPinToBit(P) (P)

#define GPIO_BITBAND_ADDR(reg, bit) (((uint32_t)&(reg) - 0x40000000) * 32 + (bit) * 4 + 0x42000000)
#define GPIO_BITBAND_PTR(reg, bit) ((uint32_t *)GPIO_BITBAND_ADDR((reg), (bit)))
//#define GPIO_SET_BIT(reg, bit) (*GPIO_BITBAND_PTR((reg), (bit)) = 1)
//#define GPIO_CLR_BIT(reg, bit) (*GPIO_BITBAND_PTR((reg), (bit)) = 0)

const struct digital_pin_bitband_and_config_table_struct digital_pin_to_info_PGM[] = {
	{GPIO_BITBAND_PTR(CORE_PIN0_PORTREG, CORE_PIN0_BIT), &CORE_PIN0_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN1_PORTREG, CORE_PIN1_BIT), &CORE_PIN1_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN2_PORTREG, CORE_PIN2_BIT), &CORE_PIN2_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN3_PORTREG, CORE_PIN3_BIT), &CORE_PIN3_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN4_PORTREG, CORE_PIN4_BIT), &CORE_PIN4_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN5_PORTREG, CORE_PIN5_BIT), &CORE_PIN5_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN6_PORTREG, CORE_PIN6_BIT), &CORE_PIN6_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN7_PORTREG, CORE_PIN7_BIT), &CORE_PIN7_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN8_PORTREG, CORE_PIN8_BIT), &CORE_PIN8_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN9_PORTREG, CORE_PIN9_BIT), &CORE_PIN9_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN10_PORTREG, CORE_PIN10_BIT), &CORE_PIN10_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN11_PORTREG, CORE_PIN11_BIT), &CORE_PIN11_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN12_PORTREG, CORE_PIN12_BIT), &CORE_PIN12_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN13_PORTREG, CORE_PIN13_BIT), &CORE_PIN13_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN14_PORTREG, CORE_PIN14_BIT), &CORE_PIN14_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN15_PORTREG, CORE_PIN15_BIT), &CORE_PIN15_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN16_PORTREG, CORE_PIN16_BIT), &CORE_PIN16_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN17_PORTREG, CORE_PIN17_BIT), &CORE_PIN17_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN18_PORTREG, CORE_PIN18_BIT), &CORE_PIN18_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN19_PORTREG, CORE_PIN19_BIT), &CORE_PIN19_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN20_PORTREG, CORE_PIN20_BIT), &CORE_PIN20_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN21_PORTREG, CORE_PIN21_BIT), &CORE_PIN21_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN22_PORTREG, CORE_PIN22_BIT), &CORE_PIN22_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN23_PORTREG, CORE_PIN23_BIT), &CORE_PIN23_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN24_PORTREG, CORE_PIN24_BIT), &CORE_PIN24_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN25_PORTREG, CORE_PIN25_BIT), &CORE_PIN25_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN26_PORTREG, CORE_PIN26_BIT), &CORE_PIN26_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN27_PORTREG, CORE_PIN27_BIT), &CORE_PIN27_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN28_PORTREG, CORE_PIN28_BIT), &CORE_PIN28_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN29_PORTREG, CORE_PIN29_BIT), &CORE_PIN29_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN30_PORTREG, CORE_PIN30_BIT), &CORE_PIN30_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN31_PORTREG, CORE_PIN31_BIT), &CORE_PIN31_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN32_PORTREG, CORE_PIN32_BIT), &CORE_PIN32_CONFIG},
	{GPIO_BITBAND_PTR(CORE_PIN33_PORTREG, CORE_PIN33_BIT), &CORE_PIN33_CONFIG}
};




typedef void (*voidFuncPtr)(void);
volatile static voidFuncPtr intFunc[CORE_NUM_DIGITAL];

void init_pin_interrupts(void)
{
	SIM_SCGC5 = 0x00043F82;		// clocks active to all GPIO
	NVIC_ENABLE_IRQ(IRQ_PORTA);
	NVIC_ENABLE_IRQ(IRQ_PORTB);
	NVIC_ENABLE_IRQ(IRQ_PORTC);
	NVIC_ENABLE_IRQ(IRQ_PORTD);
	NVIC_ENABLE_IRQ(IRQ_PORTE);
	// TODO: maybe these should be set to a lower priority
	// so if the user puts lots of slow code on attachInterrupt
	// fast interrupts will still be serviced quickly?
}

void attachInterrupt(uint8_t pin, void (*function)(void), int mode)
{
	volatile uint32_t *config;
	uint32_t cfg, mask;

	if (pin >= CORE_NUM_DIGITAL) return;
	switch (mode) {
	  case CHANGE:	mask = 0x0B; break;
	  case RISING:	mask = 0x09; break;
	  case FALLING:	mask = 0x0A; break;
	  case LOW:	mask = 0x08; break;
	  case HIGH:	mask = 0x0C; break;
	  default: return;
	}
	mask = (mask << 16) | 0x01000000;
	config = portConfigRegister(pin);

	__disable_irq();
	cfg = *config;
	cfg &= ~0x000F0000;		// disable any previous interrupt
	*config = cfg;
	intFunc[pin] = function;	// set the function pointer
	cfg |= mask;
	*config = cfg;			// enable the new interrupt
	__enable_irq();
}

void detachInterrupt(uint8_t pin)
{
	volatile uint32_t *config;

	config = portConfigRegister(pin);
	__disable_irq();
	*config = ((*config & ~0x000F0000) | 0x01000000);
	intFunc[pin] = NULL;
	__enable_irq();
}


void porta_isr(void)
{
	uint32_t isfr = PORTA_ISFR;
	PORTA_ISFR = isfr;
	if ((isfr & CORE_PIN3_BITMASK) && intFunc[3]) intFunc[3]();
	if ((isfr & CORE_PIN4_BITMASK) && intFunc[4]) intFunc[4]();
	if ((isfr & CORE_PIN24_BITMASK) && intFunc[24]) intFunc[24]();
	if ((isfr & CORE_PIN33_BITMASK) && intFunc[33]) intFunc[33]();
}

void portb_isr(void)
{
	uint32_t isfr = PORTB_ISFR;
	PORTB_ISFR = isfr;
	if ((isfr & CORE_PIN0_BITMASK) && intFunc[0]) intFunc[0]();
	if ((isfr & CORE_PIN1_BITMASK) && intFunc[1]) intFunc[1]();
	if ((isfr & CORE_PIN16_BITMASK) && intFunc[16]) intFunc[16]();
	if ((isfr & CORE_PIN17_BITMASK) && intFunc[17]) intFunc[17]();
	if ((isfr & CORE_PIN18_BITMASK) && intFunc[18]) intFunc[18]();
	if ((isfr & CORE_PIN19_BITMASK) && intFunc[19]) intFunc[19]();
	if ((isfr & CORE_PIN25_BITMASK) && intFunc[25]) intFunc[25]();
	if ((isfr & CORE_PIN32_BITMASK) && intFunc[32]) intFunc[32]();
}

void portc_isr(void)
{
	// TODO: these are inefficent.  Use CLZ somehow....
	uint32_t isfr = PORTC_ISFR;
	PORTC_ISFR = isfr;
	if ((isfr & CORE_PIN9_BITMASK) && intFunc[9]) intFunc[9]();
	if ((isfr & CORE_PIN10_BITMASK) && intFunc[10]) intFunc[10]();
	if ((isfr & CORE_PIN11_BITMASK) && intFunc[11]) intFunc[11]();
	if ((isfr & CORE_PIN12_BITMASK) && intFunc[12]) intFunc[12]();
	if ((isfr & CORE_PIN13_BITMASK) && intFunc[13]) intFunc[13]();
	if ((isfr & CORE_PIN15_BITMASK) && intFunc[15]) intFunc[15]();
	if ((isfr & CORE_PIN22_BITMASK) && intFunc[22]) intFunc[22]();
	if ((isfr & CORE_PIN23_BITMASK) && intFunc[23]) intFunc[23]();
	if ((isfr & CORE_PIN27_BITMASK) && intFunc[27]) intFunc[27]();
	if ((isfr & CORE_PIN28_BITMASK) && intFunc[28]) intFunc[28]();
	if ((isfr & CORE_PIN29_BITMASK) && intFunc[29]) intFunc[29]();
	if ((isfr & CORE_PIN30_BITMASK) && intFunc[30]) intFunc[30]();
}

void portd_isr(void)
{
	uint32_t isfr = PORTD_ISFR;
	PORTD_ISFR = isfr;
	if ((isfr & CORE_PIN2_BITMASK) && intFunc[2]) intFunc[2]();
	if ((isfr & CORE_PIN5_BITMASK) && intFunc[5]) intFunc[5]();
	if ((isfr & CORE_PIN6_BITMASK) && intFunc[6]) intFunc[6]();
	if ((isfr & CORE_PIN7_BITMASK) && intFunc[7]) intFunc[7]();
	if ((isfr & CORE_PIN8_BITMASK) && intFunc[8]) intFunc[8]();
	if ((isfr & CORE_PIN14_BITMASK) && intFunc[14]) intFunc[14]();
	if ((isfr & CORE_PIN20_BITMASK) && intFunc[20]) intFunc[20]();
	if ((isfr & CORE_PIN21_BITMASK) && intFunc[21]) intFunc[21]();
}

void porte_isr(void)
{
	uint32_t isfr = PORTE_ISFR;
	PORTE_ISFR = isfr;
	if ((isfr & CORE_PIN26_BITMASK) && intFunc[26]) intFunc[26]();
	if ((isfr & CORE_PIN31_BITMASK) && intFunc[31]) intFunc[31]();
}








#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minumim time to refresh servos in microseconds 

#define PDB_CONFIG (PDB_SC_TRGSEL(15) | PDB_SC_PDBEN | PDB_SC_PDBIE \
	| PDB_SC_CONT | PDB_SC_PRESCALER(2) | PDB_SC_MULT(0))
#define PDB_PRESCALE 4
#define usToTicks(us)    ((us) * (F_BUS / 1000) / PDB_PRESCALE / 1000)
#define ticksToUs(ticks) ((ticks) * PDB_PRESCALE * 1000 / (F_BUS / 1000))


uint16_t servo_active_mask = 0;
uint8_t servo_pin[12];
uint16_t servo_ticks[12];

void init_servo(void)
{
	// for servo
	SIM_SCGC6 |= SIM_SCGC6_PDB;	// TODO: use bitband for atomic read-mod-write
	pinMode(12, OUTPUT);
	PDB0_MOD = 0xFFFF;
	PDB0_CNT = 0;
	PDB0_IDLY = 0;
	PDB0_SC = PDB_CONFIG;
	NVIC_ENABLE_IRQ(IRQ_PDB);
	// TODO: maybe this should be a higher priority than most
	// other interrupts (init all to some default?)
	PDB0_SC = PDB_CONFIG | PDB_SC_SWTRIG;

	//servo_active_mask = 9;
	servo_active_mask = 8;
	//servo_pin[0] = 12;
	//servo_ticks[0] = usToTicks(600);
	servo_pin[3] = 11;
	servo_ticks[3] = usToTicks(2100);
	//pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
}

void pdb_isr(void)
{
	static int8_t channel=0, channel_high=12;
	static uint32_t tick_accum=0;
	uint32_t ticks;
	int32_t wait_ticks;

	// first, if any channel was left high from the previous
	// run, now is the time to shut it off
	if (servo_active_mask & (1<<channel_high)) {
		digitalWrite(servo_pin[channel_high], LOW);
		channel_high = 12;
	}
	// search for the next channel to turn on
	while (channel < 12) {
		if (servo_active_mask & (1<<channel)) {
			digitalWrite(servo_pin[channel], HIGH);
			channel_high = channel;
			ticks = servo_ticks[channel];
			tick_accum += ticks;
			PDB0_IDLY += ticks;
			PDB0_SC = PDB_CONFIG | PDB_SC_LDOK;
			channel++;
			return;
		}
		channel++;
	}
	// when all channels have output, wait for the
	// minimum refresh interval
	wait_ticks = usToTicks(REFRESH_INTERVAL) - tick_accum;
	if (wait_ticks < usToTicks(100)) wait_ticks = usToTicks(100);
	else if (wait_ticks > 60000) wait_ticks = 60000;
	tick_accum += wait_ticks;
	PDB0_IDLY += wait_ticks;
	PDB0_SC = PDB_CONFIG | PDB_SC_LDOK;
	// if this wait is enough to satisfy the refresh
	// interval, next time begin again at channel zero 
	if (tick_accum >= usToTicks(REFRESH_INTERVAL)) {
		tick_accum = 0;
		channel = 0;
	}
}



static uint32_t tone_toggle_count;
static uint8_t *tone_reg;
static uint8_t tone_pin;


void init_tone(void)
{
	SIM_SCGC6 |= SIM_SCGC6_PIT; // TODO: use bitband for atomic read-mod-write
	PIT_MCR = 0;
	PIT_TCTRL3 = 0;		// disabled
	tone_pin = 255;
	NVIC_ENABLE_IRQ(IRQ_PIT_CH3);
}

void tone(uint8_t pin, uint16_t frequency, uint32_t duration)
{
	uint32_t count, load;
	volatile uint32_t *config;

	if (pin >= CORE_NUM_DIGITAL) return;
	if (duration) {
		count = (frequency * duration / 1000) * 2;
	} else {
		count = 0xFFFFFFFF;
	}
	load = (F_BUS / 2) / frequency;
	config = portConfigRegister(pin);
	__disable_irq();
	if (pin != tone_pin) {
		if (tone_pin < CORE_NUM_DIGITAL) {
			tone_reg[0] = 1; // clear pin
		}
		tone_pin = pin;
		tone_reg = portClearRegister(pin);
		tone_reg[0] = 1; // clear pin
		tone_reg[384] = 1; // output mode;
		*config = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	}
	tone_toggle_count = count;
	if (PIT_LDVAL3 != load) {
		PIT_TCTRL3 = 0;
		PIT_LDVAL3 = load;
		PIT_TCTRL3 = 3;
	}
	__enable_irq();
}

void pit3_isr(void)
{
	PIT_TFLG3 = 1;

	if (tone_toggle_count) {
		tone_reg[128] = 1; // toggle
		if (tone_toggle_count < 0xFFFFFFFF) tone_toggle_count--;
	} else {
		PIT_TCTRL3 = 0;
		tone_reg[0] = 0; // clear
		tone_pin = 255;
	}
}

void noTone(uint8_t pin)
{
	if (pin >= CORE_NUM_DIGITAL) return;
	__disable_irq();
	if (pin == tone_pin) {
		PIT_TCTRL3 = 0;
		tone_reg[0] = 0; // clear
		tone_pin = 255;
	}
	__enable_irq();
}


//void init_pins(void)
void _init_Teensyduino_internal_(void)
{
	init_pin_interrupts();

	SIM_SCGC6 |= SIM_SCGC6_FTM0;	// TODO: use bitband for atomic read-mod-write
	SIM_SCGC6 |= SIM_SCGC6_FTM1;
	FTM0_CNT = 0;
	FTM0_MOD = 32767;
	FTM0_C0SC = 0x28; // MSnB:MSnA = 10, ELSnB:ELSnA = 10
	FTM0_C1SC = 0x28;
	FTM0_C2SC = 0x28;
	FTM0_C3SC = 0x28;
	FTM0_C4SC = 0x28;
	FTM0_C5SC = 0x28;
	FTM0_C6SC = 0x28;
	FTM0_C7SC = 0x28;
	FTM0_SC = FTM_SC_CLKS(1) | FTM_SC_PS(0);
	FTM1_CNT = 0;
	FTM1_MOD = 32767;
	FTM1_C0SC = 0x28;
	FTM1_C1SC = 0x28;
	FTM1_SC = FTM_SC_CLKS(1) | FTM_SC_PS(0);

	analog_init();
	init_servo();
	init_tone();
	delay(100); // TODO: this is not necessary, right?
	usb_init();
}



// SOPT4 is SIM select clocks?
// FTM is clocked by the bus clock, either 24 or 48 MHz
// input capture can be FTM1_CH0, CMP0 or CMP1 or USB start of frame
// 24 MHz with reload 49152 to match Arduino's speed = 488.28125 Hz
// 24 MHz with reload 32768 creates a PWM output = 732.421875 Hz

void analogWrite(uint8_t pin, int val)
{
	uint32_t cval;

	pinMode(pin, OUTPUT);
	if (val <= 0) {
		digitalWrite(pin, LOW);
		pinMode(pin, OUTPUT);	// TODO: implement OUTPUT_LOW
		return;
	} else if (val > 255) {
		digitalWrite(pin, HIGH);
		pinMode(pin, OUTPUT);	// TODO: implement OUTPUT_HIGH
		return;
	}
	if (pin == 3 || pin == 4) {
		cval = (val * (FTM1_MOD + 1)) >> 8;
	} else {
		cval = (val * (FTM0_MOD + 1)) >> 8;
	}
	switch (pin) {
	  case 3: // PTA12, FTM1_CH0
		FTM1_C0V = cval;
		CORE_PIN3_CONFIG = PORT_PCR_MUX(3) | PORT_PCR_DSE | PORT_PCR_SRE;
		break;
	  case 4: // PTA13, FTM1_CH1
		FTM1_C1V = cval;
		CORE_PIN4_CONFIG = PORT_PCR_MUX(3) | PORT_PCR_DSE | PORT_PCR_SRE;
		break;
	  case 5: // PTD7, FTM0_CH7
		FTM0_C7V = cval;
		CORE_PIN5_CONFIG = PORT_PCR_MUX(4) | PORT_PCR_DSE | PORT_PCR_SRE;
		break;
	  case 6: // PTD4, FTM0_CH4
		FTM0_C4V = cval;
		CORE_PIN6_CONFIG = PORT_PCR_MUX(4) | PORT_PCR_DSE | PORT_PCR_SRE;
		break;
	  case 9: // PTC3, FTM0_CH2
		FTM0_C2V = cval;
		CORE_PIN9_CONFIG = PORT_PCR_MUX(4) | PORT_PCR_DSE | PORT_PCR_SRE;
		break;
	  case 10: // PTC4, FTM0_CH3
		FTM0_C3V = cval;
		CORE_PIN10_CONFIG = PORT_PCR_MUX(4) | PORT_PCR_DSE | PORT_PCR_SRE;
		break;
	  case 20: // PTD5, FTM0_CH5
		FTM0_C5V = cval;
		CORE_PIN20_CONFIG = PORT_PCR_MUX(4) | PORT_PCR_DSE | PORT_PCR_SRE;
		break;
	  case 21: // PTD6, FTM0_CH6
		FTM0_C6V = cval;
		CORE_PIN21_CONFIG = PORT_PCR_MUX(4) | PORT_PCR_DSE | PORT_PCR_SRE;
		break;
	  case 22: // PTC1, FTM0_CH0
		FTM0_C0V = cval;
		CORE_PIN22_CONFIG = PORT_PCR_MUX(4) | PORT_PCR_DSE | PORT_PCR_SRE;
		break;
	  case 23: // PTC2, FTM0_CH1
		FTM0_C1V = cval;
		CORE_PIN23_CONFIG = PORT_PCR_MUX(4) | PORT_PCR_DSE | PORT_PCR_SRE;
		break;
	  default:
		digitalWrite(pin, (val > 127) ? HIGH : LOW);
	}
}


// TODO: startup code needs to initialize all pins to GPIO mode, input by default

void digitalWrite(uint8_t pin, uint8_t val)
{
	if (pin >= CORE_NUM_DIGITAL) return;
	if (*portModeRegister(pin)) {
		if (val) {
			*portSetRegister(pin) = 1;
		} else {
			*portClearRegister(pin) = 1;
		}
	} else {
		volatile uint32_t *config = portConfigRegister(pin);
		if (val) {
			// TODO use bitband for atomic read-mod-write
			*config |= (PORT_PCR_PE | PORT_PCR_PS);
		} else {
			// TODO use bitband for atomic read-mod-write
			*config &= PORT_PCR_PE;
		}
	}

}

uint8_t digitalRead(uint8_t pin)
{
	if (pin >= CORE_NUM_DIGITAL) return 0;
	return *portInputRegister(pin);
}



void pinMode(uint8_t pin, uint8_t mode)
{
	volatile uint32_t *config;

	if (pin >= CORE_NUM_DIGITAL) return;
	config = portConfigRegister(pin);

	if (mode == OUTPUT) {
		*portModeRegister(pin) = 1;
		*config = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	} else {
		*portModeRegister(pin) = 0;
		if (mode == INPUT) {
			*config = PORT_PCR_MUX(1);
		} else {
			*config = PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; // pullup
		}
	}
}


void _shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
        if (bitOrder == LSBFIRST) {
                shiftOut_lsbFirst(dataPin, clockPin, value);
        } else {
                shiftOut_msbFirst(dataPin, clockPin, value);
        }
}

void shiftOut_lsbFirst(uint8_t dataPin, uint8_t clockPin, uint8_t value)
{
        uint8_t mask;
        for (mask=0x01; mask; mask <<= 1) {
                digitalWrite(dataPin, value & mask);
                digitalWrite(clockPin, HIGH);
                digitalWrite(clockPin, LOW);
        }
}

void shiftOut_msbFirst(uint8_t dataPin, uint8_t clockPin, uint8_t value)
{
        uint8_t mask;
        for (mask=0x80; mask; mask >>= 1) {
                digitalWrite(dataPin, value & mask);
                digitalWrite(clockPin, HIGH);
                digitalWrite(clockPin, LOW);
        }
}

uint8_t _shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
        if (bitOrder == LSBFIRST) {
                return shiftIn_lsbFirst(dataPin, clockPin);
        } else {
                return shiftIn_msbFirst(dataPin, clockPin);
        }
}

uint8_t shiftIn_lsbFirst(uint8_t dataPin, uint8_t clockPin)
{
        uint8_t mask, value=0;
        for (mask=0x01; mask; mask <<= 1) {
                digitalWrite(clockPin, HIGH);
                if (digitalRead(dataPin)) value |= mask;
                digitalWrite(clockPin, LOW);
        }
        return value;
}

uint8_t shiftIn_msbFirst(uint8_t dataPin, uint8_t clockPin)
{
        uint8_t mask, value=0;
        for (mask=0x80; mask; mask >>= 1) {
                digitalWrite(clockPin, HIGH);
                if (digitalRead(dataPin)) value |= mask;
                digitalWrite(clockPin, LOW);
        }
        return value;
}



// the millis counter... not "timer0" anymore, but keeping Teensy 2.0 name
volatile uint32_t timer0_millis_count __attribute__ ((aligned (4))) = 0;

void systick_isr(void)
{
	timer0_millis_count++;
}

uint32_t micros(void)
{
	uint32_t count, current, istatus;

	__disable_irq();
	current = SYST_CVR;
	count = timer0_millis_count;
	istatus = SCB_ICSR;	// bit 26 indicates if systick exception pending
	__enable_irq();
	if ((istatus & SCB_ICSR_PENDSTSET) && current > ((F_CPU / 1000) - 50)) count++;
	current = ((F_CPU / 1000) - 1) - current;
	return count * 1000 + current / (F_CPU / 1000000);
}

void delay(uint32_t ms)
{
	uint32_t start = micros();

	while (ms > 0) {
		if ((micros() - start) >= 1000) {
			ms--;
			start += 1000;
		}
	}
}

#if F_CPU == 96000000
#define PULSEIN_LOOPS_PER_USEC 14
#elif F_CPU == 48000000
#define PULSEIN_LOOPS_PER_USEC 7
#elif F_CPU == 24000000
#define PULSEIN_LOOPS_PER_USEC 4
#endif


uint32_t pulseIn_high(volatile uint8_t *reg, uint32_t timeout)
{
	uint32_t timeout_count = timeout * PULSEIN_LOOPS_PER_USEC;
	uint32_t usec_start, usec_stop;
	
	// wait for any previous pulse to end
	while (*reg) {
		if (--timeout_count == 0) return 0;
	}
	// wait for the pulse to start
	while (!*reg) {
		if (--timeout_count == 0) return 0;
	}
	usec_start = micros();
	// wait for the pulse to stop
	while (*reg) {
		if (--timeout_count == 0) return 0;
	}
	usec_stop = micros();
	return usec_stop - usec_start;
}

uint32_t pulseIn_low(volatile uint8_t *reg, uint32_t timeout)
{
	uint32_t timeout_count = timeout * PULSEIN_LOOPS_PER_USEC;
	uint32_t usec_start, usec_stop;
	
	// wait for any previous pulse to end
	while (!*reg) {
		if (--timeout_count == 0) return 0;
	}
	// wait for the pulse to start
	while (*reg) {
		if (--timeout_count == 0) return 0;
	}
	usec_start = micros();
	// wait for the pulse to stop
	while (!*reg) {
		if (--timeout_count == 0) return 0;
	}
	usec_stop = micros();
	return usec_stop - usec_start;
}

// TODO: an inline version should handle the common case where state is const
uint32_t pulseIn(uint8_t pin, uint8_t state, uint32_t timeout)
{
	if (pin >= CORE_NUM_DIGITAL) return 0;
	if (state) return pulseIn_high(portInputRegister(pin), timeout);
	return pulseIn_low(portInputRegister(pin), timeout);;
}




























