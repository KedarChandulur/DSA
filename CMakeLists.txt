cmake_minimum_required(VERSION 4.0.1)
project(DSA)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(dsa_exec 
    ${CMAKE_SOURCE_DIR}/Source/main.cpp 
    ${CMAKE_SOURCE_DIR}/Source/Algorithms/Catalan_Algorithm/CatalanTopDown.cpp
    ${CMAKE_SOURCE_DIR}/Source/Algorithms/Catalan_Algorithm/CatalanMemoized.cpp
    ${CMAKE_SOURCE_DIR}/Source/Algorithms/Greedy_Algorithm/MaxProfit.cpp
    ${CMAKE_SOURCE_DIR}/Source/Algorithms/Greedy_Algorithm/MinNoOfBills.cpp
    ${CMAKE_SOURCE_DIR}/Source/Algorithms/Quick_Sort/BasicNumbersSort.cpp
    ${CMAKE_SOURCE_DIR}/Source/Algorithms/Split_Multiplication/Splitmultiply.cpp
    ${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/AES/AESEncryptRound.cpp
    "${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/DES/Meet in the middle attack(MITM)/SDESMitm.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/DES/Simple DES - Decryption/SDESdecrypt.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/DES/Simple DES - Encryption/SDESencrypt.cpp"
    ${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/Vigenere/BreakVigenere/BreakVigenere.cpp
    ${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/Vigenere/FindKeyLength/FindKeyLength.cpp
)

target_include_directories(dsa_exec 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/Source/Algorithms/Catalan_Algorithm
    ${CMAKE_SOURCE_DIR}/Source/Algorithms/Greedy_Algorithm
    ${CMAKE_SOURCE_DIR}/Source/Algorithms/Quick_Sort
    ${CMAKE_SOURCE_DIR}/Source/Algorithms/Split_Multiplication
    ${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/AES
    ${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/DES
    "${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/DES/Meet in the middle attack(MITM)"
    "${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/DES/Simple DES - Decryption"
    "${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/DES/Simple DES - Encryption"
    ${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/Vigenere/BreakVigenere
    ${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/Vigenere/FindKeyLength
    ${CMAKE_SOURCE_DIR}/Source/Cryptology/BasicCiphers/Vigenere/
    ${CMAKE_SOURCE_DIR}/Source/Queue/TwoStacks/
)