*
* Implementation as function calls of the main mintomic
* operations
*

*
* mint_compare_exchange_strong_32_relaxed
*

MNTCXS32     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=3

         ACONTROL FLAG(NOALIGN)
         CS    R2,R3,0(R1)
         LR    R3,R2     Initialise return R3 with the result in R2

EXIT     DS    0S
         EDCXEPLG

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
         END MNTCXS32

*
* mint_fetch_add_32_relaxed
*

MNTADD32     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=2

         L     R0,0(,R1)
ADDAGN   DS    0H
         LR    R3,R0
         AR    R3,R2
         ACONTROL FLAG(NOALIGN)
         CS    R0,R3,0(R1)
         BRC   4,ADDAGN

         LR    R3,R0
EXIT     DS    0S
         EDCXEPLG

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
         END MNTADD32

*
* mint_fetch_and_32_relaxed
*

MNTAND32     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=2

         L     R0,0(,R1)
ANDAGN   DS    0H
         LR    R3,R0
         NR    R3,R2
         ACONTROL FLAG(NOALIGN)
         CS    R0,R3,0(R1)
         BRC   4,ANDAGN

         LR    R3,R0
EXIT     DS    0S
         EDCXEPLG

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
         END MNTAND32

*
* mint_fetch_or_32_relaxed
*

MNTOR32      EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=2

         L     R0,0(,R1)
ORAGN    DS    0H
         LR    R3,R0
         OR    R3,R2
         ACONTROL FLAG(NOALIGN)
         CS    R0,R3,0(R1)
         BRC   4,ORAGN

         LR    R3,R0
EXIT     DS    0S
         EDCXEPLG

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
         END MNTOR32

*
* mint_thread_fence*
*

MNTFENCE     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=0

         BCR   15,0
EXIT     DS    0S
         EDCXEPLG

CEEDSAHP CEEDSA SECTYPE=XPLINK
* DESIRED  DS  2F
DSASZ    EQU  ((((*-CEEDSAHP_FIXED)+31)/32)*32)
*
R0       EQU 0
R1       EQU 1
R2       EQU 2
R3       EQU 3
R4       EQU 4
R5       EQU 5
R9       EQU 9
R10      EQU 10
R13      EQU 13
R15      EQU 15
         END MNTFENCE

*
* mint_load_64_relaxed
*

MNTLD64     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=1

         LM    R2,R3,0(R1)
EXIT     DS    0S
         EDCXEPLG

CEEDSAHP CEEDSA SECTYPE=XPLINK
* DESIRED  DS  2F
DSASZ    EQU  ((((*-CEEDSAHP_FIXED)+31)/32)*32)
*
R0       EQU 0
R1       EQU 1
R2       EQU 2
R3       EQU 3
R4       EQU 4
R5       EQU 5
R9       EQU 9
R10      EQU 10
R13      EQU 13
R15      EQU 15
         END MNTLD64
*
* mint_store_64_relaxed
*

MNTST64     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=3
*         USING CEEDSAHP,R4

         STM   R2,R3,0(R1)
EXIT     DS    0S
         EDCXEPLG

CEEDSAHP CEEDSA SECTYPE=XPLINK
* DESIRED  DS  2F
DSASZ    EQU  ((((*-CEEDSAHP_FIXED)+31)/32)*32)
*
R0       EQU 0
R1       EQU 1
R2       EQU 2
R3       EQU 3
R4       EQU 4
R5       EQU 5
R9       EQU 9
R10      EQU 10
R13      EQU 13
R15      EQU 15
         END MNTST64

*
* mint_compare_exchange_strong_64_relaxed
*

MNTCXS64     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=5
         USING CEEDSAHP,R4

         LR    R5,R1
         L     R0,(2124+DSASZ)(R4)
         L     R1,(2128+DSASZ)(R4)
* &object in R5
* expected in R2,R3 pair (from XPLINK)
* desired in R0,R1 pair
         ACONTROL FLAG(NOALIGN)
         CDS   R2,R0,0(R5)
