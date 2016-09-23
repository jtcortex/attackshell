# attackshell
A shell to help with attacking simple substitution ciphers based on probability of occurrence

## Dependencies
This program uses Linux-specific headers, and will not compile in non-*nix environments.

##Usage
program [flag] {file}, where [flag] is either -e, -d, or -a and {file} is the file to be encrypted, decrypted, or attacked.

*	-e will cause the file to be encrypted using the already-defined key.
*	-d decrypts the file that was previously encrypted (will cause errors if attempt to decrypt a different file).
*	-a followed by an encrypted file will cause the program to go into “attack mode.”
