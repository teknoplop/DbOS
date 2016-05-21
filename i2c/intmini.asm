;==================================================================================
; Contents of this file are copyright Grant Searle
;
; You have permission to use this for NON COMMERCIAL USE ONLY
; If you wish to use it elsewhere, please include an acknowledgement to myself.
;
; http://searle.hostei.com/grant/index.html
;
; eMail: home.micros01@btinternet.com
;
; If the above don't work, please perform an Internet search to see if I have
; updated the web page hosting service.
;
;==================================================================================

; Minimum 6850 ACIA interrupt driven serial I/O to run modified NASCOM Basic 4.7
; Full input buffering with incoming data hardware handshaking
; Handshake shows full before the buffer is totally filled to allow run-on from the sender

MODULE DARBOS

SER_BUFSIZE     EQU     3FH
SER_FULLSIZE    EQU     30H
SER_EMPTYSIZE   EQU     5

defc RTS_HIGH=$D6
defc RTS_LOW=$96

serBuf          EQU     $8000
serInPtr        EQU     serBuf+SER_BUFSIZE
serRdPtr        EQU     serInPtr+2
serBufUsed      EQU     serRdPtr+2
basicStarted    EQU     serBufUsed+1
TEMPSTACK       EQU     $80ED ; Top of BASIC line input buffer so is "free ram" when BASIC resets


EXE_ORG         EQU $8000


defc CR=$0D
defc LF=$0A
defc CS=$0C             ; Clear screen

                .ORG $0000
;------------------------------------------------------------------------------
; Reset

RST00          DI                       ;Disable interrupts
               LD        SP, $FFFF
               LD        A,RTS_LOW
               OUT       ($80),A         ; Initialise ACIA
               LD        HL,LOG_HIYA      ; Sign-on message
               CALL      PRINT           ; Output string
               LD        HL,LOG_WAITEXE      ; Sign-on message
               CALL      PRINT           ; Output string
               CALL      READWORD
               PUSH      HL
               LD        HL, LOG_EXESIZE
               CALL      PRINT
               POP       HL
               CALL      DispHLhex
               CALL      PRINTCRLF

               LD        BC, EXE_ORG
EXE_READ:      CALL      READCH
               LD        (BC), A


               INC       BC
               DEC       HL
               LD        A, H
               OR        L
               JP        NZ, EXE_READ

               LD        HL, LOG_EXESTART
               CALL      PRINT
               LD        HL, EXE_ORG
               CALL      DispHLhex
               CALL      PRINTCRLF
               CALL      PRINTCRLF 
               CALL      PRINTCRLF 
               CALL      PRINTCRLF 
               JP        (HL)

PRINTCRLF: 
                PUSH     HL
                LD      HL, CRLF
                CALL     PRINT
                POP      HL
                RET

;------------------------------------------------------------------------------
PRINT:          PUSH     AF 
                PUSH     BC
                LD       C, $80
PRINT2:         LD       A,(HL)    
                OR       A             
                JR       Z,PRINT_END   ; return if 0 terminator
PRINTWAIT:      IN       B,(C)         ; wait for ACIA buffer to be ready
                BIT      1,B            
                JR       Z,PRINTWAIT      
                OUT      ($81),A        
                INC      HL              
                JR       PRINT2          
PRINT_END:
                POP      BC
                POP      AF              
                RET

PRINTCH:        PUSH     BC
                LD       C, $80
PRINTCHWAIT:    IN       B,(C)         ; wait for ACIA buffer to be ready
                BIT      1,B            
                JR       Z,PRINTCHWAIT
                OUT      ($81),A    
                POP      BC
                RET

READCH:
                IN       A,($80) 
                BIT      0,A           
                JR       Z,READCH               
                IN       A, ($81)
                RET

READWORD:
                PUSH AF
                CALL READCH
                LD   H, A
                CALL READCH
                LD   L, A
                POP  AF
                RET

DispHLhex:
; Input: HL
   ld  c,h
   call  OutHex8
   ld  c,l
OutHex8:
; Input: C
   ld  a,c
   rra
   rra
   rra
   rra
   call  Conv
   ld  a,c
Conv:
   and  $0F
   add  a,$90
   daa
   adc  a,$40
   daa
   call PRINTCH  ;replace by bcall(_PutC) or similar
   ret



LOG_HIYA:      DEFM     CS, "DARBO/S Bootstrap v0.1 for Z80 CPU",CR,LF
               DEFM         "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",CR,LF
CRLF:          DEFMZ    CR,LF
LOG_WAITEXE:   DEFMZ    "+Waiting for exe stream on serial port",CR,LF
LOG_EXESIZE:   DEFMZ    "+Recieving exe stream bytes: 0x"
LOG_EXESTART:  DEFMZ    "Executing at: 0x"
.END
