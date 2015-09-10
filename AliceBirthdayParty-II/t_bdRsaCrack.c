
/* 
	This code uses the free BIGDIGITS library version 2.3 available from
	http://di-mgt.com.au/bigdigits.html
	To show how the Chinese Remainder Theorem and Gauss's Method can be used
	to find a message encrypted by the RSA algorithm without having to factor 
	the modulus. The same message must have been encrypted with public exponent
	e = 3 to three different recipients without any random padding.
	
    Ref: http://www.di-mgt.com.au/t_bdRsaCrack.c.html
	We modified this program to suit our problem statement. 
    It takes cipher text in integer and cracks the RSA using Chinese remainder theorem.
	
	To compile :  make t_bdRsaCrack
	             ./t_bdRsaCrack
*/


#include <stdio.h>
#include "bigd.h"

int debug = 0;

int main(void)
{
	BIGD m, e, n1, n2, n3, c1, c2, c3, N, N1, N2, N3, d1, d2, d3, s, t, x;
	m = bdNew();
	e = bdNew();
	n1 = bdNew();
	n2 = bdNew();
	n3 = bdNew();
	c1 = bdNew();
	c2 = bdNew();
	c3 = bdNew();
	N = bdNew();
	N1 = bdNew();
	N2 = bdNew();
	N3 = bdNew();
	d1 = bdNew();
	d2 = bdNew();
	d3 = bdNew();
	s = bdNew();
	t = bdNew();
	x = bdNew();

	/* Read in modulus values for three 512-bit public keys */
	bdConvFromDecimal(n1, "514745167025222387434132377137056715954750729807151447929894289695587285793889099978536904494455862473045694392353612260528582074521711735864082380505874261026769465596315849668245703081452047808798727647904141791488099702631575692170683102622471798376397440600292225038412176681344166204027842724877162681931");
	bdConvFromDecimal(n2, "332459552799915544356022641605448137617079921391832222557892949808060953028449422328281413629912335051440744955455010851012308918294549765005480121061697711447087615327860789708246235156912421474047484838827777697938563515420810650393553528058831317409340577149233554235346445890238642955390137465511286414033");
	bdConvFromDecimal(n3, "665701912162243069059653781669230805473457427767514323262762891771122352328706695409103713864384833437438648120217615990765220365745013739246022203593234785338178963805463643869398986119431772931646042972240277833431035018628949924813463553419243108837309078316455504749755062865258063926243606206806549969161");

	
	printf("Three public modulus values, 512 bits each...\n");
	bdPrintDecimal("n1=", n1, "\n");
	bdPrintDecimal("n2=", n2, "\n");
	bdPrintDecimal("n3=", n3, "\n");
	
	/* The three public keys all have public exponent e = 3 */
	bdSetShort(e, 3);
	bdPrintDecimal("e=", e, "\n");
	
	/* Read in cipher text values c1,c2,c3 */
	bdConvFromDecimal(c1, "159610386572167689266326385036487109027500941380400104125191262882664358398577536610497671009102596940624920315091422093100238619835848693651492344785000232303139338861093680138737091249739575100655219967271819921458016154329847843423233652818852580016834561970850695063090000199448970052668647861992230109134");
	bdConvFromDecimal(c2, "80704323590708576386562863656130406931573788060159775931074197125212042930440694778363300836637666152530601069635539711403775897104413839059003511049631024172974390473641408894970527777947213128650545118958630567223577806350516381008539951304600069024003674444114727988917350720932569342357635015732615468372");
	bdConvFromDecimal(c3, "290728542387622789691059470283422806073663108257730190721270583629901119139049111765276898786687400514004023098315787810926656039376046957101984075353288285867739293190825676944209163087896697394093577432590616749562076462942759742984949258019827469729922204479107792698042941392668070743176808454529741938138");
	
	

	printf("Three ciphertexts...\n");
	bdPrintDecimal("c1=", c1, "\n");
	bdPrintDecimal("c2=", c2, "\n");
	bdPrintDecimal("c3=", c3, "\n");

	/* Trudy has the public values n1, n2, n3, c1, c2 and c3 */

	/* Check that n1, n2, n3 are coprime in pairs */
	bdGcd(t, n1, n2);
	bdPrintDecimal("gcd(n1,n2)=", t, "\n");
	bdGcd(t, n2, n3);
	bdPrintDecimal("gcd(n2,n3)=", t, "\n");
	bdGcd(t, n3, n1);
	bdPrintDecimal("gcd(n3,n1)=", t, "\n");

	/* Compute N = n1 * n2 * n3 */
	bdMultiply(t, n1, n2);
	bdMultiply(N, t, n3);
	if (debug) bdPrintDecimal("N=", N, "\n");

	/* Compute N_i = N/n_i for i = 1,2,3 */
	bdMultiply(N1, n2, n3);
	bdMultiply(N2, n1, n3);
	bdMultiply(N3, n1, n2);
	if (debug) bdPrintDecimal("N1=", N1, "\n");
	if (debug) bdPrintDecimal("N2=", N2, "\n");
	if (debug) bdPrintDecimal("N3=", N3, "\n");

	/* Compute d_i = N_i^{-1} mod n_i for i = 1,2,3  */
	bdModInv(d1, N1, n1);
	bdModInv(d2, N2, n2);
	bdModInv(d3, N3, n3);
	if (debug) bdPrintDecimal("d1=", d1, "\n");
	if (debug) bdPrintDecimal("d2=", d2, "\n");
	if (debug) bdPrintDecimal("d3=", d3, "\n");

	/* Compute x = c_1 N_1 d_1 + c_2 N_2 d_2 + c_3 N_3 d_3 (mod N) */
	bdModMult(s, c1, N1, N);
	bdModMult(x, s, d1, N);
	bdModMult(s, c2, N2, N);
	bdModMult(t, s, d2, N);
	bdAdd_s(x, x, t);
	bdModMult(s, c3, N3, N);
	bdModMult(t, s, d3, N);
	bdAdd_s(s, x, t);
	bdModulo(x, s, N);
	printf("Computed value of x = c_1 N_1 d_1 + c_2 N_2 d_2 + c_3 N_3 d_3 (mod N)...\n");
	bdPrintDecimal("x=", x, "\n");

	
//clean_up:
	bdFree(&m);
	bdFree(&e);
	bdFree(&n1);
	bdFree(&n2);
	bdFree(&n3);
	bdFree(&c1);
	bdFree(&c2);
	bdFree(&c3);
	bdFree(&N);
	bdFree(&N1);
	bdFree(&N2);
	bdFree(&N3);
	bdFree(&d1);
	bdFree(&d2);
	bdFree(&d3);
	bdFree(&s);
	bdFree(&t);
	bdFree(&x);
	
	return 0;
}