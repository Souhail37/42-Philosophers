# 42-Philosophers
42-Cursus : Philosophers
# Dining Philosophers

## Overview
The **Dining Philosophers** is a classic synchronization problem involving multiple philosophers who alternately eat and think at a round table with a limited number of forks. This project is divided into two parts: the mandatory part and the bonus part.

## Table of Contents
- [Mandatory Part](#mandatory-part)
- [How to Use](#how-to-use)
- [The "philo" Program](#the-philo-program)
- [The "philo_bonus" Program](#the-philo_bonus-program)
- [Rules](#rules)

### Mandatory Part

### How to Use
1. Clone the repository.
2. Navigate to the `philo/` directory for the mandatory part or `philo_bonus/` for the bonus part.
3. Run `make` to compile the respective program.
4. Execute the program with the specified arguments as mentioned in the Rules section.

### The "philo" Program
- The `philo` program simulates the dining philosophers problem using threads and mutexes.
- Philosophers represent threads, and forks are managed with mutexes.
- Each philosopher thread has a left and right fork.
- Philosophers can eat, think, and sleep, following the specified time intervals.
- The simulation stops when a philosopher dies of starvation or all philosophers have eaten the specified number of times.

### The "philo_bonus" Program
- Description: The "philo_bonus" program is the bonus part that simulates the dining philosophers problem using processes and semaphores. It complies with the same requirements as the mandatory part.

### Rules
- The arguments for the program include the number of philosophers, time intervals for dining, and an optional parameter for the number of times each philosopher must eat.
