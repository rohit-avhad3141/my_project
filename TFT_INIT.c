/*
 * TFT_INIT.c
 *
 *  Created on: Mar 28, 2024
 *      Author: RnD
 */


	/*
 * TFT.c
 *
 *  Created on: Feb 22, 2021
 *      Author: RnD
 */
#include "main.h"

void TFT_Reset(void)
{

	RST_HIGH;
	HAL_Delay(200);
	RST_LOW;
	HAL_Delay(200);
	RST_HIGH;
	HAL_Delay(400);

	CS_HIGH;
	DC_HIGH;
	RD_HIGH;
	WR_HIGH;
}
void Write_Data(uint16_t data)
{
	CS_LOW;
	DC_HIGH;
	RD_HIGH;
	WR_HIGH;
	//GPIOA->ODR = (data&0xFF00);
	//GPIOC->ODR = (data&0x00FF);
	GPIOJ->ODR = (data&0xFFFF);
//	GPIOG->ODR = (data&0xFFFF);

	WR_STROBE;
//	WR_LOW;
//	HAL_Delay(100);
//	WR_HIGH;
	CS_HIGH;
}

void Write_Command(uint16_t cmd)
{
	CS_LOW;
	DC_LOW;
	RD_HIGH;
	WR_HIGH;
	//GPIOA->ODR = (cmd&0xFF00);
	//GPIOC->ODR = (cmd&0x00FF);
	GPIOJ->ODR = (cmd&0xFFFF);
//	GPIOG->ODR = (cmd&0xFFFF);
	WR_STROBE;
//	WR_LOW;
//	HAL_Delay(100);
//	WR_HIGH;
	DC_HIGH;
	CS_HIGH;
}

/*******************************************************************************
* Read data from LCD controller                                                *
*   Parameter:                                                                 *
*   Return:               read data                                            *
*******************************************************************************/

//inline unsigned short rd_dat (void) {
//  unsigned short val = 0;
//
//  	DC_HIGH;
//	Set_nWr;
//	Clr_Cs
//	Clr_nRd;
//        FIO0DIR&=0xFFFF0000;
//	Set_nRd;
//	val = FIO0PIN&0xFFFF;
//	FIO0DIR|=0xFFFF;
//	Set_Cs;
//	return val;
//}

void Command_Write(unsigned char command,unsigned char data1)
{
	Write_Command(command);
	Write_Data(data1);
}


