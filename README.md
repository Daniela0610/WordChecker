Input Format: The system reads from standard input, processing a sequence of instructions and words. 
It works with words consisting of lowercase and uppercase alphabetic characters (a-z, A-Z), numeric digits (0-9), and symbols like "-" (hyphen) and "_" (underscore).

Game Structure: The system reads a set of words, each of a fixed length k, which forms the set of allowed words. 
The system then processes multiple "games", each marked by the command +nuova_partita, where:

A reference word of length k is provided.
A number n indicates the maximum number of words to compare with the reference word.
The words are compared, and specific results are returned based on the matches.
Commands: Additional commands, such as +inserisci_inizio and +inserisci_fine, allow for the insertion of new words into the allowed word set.

Output: For each word compared, the system outputs a sequence indicating the relationship between the reference word and the compared word, 
providing information about correct letters, misplaced letters, and missing letters.


The project uses a binary search tree (BST) to efficiently manage and search the set of admissible words. 
Linked lists store constraints, such as required or prohibited letter positions and letter occurrences, which are checked against each word. 
The use of these data structures ensures fast word insertion, searching, and filtering, optimizing both time and memory usage.
