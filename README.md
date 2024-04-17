**Considering the 1st workload**
I created two different program codes: “1hand_over_hand.c” implements the handover-hand locking, while “1simpleLock.c” implements the one-lock-per-list present
in the textbook.
Each program code generates an empty list; then, two threads are created and arerun at the same time. The thread function is inserting 10,000 random integers each
on the same list. As I run the two programs multiple times, I’d say that the overall time needed by the two threads is almost the same. However, the hand-over-hand 
locking tends to have slightly higher values.

![image](https://github.com/CristinaZambon/Locking-performance-evaluation/assets/109516477/32a10c91-62c3-4e21-bdef-ae79bb8b2602)
