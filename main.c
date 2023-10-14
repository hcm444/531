#include <stdio.h>
#include <stdlib.h>

#define NUM_WEEKS 4
#define NUM_SETS 3
#define POUNDS_TO_KILOGRAMS 0.453592

void calculateWeights(int week, int oneRepMax, const char *liftName, int useKilograms) {
    if (week < 1 || week > NUM_WEEKS) {
        fprintf(stderr, "Invalid week number. Please select a week from 1 to %d.\n", NUM_WEEKS);
        return;
    }

    printf("%s Training Week %d (5/3/1 Wendler):\n", liftName, week);

    int repSetGoals[NUM_WEEKS][NUM_SETS] = {
        {5, 5, 5},
        {3, 3, 3},
        {5, 3, 1},
        {5, 5, 5}
    };

    int reps[NUM_SETS];
    if (week == 1) {
        reps[0] = 5;
        reps[1] = 5;
        reps[2] = 5;
    } else if (week == 2) {
        reps[0] = 3;
        reps[1] = 3;
        reps[2] = 3;
    } else if (week == 4) {
        reps[0] = 5;
        reps[1] = 5;
        reps[2] = 5;
    } else {
        reps[0] = 5;
        reps[1] = 3;
        reps[2] = 1;
    }

    float trainingPercentages[NUM_SETS];
    if (week == 1) {
        trainingPercentages[0] = 0.65;
        trainingPercentages[1] = 0.75;
        trainingPercentages[2] = 0.85;
    } else if (week == 2) {
        trainingPercentages[0] = 0.70;
        trainingPercentages[1] = 0.80;
        trainingPercentages[2] = 0.90;
    } else if (week == 3) {
        trainingPercentages[0] = 0.75;
        trainingPercentages[1] = 0.85;
        trainingPercentages[2] = 0.95;
    } else if (week == 4) {
        trainingPercentages[0] = 0.4;
        trainingPercentages[1] = 0.5;
        trainingPercentages[2] = 0.6;
    } else {
        trainingPercentages[0] = 0.75;
        trainingPercentages[1] = 0.85;
        trainingPercentages[2] = 0.95;
    }

    for (int set = 0; set < NUM_SETS; set++) {
        float weight = oneRepMax * trainingPercentages[set];

        if (useKilograms) {
            weight *= POUNDS_TO_KILOGRAMS; // Convert to kilograms
        }

        printf("Set %d: %.1f %s x %d", set + 1, weight, useKilograms ? "kg" : "lbs", reps[set]);

        if (week != 4 && set == 2) {
            printf("+");
        }

        printf("\n");
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    int squatMax = 0;
    int benchMax = 0;
    int ohpMax = 0;
    int deadliftMax = 0;
    int weekToDisplay = 0;
    int useKilograms = 0; // Default to displaying weights in pounds

    if (argc < 2) {
        fprintf(stderr, "At least one lift (squat, bench, ohp, deadlift) must be specified.\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            char option = argv[i][1];
            if (i + 1 < argc) {
                switch (option) {
                    case 's':
                        squatMax = atoi(argv[i + 1]);
                        if (squatMax <= 0) {
                            fprintf(stderr, "Invalid squat max. Please specify a positive value.\n");
                            return 1;
                        }
                        break;
                    case 'b':
                        benchMax = atoi(argv[i + 1]);
                        if (benchMax <= 0) {
                            fprintf(stderr, "Invalid bench press max. Please specify a positive value.\n");
                            return 1;
                        }
                        break;
                    case 'o':
                        ohpMax = atoi(argv[i + 1]);
                        if (ohpMax <= 0) {
                            fprintf(stderr, "Invalid overhead press max. Please specify a positive value.\n");
                            return 1;
                        }
                        break;
                    case 'd':
                        deadliftMax = atoi(argv[i + 1]);
                        if (deadliftMax <= 0) {
                            fprintf(stderr, "Invalid deadlift max. Please specify a positive value.\n");
                            return 1;
                        }
                        break;
                    case 'w':
                        weekToDisplay = atoi(argv[i + 1]);
                        if (weekToDisplay < 1 || weekToDisplay > NUM_WEEKS) {
                            fprintf(stderr, "Invalid week number. Please select a week from 1 to %d.\n", NUM_WEEKS);
                            return 1;
                        }
                        break;
                    case 'k':
                        useKilograms = 1; // Enable kilograms display
                        break;
                    default:
                        fprintf(stderr, "Unknown option: -%c\n", option);
                        return 1;
                }
            } else if (option == 'k') {
                useKilograms = 1; // Enable kilograms display
            }
        }
    }

    if (squatMax > 0 || benchMax > 0 || ohpMax > 0 || deadliftMax > 0) {
        if (weekToDisplay == 0) {
            for (int week = 1; week <= NUM_WEEKS; week++) {
                if (squatMax > 0) calculateWeights(week, squatMax, "Squat", useKilograms);
                if (benchMax > 0) calculateWeights(week, benchMax, "Bench Press", useKilograms);
                if (ohpMax > 0) calculateWeights(week, ohpMax, "Overhead Press", useKilograms);
                if (deadliftMax > 0) calculateWeights(week, deadliftMax, "Deadlift", useKilograms);
            }
        } else {
            for (int week = 1; week <= NUM_WEEKS; week++) {
                if (week == weekToDisplay) {
                    if (squatMax > 0) calculateWeights(week, squatMax, "Squat", useKilograms);
                    if (benchMax > 0) calculateWeights(week, benchMax, "Bench Press", useKilograms);
                    if (ohpMax > 0) calculateWeights(week, ohpMax, "Overhead Press", useKilograms);
                    if (deadliftMax > 0) calculateWeights(week, deadliftMax, "Deadlift", useKilograms);
                }
            }
        }
    }

    return 0;
}
