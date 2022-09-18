#include <stdio.h>
#include <math.h>
#include "disnrutil.h"

typedef struct structure_for_the_shot_method {
    /* x''(t) = g(t, x(t), x'(t))
     * alfa_1 x(a) + alfa_2 x'(a) = A
     * beta_1 x(b) + beta_2 x'(b) = B
     * the system above, we can write as below
     * x''(t) = g(t, x(t), x'(t))
     * alfa_1 x(a) + alfa_2 x'(a) = A
     * gamma_1 x(a) + gamma_2 x'(a) = S
     * where S is a shot parameter
     * and on the end we gain a system as below
     * for y = x'
     * y'(t) = g(t, x(t), y(t))
     * x(a) = alfa_2 S - A gamma_2
     * y(a) = A gamma_1 - alfa_1 S
     * then we have to estimate root of equations below
     * F(S) = beta_1 x(b) + beta_2 y(b) - B
     * ======================================================
     * in algorithm we will use
     * x_new = x_old + (y_new - y_old) h
     * y_new = y_old + h g(t_i, x_old, y_old)
     */
    double a,b;
    double alfa1, alfa2, A;
    double beta1, beta2, B;
    double (*equation_g_function)(double, double, double);

    double gamma1, gamma2;
    int M;
    double h;

    double time_old, time_new;
    double x_old, x_new;
    double y_old, y_new;

    double* time;
    double* values;

    double shot_parameter;
} MS;

double g_function(double t, double x, double x_p);
void create_structure(MS *p);
void solve_equation_with_euler_method(MS *p, _Bool if_final);
double F_function(double shot, MS *p);
void search_range_for_bisection_method(MS *p, double *start, double *end, double max_range);
void F_root_searching(MS *p);
void save_results_to_file(MS *p);

int main() {
    MS q;
    printf("Creating of structure \n");
    create_structure(&q);
    F_root_searching(&q);
    solve_equation_with_euler_method(&q, 1);
    printf("saving results to file");
    save_results_to_file(&q);
    return 0;
}

double g_function(double t, double x, double x_p){
    return t + x + sin(x_p);
}

void create_structure(MS *p){
    p->a = 0.0;
    p->b = 1.0;

    p->alfa1 = 1.0;
    p->alfa2 = 0.0;
    p->A = 0.0;

    p->beta1 = 1.0;
    p->beta2 = -1.0;
    p->B = 2.0;

    p->M = 50;
    p->h = (p->b - p->a) / (p->M-1.0);

    p->gamma1 = 3.0;
    p->gamma2 = -1.0;

    p->equation_g_function = g_function;

    p->time = dvector(1, p->M);
    p->values = dvector(1, p->M);

    p->shot_parameter = 1.0;
}

void solve_equation_with_euler_method(MS *p, _Bool if_final){
    p->x_old = p->alfa2 * p->shot_parameter - p->A * p->gamma2;
    p->y_old = p->A * p->gamma1 - p->alfa1 * p->shot_parameter;
    p->time_old = p->a;

    if (if_final == 1) {
        p->time[1] = p->time_old;
        p->values[1] = p->x_old;
    }

    for(int i=1; i<p->M; i++){
        p->time_new = p->time_old + p->h;
        p->x_new = p->x_old + p->h * p->y_old;
        p->y_new = p->y_old + p->h * (*p->equation_g_function)(p->time_old,
                                                               p->x_old,
                                                               p->y_old);

        if (if_final == 1) {
            p->time[i + 1] = p->time_new;
            p->values[i + 1] = p->x_new;
        }

        if(i != p->M-1){
            p->time_old = p->time_new;
            p->x_old = p->x_new;
            p->y_old = p->y_new;
        }
    }
}

double F_function(double shot, MS *p){
    p->shot_parameter = shot;
    solve_equation_with_euler_method(p, 0);
    return p->beta1 * p->x_new + p->beta2 * p->y_new - p->B;
}

void search_range_for_bisection_method(MS *p, double *start, double *end, double max_range)
{
    // function estimate a range where is a root of F function
    double length_of_step = 0.1;
    double left, right, test_value;
    double value_in_zero = F_function(0.0, p);
    left = right = 0.0;
    while (right <= max_range)
    {
        left -= length_of_step;
        right += length_of_step;
        // left search
        test_value = F_function(left, p);
        if(value_in_zero * test_value <= 0.0)
        {
            *start = left;
            *end = left + length_of_step;
            break;
        }
        // right search
        test_value = F_function(right, p);
        if(value_in_zero * test_value <= 0.0)
        {
            *end = right;
            *start = right - length_of_step;
            break;
        }
    }
}

void F_root_searching(MS *p){
    double start, end;
    search_range_for_bisection_method(p, &start, &end, 10);
    double minimal_error = fabs(F_function(start, p) - 0);
    double arg_for_minimal_error = start;
    for (int i=1; i <= 10; i++) {
        if (minimal_error > fabs(F_function(start + i * 0.01, p) - 0)) {
            minimal_error = fabs(F_function(start + i * 0.01, p) - 0);
            arg_for_minimal_error = start + i * 0.01;
        }
    }
    p->shot_parameter = arg_for_minimal_error;
}

void save_results_to_file(MS *p){
    FILE *f = fopen("results_time.txt", "at");
    for(int i = 1; i < p->M + 1; i++){
        fprintf(f, "%lf, ", p->time[i]);
    }
    fclose(f);
    FILE *g = fopen("results_function.txt", "at");
    for(int i = 1; i < p->M + 1; i++){
        fprintf(g, "%lf, ", p->values[i]);
    }
    fclose(f);
}
