/*
 * AliceBirthdayParty1.c
 *
 * This program aims to solve the Part - 1 of the "Alice Birthday Party" challenge.
 * References: GMP Library: Retrieved from: https://gmplib.org/
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
/**
 * This function uses Euclidean algorithm to find the coefficients.
 *
 */
long* findpowers(long a,long b){

	long s = 0, old_s = 1;
	long t = 1, old_t = 0;
	long r = a, old_r = b;
	long c[2];
	while (r != 0) {
		long quotient = old_r / r;
		long temp_r = r;
		r = old_r - quotient * r;
		old_r = temp_r;
		long temp_s = s;
		s = old_s - quotient * s;
		old_s = temp_s;
		long temp_t = t;
		t = old_t - quotient * t;
		old_t = temp_t;
	}
	c[0] = old_s;
	c[1] = old_t;
	//printf("old s: %ld,  and old t : %ld", old_s, old_t);
	//printf("\nGCD: %ld", old_r);
	//printf("\nQuotients t = %ld, s = %ld", t, s);

	return c;
}

/**
 * This function uses the GMP library and obtain the decimal value of Message.
 * This computes the message using the formula M = (C1) ^ pow1 * (C2) ^ pow2 mod N
 */
char* decryptMessage(char *c1Value, char *c2Value, char *nModuloValue, long pow1, long pow2) {

	mpz_t N;
	mpz_t c1, c2;

	mpz_init(N);
	mpz_init(c1);
	mpz_init(c2);

	mpz_set_str(N, nModuloValue, 10);
	mpz_set_str(c1, c1Value, 10);
	mpz_set_str(c2, c2Value, 10);

	mpz_t c1PowerValue, c2PowerValue;

	mpz_init(c1PowerValue);
	mpz_init(c2PowerValue);

	mpz_pow_ui(c1PowerValue, c1, 21846);
	mpz_invert(c2PowerValue, c2, N);

	//gmp_printf("%s is an mpz %Zd\n", "here", c1PowerValue);
	//gmp_printf("%s is an mpz %Zd\n", "here", c2PowerValue);

	mpz_t prod;
	mpz_init(prod);

	mpz_mul(prod, c1PowerValue, c2PowerValue);

	mpz_t finalM;
	mpz_init(finalM);

	mpz_mod(finalM, prod, N);

	gmp_printf("\nFinal message : %Zd\n", finalM);


	char *res = mpz_get_str(NULL, 16, finalM);
	printf("\nHex Representation : %s\n", res);

	/* free used memory */
	mpz_clear(N);
	mpz_clear(c1);
	mpz_clear(c2);
	mpz_clear(c1PowerValue);
	mpz_clear(c2PowerValue);
	mpz_clear(prod);
	mpz_clear(finalM);

	return res;

}

int main() {
	printf("START \n\n");
	long *powers;
	long a = 3;
	long b = 65537;
	powers = findpowers(a,b);
	printf("The a and b powers obtained are : a = %ld and b = %ld \n", powers[0], powers[1]);

	char *c1Value =
			"239450055536579126410433057119955568243208878037441558052345538060429910227864196906345427754000499641521575512944473380047865623679664401229365345208068050995600248796358129950676950842724758743044543343426938845678892776396315240898265648919893384723100132425351735921836372375270138768751862889295179915967";
	char *c2Value =
			"138372640918712441635048432796183745163164033759933692015738688043514876808030419408866658926149572619049975479533518038543123781439635367988204599740411304464710538234675409552954543439980522243416932759834006973717964032712098473752496471182275216438174279723470286674311474283278293265668947915374771552561";
	char *number =
			"402394248802762560784459411647796431108620322919897426002417858465984510150839043308712123310510922610690378085519407742502585978563438101321191019034005392771936629869360205383247721026151449660543966528254014636648532640397857580791648563954248342700568953634713286153354659774351731627683020456167612375777";

	char* hexString = decryptMessage(c1Value, c2Value, number, powers[0], powers[1]);
	char* binaryString = base64Decode(hexString);
	char* invitation = binary_to_Ascii(binaryString);
	printf("\nInvitation is : \n %s", invitation);

	printf("\n\nThe End \n");
	return 0;

}



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

int mainParty() {
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

