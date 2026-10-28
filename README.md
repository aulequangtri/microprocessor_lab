# Microcontroller Laboratory (Vi xử lý - Vi điều khiển)

**Ho Chi Minh City University of Technology (HCMUT - VNU-HCM)**  
**Faculty of Computer Science and Engineering**  
**Student:** Âu Lê Quang Trí (ID: 2453300)  
**Target Platform:** STM32F103C6 (ARM Cortex-M3), STM32CubeIDE, Proteus 8 Professional

---

## Repository Structure

```
microprocessor/
├── Lab1/                               # Lab 1: LED Animations & GPIO Control
│   ├── Lab_01 (1).pdf                  # Lab manual
│   ├── main.tex                        # LaTeX report source
│   ├── main.pdf                        # Compiled report PDF
│   ├── 2453300.pdf                     # Submission copy of Lab 1 Report PDF
│   ├── codespace.sty                   # Syntax highlighting style
│   ├── hcmut-report.cls                # HCMUT standard report class
│   ├── graphics/                       # Cover logo (hcmut.png)
│   ├── images/                         # Proteus simulation schematics
│   │   ├── ex1.png
│   │   ├── 2.png
│   │   ├── ex4.png
│   │   ├── ex5.png
│   │   ├── ex6.png
│   │   └── 7_to_10.png
│   └── src/                            # Lab 1 C source code
│       ├── Led_animation_main.c
│       ├── ex2_main.c
│       ├── ex4_main.c
│       ├── ex5_main.c
│       ├── ex6_main.c
│       ├── ex6_2_main.c
│       └── ex6_7_8_9_10_main.c
│
├── Lab2/                               # Lab 2: Timer Interrupt & LED Scanning
│   ├── VXL_VDK_Lab_2 (1).pdf           # Lab manual
│   ├── main.tex                        # LaTeX report source
│   ├── main.pdf                        # Compiled report PDF
│   ├── 2453300_Lab2.pdf                # Submission copy of Lab 2 Report PDF
│   ├── Lab2_Report_2453300.pdf         # Lab 2 submission report
│   ├── codespace.sty                   # Syntax highlighting style
│   ├── hcmut-report.cls                # HCMUT standard report class
│   ├── graphics/                       # Cover logo (hcmut.png)
│   ├── images/                         # Proteus simulation schematics
│   │   ├── lap2_ex1.png                # Ex 1: Dual 7-segment display
│   │   ├── lap2_ex2.png                # Ex 2-8: Quad 7-segment display + DOT
│   │   └── lap2_ex9.png                # Ex 9-10: 8x8 LED matrix + ULN2803
│   └── src/                            # Lab 2 C source code
│       ├── lap2_ex1_main.c             # Dual 7-segment scanning
│       ├── lap2_ex2_main.c             # Quad 7-segment + blinking DOT
│       ├── lap2_ex3_main.c             # Modular update7SEG()
│       ├── lap2_ex4_main.c             # 1 Hz overall scanning frequency
│       ├── lap2_ex5_main.c             # Digital clock buffer updating
│       ├── lap2_ex6_main.c             # Software timer concept
│       ├── lap2_ex7_main.c             # Non-blocking clock main loop
│       ├── lap2_ex8_main.c             # Decoupled ISR and task scheduler
│       ├── lap2_ex9_main.c             # 8x8 LED matrix display ('A')
│       └── lap2_ex10_main.c            # Horizontal scrolling text animation
│
├── codespace.sty                       # Root style reference
├── hcmut-report.cls                    # Root class reference
├── graphics/
│   └── hcmut.png                       # University logo
└── README.md
```

---

## Lab Summaries

### Lab 1: LED Animations & GPIO Control
- Basic GPIO initialization and push-pull output control on STM32F103C6.
- 2-state LED toggling with software delays (`HAL_Delay`).
- 3-color traffic light sequencing.
- 7-segment display decoding via GPIO.
- 12-LED analog clock simulation.

### Lab 2: Timer Interrupt and LED Scanning
- **Hardware Timer Configuration:** TIM2 configured with $\text{Prescaler} = 7999$ and $\text{Period} = 9$ generating precise $10\,\text{ms}$ ticks ($100\,\text{Hz}$).
- **Time-Division Multiplexing (POV):** Multi-digit 7-segment and 8x8 matrix scanning with active-low segment lines and PNP / ULN2803 column drivers.
- **Cooperative Software Timers:** Array-based non-blocking timers eliminating blocking `HAL_Delay()` and keeping the ISR ultra-lean ($O(1)$).
- **Matrix Animation:** Circular column shifting buffer producing smooth horizontal scrolling text.

---

## Build Instructions (LaTeX)

Each subfolder (`Lab1` and `Lab2`) is fully self-contained. To compile:

```powershell
# For Lab 1
cd Lab1
pdflatex -shell-escape -interaction=nonstopmode main.tex

# For Lab 2
cd Lab2
pdflatex -shell-escape -interaction=nonstopmode main.tex
```
