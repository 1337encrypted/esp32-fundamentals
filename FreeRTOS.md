## Basics

Multitasking?

<img width="1039" alt="image" src="https://github.com/1337encrypted/esp32-fundamentals/assets/46808309/2bc2297b-2c9e-48fd-ae9d-ce44bb549f0f">

The CPU is capable of performing only one task at a time, in multitaking we switch between tasks rapidly which gives us the illusion that all the tasks are been executed simultaneously in parallel.

Symmetric multi-processing

<img width="1039" alt="image" src="https://github.com/1337encrypted/esp32-fundamentals/assets/46808309/1539a8fd-cc91-4743-acc6-402bb928e763">

A multi-core system where each CPU has access to the same memory bus
In context with multasking, different tasks can run on both CPU's and if the CPU can switch between the task fast enough then it gives an illusion that all the tasks are running in parallel.

## FreeRTOS

1. Vanilla FreeRTOS (single core)
2. IDF SMP FreeRTOS (dual core SMP)
3. Amazon SMP FreeRTOS (N core SMP)

## Design differences

1. Tasks
1. Operating model
1. Scheduling
1. Tick Interrupts
1. Critical Sections

## Tasks

<img width="564" alt="image" src="https://github.com/1337encrypted/esp32-fundamentals/assets/46808309/752ed2ab-820c-4ad5-a8a8-f2b37cbdd3ba">

Tasks are implemented as functions and within each task there is an infite loop

Tasks can be in either on of these states
- Running
- Ready
- Blocked
- Suspended

1. When a task is created its usually in the **Ready state** which means ready to be run by the CPU
2. The task CPU choses to run goes to the **Running state**
3. When the waits for something or calls another function within itself then it calls the blocking API which puts it in **Blocked state**
4. Tasks are unblocked if they are timed out, then they go back to the **Ready state**
5. Tasks in suspended state have to be explictly put into it and unlike the blocked state they cannot wait for timeout or receive any resources, they have to be explictly resumed.

6. ### Creating a task in FreeRTOS

7. | RTOS | Creating | Affinity | tskNO_Affinity|
8. | :---: | :---: |
9. |  |  |

## Operating Model

1. Vanilla FreeRTOS

<img width="1054" alt="image" src="https://github.com/1337encrypted/esp32-fundamentals/assets/46808309/d703f822-b0b9-44bc-9cd8-f2a4c2898960">

CPU chooses one task from ready tasks

2. IDF SMP

<img width="1054" alt="image" src="https://github.com/1337encrypted/esp32-fundamentals/assets/46808309/d873767a-3931-4af1-b65a-72dae037114a">

Both CPU choose one task to execute from the available ready tasks
A task cannot be run by two CPU at any given point of time.

13:11



  
  
  

