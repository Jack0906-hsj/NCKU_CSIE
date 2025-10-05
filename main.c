#include <stdio.h>
#include <stdbool.h>

void clearBuffer()
{
    int ch;
    while ( ( ch = getchar() ) != '\n' && ch != EOF );
}

int max( int a, int b )
{
    if ( a >= b )
        return a;
    return b;
}

int isOdd( int n )
{
    if ( n < 0 )
        n = -n;
    if ( n % 2 == 1 )
        return true;
    return false;
}

bool isPrime( int n )
{
    if ( n <= 1 )
        return false;
    if ( n == 2 )
        return true;
    for ( int i = 2; i * i <= n; i++ )
        if ( n % i == 0 )
            return false;
    return true;
}

int main()
{
    do
    {
        // Print home page
        printf("=================================\n");
        printf("Welcome IVE to NCKU CSIE!\n");
        printf("=================================\n");
        printf("1: Photocard Lucky Draw\n");
        printf("2: Album Sales\n");
        printf("3: Prize Claim System\n");
        printf("4: Calculator\n");
        printf("5: Exit\n");
        printf("please choose your operation: ");

        // Declare and initialize option and extra
        // Variable extra for checking '\n'
        int option = -1;
        char extra = '0';

        // Check scanf return value
        if ( scanf("%d%c", &option, &extra) != 2 )
        {
            clearBuffer();
            printf("[Error]: Option is invalid.\n");
            continue;
        }
        
        if ( extra != '\n' )
        {
            clearBuffer();
            printf("[Error]: Option is invalid.\n");
            continue;
        }

        // Format is correct
        // Do option 1
        if ( option == 1 )
        {   
            printf("please input N: ");
            int N;
            scanf("%d", &N);

            char idol[ 6 ][ 16 ] = { "Yujin", "Wonyoung", "Liz", "Gaeul", "Rei", "Leeseo" };
            printf( "%s\n", idol[ ( N + 4096 ) % 6 ] );
            continue;
        }
        // Do option 2
        else if ( option == 2 )
        {
            printf("please input album quantities in the format: \"number,number,number\": ");
            int albumAmount[ 3 ];
            char extra;

            // Check scanf retur value
            if ( scanf( "\"%d,%d,%d\"%c", &albumAmount[ 0 ], &albumAmount[ 1 ], &albumAmount[ 2 ], &extra ) != 4 )
            {
                clearBuffer();
                printf("[Error]: Input is invalid.\n");
                continue;
            } 
            
            if ( extra != '\n' )
            {
                clearBuffer();
                printf("[Error]: Input is invalid.\n");
                continue;
            }
            else
            {
                char albumName[ 3 ][ 24 ] = { "IVE EMPATHY", "IVE SECRET", "Be Alright" };
                // All the amount is under limit
                // Print the price
                if ( albumAmount[ 0 ] <= 5 && albumAmount[ 1 ] <= 5 && albumAmount[ 2 ] <= 5 )
                {
                    int price = albumAmount[ 0 ] * 600 + albumAmount[ 1 ] * 800 + albumAmount[ 2 ] * 750;
                    printf("total price: %d\n", price);
                    continue;
                }
                else
                {
                    printf("[Error]: You cannot purchase more than 5 albums.(");
                    bool firstOutput = true;
                    for ( int i = 0; i < 3; i++ )
                    {
                        if ( albumAmount[ i ] > 5 )
                        {
                            if ( firstOutput )
                            {
                                printf("%s", albumName[ i ]);
                                firstOutput = false;
                            }
                            else
                                printf(",%s", albumName[ i ]);
                        }
                    }
                    printf(")\n");
                    continue;
                }
            }
        }
        // Do option 3
        else if ( option == 3 )
        {
            int winningNumber[ 5 ], diveNumber[ 5 ];
            int oddOfWinningNumber = 0, oddOfDiveNumber = 0;
            int sumOfWinningNumber = 0, sumOfDiveNumber = 0;
            int primeOfDiveNumber = 0;
            bool accumulateMode = true;
            
            printf("Please input the 5 winning numbers: ");
            for ( int i = 0; i < 5; i++ )
            {
                scanf("%d", &winningNumber[ i ]);
                // 1. Whether is an odd number
                if ( isOdd( winningNumber[ i ] ) )
                    oddOfWinningNumber++;
                // 2. Sum all the numbers
                sumOfWinningNumber += winningNumber[ i ];
            }

            printf("Please input your 5 numbers (DIVE's numbers): ");
            for ( int i = 0; i < 5; i++ )
            {
                scanf("%d", &diveNumber[ i ]);
                // If negative number exists, convert to choose-the-best mode
                if ( diveNumber[ i ] < 0 )
                    accumulateMode = false;
                // 1. Whether is an odd number
                if ( isOdd( diveNumber[ i ] ) )
                    oddOfDiveNumber++;
                // 2. Sum all the numbers
                sumOfDiveNumber += diveNumber[ i ];
                // 3. Whether is a prime number
                if ( isPrime( diveNumber[ i ] ) )
                    primeOfDiveNumber++;
            }

            // Calculte the bonus money
            int bonusMoney = 0;

            // 1. Odd number amount
            if ( oddOfWinningNumber == oddOfDiveNumber )
            {
                if ( accumulateMode )
                    bonusMoney += 300;
                else
                    bonusMoney = max( bonusMoney, 300 );
            }
            // 2. Comparison
            if ( sumOfWinningNumber > sumOfDiveNumber )
            {
                if ( accumulateMode )
                    bonusMoney += 150;
                else 
                    bonusMoney = max( bonusMoney, 150 );
            }
            // 3. Prime number >= 2
            if ( primeOfDiveNumber >= 2 )
            {
                if ( accumulateMode )
                    bonusMoney += 500;
                else
                    bonusMoney = max( bonusMoney, 500 );
            }

            printf("total win: %d\n", bonusMoney);
            continue;
        }
        // Do option 4
        else if ( option == 4 )
        {
            long long a, b;
            printf("please input (a): ");
            scanf("%lld", &a);
            printf("please input (b): ");
            scanf("%lld", &b);
            
            // Analyze each possible case
            // Special case -> special output
            if ( a == ( -9223372036854775807LL - 1 ) && b == ( -9223372036854775807LL - 1 ) )
            {
                printf("result: -18446744073709551616\n");
            }
            // One positive and one negative -> long long is enough
            else if ( ( a >= 0 && b <= 0 ) || ( a < 0 && b > 0 ) )
            {
                long long result = a + b;
                printf("result: %lld\n", result);
            }
            // Both positive -> use unsigned long long
            else if ( a > 0 && b > 0 )
            {
                unsigned long long result = a + b;
                printf("result: %llu\n", result);
            }
            // Both negative -> convert to positive and add
            // Then output -result
            else if ( a < 0 && b < 0 )
            {
                unsigned long long result = -a + -b;
                printf("result: -%llu\n", result);
            }
            continue;
        }
        // Do option 5
        else if ( option == 5 )
        {
            break;
        }
        // option < 1 or option is > 5
        else
        {
            printf("[Error]: Option is invalid.\n");
            continue;
        }
    } while ( true );
    
    return 0;
}