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
#include "BreakVigenere.h"
#include "FindKeyLength.h"
#include "CircularDeque.h"
#include "CircularQueue.h"
#include "Queue2Stacks.h"
#include "DFS.h"
#include "BFS.h"

#define CATALAN_TOP_DOWN_TEST false
#define CATALAN_MEMOIZED_TEST false

#define MAX_PROFIT_TEST       false
#define MIN_NO_OF_BILLS_TEST  false

#define QUICK_SORT_TEST       false
#define SPLIT_MULTIPLY_TEST   false

#define AES_TEST              false
#define SDES_ENCRYPT_TEST     false
#define SDES_DECRYPT_TEST     false
#define SDES_MITM_TEST        false

#define BREAK_VIGENERE_TEST   false
#define FIND_KEY_LENGTH_TEST  false

#define DEPTH_FIRST_SEARCH    false
#define BREADTH_FIRST_SEARCH  false

#define CIRCULAR_DEQUE        false
#define CIRCULAR_QUEUE        false
#define QUEUE_TWO_STACKS      true

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


    // --- SDES encrypt example ---

    #if SDES_ENCRYPT_TEST
    {
        SDES_Encrypt sDES_Encrypt(true);

        sDES_Encrypt.RunDemo();
    }
    #endif

    // --- SDES encrypt example ---


    // --- SDES decrypt example ---

    #if SDES_DECRYPT_TEST
    {
        SDES_Decrypt sDES_Decrypt(true);

        sDES_Decrypt.RunDemo();
    }
    #endif

    // --- SDES decrypt example ---


    // --- SDES MITM example ---

    #if SDES_MITM_TEST
    {
        SDES_MITM sDES_MITM(true);

        sDES_MITM.RunDemo();
    }
    #endif

    // --- SDES MITM example ---


    // --- Break Vigenere example ---

    #if BREAK_VIGENERE_TEST
    {
        BreakVigenere breakVigenere;

        breakVigenere.RunDemo();
    }
    #endif

    // --- Break Vigenere example ---


    // --- Find Key Length example ---

    #if FIND_KEY_LENGTH_TEST
    {
        FindKeyLength_Vigenere findKeyLength_Vigenere;

        findKeyLength_Vigenere.RunDemo();
    }
    #endif

    // --- Find Key Length example ---

    // --- Depth First Search example ---

    #if DEPTH_FIRST_SEARCH
    {
        DFS dfs;

        dfs.RunDemo();
    }
    #endif

    // --- Depth First Search example ---

    // --- Breadth First Search example ---

    #if BREADTH_FIRST_SEARCH
    {
        BFS bfs;

        bfs.RunDemo();
    }
    #endif

    // --- Breadth First Search example ---

    // --- Circular Queue example ---

    #if CIRCULAR_QUEUE
    {
        MyCircularQueue myCircularQueue(2);

        myCircularQueue.RunDemo();
    }
    #endif

    // --- Circular Queue example ---

    // --- Circular Deque example ---

    #if CIRCULAR_DEQUE
    {
        MyCircularDeque myCircularDeque(4);

        myCircularDeque.RunDemo();
    }
    #endif

    // --- Circular Deque example ---

    // --- Queue two stacks example ---

    #if QUEUE_TWO_STACKS
    {
        Queue2Stacks<int> queue2Stacks;

        queue2Stacks.RunDemo();
    }
    #endif

    // --- Queue two stacks example ---

    std::cout << "\nDSA Program Complete..." << std::endl;

    return 0;
}