# attackshell
A shell to help with attacking simple substitution ciphers based on probability of occurrence

## Dependencies
This program uses Linux-specific headers, and will not compile in non-*nix environments.

##Usage
program [flag] {file}, where [flag] is either -e, -d, or -a and {file} is the file to be encrypted, decrypted, or attacked.

*	-e will cause the file to be encrypted using the already-defined key.
*	-d decrypts the file that was previously encrypted (will cause errors if attempt to decrypt a different file).
*	-a followed by an encrypted file will cause the program to go into “attack mode.”

In order to assign a letter value in the key, you must follow the convention c=h, where c is a lower-case character that you want to replace h with in the ciphertext, and h an upper-case letter of ciphertext. In other words, e(c) = h and d(h) = c.

When attack mode is exited, the key is reset by default. It is therefore recommended to record the key elsewhere. 
