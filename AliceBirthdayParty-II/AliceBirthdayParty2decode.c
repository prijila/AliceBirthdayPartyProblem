/*
 * AliceBirthdayParty2.c
 *
 * This program aims to solve the decoding Part of the "Alice Birthday Party - II" challenge.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

/**
 *	This function takes in an character or ASCII value of the encoded characters and gives back the index at which it is stored
 *	in the table.
 */
int getIndexofBase64(int c){
 switch(c){

 case 65 : return 0 ;
 case 66 : return 1 ;
 case 67 : return 2 ;
 case 68 : return 3 ;
 case 69 : return 4 ;
 case 70 : return 5 ;
 case 71 : return 6 ;
 case 72 : return 7 ;
 case 73 : return 8 ;
 case 74 : return 9 ;
 case 75 : return 10 ;
 case 76 : return 11 ;
 case 77 : return 12 ;
 case 78 : return 13 ;
 case 79 : return 14 ;
 case 80 : return 15 ;
 case 81 : return 16 ;
 case 82 : return 17 ;
 case 83 : return 18 ;
 case 84 : return 19 ;
 case 85 : return 20 ;
 case 86 : return 21 ;
 case 87 : return 22 ;
 case 88 : return 23 ;
 case 89 : return 24 ;
 case 90 : return 25 ;
 case 97 : return 26 ;
 case 98 : return 27 ;
 case 99 : return 28 ;
 case 100 : return 29 ;
 case 101 : return 30 ;
 case 102 : return 31 ;
 case 103 : return 32 ;
 case 104 : return 33 ;
 case 105 : return 34 ;
 case 106 : return 35 ;
 case 107 : return 36 ;
 case 108 : return 37 ;
 case 109 : return 38 ;
 case 110 : return 39 ;
 case 111 : return 40 ;
 case 112 : return 41 ;
 case 113 : return 42 ;
 case 114 : return 43 ;
 case 115 : return 44 ;
 case 116 : return 45 ;
 case 117 : return 46 ;
 case 118 : return 47 ;
 case 119 : return 48 ;
 case 120 : return 49 ;
 case 121 : return 50 ;
 case 122 : return 51 ;
 case 48 : return 52 ;
 case 49 : return 53 ;
 case 50 : return 54 ;
 case 51 : return 55 ;
 case 52 : return 56 ;
 case 53 : return 57 ;
 case 54 : return 58 ;
 case 55 : return 59 ;
 case 56 : return 60 ;
 case 57 : return 61 ;
 case 43 : return 62 ;
 case 47 : return 63 ;
 default : return -1;
 }


}

/**
 * Converts the decimal number into binary string.
 */
char *decimal_to_binary(int n)
{
   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(32+1);

   if ( pointer == NULL )
      exit(EXIT_FAILURE);

   for ( c = 5 ; c >= 0 ; c-- )
   {
      d = n >> c;

      if ( d & 1 )
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';

      count++;
   }
   *(pointer+count) = '\0';
   //printf("Binary rep: %s\n ",pointer);
   return  pointer;
}

/**
 * Converts the binary string into ASCII text.
 */
char* binary_to_Ascii(char* binaryString){
	char binArr[8];
	int len = strlen(binaryString);
	char* asciiText = (char*) malloc(sizeof(char) *len);

	for (int i = 0; i < len; i = i + 8) {
		binArr[0] = binaryString[i + 0];
		binArr[1] = binaryString[i + 1];
		binArr[2] = binaryString[i + 2];
		binArr[3] = binaryString[i + 3];
		binArr[4] = binaryString[i + 4];
		binArr[5] = binaryString[i + 5];
		binArr[6] = binaryString[i + 6];
		binArr[7] = binaryString[i + 7];
		char* stop;
		int i = strtol(binArr, &stop, 2);
		//printf("\nDecimal: %d = ASCII : %c", i, i);
		char buf[10] ;
		sprintf(buf, "%c", i);
		strcat(asciiText, buf);
	}
	//printf("\nMessage %s ", asciiText);
	return asciiText;
}

/**
 * Converts the hexadecimal string into base64 encoded string.
 */
char* hex_to_base64(char *hexString){
	int len = strlen(hexString);
	char* encodedString = (char*) malloc(sizeof(char) *len);
	char hexArr[2];

	for (int i = 0; i < len; i = i + 2) {
		hexArr[0] = hexString[i + 0];
		hexArr[1] = hexString[i + 1];
		char* stop;
		int i = strtol(hexArr, &stop, 16);
		char buf[10] ;
		sprintf(buf, "%c", i);
		strcat(encodedString, buf);
	}
	printf("\nBase64 Encoded string : %s ", encodedString);
	return encodedString;
}
/**
 * Decodes the base64 encoded string into ASCII value.
 * The hexstring represents the hexadecimal representation of the Message.
 */
char* base64Decode(char* hexString) {
	char* base64String = hex_to_base64(hexString);
	int len = strlen(base64String);

	char* binaryString = (char*) malloc(sizeof(char) * len);

	for (int i = 0; i < len; i++) {
		//printf("%c %d \n", base64String[i], base64String[i]);
		int index = getIndexofBase64((int) base64String[i]);
		//printf("%d \n", index);
		if(index != -1){
			char *buffer = decimal_to_binary(index);
			strcat(binaryString, buffer);
		}
	}

	printf("\nBinary string : %s \n", binaryString);

	return binaryString;

}
/

/**
 * This function uses the GMP library and obtain the hexadecimal value of the message
 */
char* intToHex(char *intValue) {

	mpz_t fM;
	mpz_init(fM);
	mpz_set_str(fM, intValue, 10);
	char *res = mpz_get_str(NULL, 16, fM);
	printf("\nHex Representation : %s\n", res);

	/* free used memory */
	
	mpz_clear(fM);

	return res;

}

int main() {
	printf("START \n\n");
	
	char *number =
			"205425602805833558906173513508033709272535152385063523717374966166828327746335183200430848916267302274113009813087406984304666443494047439511650193206035438356876437372761576599841427984789312047544320424021383582193773217671829331927409339102412127578769896106263788690007769028910522966162698";

	char* hexString = intToHex(number);
	char* binaryString = base64Decode(hexString);
	char* invitation = binary_to_Ascii(binaryString);
	printf("\nInvitation is : \n %s", invitation);

	printf("\n\nThe End \n");
	return 0;

}
