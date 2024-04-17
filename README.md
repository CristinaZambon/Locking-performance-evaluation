# Intro
The C programs were designed to compare the performance of hand-over-hand locking and simple lock implementations under various workloads. The evaluation results highlighted differences in performance between the two locking mechanisms, with the hand-over-hand locking showing potential scalability but also demonstrating performance degradation under heavy workloads.

## 1st Workload: 
### Evaluation with 1,000,000 integers on the list and looking up for 10,000
I created two different program codes: “1hand_over_hand.c” implements the handover-hand locking, while “1simpleLock.c” implements the one-lock-per-list present
in the textbook.
Each program code generates an empty list; then, two threads are created and arerun at the same time. The thread function is inserting 10,000 random integers each
on the same list. As I run the two programs multiple times, I’d say that the overall time needed by the two threads is almost the same. However, the hand-over-hand 
locking tends to have slightly higher values.

![image](https://github.com/CristinaZambon/Locking-performance-evaluation/assets/109516477/b6881c0d-4edf-4f84-8a6e-46afbe261eb4)
![image](https://github.com/CristinaZambon/Locking-performance-evaluation/assets/109516477/ac6c9a62-9288-4f87-ab01-4eb069429844)

## 2nd Workload:
### Evaluation with 100,000 integers on the list and looking up for 1,000
I created two different program codes: “2_hand_over_hand.c” implements the
hand-over-hand locking, while “2_simpleLock.c” implements the one-lock-per-list
present in the textbook (Figure 29.7).
Each program code generates an empty list; then, two threads are created and are
run at the same time. The first thread function is inserting 1,000,000 random
integers on the list, while the second thread function is looking up 10,000 random
integers on the very same list. The hand-over-hand locking is way slower than the
simple lock. Because of this, I had to decrease the number of random integers
inserted by the first thread for both the locking implementations.

![image](https://github.com/CristinaZambon/Locking-performance-evaluation/assets/109516477/b37e75d3-a874-473a-a931-6933aba7971f)
![image](https://github.com/CristinaZambon/Locking-performance-evaluation/assets/109516477/e3c1703b-a417-4e06-af1c-82eced682e57)


## 3rd Workload: 
### Evaluation with 1,000 integers on the list and looking up for 100

The two programs generate a list with 100,000 random numbers and the two threads look up for 10,000 values. The hand-over-hand locking was slower and slower!
So we can state that even though the hand-over-hand locking is more scalable, the performances could get worse if the workload is too heavy.

![image](https://github.com/CristinaZambon/Locking-performance-evaluation/assets/109516477/f4b4b74d-a528-4200-afb0-58d62059db37)
