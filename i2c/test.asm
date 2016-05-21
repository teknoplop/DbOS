MODULE TEST
defc CR=$0D
defc LF=$0A
                .ORG $8000
		
                LD 	HL, LOG_HW
		CALL    PRINT
		HALT


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

LOG_HW:  DEFMZ    "Hello World!", CR, LF
