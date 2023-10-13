#include <stdio.h>
#include <stdlib.h>

#define NUM_WEEKS 4
#define NUM_SETS 3


void calculateWeights(int week, int oneRepMax, float trainingPercentages[], const char *liftName) {
    printf("%s Training Week %d (5/3/1 Wendler):\n", liftName, week);

    int repSetGoals[NUM_WEEKS][NUM_SETS] = {
        {3, 5, 5},
        {3, 3, 3},
        {3, 5, 1},
        {3, 5, 5}  
    };

    printf("Rep-Set Goals: %d x %d, %d x %d, %d x %d\n",
           repSetGoals[week - 1][0], repSetGoals[week - 1][1], repSetGoals[week - 1][2],
           repSetGoals[week - 1][0], repSetGoals[week - 1][1], repSetGoals[week - 1][2]);

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

int main(int argc, char *argv[]) {
    int squatMax = 300;
    int benchMax = 250;
    int ohpMax = 150;
    int deadliftMax = 400;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            char option = argv[i][1];
            switch (option) {
                case 's':
                    squatMax = atoi(argv[i + 1]);
                    break;
                case 'b':
                    benchMax = atoi(argv[i + 1]);
                    break;
                case 'o':
                    ohpMax = atoi(argv[i + 1]);
                    break;
                case 'd':
                    deadliftMax = atoi(argv[i + 1]);
                    break;
                default:
                    fprintf(stderr, "Unknown option: -%c\n", option);
                    return 1;
            }
        }
    }

    if (argc > 1) {
        for (int week = 1; week <= NUM_WEEKS; week++) {
            float trainingPercentages[NUM_SETS];
            calculateWeights(week, squatMax, trainingPercentages, "Squat");
            calculateWeights(week, benchMax, trainingPercentages, "Bench Press");
            calculateWeights(week, ohpMax, trainingPercentages, "Overhead Press");
            calculateWeights(week, deadliftMax, trainingPercentages, "Deadlift");
        }
    }

    return 0;
}
