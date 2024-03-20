
This project will compute the most likely deciphering of a Ceasar cipher by using a brute-force metod. The project will recieve from distribution.txt the rough percentage of a character's frequency in the English language and it will place it inside the "freq_eng" array, using the "SetUp" function. 

The program will place inside of the "text" variable either an example string or a string which is inputed by the user. If the example string is selected that string will be printed prior to decryption to show the user the original text inside of the main.

The program will them compute the number of appearances of each character inside the string and store said frequncy in the "freq" array using the "freqWord" function. Then the program will normalize the histograph, by turning every single value into a percentage based representation of how frequently it appearss in the text using the "normHist" function and then finally, it will compute the Chi Squared distance between the histograph of the word and every single possible permutation of the Ceasar Cipher, the lowest distance being the most likely outcome.

This process is done using the "chisSquaredSol" function, which will go through all of the permutations using a for from 0 to 25, which represent the 26 letters of the alphabet, with the i value incrementing the cipher further and further until all possible combinations were computed. The distance is calculated in the function "chiSquared", using the following formula:
![Captură ecran (353)](https://github.com/EmilianPal/Optional-Problem-1/assets/163346280/a8c86b3f-a28f-453c-aa2a-3323ce532445)

Once we compute the lowest possible distance and return the most likely key, the "decrypt" function will add the value of the solution to each character, looping them back around to the letter 'a' if they still need to move after already having reached 'z'. The program will then print the decrypted text and await further input.

The size of the input string can be modified from the definition of Size, albeit, the program WILL have errors when trying to decipher the example text, albeit, they won't result in a crash.