void SSD1963_begin()
{
    TFT_Reset();
//	delay(100);
//	asm("nop");
//	asm("nop");
//	asm("nop");
//	IC_RST = 1;
//	asm("nop");
//	asm("nop");
//	asm("nop");
//	delay(1000);
	Write_Command(0x01); //Software Reset
	Write_Command(0x01);
	Write_Command(0x01);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	 Write_Command(0xe2);
	Write_Data(0x1D);
	Write_Data(0x02);
	Write_Data(0x54);
	HAL_Delay(100);
	Command_Write(0xe0,0x01); //START PLL
	HAL_Delay(100);
	Command_Write(0xe0,0x03); //LOCK PLL
	asm("nop");
	asm("nop");
	asm("nop");
	HAL_Delay(100);
	Write_Command(0xb0);
	Write_Data(0x20);
	Write_Data(0x80);
	Write_Data(0x03);
	Write_Data(0x1f);
	Write_Data(0x01);
	Write_Data(0xdf);
	Write_Data(0x00);
	Command_Write(0xf0,0x03);
	Command_Write(0x36,0x00);

	Write_Command(0xe6);
	Write_Data(0x03);
	Write_Data(0xff);
	Write_Data(0xff);
	//delay(Timer);
	Write_Command(0xb4);
	Write_Data(0x03);
	Write_Data(0x2F);
	Write_Data(0x00);
	Write_Data(0x0C);
	Write_Data(0x03);
	Write_Data(0x00);
	Write_Data(0x00);
	Write_Data(0x00);
	Write_Command(0xb6);
	Write_Data(0x01);
	Write_Data(0xEF);
	Write_Data(0x00);
	Write_Data(0x0C);
	Write_Data(0x03);
	Write_Data(0x00);
	Write_Data(0x00);
	Write_Command(0x2a);
	Write_Data(0x00);
	Write_Data(0x00);
	Write_Data(0x03);
	Write_Data(0x1f);
	Write_Command(0x2b);
	Write_Data(0x00);
	Write_Data(0x00);
	Write_Data(0x01);
	Write_Data(0xdf);
	Write_Command(0xb8);
	Write_Data(0x0f);
	Write_Data(0x01);
	Write_Command(0xba);
	 Write_Data(0x01);
	Write_Command(0x29); //SET display on
	Write_Command(0x2c);


//
//	TFT_Reset();
//	HAL_Delay(10);
//	// Set PLL MN -------------------------------------------------------------
//	// @Parameters : 3
//
//	Write_Command(0x01);
//	Write_Command(0x01);
//	HAL_Delay(100);
//
//
//	// Set PLL
//	// @Parameters : 1
//	Write_Command(0xE0);
//	Write_Data(0x01);             // Use reference clock as system clock & Enable PLL
//	HAL_Delay(100);                  // Wait 100us to let the PLL stable
//	Write_Command(0xE0);             // Set PLL
//	Write_Data(0x03);             // Use PLL output as system clock & Enable PLL
//	HAL_Delay(100);
//
//	// Software Reset ---------------------------------------------------------
//	Write_Command(0x01);
//	HAL_Delay(100);
//
//	// Set LSHIFT Frequency ---------------------------------------------------
//	// @Parameters : 3
//
//
//	Write_Command(0xe2);
//	Write_Data(0x1d);
//	Write_Data(0x02);
//	Write_Data(0x54);
//
//	Write_Command(0xE6);             // Set LSHIFT Frequency
//	//    Write_Data(0x03);             // LCDC_FPR[19:16] : The highest 4 bits for the pixel clock frequency settings
//	//    Write_Data(0xFF);             // LCDC_FPR[15:8]  : The higher byte for the pixel clock frequency settings
//	//    Write_Data(0xFF);             // LCDC_FPR[7:0]   : The low byte for the pixel clock frequency settings
//	Write_Data(0x01);
//	//    Write_Data(0xdd);
//	//    Write_Data(0xde);
//
//	//    Write_Parameter(0x01);
//	Write_Data(0x99);
//	Write_Data(0x9a);
//	//Set front porch and back
//	// Set LCD Mode
//	// @Parameters : 7
//	Write_Command(0xB0);
//	/*
//    Write_Data(0x00);             // A[5..0] TFT
//    //Write_Data(0x10);
//    Write_Data(0x00);             // B[7..5]   : Hsync+Vsync +DE mode & TFT mode
//    //Write_Data(0x80);
//    Write_Data((HDP>>8)&0xFF);    // HPS[10:8] : Set the horizontal panel size (POR = 010)
//    Write_Data(HDP&0xFF);         // HPS[7:0]  : Set the horizontal panel size (POR = 01111111)
//    Write_Data((VDP>>8)&0xFF);    // VPS[10:8] : Set the vertical panel size (POR = 001)
//    Write_Data(VDP&0xFF);         // VPS[7:0]  : Set the vertical panel size (POR = 11011111)
//    Write_Data(0x00);             // G[5..0]   : Even line RGB sequence & Odd line RGB sequence
//	 */
//	Write_Data(0x2c);                // set 18-bit for 7" panel TY700TFT800480
//	Write_Data(0x80);                // set TTL mode
//	Write_Data((DISP_HOR_RESOLUTION-1)>>8); //Set panel size
//	Write_Data(DISP_HOR_RESOLUTION-1);
//	Write_Data((DISP_VER_RESOLUTION-1)>>8);
//	Write_Data(DISP_VER_RESOLUTION-1);
//	Write_Data(0x00);
//
//
//	Write_Command(0xf0);
//	Write_Data(0x03);
//	Write_Command(0xE2);
//	Write_Data(0x23);             // N[7:0] : Multiplier (N) of PLL. (POR = 00101101) b00100011
//	Write_Data(0x02);             // M[3:0] : Divider (M) of PLL. (POR = 0011)
//	Write_Data(0x04);             // C[2] : Effectuate MN value (POR = 100) - Effectuate the multiplier and divider value
//	Write_Data(0x54);
//
//	// Set Horizontal Period --------------------------------------------------
//	// @Parameters : 8
//	Write_Command(0xB4);
//	/*
//    Write_Data((HT>>8)&0xFF);     // HT[10:8]   : High byte of horizontal total period (display + non-display) in pixel clock
//    Write_Data(HT&0xFF);          // HT[7:0]    : Low byte of the horizontal total period (display + non-display) in pixel clock
//    Write_Data((HPS>>8)&0xFF);    // HPS[10:8]  : High byte of the non-display period between the start of the horizontal sync (LLINE) signal
//    Write_Data(HPS&0xFF);         // HPS[7:0]   : Low byte of the non-display period between the start of the horizontal sync (LLINE) signal
//    Write_Data(HPW&0xFF);         // HPW[6:0]   : Set the horizontal sync pulse width (LLINE) in pixel clock
//    Write_Data((LPS>>8)&0xFF);    // LPS[10:8]  : Set the horizontal sync pulse (LLINE) start location in pixel clock
//    Write_Data(LPS&0xFF);         // LPS[7:0]   : Set the horizontal sync pulse width (LLINE) in start.
//    Write_Data(0x00);             // LPSPP[1:0] : Set the horizontal sync pulse subpixel start position
//	 */
//	//    #define HT (DISP_HOR_RESOLUTION+DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH+DISP_HOR_FRONT_PORCH)
//	//    Write_Data((HT-1)>>8);
//	//    Write_Data(HT-1);
//	//    #define HPS (DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH)
//	//    Write_Data((HPS-1)>>8);
//	//    Write_Data(HPS-1);
//	//    Write_Data(DISP_HOR_PULSE_WIDTH-1);
//
//	Write_Data(0x01);
//	Write_Data(0x98);
//	Write_Data(0x00);
//	Write_Data(0x44);
//	Write_Data(0x14);
//	Write_Data(0x00);
//	Write_Data(0x00);
//	Write_Data(0x00);
//
//	// Set Vertical Period ----------------------------------------------------
//	// @Parameters : 7
//	Write_Command(0xB6);
//	//
//	//    Write_Data(0x00);
//	//    Write_Data(0x12);
//	//    Write_Data(0x04);
//	//    Write_Data(0x00);
//	//    Write_Data(0x00);
//	/*
//    Write_Data((VT>>8)&0xFF);     // VT[10:8]  : High byte of the vertical total (display + non-display) period in lines
//    Write_Data(VT&0xFF);          // VT[7:0]   : Low byte of the vertical total (display + non-display) period in lines
//    Write_Data((VPS>>8)&0xFF);    // VPS[10:8] : High byte the non-display period in lines between the start of the frame and the first display data in line
//    Write_Data(VPS&0xFF);         // VPS[7:0]  : The non-display period in lines between the start of the frame and the first display data in line
//    Write_Data(VPW&0xFF);         // VPW[6:0]  : Set the vertical sync pulse width (LFRAME) in lines
//    Write_Data((FPS>>8)&0xFF);    // FPS[10:8] : High byte of the vertical sync pulse (LFRAME) start location in lines
//    Write_Data(FPS&0xFF);         // FPS[7:0]  : Low byte of the vertical sync pulse (LFRAME) start location in lines
////    */
//#define VT (DISP_VER_PULSE_WIDTH+DISP_VER_BACK_PORCH+DISP_VER_FRONT_PORCH+DISP_VER_RESOLUTION)
//	Write_Data((VT-1)>>8);
//	Write_Data(VT-1);
//#define VSP (DISP_VER_PULSE_WIDTH+DISP_VER_BACK_PORCH)
//	Write_Data((VSP-1)>>8);
//	Write_Data(VSP-1);
//	Write_Data(DISP_VER_PULSE_WIDTH-1);
//
//
//	Write_Data(0x00);
//	Write_Data(0x00);
////	Write_Command(0xB4);
////	Write_Data(0x01);
////	Write_Data(0xB8);
////	Write_Data(0x00);
////	Write_Data(0x44);
////	Write_Data(0x07);
////	Write_Data(0x00);
////	Write_Data(0x00);
////	Write_Data(0x00);
////
////	Write_Command(0xB6);
////	Write_Data(0x01);
////	Write_Data(0x08);
////	Write_Data(0x00);
////	Write_Data(0x13);
////	Write_Data(0x07);
////	Write_Data(0x00);
////	Write_Data(0x00);
//	// Set GPIO Value ---------------------------------------------------------
//	// @Parameters : 1
//	Write_Command(0xBA);
//	Write_Data(0x05);             // A[3..0] : GPIO[2:0] Output 1
//
//	// Set GPIO Configuration
//	// @Parameters : 2
//	Write_Command(0xB8);
//	Write_Data(0x07);             // A[7..0] : GPIO3 = Input, GPIO[2:0] = Output
//	Write_Data(0x01);             // B[0] : GPIO0 Normal
//
//	//Set pixel format, i.e. the bpp
//	Write_Command(0x3A);
//	Write_Data(0x55);                // set 16bpp
//
//	// Set Address Mode -------------------------------------------------------
//	// @Parameters : 1
//	Write_Command(0x36);             // Set Rotation
//	Write_Data(0x00);             // A[7..0] : Set the read order from host processor to frame buffer by A[7:5] and A[3] and
//	// from frame buffer to the display panel by A[2:0] and A[4].
//	// A[7] : Page address order
//	// Set Pixel Data Interface -----------------------------------------------
//	// @Parameters : 1
//	Write_Command(0xF0);             // A[2:0] : Pixel Data Interface Format
//	Write_Data(0x03);             // 16-bit (565 format)
//	HAL_Delay(100);
//
//	// enter_partial_mode
//	Write_Command(0x12);             // Part of the display area is used for image display
//	// set_display_on
//	Write_Command(0x29);             // Show the image on the display device
//
//	Write_Command(0x2C);


}

