#include <iostream>
#include <vector>
#include <cassert>

#include "CatalanTopDown.h"
#include "CatalanMemoized.h"
#include "MaxProfit.h"
#include "MinNoOfBills.h"
#include "BasicNumbersSort.h"
#include "Splitmultiply.h"
#include "AESEncryptRound.h"
#include "SDESMitm.h"

#define CATALAN_TOP_DOWN_TEST false
#define CATALAN_MEMOIZED_TEST false
#define MAX_PROFIT_TEST       false
#define MIN_NO_OF_BILLS_TEST  false
#define QUICK_SORT_TEST       false
#define SPLIT_MULTIPLY_TEST   false
#define AES_TEST              false
#define DES_MITM_TEST         true

int main()
{
    std::cout << "\nDSA Program Started Running..." << std::endl;

    // --- Catalan Top Down example ---

    #if CATALAN_TOP_DOWN_TEST
    {
        CatalanTopDown catalanTopDown;

        catalanTopDown.RunDemo();
    }
    #endif

    // --- Catalan Top Down example ---


    // --- Catalan Memoized example ---

    #if CATALAN_MEMOIZED_TEST
    {
        CatalanMemoized catalanMemoized;

	    catalanMemoized.RunDemo();
    }
    #endif

    // --- Catalan Memoized example ---


    // --- Max Profit example ---

    #if MAX_PROFIT_TEST
    {
        MaxProfit maxProfit;

        maxProfit.RunDemo();
    }
    #endif

    // --- Max Profit example ---


    // --- Min No Of Bills example ---

    #if MIN_NO_OF_BILLS_TEST
    {
        MinNoOfBills minNoOfBills;

        minNoOfBills.RunDemo();
    }
    #endif

    // --- Min No Of Bills example ---


    // --- Quick Sort example ---

    #if QUICK_SORT_TEST
    {
        BasicNumbersSort basicNumbersSort;

	    basicNumbersSort.RunDemo();
    }
    #endif

    // --- Quick Sort example ---


    // --- Split Multiply example ---

    #if SPLIT_MULTIPLY_TEST
    {
        Splitmultiply splitMultiply;

        splitMultiply.RunDemo();
    }
    #endif
    
    // --- Split Multiply example ---


    // --- AES example ---

    #if AES_TEST
    {
        AESEncryptRound aesEncryptRound;
   
        aesEncryptRound.RunDemo();
    }
    #endif

    // --- AES example ---


    // --- DES MITM example ---

    #if DES_MITM_TEST
    {
        SDES_MITM sDES_MITM;

        sDES_MITM.RunDemo();
    }
    #endif

    // --- DES MITM example ---

    std::cout << "\nDSA Program Complete..." << std::endl;

    return 0;
}