void set_func(int funcID);
void set_data_dir(char *new_data_dir);
double eval_sol(double *x, bool simpleWeights);
void free_func(void);
void next_run(void);
double *get_partials();
int get_partials_num();