//void SSD1963_Init(void)
//{
//
//	TFT_Reset();
//	HAL_Delay(10);
//
//	Write_Command(0x01);
//	Write_Command(0x01);
//	HAL_Delay(100);
//
//
//	// Set PLL
//	// @Parameters : 1
//	Write_Command(0xE0);
//	Write_Data(0x01);             // Use reference clock as system clock & Enable PLL
//	HAL_Delay(100);                  // Wait 100us to let the PLL stable
//	Write_Command(0xE0);             // Set PLL
//	Write_Data(0x03);             // Use PLL output as system clock & Enable PLL
//	HAL_Delay(100);
//
//	// Software Reset ---------------------------------------------------------
//	Write_Command(0x01);
//	HAL_Delay(100);
//
//	// Set LSHIFT Frequency ---------------------------------------------------
//	// @Parameters : 3
//
//
//	Write_Command(0xe2);
//	Write_Data(0x1d);
//	Write_Data(0x02);
//	Write_Data(0x54);
//
//	Write_Command(0xE6);             // Set LSHIFT Frequency
//	//    Write_Data(0x03);             // LCDC_FPR[19:16] : The highest 4 bits for the pixel clock frequency settings
//	//    Write_Data(0xFF);             // LCDC_FPR[15:8]  : The higher byte for the pixel clock frequency settings
//	//    Write_Data(0xFF);             // LCDC_FPR[7:0]   : The low byte for the pixel clock frequency settings
//	Write_Data(0x01);
//	//    Write_Data(0xdd);
//	//    Write_Data(0xde);
//
//	//    Write_Parameter(0x01);
//	Write_Data(0x99);
//	Write_Data(0x9a);
//	//Set front porch and back
//	// Set LCD Mode
//	// @Parameters : 7
//	Write_Command(0xB0);
//	/*
//    Write_Data(0x00);             // A[5..0] TFT
//    //Write_Data(0x10);
//    Write_Data(0x00);             // B[7..5]   : Hsync+Vsync +DE mode & TFT mode
//    //Write_Data(0x80);
//    Write_Data((HDP>>8)&0xFF);    // HPS[10:8] : Set the horizontal panel size (POR = 010)
//    Write_Data(HDP&0xFF);         // HPS[7:0]  : Set the horizontal panel size (POR = 01111111)
//    Write_Data((VDP>>8)&0xFF);    // VPS[10:8] : Set the vertical panel size (POR = 001)
//    Write_Data(VDP&0xFF);         // VPS[7:0]  : Set the vertical panel size (POR = 11011111)
//    Write_Data(0x00);             // G[5..0]   : Even line RGB sequence & Odd line RGB sequence
//	 */
//	Write_Data(0x2c);                // set 18-bit for 7" panel TY700TFT800480
//	Write_Data(0x80);                // set TTL mode
//	Write_Data((DISP_HOR_RESOLUTION-1)>>8); //Set panel size
//	Write_Data(DISP_HOR_RESOLUTION-1);
//	Write_Data((DISP_VER_RESOLUTION-1)>>8);
//	Write_Data(DISP_VER_RESOLUTION-1);
//	Write_Data(0x00);
//
//
//	Write_Command(0xf0);
//	Write_Data(0x03);
//	Write_Command(0xE2);
//	Write_Data(0x23);             // N[7:0] : Multiplier (N) of PLL. (POR = 00101101) b00100011
//	Write_Data(0x02);             // M[3:0] : Divider (M) of PLL. (POR = 0011)
//	Write_Data(0x04);             // C[2] : Effectuate MN value (POR = 100) - Effectuate the multiplier and divider value
//	Write_Data(0x54);
//
//	// Set Horizontal Period --------------------------------------------------
//	// @Parameters : 8
//	Write_Command(0xB4);
//	/*
//    Write_Data((HT>>8)&0xFF);     // HT[10:8]   : High byte of horizontal total period (display + non-display) in pixel clock
//    Write_Data(HT&0xFF);          // HT[7:0]    : Low byte of the horizontal total period (display + non-display) in pixel clock
//    Write_Data((HPS>>8)&0xFF);    // HPS[10:8]  : High byte of the non-display period between the start of the horizontal sync (LLINE) signal
//    Write_Data(HPS&0xFF);         // HPS[7:0]   : Low byte of the non-display period between the start of the horizontal sync (LLINE) signal
//    Write_Data(HPW&0xFF);         // HPW[6:0]   : Set the horizontal sync pulse width (LLINE) in pixel clock
//    Write_Data((LPS>>8)&0xFF);    // LPS[10:8]  : Set the horizontal sync pulse (LLINE) start location in pixel clock
//    Write_Data(LPS&0xFF);         // LPS[7:0]   : Set the horizontal sync pulse width (LLINE) in start.
//    Write_Data(0x00);             // LPSPP[1:0] : Set the horizontal sync pulse subpixel start position
//	 */
//	//    #define HT (DISP_HOR_RESOLUTION+DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH+DISP_HOR_FRONT_PORCH)
//	//    Write_Data((HT-1)>>8);
//	//    Write_Data(HT-1);
//	//    #define HPS (DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH)
//	//    Write_Data((HPS-1)>>8);
//	//    Write_Data(HPS-1);
//	//    Write_Data(DISP_HOR_PULSE_WIDTH-1);
//
//	Write_Data(0x01);
//	Write_Data(0x98);
//	Write_Data(0x00);
//	Write_Data(0x44);
//	Write_Data(0x14);
//	Write_Data(0x00);
//	Write_Data(0x00);
//	Write_Data(0x00);
//
//	// Set Vertical Period ----------------------------------------------------
//	// @Parameters : 7
//	Write_Command(0xB6);
//	//
//	//    Write_Data(0x00);
//	//    Write_Data(0x12);
//	//    Write_Data(0x04);
//	//    Write_Data(0x00);
//	//    Write_Data(0x00);
//	/*
//    Write_Data((VT>>8)&0xFF);     // VT[10:8]  : High byte of the vertical total (display + non-display) period in lines
//    Write_Data(VT&0xFF);          // VT[7:0]   : Low byte of the vertical total (display + non-display) period in lines
//    Write_Data((VPS>>8)&0xFF);    // VPS[10:8] : High byte the non-display period in lines between the start of the frame and the first display data in line
//    Write_Data(VPS&0xFF);         // VPS[7:0]  : The non-display period in lines between the start of the frame and the first display data in line
//    Write_Data(VPW&0xFF);         // VPW[6:0]  : Set the vertical sync pulse width (LFRAME) in lines
//    Write_Data((FPS>>8)&0xFF);    // FPS[10:8] : High byte of the vertical sync pulse (LFRAME) start location in lines
//    Write_Data(FPS&0xFF);         // FPS[7:0]  : Low byte of the vertical sync pulse (LFRAME) start location in lines
////    */
//#define VT (DISP_VER_PULSE_WIDTH+DISP_VER_BACK_PORCH+DISP_VER_FRONT_PORCH+DISP_VER_RESOLUTION)
//	Write_Data((VT-1)>>8);
//	Write_Data(VT-1);
//#define VSP (DISP_VER_PULSE_WIDTH+DISP_VER_BACK_PORCH)
//	Write_Data((VSP-1)>>8);
//	Write_Data(VSP-1);
//	Write_Data(DISP_VER_PULSE_WIDTH-1);
//
//
//	Write_Data(0x00);
//	Write_Data(0x00);
//
//	// Set GPIO Value ---------------------------------------------------------
//	// @Parameters : 1
//	Write_Command(0xBA);
//	Write_Data(0x05);             // A[3..0] : GPIO[2:0] Output 1
//
//	// Set GPIO Configuration
//	// @Parameters : 2
//	Write_Command(0xB8);
//	Write_Data(0x07);             // A[7..0] : GPIO3 = Input, GPIO[2:0] = Output
//	Write_Data(0x01);             // B[0] : GPIO0 Normal
//
//	//Set pixel format, i.e. the bpp
//	Write_Command(0x3A);
//	Write_Data(0x55);                // set 16bpp
//
//	// Set Address Mode -------------------------------------------------------
//	// @Parameters : 1
//	Write_Command(0x36);             // Set Rotation
//	Write_Data(0x00);             // A[7..0] : Set the read order from host processor to frame buffer by A[7:5] and A[3] and
//	// from frame buffer to the display panel by A[2:0] and A[4].
//	// A[7] : Page address order
//	// Set Pixel Data Interface -----------------------------------------------
//	// @Parameters : 1
//	Write_Command(0xF0);             // A[2:0] : Pixel Data Interface Format
//	Write_Data(0x03);             // 16-bit (565 format)
//	HAL_Delay(100);
//
//	// enter_partial_mode
//	Write_Command(0x12);             // Part of the display area is used for image display
//	// set_display_on
//	Write_Command(0x29);             // Show the image on the display device
//
//	Write_Command(0x2C);
//
//}

