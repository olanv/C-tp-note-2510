#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N_STUDENTS 10
#define MAX_NOTE 20

typedef struct info_test info_test_t;

int get_int(char *message);

void fill_grades(int *grades, int choice);
void fill_grades_from_stdin(int *grades);
void fill_grades_rng(int *grades);

float get_average(int * grades);
int get_occurences(int *grades, int grade_target);
int get_max_grade(int *grades);
int get_min_grade(int *grades);
int get_nb_grade(int *grades); 

info_test_t get_info_test(int *grades, char *class_name); 

void display_grades(int *grades);
void display_full_info_grades(int *grades, info_test_t info_test); 

struct info_test {
    int nb_grade;
    char class_name[20];
    float average;
    int max_grade;
    int min_grade;
};

int get_int(char *message) {
    int nb = 0;
    printf("%s", message);
    scanf("%d", &nb);
    return nb;
}

void fill_grades(int *grades, int choice) {
    if (choice == 1) {
        fill_grades_from_stdin(grades);
    } else {
        srand(time(NULL));
        fill_grades_rng(grades);
    }
}

char* get_sufix(int i) {
    switch(i) {
        case 0:
        return "st";
        case 1:
        return "nd";
        case 2:
        return "rd";
        default:
        return "th";
    }
}

void fill_grades_from_stdin(int *grades) {
    int grade = -2;
    for (int i = 0 ; i < N_STUDENTS ; i++) {
blind_filling:
        printf("%d%s -> ", i+1, get_sufix(i));
        scanf("%d", &grade);
        if (grade < -1 || grade > MAX_NOTE) {
            printf("Enter a grade between -1 (missing) and %d\n", MAX_NOTE);
            goto blind_filling;
        }
    }
}

void fill_grades_rng(int *grades) {
    for (int i = 0 ; i < N_STUDENTS ; i++) {
        grades[i] = rand() % (MAX_NOTE + 1);
    }
}

float get_average(int * grades) {
    float sum = 0.0;
    for (int i = 0 ; i < N_STUDENTS ; i++) {
        sum += (grades[i] == -1 ? 0 : grades[i]);
    }
    return (sum/N_STUDENTS);
}

int get_occurences(int *grades, int grade_target) {
    int occurences = 0;
    for (int i = 0 ; i < N_STUDENTS ; i++) {
        if (grades[i] == grade_target) {
            occurences++;
        }
    }
    return occurences;
}

int get_max_grade(int *grades) {
    int max_grade = 0;
    for (int i = 0 ; i < N_STUDENTS ; i++) {
        if (grades[i] > max_grade) {
            max_grade = grades[i];
        }
    }
    return max_grade;
}

int get_min_grade(int *grades) {
    int min_grade = MAX_NOTE;
    for (int i = 0 ; i < N_STUDENTS ; i++) {
        if (grades[i] < min_grade && grades[i] != -1) {
            min_grade = grades[i];
        }
    }
    return min_grade;
}

int get_nb_grade(int *grades) {
    int tot_grade = 0;
    for (int i = 0 ; i < N_STUDENTS ; i++) {
        tot_grade += (grades[i] == -1 ? 0 : 1);
    }
    return tot_grade;
}

info_test_t get_info_test(int *grades, char *class_name) {
    info_test_t info_test; 
    info_test.average = get_average(grades);
    strcpy(info_test.class_name, class_name);
    info_test.nb_grade = get_nb_grade(grades);
    info_test.max_grade = get_max_grade(grades);
    info_test.min_grade = get_min_grade(grades);

    return info_test;
} 

void display_grades(int *grades) {
    for (int i = 0 ; i < N_STUDENTS ; i++) {
        printf("%d%s -> %d\n", i+1, get_sufix(i), grades[i]);
    }
}

void display_full_info_grades(int *grades, info_test_t info_test) {
    int grades_under_avg = 0, grades_above_avg = 0;
    for (int i = 0 ; i < info_test.average; i++) {
        grades_under_avg += get_occurences(grades, i); 
    }
    grades_above_avg = info_test.nb_grade - grades_under_avg;

    printf("The %s test:\n"
           "\t%d grades in total\n"
           "\tmax grade: %d occured %d times\n"
           "\tmin grade: %d occured %d times\n"
           "\taverage: %f\n"
           "\tnumber of grade above average: %d\n"
           "\tnumber of grade under average: %d\n"
           "\tmissing grades: %d\n"
           , info_test.class_name, get_nb_grade(grades)
           , get_max_grade(grades), get_occurences(grades, get_max_grade(grades))
           , get_min_grade(grades), get_occurences(grades, get_min_grade(grades))
           , get_average(grades), grades_above_avg, grades_under_avg
           , get_occurences(grades, -1)
           );
}

int main() {
    int grades[N_STUDENTS];
    char class_name[20];

    printf("What is the class name ?\nclass name: ");
    scanf("%s", class_name);

    fill_grades(grades, get_int("To fill the grades by yourself: 1\n"
                                "To fill randomly the grades: something else\n"
                                "choice: "));

    info_test_t info_test = get_info_test(grades, class_name);

    display_full_info_grades(grades, info_test);
}