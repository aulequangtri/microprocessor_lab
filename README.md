# Microcontroller Laboratory (Vi xử lý - Vi điều khiển)

**Ho Chi Minh City University of Technology (HCMUT - VNU-HCM)**  
**Faculty of Computer Science and Engineering**  
**Student:** Âu Lê Quang Trí (ID: 2453300)  
**Target Platform:** STM32F103C6 (ARM Cortex-M3), STM32CubeIDE, Proteus 8 Professional

---

## Repository Structure

```
microprocessor/
├── Lab_01 (1).pdf                  # Assignment manual: Lab 1 (LED Animations)
├── VXL_VDK_Lab_2 (1).pdf           # Assignment manual: Lab 2 (Timer Interrupt & LED Scanning)
├── graphics/
│   └── hcmut.png                   # University logo for LaTeX report cover page
├── images/
│   ├── ex1.png ... 7_to_10.png     # Lab 1 Proteus schematics
│   ├── lap2_ex1.png                # Lab 2 Ex 1 schematic (Two 7-segment displays)
│   ├── lap2_ex2.png                # Lab 2 Ex 2-8 schematic (Four 7-segment displays + DOT)
│   └── lap2_ex9.png                # Lab 2 Ex 9-10 schematic (8x8 LED Matrix + ULN2803)
├── src/
│   ├── Lab1/                       # Lab 1 source code (LED animations, traffic lights)
│   │   ├── Led_animation_main.c
│   │   ├── ex2_main.c
│   │   ├── ex4_main.c
│   │   ├── ex5_main.c
│   │   ├── ex6_main.c
│   │   ├── ex6_2_main.c
│   │   └── ex6_7_8_9_10_main.c
│   └── Lab2/                       # Lab 2 source code (Timer interrupts, cooperative multitasking)
│       ├── lap2_ex1_main.c         # Ex 1: Dual 7-segment display scanning
│       ├── lap2_ex2_main.c         # Ex 2: Quad 7-segment display + blinking DOT
│       ├── lap2_ex3_main.c         # Ex 3: Modular update7SEG() function
│       ├── lap2_ex4_main.c         # Ex 4: 1 Hz overall scanning frequency
│       ├── lap2_ex5_main.c         # Ex 5: Digital clock buffer updating
│       ├── lap2_ex6_main.c         # Ex 6: Software timer concept and timing tests
│       ├── lap2_ex7_main.c         # Ex 7: Digital clock non-blocking main loop
│       ├── lap2_ex8_main.c         # Ex 8: Decoupled ISR and main() task scheduler
│       ├── lap2_ex9_main.c         # Ex 9: 8x8 LED matrix display ('A') via ULN2803
│       └── lap2_ex10_main.c        # Ex 10: Horizontal scrolling text animation
├── codespace.sty                   # LaTeX code listing and syntax highlighting style
├── hcmut-report.cls                # HCMUT standard report document class
├── main_lab1.tex                   # LaTeX report source for Lab 1
├── 2453300.pdf                     # Compiled Lab 1 Report PDF
├── main.tex                        # LaTeX report source for Lab 2
├── Lab2_Report.pdf                 # Compiled Lab 2 Report PDF
└── 2453300_Lab2.pdf                # Submission copy of Lab 2 Report PDF
```

---

## Lab Summaries

### Lab 1: LED Animations & GPIO Control
- Basic GPIO initialization and push-pull output control on STM32F103C6.
- 2-state LED toggling with software delays (`HAL_Delay`).
- 3-color traffic light sequencing.
- 7-segment display decoding via GPIO.

### Lab 2: Timer Interrupt and LED Scanning
- **Hardware Timer Configuration:** TIM2 configured with $\text{Prescaler} = 7999$ and $\text{Period} = 9$ generating precise $10\,\text{ms}$ ticks ($100\,\text{Hz}$).
- **Time-Division Multiplexing (POV):** Multi-digit 7-segment and 8x8 matrix scanning with active-low segment lines and PNP / ULN2803 column drivers.
- **Cooperative Software Timers:** Array-based non-blocking timers eliminating blocking `HAL_Delay()` and keeping the ISR ultra-lean ($O(1)$).
- **Matrix Animation:** Circular column shifting buffer producing smooth horizontal scrolling text.

---

## Build Instructions (LaTeX)

To compile the Lab 2 report using `latexmk` and MiKTeX with Strawberry Perl:
```powershell
latexmk -pdf -shell-escape -jobname=Lab2_Report -interaction=nonstopmode main.tex
```
