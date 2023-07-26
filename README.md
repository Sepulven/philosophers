## Observation (19/07/2023)

1. Mutex should always protect the fork variable, not be the fork itself;
2. Mutex should be seem as a room;
3. We should always lock the shared variables;
4. The most important part of the beginning is to understand how mutex work;
5. If more than one thread is going to be using the variable we should have a mutex for it;

## Observation (25/07/2023)

My proposal for the algo:
	1. We must init. the philo.;
	2. Always check if they are alive of not.