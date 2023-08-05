# Philosophers

## Notes (19/07/2023)

1. Mutex should always protect the fork variable, not be the fork itself;
2. Mutex should be seem as a room;
3. We should always lock the shared variables;
4. The most important part of the beginning is to understand how mutex work;
5. If more than one thread is going to be using the variable we should have a mutex for it;

## Notes (25/07/2023)

My proposal for the algo:
	1. We must init. the philo.;
	2. Always check if they are alive of not.

## Notes (26/07/2023)


Important information:
	struct timeval {
		time_t      tv_sec;     // Represents the number of whole seconds.
		suseconds_t tv_usec;    // Represents the number of microseconds (1/1,000,000 of a second).
	};

	usleep():

Description:
The usleep() function suspends execution of the calling thread for (at least) usec microseconds. The sleep may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers. 

To check data races, we can use hellgrind

	gcc -g -o your_program your_program.c -pthread
	valgrind --tool=helgrind ./your_program

## Notes (27/07/2023)

I will use the mutex to lock the use of the varible fork_status to check whether the forks/mutexes are availble or not.

Init. Philos:
	I loop through the amount of philosophers and its left fork is going go be its current index. The right fork is going to be the current index + 1. For the last philosopher the left fork is the current index and the right one is the 0;

Pick fork:
	A philo. is going to take its fork and lock the thread with pthread_mutex_lock and change the state of the fork_status.
Place fork:
	Do the inverse of the take fork.
Eat:
	With the forks taken, the philosophers eats for an X amount of time(usleep). When done it drops the forks.
Sleep:
	A philosopher sleeps (usleep) for X amount of time; With the fork realeased.
Think:
	While it hasn't timed out the philo. waits until there is another fork avaible. If the philosophers times out its status should change.

Die:
	On the main thread we are going to be looping over and over until we find whether a philosophers died or not through its status on the philo. struct.
	If a philo. died it should print the message and clear the message.

Chaleira note: Verify in each action wether the philo. is alive or not. They may die during a loot


Convertion note: usleep works with microseconds; gettimeofday works with microsendcs aswell; the subject says we must work with miliseconds.
	1 millisecond (ms) = 1000 microseconds (μs)
	1 microsecond (μs) = 0.001 milliseconds (ms)

## Notes (03/07/2023)

I've defined that the fork of the philosopher is going to be on its left side.
I've figured out the algo for the philosophers turn.

## Notes (03/07/2023)

In order to have access to the posix manual we should install it as follow:

```
sudo apt install manpages-posix-dev
```
