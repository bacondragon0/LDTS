LDTS - Laser Data Transmission System

Current encoder algorithm is representing chars using a binary number of 6 bits,
letters go from 1 to 26, 27 to 53 for lowercase, with special symbols and numbers following after 
and 53 to 63 for digits. 0 is reserved for end of line, 64 for space.
dots, commas and ect are not considered rn and will be implemented with 2 character encoding.
