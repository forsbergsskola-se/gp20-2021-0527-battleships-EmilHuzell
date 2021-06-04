// RandomNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    
    int integers[20] = {0};
    for (int i = 0; i < 100000; i++) {
        integers[rand() % 20]++;
    }

    float maxOffset;
    int maxOffsetInt;
    float minOffset;
    int minOffsetInt;
    float combinedOffset = 0;
    float avarageOffset;
    for (int i = 0; i < 20; i++) {
         //integers[i] * 100 / 100000 more readable than integers[i] / 1000
         float Percentage = (float)integers[i] * 100 / 100000;
         float offset = abs(Percentage - 5);
         combinedOffset += offset;
          
         if (i == 0) {
             maxOffset = offset;
             maxOffsetInt = i;

             minOffset = offset;
             minOffsetInt = i;
         }
         if (offset > maxOffset) {
             maxOffset = offset;
             maxOffsetInt = i;
         }
         if (offset < minOffset) {
             minOffset = offset;
             minOffsetInt = i;
         }

         //Personally dont consider the i+1 cheating, check with marc, string interpolation needed,
         std::cout << "Number " << i+1 << ": " << integers[i] << '(' << Percentage << ')'<< '\n';
    }
 
    std::cout << '\n';
    std::cout << "MaxOffset: Number " << maxOffsetInt << " " << maxOffset << '\n';
    std::cout << "MinOffset: Number " << minOffsetInt << " " << minOffset << '\n';

    avarageOffset = combinedOffset / 20;
    std::cout << "AvarageOffset: " << avarageOffset << '\n';
}


