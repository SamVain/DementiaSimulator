#include <iostream>
#include <vector>
#include <ctime>

struct Neuron
{
    bool healthy;
    bool resistant;
    Neuron() : healthy(true), resistant(rand() < 0.1 * RAND_MAX) {} // 10% of neurons are resistant
};

class Brain
{
public:
    Brain(int size, double spreadRate, std::tuple<int, int, int> diseaseOrigin)
        : spreadRate(spreadRate), diseaseOrigin(diseaseOrigin)
    {
        // Initialize 3D grid of neurons
        for (int i = 0; i < size; i++)
        {
            std::vector<std::vector<Neuron>> layer;
            for (int j = 0; j < size; j++)
            {
                std::vector<Neuron> row(size);
                layer.push_back(row);
            }
            neurons.push_back(layer);
        }
        // Start the disease at the specified origin
        neurons[std::get<0>(diseaseOrigin)][std::get<1>(diseaseOrigin)][std::get<2>(diseaseOrigin)].healthy = false;
    }

    // Spread disease to adjacent neurons
    void spreadDisease()
    {
        // Copy the current state of the brain
        auto neuronsCopy = neurons;
        for (int i = 0; i < neurons.size(); i++)
        {
            for (int j = 0; j < neurons[i].size(); j++)
            {
                for (int k = 0; k < neurons[i][j].size(); k++)
                {
                    // If the current neuron is not healthy
                    if (!neurons[i][j][k].healthy)
                    {
                        // Try to infect its neighbors
                        for (int di = -1; di <= 1; di++)
                        {
                            for (int dj = -1; dj <= 1; dj++)
                            {
                                for (int dk = -1; dk <= 1; dk++)
                                {
                                    int ni = i + di;
                                    int nj = j + dj;
                                    int nk = k + dk;
                                    // Check if the neighbor is within the brain and is healthy and not resistant
                                    if (ni >= 0 && ni < neurons.size() && nj >= 0 && nj < neurons[i].size() && nk >= 0 && nk < neurons[i][j].size() && neuronsCopy[ni][nj][nk].healthy && !neuronsCopy[ni][nj][nk].resistant)
                                    {
                                        // Try to infect the neighbor
                                        if (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) < spreadRate)
                                        {
                                            neurons[ni][nj][nk].healthy = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Count the number of healthy neurons
    int countHealthy()
    {
        int count = 0;
        for (const auto &layer : neurons)
        {
            for (const auto &row : layer)
            {
                for (const auto &neuron : row)
                {
                    if (neuron.healthy)
                    {
                        count++;
                    }
                }
            }
        }
        return count;
    }

private:
    std::vector<std::vector<std::vector<Neuron>>> neurons;
    double spreadRate;
    std::tuple<int, int, int> diseaseOrigin;
};

int main()
{
    srand(time(NULL));                // Seed for randomness
    Brain brain(10, 0.05, {5, 5, 5}); // Create a 10x10x10 brain with a 5% spread rate, disease starts at the center

    for (int i = 0; i < 100; i++)
    { // Run the simulation for 100 iterations
        brain.spreadDisease();
        std::cout << "Healthy neurons after " << i << " iterations: " << brain.countHealthy() << std::endl;
    }

    return 0;
}
