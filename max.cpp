/*
 * Mike Verdicchio
 * Thread Synchronization
 * max.cpp
 * 
 * This program uses N/2 threads to find the largest number
 * in a pool of N numbers. It compares two numbers at a time,
 * per thread, and then passes on the larger to the next round.
 * It also uses an implementation of a barrier using POSIX
 * binary semaphores.
 */

#include <iostream>
#include <vector>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include "barrier.cpp"
using namespace std;

// Struct for all the data necessary for each thread to execute
struct game_info
{
    int number1;
    int number2;
    int result;
    int thread;
    int total_threads;
    int total_rounds;
    vector<vector<int>> *matrix;
    Barrier *barrier;
};

void *compare(void *param);
bool PowerOfTwo(int N);

int main()
{

    // Variables to store input lines, temporary numbers, and the result
    string input;
    int result;
    vector<int> temp_numbers;

    // Fill the vector with number input - one per line until an empty line
    while (getline(cin, input) && !input.empty())
    {
        temp_numbers.push_back(stoi(input));
    }

    // Check to make sure that there is input that is a power of 2 not 0 or 1
    int N = temp_numbers.size();
    if (N == 0 || N == 1 || !PowerOfTwo(N))
    {
        cout << "Input must be a power of 2 larger than 0." << endl;
        exit(1);
    }

    // Set up game information (structs to send to thread function)
    int num_threads = N / 2;
    int num_rounds = log2(N);
    game_info games[num_threads];

    // Create more vectors for each round (not the first)
    vector<vector<int>> numbers;
    int size = N;
    for (int index = 0; index < num_rounds + 1; index++)
    {
        if (index == 0)
            numbers.push_back(temp_numbers);
        else
            numbers.push_back(vector<int>(size));
        size /= 2;
    }

    // Set up threads and barrier
    pthread_t tid[num_threads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    Barrier barrier(num_threads);

    // Create theads (which are games of two numbers versus each other)
    for (int index = 0; index < num_threads; index++)
    {
        // Add necesssary variables to game struct
        games[index].total_threads = num_threads;
        games[index].total_rounds = num_rounds;
        games[index].thread = index;
        games[index].barrier = &barrier;
        games[index].matrix = &numbers;

        // Create new thread (and throw error if neceessary)
        int ret = pthread_create(&tid[index], &attr, compare, (void *)&games[index]);
        if (ret != 0)
        {
            cout << "Error creating thread." << endl;
            exit(EXIT_FAILURE);
        }
    }

    // Join all the threads at the end
    for (int index = 0; index < num_threads; index++)
    {
        pthread_join(tid[index], NULL);
    }

    // The max number is stored in the final vector at index 0
    result = numbers[num_rounds][0];
    cout << result << endl;

    return 0;
}

void *compare(void *param)
{
    // Cast parameter as game_info
    game_info *game = (game_info *)param;

    // Iterate over all the rounds, waiting between rounds
    for (int i = 0; i < game->total_rounds; i++)
    {
        // Only write to next vector if thread has permission
        if (game->thread < game->total_threads / (pow(2, i)))
        {
            game->number1 = game->matrix->at(i).at(2 * game->thread);
            game->number2 = game->matrix->at(i).at(2 * game->thread + 1);

            // Find the larger of the two numbers
            if (game->number1 > game->number2)
                game->result = game->number1;
            else
                game->result = game->number2;

            // Store the larger number in the next round's vector
            game->matrix->at(i + 1).at(game->thread) = game->result;
        }

        // Wait on all the other threads to continue
        game->barrier->wait();
    }

    // Exit thread
    pthread_exit(NULL);
}

// Function that determines if a number is a power of 2
bool PowerOfTwo(int N)
{
    while (((N % 2) == 0) && N > 1)
        N /= 2;
    return (N == 1);
}