**LDTS - Laser Data Transmission System**

The goal of the project is make a basic DIY version of the Orion Artemis II Optical Communications System,
capable of sending and receiving text and images using a single laser beam.
*Thus, all information needs to be converted to 1s and 0s*

***Text Encoding Algorithm***

Text is encoded in two steps, the first step is turning all special characters in the text to their two character substitutes.
For example, the string "Hello World!" is turned into "Hello$0World$4", this step is skipped if no special chars are found.

The second step is turning the alphabetical string into 1s and 0s.

The chosen representation is 1 char = 6 bits, which means a total of 64 unique symbols can be stored.

*Conversion Table :*
End of Line  | 0         | 000000
a <-> z      | 1 <-> 26  | 000001 <-> 011010
A <-> Z      | 27 <-> 52 | 011011 <-> 110100
0 <-> 9      | 53 <-> 62 | 110101 <-> 111110
Sp. char ($) | 63        | 111111

Special char ($) rule :
The next three bits after the special character are special and are read differently, as they define the replaced character.
*Special Character Table:*
$0 |  (Space)
$1 | .
$2 | ,
$3 | ?
$4 | !

A total of 8 characters can be defined this way.

Finally, the string "Hello$0World$4" gets turned into "100010000101001100001100001111111111000110001001111010010001100000100111111100000000"
