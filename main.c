#include <stdio.h>
#include <stdlib.h>

#define NUM_WEEKS 4
#define NUM_SETS 3

void calculateWeights(int week, int oneRepMax, float trainingPercentages[], const char *liftName) {
    printf("%s Training Week %d (5/3/1 Wendler):\n", liftName, week);

    int repSetGoals[NUM_WEEKS][NUM_SETS] = {
        {5, 5, 5},
        {3, 3, 3},
        {5, 3, 1},
        {5, 5, 5}
    };

    printf("Rep-Set Goals: %d x %d, %d x %d, %d x %d\n",
           repSetGoals[week - 1][0], repSetGoals[week - 1][1], repSetGoals[week - 1][2],
           repSetGoals[week - 1][0], repSetGoals[week - 1][1], repSetGoals[week - 1][2]);

    if (week == 1) {
        trainingPercentages[0] = 0.65;
        trainingPercentages[1] = 0.75;
        trainingPercentages[2] = 0.85;
    } else if (week == 4) {
        trainingPercentages[0] = 0.4;
        trainingPercentages[1] = 0.5;
        trainingPercentages[2] = 0.6;
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
    int squatMax = 0;
    int benchMax = 0;
    int ohpMax = 0;
    int deadliftMax = 0;
    int weekToDisplay = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            char option = argv[i][1];
            if (i + 1 < argc) {
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
                    case 'w':
                        weekToDisplay = atoi(argv[i + 1]);
                        if (weekToDisplay < 1 || weekToDisplay > NUM_WEEKS) {
                            fprintf(stderr, "Invalid week number. Please select a week from 1 to %d.\n", NUM_WEEKS);
                            return 1;
                        }
                        break;
                    default:
                        fprintf(stderr, "Unknown option: -%c\n", option);
                        return 1;
                }
            }
        }
    }

    // Calculate routines only if at least one lift is specified.
    if (squatMax > 0 || benchMax > 0 || ohpMax > 0 || deadliftMax > 0) {
        if (argc > 1 && weekToDisplay == 0) {
            for (int week = 1; week <= NUM_WEEKS; week++) {
                float trainingPercentages[NUM_SETS];
                if (squatMax > 0) calculateWeights(week, squatMax, trainingPercentages, "Squat");
                if (benchMax > 0) calculateWeights(week, benchMax, trainingPercentages, "Bench Press");
                if (ohpMax > 0) calculateWeights(week, ohpMax, trainingPercentages, "Overhead Press");
                if (deadliftMax > 0) calculateWeights(week, deadliftMax, trainingPercentages, "Deadlift");
            }
        } else if (weekToDisplay > 0) {
            float trainingPercentages[NUM_SETS];
            if (squatMax > 0) calculateWeights(weekToDisplay, squatMax, trainingPercentages, "Squat");
            if (benchMax > 0) calculateWeights(weekToDisplay, benchMax, trainingPercentages, "Bench Press");
            if (ohpMax > 0) calculateWeights(weekToDisplay, ohpMax, trainingPercentages, "Overhead Press");
            if (deadliftMax > 0) calculateWeights(weekToDisplay, deadliftMax, trainingPercentages, "Deadlift");
        }
    } else {
        fprintf(stderr, "At least one lift (squat, bench, ohp, deadlift) must be specified.\n");
        return 1;
    }

    return 0;
}
