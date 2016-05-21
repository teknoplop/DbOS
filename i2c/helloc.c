#include <stdio.h>

void i2c_init();
void i2c_probe();
void i2c_scan();
void i2c_led();
void i2c_start(); 
void i2c_stop(); 
void
calc_primes( int n )
{
	int i = 3, count, c;

   if ( n >= 1 )
   {
      printf("First %d prime numbers are :\r\n",n);
      printf("2\r\n");
   }
 
   for ( count = 2 ; count <= n ;  )
   { 
      for ( c = 2 ; c <= i - 1 ; c++ )
      {
         if ( i%c == 0 )
            break;
      }
      if ( c == i )
      {
         printf("%d\r\n",i);
         count++;
      }
      i++;
   }
 }

void
greetings( char *name )
{
	printf("Hello %s from C\r\n",  name);
}

#define FT240_STATUS $00
#define FT240_FIFO  $20

unsigned char 
ft240_read_status( )
{
	#asm
	xor a
	ld h, a
    in a, (FT240_STATUS)
    ld l, a
    #endasm	
} 

unsigned char 
ft240_read_fifo( )
{
	#asm
	xor a
	ld h, a
    in a, (FT240_STATUS)
    ld l, a
    #endasm	
} 

void
ft240_write_fifo( unsigned char v )
{
	printf("tx fifo:%02x\r\n", v);

    #asm
    ld hl,2
    add hl,sp            
    ld a,(hl)
    out (FT240_FIFO), A
    #endasm
} 



int 
main()
{
	greetings( "Laine" );
	greetings( "Sam" );	
	greetings( "Misty" );
	//calc_primes( 50 );

	printf("rx status:%02x\r\n", ft240_read_status() );



	return;

	printf("\r\n");
	printf( "i2c: init\r\n");
	i2c_init();

	//printf( "i2c: scan\r\n");
	//i2c_scan();

	printf( "i2c: led\r\n");
	i2c_led();

	printf("\r\nttfn.... :-)\r\n");
}

// https://www-users.cs.york.ac.uk/~pcc/Circuits/64180/source/diag/i2c.h
// https://searchcode.com/codesearch/view/51548034/

#define PCF8584_DATA $00
#define PCF8584_CSR  $40

#define OBD_SEND_START	0xc5    /* value to generate I2c_bus START condition */
#define OBD_SEND_STOP 	0xc3    /* value to generate I2c_bus STOP condition */

/* ----- Control register bits --------------------------------------------- */
#define PCF_PIN  0x80
#define PCF_ESO  0x40
#define PCF_ES1  0x20
#define PCF_ES2  0x10
#define PCF_ENI  0x08
#define PCF_STA  0x04
#define PCF_STO  0x02
#define PCF_SACK 0x01

/* ----- Status register bits ---------------------------------------------- */

#define PCF_INI 0x40  /* 1 if not initialized */
#define PCF_STS 0x20
#define PCF_BER 0x10
#define PCF_AD0 0x08
#define PCF_LRB 0x08
#define PCF_AAS 0x04
#define PCF_LAB 0x02
#define PCF_BB  0x01

/* ----- Chip clock frequencies -------------------------------------------- */
#define PCF_CLK3    0x00
#define PCF_CLK443  0x10
#define PCF_CLK6    0x14
#define PCF_CLK8    0x18
#define PCF_CLK12   0x1c

/* ----- transmission frequencies ------------------------------------------ */
#define PCF_TRNS90 0x00  /*  90 kHz */
#define PCF_TRNS45 0x01  /*  45 kHz */
#define PCF_TRNS11 0x02  /*  11 kHz */
#define PCF_TRNS15 0x03  /* 1.5 kHz */


void 
i2c_csr_out( unsigned char v )
{
	printf("out csr:%02x\r\n", v);

    #asm
    ld hl,2
    add hl,sp            
    ld a,(hl)
    out (PCF8584_CSR), A
    #endasm
} 

void 
i2c_dat_out( unsigned char v )
{
	printf("out dat:%02x\r\n", v);
    
    #asm
    ld hl,2
    add hl,sp            
    ld a,(hl)
    out (PCF8584_DATA), A
    #endasm	
} 

unsigned char  
i2c_csr_in( )
{
	#asm
	xor a
	ld h, a
    in a, (PCF8584_CSR)
    ld l, a
    #endasm	
} 

unsigned char 
i2c_dat_in( )
{
	#asm
	xor a
	ld h, a
    in a, (PCF8584_DATA)
    ld l, a
    #endasm	
} 

void
i2c_delay()
{
	#asm

	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

    #endasm	

}

void
delay_seconds( int s )
{
	int c = s * 10000;
	int i ;

	for ( i = 0; i < c; i++)
	{
		i2c_delay();
	}

}

