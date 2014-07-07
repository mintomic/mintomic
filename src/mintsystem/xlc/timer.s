*
* Simple function that calls the STCK instruction
*
* The parameters are
*  uint64* result
*
STCK     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=1
*
* pointer to location to store result passed in register 1.
         STCK 0(R1)
* TODO: extract condition code and return
EXIT     EDCXEPLG
*
CEEDSAHP CEEDSA SECTYPE=XPLINK
DSASZ    EQU *-CEEDSAHP_FIXED
*
R0       EQU 0
R1       EQU 1
R2       EQU 2
R3       EQU 3
R9       EQU 9
R10      EQU 10
R13      EQU 13
R15      EQU 15
         END STCK
