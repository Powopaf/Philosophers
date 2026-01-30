# Philosophers

A small simulation of the classical "Dining Philosophers" concurrency problem implemented in C using POSIX threads (pthreads). The program models philosophers who alternate between thinking and eating while sharing forks (mutexes). The goal of the project is to correctly synchronize the philosophers to avoid data races and ensure the program follows the expected behavior (tracking death by starvation, optional meal count, proper locking/unlocking, etc.).

## Description

This project implements a solution to the Dining Philosophers problem. Each philosopher is represented by a thread. Forks are modeled using `pthread_mutex_t`. The program tracks the time of the last meal for each philosopher, detects when a philosopher dies (has not eaten for longer than `time_to_die`), and optionally stops when each philosopher has eaten a specified number of times.

Key points:

- Uses pthreads and mutexes to synchronize access to forks and shared state.
- Tracks timestamps (in milliseconds) to decide when philosophers die.
- Includes a monitor thread to detect finished or dead philosophers.

## Instructions

### Build

1. Open a terminal and go to the `philo` directory:

```bash
cd philo
```

2. Build the program using the provided Makefile:

```bash
make
```

This produces the `philo` executable.

### Usage

Run the executable with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: number of philosophers and forks (int > 0)
- `time_to_die` (ms): time (in milliseconds) after which a philosopher dies if they haven't started eating
- `time_to_eat` (ms): time (in milliseconds) it takes a philosopher to eat
- `time_to_sleep` (ms): time (in milliseconds) a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` (optional): if provided, the simulation stops when each philosopher has eaten at least this many times

Example:

```bash
./philo 5 800 200 200
./philo 4 410 200 200 3
```

### Clean

From the `philo` directory you can clean build artifacts with:

```bash
make fclean
```

## Resources

[Explanation](https://github.com/TommyJD93/Philosophers)
[Base des threads](https://franckh.developpez.com/tutoriels/posix/pthreads/)

## Notes

- The program uses `pthread_mutex_t` for forks and per-philosopher mutexes to protect shared fields (e.g., last meal timestamp). If you change locking strategy or function signatures, review call sites carefully to avoid deadlocks (don't double-lock the same mutex).
- See the `philo/Makefile` for compilation flags and sanitizer options used during development.

For more details, read the source files in `philo/`.

*This project has been created as part of the 42 curriculum by pifourni*
