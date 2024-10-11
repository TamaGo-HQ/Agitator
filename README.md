# Project Context
Chemotherapy requires precise drug preparation, often involving powdered drugs mixed with a diluting solution. The challenge is to avoid damaging the sensitive drug molecules during the mixing process. This project focuses on developing a medical agitator that gently mixes vials at low speeds to prevent molecular degradation, ensuring accurate and safe chemotherapy drug preparation.
# Notes on the code
To make the machine responsive to external events and user input (e.g., controlling the rotating motors and stopping/continuing operations when interrupted), we employ pseudo multi-threading

**Pseudo Multi-threading Explanation**
Multi-threading generally refers to running multiple threads (or processes) simultaneously. However, on an Arduino board, which lacks an operating system and can only run one program at a time, true multi-threading is not feasible. Thus, we use the term "pseudo."

**Main Loop Functionality**
The main loop function executes all operations sequentially throughout the board's running time. An examination of the algorithm reveals that there are no loops or delays in any function—only conditional statements (if-else and, occasionally, switch-case) are utilized. This design ensures the board remains responsive to user interrupts.

**Library**
All functions and global variables are declared in a library specifically developed for this project.
