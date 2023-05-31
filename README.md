# Alzheimer's Disease Simulation

This project provides a simple simulation of the spread of Alzheimer's disease through the brain using a 3D grid of neurons.

## Context

Alzheimer's disease is a progressive disorder that causes brain cells to waste away (degenerate) and die. Alzheimer's disease is the most common cause of dementia — a continuous decline in thinking, behavioral and social skills that disrupts a person's ability to function independently.

The precise cause of Alzheimer's disease isn't known. Plaques, abnormal clusters of protein fragments, accumulate between nerve cells. Dead and dying nerve cells contain tangles, which are made up of twisted strands of another protein. Scientists are not absolutely sure what role plaques and tangles play in Alzheimer's disease.

## Model

In this simulation, we model the brain as a 3D grid of neurons. Each neuron can be in one of two states: healthy or not healthy. A healthy neuron can become not healthy if it's adjacent to a not healthy neuron, simulating the spread of the disease through the brain. Each neuron also has a 10% chance of being resistant to the disease, meaning it can't become not healthy.

The spread of the disease is modeled as a random process with a given spread rate. In each iteration of the simulation, for each not healthy neuron, we attempt to "infect" its neighbors with a success probability equal to the spread rate.

Here is a simple diagram of the model:

Healthy neuron: O Not healthy neuron: X Resistant neuron: R

Initial state:
O O O O O
O O O O O
O O X O O
O O O O O
O O O O O

After one iteration with spread rate = 0.5:
O O O O O
O O X O O
O X X X O
O O X O O
O O O O O

## Code

The code is written in C++ and uses a 3D grid to represent the brain. Each cell in the grid is a neuron, represented by the `Neuron` struct. The `Neuron` struct has two boolean variables, `healthy` and `resistant`, which represent the neuron's state and whether it's resistant to the disease.

The `Brain` class represents the brain and contains the 3D grid of neurons. It has a method `spreadDisease()` that spreads the disease through the brain according to the model described above, and a method `countHealthy()` that counts the number of healthy neurons.

The `main` function creates a `Brain` object, runs the simulation for 100 iterations, and prints the number of healthy neurons after each iteration.

## Usage

To run the simulation, compile and run the code using a C++ compiler.
