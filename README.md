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
├── Lab3/                               # Lab 3: Buttons, Switches & FSM Traffic Light
│   ├── VXL_VDK_Lab_3_Buttons-Switches (1).pdf # Lab manual
│   ├── Traffic_Light_Project_Overview.docx    # Architecture overview
│   ├── main.tex                        # LaTeX report source (30 pages)
│   ├── main.pdf                        # Compiled report PDF
│   ├── 2453300_Lab3.pdf                # Submission copy of Lab 3 Report PDF
│   ├── codespace.sty                   # Syntax highlighting style
│   ├── hcmut-report.cls                # HCMUT standard report class
│   ├── graphics/                       # Cover logo (hcmut.png)
│   ├── images/                         # Proteus simulation schematics
│   │   └── lap3.png                    # Complete 4-way traffic light circuit
│   └── src/                            # Lab 3 C firmware & drivers
│       ├── main.c                      # Super-loop scheduler & initialization
│       ├── pin_map.h                   # Port and pin abstraction
│       ├── software_timer.c/.h         # Hardware-independent timer subsystem
│       ├── input_reading.c/.h          # Double-buffer button debounce engine
│       ├── input_processing.c/.h       # 3-state button event & auto-repeat FSM
│       ├── output_display.c/.h         # 4-digit 7-segment multiplex scanning
│       ├── fsm_traffic.c/.h            # Traffic lights & parameter tuning FSM
│       └── timer.c                     # TIM2 ISR callback router
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

### Lab 3: Buttons, Switches & FSM Traffic Light System
- **Layered Software Architecture:** Completely modularized architecture separating hardware access (`pin_map.h`), input debounce (`input_reading.c`), button FSM with auto-repeat (`input_processing.c`), timebase (`software_timer.c`), display multiplexing (`output_display.c`), and operational logic (`fsm_traffic.c`).
- **Input Debounce & Auto-Repeat:** 2-buffer consecutive-match debouncing sampled every $10\,\text{ms}$. Press-and-hold detected after $1\,\text{s}$, transitioning to continuous auto-repeating every $500\,\text{ms}$.
- **Multi-Rate Software Timer Subsystem:** Accepts durations directly in milliseconds, parameterized by `TIMER_CYCLE` ($10\,\text{ms}$ hardware tick). Decoupled from hardware prescalers.
- **Display Scanning & Ghosting Prevention:** 4-digit 7-segment multiplexing with 2N2907 PNP driver transistors ($5\,\text{ms}$ per digit, $50\,\text{Hz}$ frame rate). GPIOs initialized HIGH to prevent power-on display ghosting.
- **4 Operational Modes:**
  - **Mode 1 (Normal):** Dual synchronized road countdowns obeying 4-phase sequence.
  - **Mode 2 (Tuning Red):** Road LEDs blink Red at $2\,\text{Hz}$ ($250\,\text{ms}$ toggle). Displays show mode index `02` and calibrated duration.
  - **Mode 3 (Tuning Amber):** Road LEDs blink Amber at $2\,\text{Hz}$. Displays show mode `03` and calibrated duration.
  - **Mode 4 (Tuning Green):** Road LEDs blink Green at $2\,\text{Hz}$. Displays show mode `04` and calibrated duration.
- **Timing Invariant Enforcement:** Mathematical validation $t_{\text{red}} = t_{\text{green}} + t_{\text{amber}}$ guarantees that traffic phases remain safe and conflict-free upon saving. Uncommitted edits are discarded on mode transition.

---

## Build Instructions (LaTeX)

Each subfolder (`Lab1`, `Lab2`, and `Lab3`) is fully self-contained. To compile:

```powershell
# For Lab 1
cd Lab1
pdflatex -shell-escape -interaction=nonstopmode main.tex

# For Lab 2
cd Lab2
pdflatex -shell-escape -interaction=nonstopmode main.tex

# For Lab 3
cd Lab3
pdflatex -shell-escape -interaction=nonstopmode main.tex
```
