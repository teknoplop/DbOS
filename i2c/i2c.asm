MODULE I2C

defc AR_8584=$01 /* Address Register 0 0 0 */
defc VR_8584=$01 /* Vector Register 0 0 1 */
defc CL_8584=$01 /* Clock Register 0 1 0 */
defc DR_8584=$01 /* Data Register 1 0 0 */
defc CR_8584=$03 /* Control Register 0 x x */
defc CS_8584=$03 /* Cntrl/Status Reg 1 x x */


DEFVARS i2c_message
{
    ic2_slv_address   ds.b 1
    ic2_msg_length    ds.b 1
    ic2_msg_address   ds.w 1
}


xdef    i2c_master_init

i2c_master_init:
	RET