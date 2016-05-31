#include <stdio.h>
#include <math.h>
#include "cs50.h"

#define COIN_VALUES_IN_USD_COUNT_INT    5

int calculateMinCoinCountForChangeUSD(float changeOwedUsd) {
/**
 * -----------------/ Summary /-----------------------
 * 
 * Calculates the minimal number of coins required to 
 * change a customer.
 * 
 * -----------------/ Arguments /---------------------
 * 
 *  changeOwedUsd : float - the amount of change owed 
 *  to the customer in dollars.
 * 
 * -----------------/ Pre-condition /-----------------
 * 
 *  The changeOwedUsd argument cannot be negative or 
 *  else 0 will be returned.
 * 
 * -----------------/ Post-condition /----------------
 * 
 *  The minimal number of coins required to change a 
 *  customer is returned.
 * 
 * -----------------/ Side-effects /------------------
 * 
 *  None.
 * 
 */


    if (changeOwedUsd <= 0.0) {
        return 0;
    }

    
    int coinValues[COIN_VALUES_IN_USD_COUNT_INT] = {
        25, 10, 5, 1
    };
    
    int changeOwedCts = (int) ( round(changeOwedUsd * 100));
    
    int coinCount = 0;
    int coinValueIndex = 0;
    while ( (coinValueIndex < COIN_VALUES_IN_USD_COUNT_INT) && (changeOwedCts > 0)) {
        
        int coinValue = coinValues[coinValueIndex];
            
        if (changeOwedCts >= coinValue) {
            
            int rem = changeOwedCts % coinValue;
            if (rem == 0) {
                coinCount += changeOwedCts / coinValue;
                return coinCount;
                
            } else {
                ++coinCount;
                changeOwedCts -= coinValue;

            }
            
        } else {
            ++coinValueIndex;
        }
    }

    return coinCount; 
}

int main(int argc, char** argv) {
    
    printf("O hai! ");
    printf("How much change is owed (USD)?\n");
    
    float changeOwedUsd;
    while ( (changeOwedUsd = GetFloat()) < 0) {
        printf("How much change is owed (USD)?\n");
    }
    
    int coinCountOwed = calculateMinCoinCountForChangeUSD(changeOwedUsd);
    printf("%i\n", coinCountOwed);
    
    return 0;
}