/*
#define PCF_PIN  0x80
#define PCF_ESO  0x40
#define PCF_ES1  0x20
#define PCF_ES2  0x10
#define PCF_ENI  0x08
#define PCF_STA  0x04
#define PCF_STO  0x02
#define PCF_SACK 0x01


#define PCF_INI 0x40  
#define PCF_BER 0x10
#define PCF_AD0 0x08
#define PCF_LRB 0x08
#define PCF_AAS 0x04
#define PCF_LAB 0x02
#define PCF_BB  0x01
*/

 #define PCF_IDLE     (PCF_PIN | PCF_ESO | PCF_SACK)

void
i2c_init()
{
	// Reset the chip
	i2c_csr_out( PCF_PIN );
	printf( "csr:%02x\r\n", i2c_csr_in());	

	// Interface address, this will change
	i2c_dat_out( 0x55 );
	printf( "S0:%02x\r\n", i2c_dat_in() );

	// load the clock (8MHz CPU clock) into S2
	i2c_csr_out( PCF_PIN | PCF_ES1 ); //0xA0
	printf( "csr:%02x\r\n", i2c_csr_in());	
	
	i2c_dat_out( PCF_CLK8 | PCF_TRNS90 ); // 
	printf( "S2:%02x\r\n", i2c_dat_in() );	

	// Enable Interface
	i2c_csr_out( PCF_IDLE ); // 0xC1	
	i2c_delay();

	printf( "csr:%02x\r\n", i2c_csr_in() );	
}

struct i2c_buf
{
	unsigned char address;
	unsigned char buffer_length;
	unsigned char returned_status;
	unsigned char returned_length;
	unsigned char buffer[255];
}


unsigned char
i2c_waitforpin()
{
	int c;
	int r = 0;
	int i = 0;
	do
	{
		c = i2c_csr_in();

		if ( i == 0 || r != c )
		{
			i = 1;
			r = c;
		//	printf( "pin:%02x\r\n", c);			
		}

	} while( c & PCF_PIN );

	return c;
}

void 
i2c_waitforbb()
{
	int c;
	// loop until BB is high 
	do
	{
		c = i2c_csr_in();
		printf( "bb:%02x\r\n", c);
	} while( c & PCF_BB == 0);


}


void
i2c_read( struct i2c_buf* bz )
{
	unsigned char c;
	int n = 0;
		
	//i2c_waitforbb();

	// Load Slave Address into S0
	// Set the first bit to force read on bus
	// http://electronics.stackexchange.com/questions/76617/determining-i2c-address-without-datasheet
	// Don't forget that I2C addresses are in the upper 7 bits of the byte (the last bit is for read/write)
	i2c_dat_out( ( bz->address << 1 ) | 0x01 );

	// wait for the bus to come free
	i2c_waitforbb();

	// grab the bus
	i2c_csr_out( OBD_SEND_START );

	while ( 1 )
	{
		i2c_waitforpin();

		// check for error
		if ( i2c_csr_in() & PCF_LRB )
		{
			bz->returned_status = 0;	
			break;
		}

		if ( n == bz->buffer_length - 1)
		{
			// Set ACK bit S1 to 0 in preparation for negative acknowledgement
			i2c_csr_out( 0x40 );

			// This command simultaneously receives the final data byte from the I2C-bus and loads
			// it into register S0. Neg. ACK is also sent
			bz->buffer[n++] = i2c_dat_in();
			i2c_waitforpin();
			
			bz->returned_status = 1;	
			break;
		}

		bz->buffer[n++] = i2c_dat_in();
	} 

	bz->returned_length = n;
	i2c_csr_out( OBD_SEND_STOP );
	i2c_dat_in();

	i2c_delay();

}

void
i2c_write( struct i2c_buf* bz )
{
	int n = 0;
	bz->returned_status = 0;
	
	// wait for the bus to come free
	i2c_waitforbb();

	// Load 'slave address' into S0 register 'slave address' = value of slave address
	// (7-bits + R/W = 0). After reset, default = '0'
	i2c_dat_out( bz->address << 1 );

	i2c_start();

	while ( 1 )
	{
		unsigned char c = i2c_waitforpin();

		// check for error
		if ( c & PCF_LRB )
		{
			break;
		}

		if ( n == bz->buffer_length)
		{
			bz->returned_status = 1;	
			break;
		}

		i2c_dat_out( bz->buffer[n++] );
	}

	i2c_stop();

	if ( bz->returned_status == 0)
	{
		printf("i2c_write: error\r\n" );
	}
}

void i2c_start() 
{
	i2c_csr_out( OBD_SEND_START );
}

void i2c_stop() 
{
	i2c_csr_out( OBD_SEND_STOP);
}

void i2c_outb( unsigned char v) 
{
	i2c_dat_out( v );
}

