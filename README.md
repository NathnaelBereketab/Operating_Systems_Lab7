# Operating Systems – Lab 7  
## Programming Using Threads (pThreads Lab)

---

### Overview
This lab demonstrates the use of **POSIX Threads (pThreads)** to perform **parallel matrix arithmetic**.  
The program executes **addition**, **subtraction**, and **dot product (matrix multiplication)** operations  
on two 20×20 matrices using a total of **10 threads**.

Each thread is assigned **2 rows** of the matrices, allowing the workload to be divided evenly across threads.  
This approach demonstrates how multi-threading can improve computation efficiency using divide-and-conquer parallelism.

---

### Features
- Uses **10 total threads** (2 rows per thread)  
- Performs **addition**, **subtraction**, and **dot product** in parallel  
- Safe memory management (`malloc` + `free` per thread)  
- Based on provided Codio `matrix.c` template  
- Outputs results for verification  

---

### 💻 Compilation
To compile the program, run:

    gcc -std=c99 -pthread -o matrix matrix.c -I.

---

### ▶️ Execution
To execute the program, run:

    ./matrix

---

### 📤 Output Example
    Matrix A:
    ... (20x20 random numbers)

    Matrix B:
    ... (20x20 random numbers)

    Sum of Matrices:
    ... (A + B results)

    Difference of Matrices:
    ... (A - B results)

    Product of Matrices:
    ... (A × B dot product results)

---

### Implementation Details
- **Matrix Size:** 20 × 20  
- **Threads:** 10 total (2 rows per thread)  
- **Libraries Used:**  
  - `<pthread.h>`  
  - `<stdlib.h>`  
  - `<time.h>`  
- **Synchronization:** No shared writes — each thread handles its own rows, avoiding race conditions.  
- **Memory:** Each thread dynamically allocates and frees its argument struct safely.

---

### Author
**Nathnael Bereketab**  

---

**Compile Instruction:**

    gcc -std=c99 -pthread -o matrix matrix.c -I.

**Run Instruction:**

    ./matrix
