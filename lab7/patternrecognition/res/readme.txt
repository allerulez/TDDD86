/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150			52   		  48
    200		   108  		  67
    300		   326			 129
    400		   747			 190
    800		  5892			 729
   1600		 48000			3028
   3200		380000		   12000
   6400	   3000000		   48000
  12800	  24000000		  192000


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4)
	fýra nästlade loopar leder till worst case:
	n --> O(n^4)	
	(ovan är inte worst case) 

Sortering: O(n^3)
	två nästlade loopar och insert sort i priority queue ger worst case:
	n --> O(n^3)