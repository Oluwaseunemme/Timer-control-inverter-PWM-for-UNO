🔧 Custom PWM Generator Using ATmega328P Timer1

This project explores the generation of a custom PWM signal using the ATmega328P Timer1 hardware, without relying on Arduino's built-in analogWrite() function.

The goal was to understand how PWM frequency, resolution, duty cycle, timer TOP values, complementary outputs, and dead time can be implemented directly through AVR registers.

🎯 Project Objective

The project was developed as a hands-on exercise to understand the relationship between:

CPU clock frequency
PWM frequency
Timer prescaler
Timer TOP value
PWM resolution
Duty-cycle calculation
Output Compare Registers (OCR1A / OCR1B)
Timer configuration registers
Complementary PWM outputs
Dead-time insertion

The generated PWM signals were verified using an oscilloscope.

⚙️ How It Works

The system uses the ATmega328P's 16-bit Timer1 to generate PWM.

Instead of using:

analogWrite();

the timer is configured directly through registers such as:

TCCR1A
TCCR1B
ICR1
OCR1A
OCR1B
TIMSK1

The PWM frequency is determined from the CPU clock, prescaler, and Timer1 TOP value.

For Phase and Frequency Correct PWM (Mode 8):

$$ f_{PWM}=\frac{F_{CPU}}{2\times N\times TOP} $$

Therefore:

$$ TOP=\frac{F_{CPU}}{2\times N\times f_{PWM}} $$

where:

\(F_{CPU}\) = 16 MHz
\(N\) = timer prescaler
\(f_{PWM}\) = desired PWM frequency

The duty-cycle command is then converted into a corresponding OCR1A/OCR1B compare value.

🔄 Complementary PWM

The project also generates complementary PWM outputs on:

OC1A → Arduino Pin 9
OC1B → Arduino Pin 10

The two outputs are configured so that their switching states are complementary.

This is particularly useful as a foundation for applications such as:

Half-bridge converters
Full-bridge inverters
Motor drives
Switching power supplies
⏱️ Dead Time

A small dead time was introduced between the complementary switching signals.

This prevents both switches in the same bridge leg from being commanded ON simultaneously.

Conceptually:

PWM A:  ────────┐       ┌────────
                │       │
                └───────┘
                  ↑   ↑
               dead time

PWM B:          ────────┐       ┌──────
                        │       │
                        └───────┘

The resulting signals were observed and verified using an oscilloscope.

🧪 Hardware / Tools
Arduino Uno / ATmega328P
16 MHz clock
Timer1
Oscilloscope
Arduino IDE
AVR register-level programming
📊 Verification

The oscilloscope was used to verify:

PWM frequency
Duty cycle
Complementary switching
Dead-time interval
Output waveform behavior

The scope measurements provided practical confirmation that the Timer1 register configuration was producing the expected switching signals.

📁 Repository Contents
├── PWM_Generator.ino
├── README.md
└── images/
    ├── code.png
    └── oscilloscope.png
🚀 What I Learned

This project helped me understand PWM at a much deeper level by moving from high-level Arduino functions to direct hardware control.

The major takeaway was understanding that the microcontroller does not need to continuously toggle the GPIO pins in software. Instead, the CPU configures the timer, loads the compare values, and the Timer1 peripheral generates the PWM waveform in hardware.