void SSD1963_Init(void)//Winstar
{
	TFT_Reset();
	HAL_Delay(10);
	// Set PLL MN -------------------------------------------------------------
	// @Parameters : 3
	Write_Command(0x01);
	Write_Command(0x01);
	Write_Command(0x01);
	HAL_Delay(100);

	Write_Command(0xE0);
	Write_Data(0x01);             		// Use reference clock as system clock & Enable PLL
	HAL_Delay(1);                  		// Wait 100us to let the PLL stable
	Write_Command(0xE0);             	// Set PLL
	Write_Data(0x03);             		// Use PLL output as system clock & Enable PLL
	HAL_Delay(100);


	Write_Command(0xB0);
	Write_Data(0x24);
	Write_Data(0x20);
	Write_Data(0x01);                // set 18-bit for 7" panel TY700TFT800480
	Write_Data(0x3f);                // set TTL mode
	Write_Data(0x00); //Set panel size
	Write_Data(0xef);
	Write_Data(0x00);


	Write_Command(0xf0);
	Write_Data(0x03);

	Write_Command(0x3A);
	Write_Data(0x50);                // set 16bpp

	Write_Command(0x36);             // Set Rotation
	Write_Data(0x08);


	Write_Command(0xe2);
	Write_Data(0x1d);
	Write_Data(0x02);
	Write_Data(0x54);
	HAL_Delay(1);

	Write_Command(0xE6);             	// Set LSHIFT Frequency
	Write_Data(0x01);             	// LCDC_FPR[19:16] : The highest 4 bits for the pixel clock frequency settings
	Write_Data(0x40);             	// LCDC_FPR[15:8]  : The higher byte for the pixel clock frequency settings
	Write_Data(0xff);             	// LCDC_FPR[7:0]   : The low byte for the pixel clock frequency settings


	Write_Command(0xB4);
	Write_Data(0x01);
	Write_Data(0xB8);
	Write_Data(0x00);
	Write_Data(0x44);
	Write_Data(0x07);
	Write_Data(0x00);
	Write_Data(0x00);
	Write_Data(0x00);

	Write_Command(0xB6);
	Write_Data(0x01);
	Write_Data(0x08);
	Write_Data(0x00);
	Write_Data(0x13);
	Write_Data(0x07);
	Write_Data(0x00);
	Write_Data(0x00);

	Write_Command(0x2a);
	Write_Data(0x00);
	Write_Data(0x00);
	Write_Data(0x01);
	Write_Data(0x3f);

	Write_Command(0x2b);
	Write_Data(0x00);
	Write_Data(0x00);
	Write_Data(0x00);
	Write_Data(0x3f);

	Write_Command(0xB8);
	Write_Data(0x0f);             // A[7..0] : GPIO3 = Input, GPIO[2:0] = Output
	Write_Data(0x01);             // B[0] : GPIO0 Normal

	Write_Command(0xBA);
	Write_Data(0x01);             // A[3..0] : GPIO[2:0] Output 1
	// Set PLL
	// @Parameters : 1
	Write_Command(0x29);             // Show the image on the display device
	Write_Command(0x2C);
}