* Return goes in R2, R3, which it's already in

EXIT     DS    0S
         EDCXEPLG

CEEDSAHP CEEDSA SECTYPE=XPLINK
* DESIRED  DS  2F
DSASZ    EQU  ((((*-CEEDSAHP_FIXED)+31)/32)*32)
*
R0       EQU 0
R1       EQU 1
R2       EQU 2
R3       EQU 3
R4       EQU 4
R5       EQU 5
R9       EQU 9
R10      EQU 10
R13      EQU 13
R15      EQU 15
         END MNTCXS64

*
* mint_fetch_add_64_relaxed
*

MNTADD64     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=3
*         USING CEEDSAHP,R4

         LR    R9,R1
         LM    R0,R1,0(R9)
ADDAGN   DS 0H
         LR    R10,R0
         LR    R11,R1
         AR    R10,R2
         ALR   R11,R3
         BRC   12,NOCARRY
         AHI   R10,1
NOCARRY  DS 0H
         ACONTROL FLAG(NOALIGN)
         CDS   R0,R10,0(R9)
         BRC   4,ADDAGN
* Return goes in R2, R3
         LR    R3,R1
         LR    R2,R0

EXIT     DS    0S
         EDCXEPLG

CEEDSAHP CEEDSA SECTYPE=XPLINK
* DESIRED  DS  2F
DSASZ    EQU  ((((*-CEEDSAHP_FIXED)+31)/32)*32)
*
R0       EQU 0
R1       EQU 1
R2       EQU 2
R3       EQU 3
R6       EQU 6
R9       EQU 9
R10      EQU 10
R11      EQU 11
R13      EQU 13
R15      EQU 15
         END MNTADD64

*
* mint_fetch_and_64_relaxed
*

MNTAND64     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=3
*         USING CEEDSAHP,R4

         LR    R9,R1
         LM    R0,R1,0(R9)
ANDAGN   DS 0H
         LR    R10,R0
         LR    R11,R1
         NR    R10,R2
         NR    R11,R3
         ACONTROL FLAG(NOALIGN)
         CDS   R0,R10,0(R9)
         BRC   4,ANDAGN
* Return goes in R2, R3
         LR    R3,R1
         LR    R2,R0

EXIT     DS    0S
         EDCXEPLG

CEEDSAHP CEEDSA SECTYPE=XPLINK
* DESIRED  DS  2F
DSASZ    EQU  ((((*-CEEDSAHP_FIXED)+31)/32)*32)
*
R0       EQU 0
R1       EQU 1
R2       EQU 2
R3       EQU 3
R6       EQU 6
R9       EQU 9
R10      EQU 10
R11      EQU 11
R13      EQU 13
R15      EQU 15
         END MNTAND64

*
* mint_fetch_or_64_relaxed
*

MNTOR64     EDCXPRLG DSASIZE=DSASZ,BASEREG=8,PARMWRDS=3
*         USING CEEDSAHP,R10

         LR    R9,R1
         LM    R0,R1,0(R9)
ORAGN   DS 0H
         LR    R10,R0
         LR    R11,R1
         OR    R10,R2
         OR    R11,R3
         ACONTROL FLAG(NOALIGN)
         CDS   R0,R10,0(R9)
         BRC   4,ORAGN
* Return goes in R2, R3
         LR    R3,R1
         LR    R2,R0

EXIT     DS    0S
         EDCXEPLG

CEEDSAHP CEEDSA SECTYPE=XPLINK
* DESIRED  DS  2F
DSASZ    EQU  ((((*-CEEDSAHP_FIXED)+31)/32)*32)
*
R0       EQU 0
R1       EQU 1
R2       EQU 2
R3       EQU 3
R6       EQU 6
R9       EQU 9
R10      EQU 10
R11      EQU 11
R13      EQU 13
R15      EQU 15
         END MNTOR64
