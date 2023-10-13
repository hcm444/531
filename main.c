#include <stdio.h>

// Constants for the number of weeks and sets
#define NUM_WEEKS 4
#define NUM_SETS 3

// Function to calculate training weights for a lift based on 1RM, week, and lift name
void calculateWeights(int week, int oneRepMax, float trainingPercentages[], const char *liftName) {
    printf("%s Training Week %d (5/3/1 Wendler):\n", liftName, week);
    if (week == 1) {
        trainingPercentages[0] = 0.65;
        trainingPercentages[1] = 0.75;
        trainingPercentages[2] = 0.85;
    } else {
        trainingPercentages[0] = 0.75 + (week - 2) * 0.05;
        trainingPercentages[1] = 0.85 + (week - 2) * 0.05;
        trainingPercentages[2] = 0.95 + (week - 2) * 0.05;
    }

    for (int set = 0; set < NUM_SETS; set++) {
        int weight = oneRepMax * trainingPercentages[set];
        printf("Set %d: %d lbs\n", set + 1, weight);
    }
    printf("\n");
}

int main() {
    int squatMax = 300; // Replace with your actual squat 1RM
    int benchMax = 250; // Replace with your actual bench press 1RM
    int ohpMax = 150;   // Replace with your actual overhead press 1RM
    int deadliftMax = 400; // Replace with your actual deadlift 1RM

    for (int week = 1; week <= NUM_WEEKS; week++) {
        float trainingPercentages[NUM_SETS];
        calculateWeights(week, squatMax, trainingPercentages, "Squat");
        calculateWeights(week, benchMax, trainingPercentages, "Bench Press");
        calculateWeights(week, ohpMax, trainingPercentages, "Overhead Press");
        calculateWeights(week, deadliftMax, trainingPercentages, "Deadlift");
    }

    return 0;
}
