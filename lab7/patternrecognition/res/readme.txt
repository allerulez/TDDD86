/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
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
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4)
	f�ra n�stlade loopar leder till worst case:
	n --> O(n^4)	
	(ovan �r inte worst case) 

Sortering: O(n^2)
	tv� n�stlade loopar ger worst case:
	n --> O(n^2)