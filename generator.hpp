#ifndef GENERATOR_H
#define GENERATOR_H

/**
 * Runs generator and returns 0 if operation is successful, should be mapped to ui item
 * 
 * @return int 
 */
int ui_run_generator();

int generator(int number_samples, int sample_skip, int file_number);

#endif