void
i2c_scan()
{
	int i;

	for (i = 0x10; i < 0x77 * 2; i+=2) 
	{
		int s;

		i2c_waitforbb();

		i2c_outb( i );

		i2c_start();
		
		if ( ( i2c_waitforpin() & PCF_LRB ) == 0 )
		{
			printf("%02x\r\n",i>>1); 
		} 
		else 
		{
			printf(".\r\n"); 
		}
		
		i2c_stop();

		//i2c_delay();
	}
}


void 
i2c_probe()
{
	struct i2c_buf bz;
	int i;

	bz.buffer_length = 1;

	for ( i = 0x08; i < 0x77; ++i)
	{
		bz.address = i;

		i2c_read( &bz );

		printf("%02x:%d\r\n", i, bz.returned_status );
	}
}

#define DEFAULT_ADDRESS				 0x70
#define HT16K33_BLINK_CMD 			 0x80
#define HT16K33_BLINK_DISPLAYON 	 0x01
#define HT16K33_BLINK_OFF 			 0x00
#define HT16K33_BLINK_2HZ 			 0x02
#define HT16K33_BLINK_1HZ 			 0x04
#define HT16K33_BLINK_HALFHZ 		 0x06
#define HT16K33_SYSTEM_SETUP		 0x20
#define HT16K33_OSCILLATOR			 0x01
#define HT16K33_CMD_BRIGHTNESS 		 0xE0

void i2c_led()
{
	int i = 0;
	struct i2c_buf bz;

	bz.address = 0x70;
	bz.buffer_length = 1;	
	bz.buffer[0] = HT16K33_SYSTEM_SETUP | HT16K33_OSCILLATOR;
	i2c_write( &bz );	

	bz.buffer[0] = HT16K33_BLINK_OFF | HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON;
	i2c_write( &bz );	

	bz.buffer[0] = HT16K33_CMD_BRIGHTNESS | 7;
	i2c_write( &bz );	

	bz.buffer_length = 11;	
	bz.buffer[i++] = 0x00;

	while( 1 )
	{
		i  = 1;
		// Seg0
		bz.buffer[i++] = 0x5e;
		bz.buffer[i++] = 0;

		// Seg1
		bz.buffer[i++] = 0x79;
		bz.buffer[i++] = 0x00;

		// Colon
		bz.buffer[i++] = 0x00;
		bz.buffer[i++] = 0x00;

		// Seg 2
		bz.buffer[i++] = 0x77;
		bz.buffer[i++] = 0x00;

		// Seg 3
		bz.buffer[i++] = 0x5e;
		bz.buffer[i++] = 0x0;

		i2c_write( &bz );

		delay_seconds( 1 );

		i = 1;

		// Seg0
		bz.buffer[i++] = 0x7c;
		bz.buffer[i++] = 0;

		// Seg1
		bz.buffer[i++] = 0x79;
		bz.buffer[i++] = 0x00;

		// Colon
		bz.buffer[i++] = 0x00;
		bz.buffer[i++] = 0x00;

		// Seg 2
		bz.buffer[i++] = 0x79;
		bz.buffer[i++] = 0x00;

		// Seg 3
		bz.buffer[i++] = 0x71;
		bz.buffer[i++] = 0x0;

		i2c_write( &bz );

		delay_seconds( 1 );


	}

	/*
	return;
	// Seg0
	bz.buffer[i++] = 0x3F;
	bz.buffer[i++] = 0x06;

	// Seg1
	bz.buffer[i++] = 0x5b;
	bz.buffer[i++] = 0x4f;

	// Colon
	bz.buffer[i++] = 0x66;
	bz.buffer[i++] = 0x6d;

	// Seg 2
	bz.buffer[i++] = 0x7d;
	bz.buffer[i++] = 0x07;

	// Seg 3
	bz.buffer[i++] = 0x7f;
	bz.buffer[i++] = 0x6f;

	// NC
	bz.buffer[i++] = 0x77;
	bz.buffer[i++] = 0x7c;

	// NC
	bz.buffer[i++] = 0x39;
	bz.buffer[i++] = 0x58;

	// NC
	bz.buffer[i++] = 0x79;
	bz.buffer[i++] = 0x71;

	bz.buffer_length = 6;	
	bz.buffer[0] = 0x00;
	bz.buffer[1] = 0x71;
	bz.buffer[2] = 0x3e; //0x3e;	
	bz.buffer[3] = 0x00;	
	bz.buffer[4] = 0x79; //0x79;	
	bz.buffer[5] = 0x38; //0x38;	

	i2c_write( &bz );

	bz.buffer_length = 2;	
	bz.buffer[0] = 0x01;
	bz.buffer[1] = 0x3e;
	i2c_write( &bz );

	bz.buffer[0] = 0x02;
	bz.buffer[1] = 0x00;
	i2c_write( &bz );

	bz.buffer[0] = 0x03;
	bz.buffer[1] = 0x79;
	i2c_write( &bz );

	bz.buffer[0] = 0x04;
	bz.buffer[1] = 0x38;
	i2c_write( &bz );*/
}
