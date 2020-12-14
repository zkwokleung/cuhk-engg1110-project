/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 * https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name : SZE-TO Kwok Leung
 * Student ID : 1155149068
 * Class/Section : D
 * Date : 25-Nov-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// TODO: Merge the .h files and Remove these lines
#include "Menu.h"
#include "Input.h"

// TODO: Refactor main logic
/* The main function */
int main()
{
    // Initialize random number generator
    srand(time(NULL));

    // Let the internal logic to terminate the program
    while (1)
    {
        startMainMenu();
    }

    return 0;
}