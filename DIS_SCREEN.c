/////*
//// * Display_Screens.c
//// *
//// *  Created on: 24-Feb-2021
//// *      Author: RnD
//// */

//shree ram

#include "main.h"
//#include "stdio.h"

#define line_space_HV_scr 60
#define line_space_phase  60
#define line_space_curr   50
#define line_space_resi   50
#define line_space_wel    50

 volatile unsigned short  TextColor1 = Blue;
 volatile unsigned short  BackColor =  Cyan;
 volatile unsigned short  TextColor2 = Yellow;
 volatile unsigned short  BackColor2 = Blue;

uint8_t vtest_select,vphase_select,vcurr_select,vreg_select,Vwelcome_scr;
char volt[2][10]={"400000.0","220000.0"};

void set_time_date_dis()
{
	GLCD_clear(BackColor);
	HAL_Delay(10);
	print_str(248,150,1,TextColor1,BackColor,"SET TIME:- 00:00:00", F_GroteskBold16x32);
	print_str(248,250,1,TextColor1,BackColor,"Date:-     00-00-2000",F_GroteskBold16x32);
	Draw_Rectangle(350, 420, 450, 460, 0, 1, Black,BackColor);
	Draw_Rectangle(349, 419, 449, 459, 0, 1, Black,BackColor);
	print_str(370,425, 1, TextColor1, BackColor, "SKIP", F_GroteskBold16x32);

}

void Cursor_time_date_setting(uint8_t Cursor)
{
	fun_print_str(Cursor,1,248,150,1,TextColor1,BackColor,TextColor2, BackColor2,"SET TIME", F_GroteskBold16x32);
	fun_print_str(Cursor,2,248,250,1,TextColor1,BackColor,TextColor2, BackColor2,"Date",F_GroteskBold16x32);

	if(Cursor==3)
		print_str(370,425, 1, TextColor2, BackColor2, "SKIP", F_GroteskBold16x32);
	else
		print_str(370,425, 1, TextColor1, BackColor, "SKIP", F_GroteskBold16x32);
}


void fun_print_str(unsigned int Cursor,unsigned int aCursor,unsigned int x_pos, unsigned int y_pos,unsigned char font_size, unsigned int colour1, unsigned int back_colour1,unsigned int colour2,unsigned int back_colour2, char *ch , unsigned char Sel_font)
{
	if(Cursor==aCursor)
	{
		print_str(x_pos,y_pos,1,colour2,back_colour2,ch,Sel_font);
	}
	else
	{
		print_str(x_pos,y_pos, 1,colour1,back_colour1,ch,Sel_font);
	}
}

void info_screen()
{
	print_str(280, 50, 1, Maroon, BackColor, "WELCOME" , F_Grotesk32x64);
	print_str(200, 150, 1, TextColor1, BackColor, "THE MOTWANE MFG.CO.PVT.LTD" , F_GroteskBold16x32);
	print_str(170, 200, 1, White, BackColor, "Gyan Baug, Nashik Road -422101" , F_GroteskBold16x32);
	print_str(180, 250, 1, White, BackColor, "Nashik, Maharashtra, INDIA" , F_GroteskBold16x32);
	print_str(170, 300, 1, White, BackColor, "India Toll Free:1800 233 7766" , F_GroteskBold16x32);
//	print_str(, 180, 1, White, BackColor, "1800 233 7766" , F_GroteskBold16x32);
	print_str(280, 350, 1, TextColor1, BackColor, "www.motwane.com" , F_GroteskBold16x32);
	print_str(140, 400, 1, Black, BackColor, "Winding Resistance Meter XWRM-253" , F_GroteskBold16x32);
	//print_str(162, 252, 1, White, BackColor, test_str, F_console_font_12x16);
}

 void home_screen(void)
 {
	 GLCD_clear(BackColor);
	 HAL_Delay(10);
	 home_scr_flag=1;
//   Draw_H_Line(1,800,70,Black);
//	 print_str(100,80, 1,Black, BackColor, "Winding Resistance Meter Model-XWRM-10A",F_GroteskBold16x32);

	print_str(300,150, 1,  Yellow, Blue, "Start Test", F_GroteskBold16x32);
	print_str(300,220, 1, TextColor1, BackColor, "View Report" , F_GroteskBold16x32);
	print_str(300,290, 1, TextColor1, BackColor,"Settings" , F_GroteskBold16x32);

    bottom_block();
 }

 void Cursor_home_screen(unsigned int Cursor)
 {

    test_on_flag=1;
//	Draw_H_Line(1,800,70,Black);
//	Draw_H_Line(1,800,71,Black);
//	print_str(100,80, 1,Black, BackColor, "Winding Resistance Meter Model-XWRM-10A",F_GroteskBold16x32);
 	fun_print_str(Cursor,1,300,150, 1, TextColor1, BackColor, TextColor2, BackColor2, "Start Test", F_GroteskBold16x32);
 	fun_print_str(Cursor,2,300,220, 1, TextColor1, BackColor, TextColor2, BackColor2, "View Report" , F_GroteskBold16x32);
 	fun_print_str(Cursor,3,300,290, 1, TextColor1, BackColor, TextColor2, BackColor2,"Settings" , F_GroteskBold16x32);
 }

 void Test_screen(void)
 {
	 HAL_Delay(10);
	 GLCD_clear(BackColor);
     first_scr_flag=1;
     test_on_flag=1;
//	Draw_H_Line(1,800,70,Black);
//	Draw_H_Line(1,800,71,Black);
//	print_str(100,80, 1,Black, BackColor, "Winding Resistance Meter Model-XWRM-10A",F_GroteskBold16x32);
	print_str(50,130, 1,TextColor2, Blue, "Winding Resistance Test", F_GroteskBold16x32);
	print_str(50,180, 1, TextColor1, BackColor, "Heat Run Test" , F_GroteskBold16x32);
    print_str(50,230, 1,  TextColor1, BackColor, "OLTC  Test" , F_GroteskBold16x32);
    print_str(50,280, 1, TextColor1, BackColor, "Demagnetizing Test" , F_GroteskBold16x32);
    print_str(50,330, 1, TextColor1, BackColor, "Dynamic Resistance Test" , F_GroteskBold16x32);


   bottom_block();
 }

void Cursor_Test_screen(uint8_t Cursor)
{
	test_on_flag=1;
//	Draw_H_Line(1,800,70,Black);
//	Draw_H_Line(1,800,71,Black);
//	print_str(100,80, 1,Black, BackColor, "Winding Resistance Meter Model-XWRM-10A",F_GroteskBold16x32);
	fun_print_str(Cursor,1,50,130, 1, TextColor1, BackColor,TextColor2,BackColor2, "Winding Resistance Test", F_GroteskBold16x32);
	fun_print_str(Cursor,2,50,180, 1, TextColor1, BackColor,TextColor2,BackColor2, "Heat Run Test" , F_GroteskBold16x32);
	fun_print_str(Cursor,3,50,230, 1, TextColor1, BackColor,TextColor2,BackColor2, "OLTC  Test" , F_GroteskBold16x32);
	fun_print_str(Cursor,4,50,280, 1, TextColor1, BackColor,TextColor2,BackColor2, "Demagnetizing Test" , F_GroteskBold16x32);
	fun_print_str(Cursor,5,50,330, 1, TextColor1, BackColor,TextColor2,BackColor2, "Dynamic Resistance Test" , F_GroteskBold16x32);

}

void parameter_screen(void)
 {

	test_on_flag=1;
	second_scr_flag=1;
	print_str(100, 120, 1, TextColor1, BackColor, "              :-" , F_GroteskBold16x32);
	print_str(100, 120, 1, TextColor2,BackColor2, "Test Object" , F_GroteskBold16x32);
	print_str(100, 170, 1, TextColor1, BackColor, "Specification :-" , F_GroteskBold16x32);
	print_str(100, 220, 1, TextColor1, BackColor,"Serial No.    :-" , F_GroteskBold16x32);
	print_str(100, 270, 1, TextColor1, BackColor, "Make          :-" , F_GroteskBold16x32);
	print_str(100, 320, 1, TextColor1, BackColor, "Year Of Mgf   :-" , F_GroteskBold16x32);
	print_str(100, 370, 1, TextColor1, BackColor, "Location      :-" , F_GroteskBold16x32);

	Draw_Rectangle(445, 422, 530, 457, 1, 1, Black,Black);
	Draw_Rectangle(225, 422, 315, 457, 1, 1, Black,Black);
	print_str(460,425, 1, White, Black, "NEXT", F_GroteskBold16x32);
	print_str(240,425, 1, White, Black, "BACK", F_GroteskBold16x32);

	bottom_block();
	//HAL_Delay(1000);

}

void Cursor_parameter_screen(uint8_t Cursor)
{
	fun_print_str(Cursor,1,100, 120, 1, TextColor1, BackColor, TextColor2,BackColor2, "Test Object" , F_GroteskBold16x32);
	fun_print_str(Cursor,2,100, 170, 1, TextColor1, BackColor, TextColor2,BackColor2, "Specification" , F_GroteskBold16x32);
	fun_print_str(Cursor,3,100, 220, 1, TextColor1, BackColor, TextColor2,BackColor2,"Serial No." , F_GroteskBold16x32);
	fun_print_str(Cursor,4,100, 270, 1, TextColor1, BackColor, TextColor2,BackColor2, "Make" , F_GroteskBold16x32);
	fun_print_str(Cursor,5,100, 320, 1, TextColor1, BackColor, TextColor2,BackColor2, "Year Of Mgf" , F_GroteskBold16x32);
	fun_print_str(Cursor,6,100, 370, 1, TextColor1, BackColor,TextColor2,BackColor2, "Location" , F_GroteskBold16x32);

	fun_print_str(Cursor,7, 460,425, 1, White, Black,TextColor2, BackColor2, "NEXT", F_GroteskBold16x32);
	fun_print_str(Cursor,8, 240, 425, 1, White, Black,TextColor2, BackColor2, "Back", F_GroteskBold16x32);

//	if(Cursor==7)
//	{
//		//Draw_Rectangle(350, 420, 450, 460, 0, 1, Black,BackColor);
//		print_str(370,425, 1, TextColor2, BackColor2, "NEXT", F_GroteskBold16x32);
//	}
//	else
//	{
//		print_str(370,425, 1, White, Black, "NEXT", F_GroteskBold16x32);
//	}
}

void select_curr_res()
{
	 GLCD_clear(BackColor);
	 HAL_Delay(10);
	 third_scr_flag=1;
	 test_on_flag=1;

//	 Draw_H_Line(1,800,60,Black);
//	 Draw_H_Line(1,800,61,Black);
//	 print_str(100,70, 1,Black, BackColor, "Winding Resistance Meter Model-XWRM-10A",F_GroteskBold16x32);
	 print_str(40,150, 1, TextColor1, BackColor, "Select Resistanace Channel:-" , F_GroteskBold16x32);
	 print_str(40,250, 1, TextColor1, BackColor, "Select Test Current:-" , F_GroteskBold16x32);

	     if(third_scr_line1_flag)
	        print_str(500,150, 1,Yellow,Blue, "single" , F_GroteskBold16x32);
	     else
	     {
	    	if(para[0]==1)
		       print_str(500,150, 1, TextColor1, BackColor, "single" , F_GroteskBold16x32);
	    	else
	           print_str(500,150, 1, TextColor1, BackColor, "single" , F_GroteskBold16x32);
	     }
	     if(para[0]==2)
		     print_str(620,150, 1, TextColor1, BackColor, "Dual" , F_GroteskBold16x32);
	     else
	    	 print_str(620,150, 1, TextColor1, BackColor, "Dual" , F_GroteskBold16x32);

	     if(para[0]==3)
		     print_str(710,150, 1, TextColor1, BackColor, "All" , F_GroteskBold16x32);
	     else
	    	 print_str(710,150, 1, TextColor1, BackColor, "All" , F_GroteskBold16x32);
/***********************************************************************************************/

		 if(third_scr_line2_flag)
	           print_str(390,250, 1,Yellow,Blue, "1mA" , F_GroteskBold16x32);
		 else
		 {
//			 if(para[1]==4)
//				print_str(390,250, 1,Black,BackColor, "1mA" , F_GroteskBold16x32);
//		    else
	            print_str(390,250, 1, TextColor1, BackColor, "1mA" , F_GroteskBold16x32);
		 }
//		 if(para[1]==5)
//		      print_str(475,250, 1, Black, BackColor, "10mA" , F_GroteskBold16x32);
//		 else
			 print_str(475,250, 1, TextColor1, BackColor, "10mA" , F_GroteskBold16x32);

//		 if(para[1]==6)
//		      print_str(580,250, 1, Black, BackColor, "100mA" , F_GroteskBold16x32);
//		 else
			  print_str(580,250, 1, TextColor1, BackColor, "100mA" , F_GroteskBold16x32);

//		 if(para[1]==7)
//		     print_str(680,250, 1, Black, BackColor, "1A" , F_GroteskBold16x32);
//		 else
			 print_str(680,250, 1, TextColor1, BackColor, "1A" , F_GroteskBold16x32);

//		 if(para[1]==8)
//		     print_str(390,300, 1, Black, BackColor, "5Amp" , F_GroteskBold16x32);
//		 else
			 print_str(390,300, 1, TextColor1, BackColor, "5Amp" , F_GroteskBold16x32);

//		 if(para[1]==9)
//		     print_str(475,300, 1, Black, BackColor, "10Amp" , F_GroteskBold16x32);
//		 else
			 print_str(475,300, 1, TextColor1, BackColor, "10Amp" , F_GroteskBold16x32);

//		 if(para[1]==10)
//		      print_str(580,300, 1, Black, BackColor, "25Amp" , F_GroteskBold16x32);
//		 else
			 print_str(580,300, 1, TextColor1, BackColor, "25Amp" , F_GroteskBold16x32);

//		 if(para[1]==11)
//		     print_str(680,300, 1, Black, BackColor, "50Amp" , F_GroteskBold16x32);
//		 else
			 print_str(680,300, 1, TextColor1, BackColor, "50Amp" , F_GroteskBold16x32);

      bottom_block();

        Draw_Rectangle(445, 422, 530, 457, 1, 1, Black,Black);
		Draw_Rectangle(225, 422, 315, 457, 1, 1, Black,Black);
		print_str(460,425, 1, White, Black, "NEXT", F_GroteskBold16x32);
		print_str(240,425, 1, White, Black, "BACK", F_GroteskBold16x32);
   // HAL_Delay(1000);
}


void Cursor_select_curr_res(uint8_t Cursor)
{
   fun_print_str(Cursor,1,40,150, 1, TextColor1, BackColor,TextColor2,BackColor2, "Select Resistanace Channel" , F_GroteskBold16x32);
   fun_print_str(Cursor,2,40,250, 1, TextColor1, BackColor,TextColor2,BackColor2, "Select Test Current" , F_GroteskBold16x32);
   fun_print_str(Cursor,3, 460,425, 1, White, Black,TextColor2, BackColor2, "NEXT", F_GroteskBold16x32);
   fun_print_str(Cursor,4, 240, 425, 1, White, Black,TextColor2, BackColor2, "Back", F_GroteskBold16x32);

}

void Cursor_select_curr_res1(uint8_t Cursor)
{

		 if(para[0]==1)
		    print_str(500,150, 1, Black, BackColor, "single" , F_GroteskBold16x32);
		 else
		   fun_print_str(Cursor,1,500,150, 1, TextColor1, BackColor,TextColor2,BackColor2, "single" , F_GroteskBold16x32);

		 if(para[0]==2)
		    print_str(620,150, 1, Black, BackColor, "Dual" , F_GroteskBold16x32);
		 else
		    fun_print_str(Cursor,2,620,150, 1, TextColor1, BackColor,TextColor2,BackColor2, "Dual" , F_GroteskBold16x32);

		 if(para[0]==3)
		    print_str(710,150, 1, Black, BackColor, "All" , F_GroteskBold16x32);
		else
		    fun_print_str(Cursor,3,710,150, 1, TextColor1, BackColor,TextColor2,BackColor2, "All" , F_GroteskBold16x32);

//		 if(para[1]==4)
//		     print_str(390,250, 1,Black,BackColor, "1mA" , F_GroteskBold16x32);
//	     else
		    fun_print_str(Cursor,4,390,250, 1, TextColor1, BackColor,TextColor2,BackColor2, "1mA" , F_GroteskBold16x32);

//		 if(para[1]==5)
//		    print_str(475,250, 1, Black, BackColor, "10mA" , F_GroteskBold16x32);
//		 else
		 fun_print_str(Cursor,5,475,250, 1, TextColor1, BackColor,TextColor2,BackColor2, "10mA" , F_GroteskBold16x32);

//		 if(para[1]==6)
//		    print_str(580,250, 1, Black, BackColor, "100mA" , F_GroteskBold16x32);
//		 else
		    fun_print_str(Cursor,6,580,250, 1, TextColor1, BackColor,TextColor2,BackColor2, "100mA" , F_GroteskBold16x32);

//		 if(para[1]==7)
//		    print_str(680,250, 1, Black, BackColor, "1A" , F_GroteskBold16x32);
//		 else
		    fun_print_str(Cursor,7,680,250, 1, TextColor1, BackColor,TextColor2,BackColor2, "1A" , F_GroteskBold16x32);

//		 if(para[1]==8)
//		    print_str(390,300, 1, Black, BackColor, "5Amp" , F_GroteskBold16x32);
//		 else
		    fun_print_str(Cursor,8,390,300, 1, TextColor1, BackColor,TextColor2,BackColor2, "5Amp" , F_GroteskBold16x32);

//		 if(para[1]==9)
//		    print_str(475,300, 1, Black, BackColor, "10Amp" , F_GroteskBold16x32);
//		 else
		    fun_print_str(Cursor,9,475,300, 1, TextColor1, BackColor,TextColor2,BackColor2, "10Amp" , F_GroteskBold16x32);

//		 if(para[1]==10)
//		 	 print_str(580,300, 1, Black, BackColor, "25Amp" , F_GroteskBold16x32);
//		 else
		 fun_print_str(Cursor,10,580,300, 1, TextColor1, BackColor,TextColor2,BackColor2, "25Amp" , F_GroteskBold16x32);

//		 if(para[1]==11)
//			print_str(680,300, 1, Black, BackColor, "50Amp" , F_GroteskBold16x32);
//	     else
		 fun_print_str(Cursor,11,680,300, 1, TextColor1, BackColor,TextColor2,BackColor2, "50Amp" , F_GroteskBold16x32);


}

void result_before_screen()
{
	//char num[4];
//	GLCD_clear(BackColor);
//	HAL_Delay(10);
    fourth_scr_flag=1;
    test_on_flag=1;
    //enter_num_flag=1;
    Test_selected();

/************************resistance showing ********************************************************/
    print_str(50,200, 1, TextColor1, BackColor, "Select Resistanace Channel:-" , F_GroteskBold16x32);
	if(para[0]==single)
	  print_str(550, 200, 1,Black, BackColor,"Single", F_GroteskBold16x32);

	else if(para[0]==dual)
	  print_str(550, 200, 1, Black, BackColor, "Dual", F_GroteskBold16x32);

	else if(para[0]==all)
	  print_str(550, 200, 1, Black, BackColor, "All", F_GroteskBold16x32);

/********************* Current showing ***********************************/
	print_str(50, 270, 1, TextColor1, BackColor, "Select Test Current:-", F_GroteskBold16x32);

	if(para[1]==onemA)
		print_str(550, 270, 1, Black, BackColor, "1mA", F_GroteskBold16x32);
	else if(para[1]==tenmA)
		print_str(550, 270, 1, Black, BackColor, "10mA", F_GroteskBold16x32);
	else if(para[1]==hundredmA)
		print_str(550, 270, 1, Black, BackColor, "100mA", F_GroteskBold16x32);
	else if(para[1]==oneAmp)
		print_str(550, 270, 1, Black, BackColor, "1A", F_GroteskBold16x32);
	else if(para[1]==fiveAmp)
	    print_str(550, 270, 1, Black, BackColor, "5Amp", F_GroteskBold16x32);
	else if(para[1]==tenAmp)
		print_str(550, 270, 1, Black, BackColor, "10Amp", F_GroteskBold16x32);
	else if(para[1]==twentyfiveAmp)
		print_str(550, 270, 1, Black, BackColor, "25Amp", F_GroteskBold16x32);
	else if(para[1]==fiftyAmp)
		print_str(550, 270, 1, Black, BackColor, "50Amp",F_GroteskBold16x32);


	     print_str(50, 340, 1, TextColor1,BackColor, "Enter Tap No.", F_GroteskBold16x32);
	     print_str(550, 340, 1,TextColor1,BackColor, "00", F_GroteskBold16x32 );
	     print_str(630, 350, 1, Black, BackColor, "(1 to 35)", F_console_font_12x16 );
	     HAL_Delay(10);

     if(num_entered_flag==1)
	 {
		 //sprintf(num,"%d",Tnum);
		 //print_str(550, 340, 1, Cyan, Cyan, "1 to 35", F_GroteskBold16x32);
    	 print_str(630, 350, 1, BackColor, BackColor, "(1 to 35)", F_console_font_12x16 );
		 print_str(550, 340, 1,Black, BackColor, tap_no, F_GroteskBold16x32);
		 enter_num_flag=0;
		// Tnum=0;
	 }

	 bottom_block();
   // HAL_Delay(100);
}

void result_screen()
{
	print_str(150, 170, 1, TextColor1, BackColor, "Test Current     :" , F_GroteskBold16x32);
	print_str(150, 230, 1, TextColor1, BackColor, "Resistance CH1   :" , F_GroteskBold16x32);
	print_str(150, 290, 1, TextColor1, BackColor, "Resistance CH2   :", F_GroteskBold16x32);
	print_str(150, 350, 1, TextColor1,BackColor,  "Resistance CH3   :", F_GroteskBold16x32);

	bottom_block();

	for(int i=0;i<10000000;i++)
	{
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, RESET);
		HAL_Delay(1000);
		get_time();
	}

}

void Test_selected()
{
	if(Dummy_cursor==WindingResistanceTest)
		print_str(245,120, 1,Maroon, BackColor, "Winding Resistance Test", F_GroteskBold16x32);
	else if(Dummy_cursor==HeatRunTest)
		print_str(265,120, 1, Maroon, BackColor, "Heat Run Test" , F_GroteskBold16x32);
	else if(Dummy_cursor==OLTCTest)
	    print_str(275,120, 1,  Maroon, BackColor, "OLTC  Test" , F_GroteskBold16x32);
	else if(Dummy_cursor==DemagnetizingTest)
	    print_str(245,120, 1, Maroon, BackColor, "Demagnetizing Test" , F_GroteskBold16x32);
	else if(Dummy_cursor==DynamicResistanceTest)
	    print_str(245,120, 1, Maroon, BackColor, "Dynamic Resistance Test" , F_GroteskBold16x32);

}

void specification_fun()
{
	HAL_Delay(10);
	GLCD_clear(BackColor);
	test_on_flag=1;
	print_str(150, 150, 1, Blue, BackColor,"Select Voltage:-", F_GroteskBold16x32);
	print_str(450,150, 1,Blue,BackColor,"400000.0",F_GroteskBold16x32);
	print_str(450, 210, 1, Blue, BackColor, "220000.0", F_GroteskBold16x32);

	bottom_block();
}

void Cursor_specification_fun(uint8_t Cursor)
{
	fun_print_str(Cursor,1,450,150, 1, Blue, Cyan, Yellow, Blue,"400000.0", F_GroteskBold16x32);
	fun_print_str(Cursor,2,450,210, 1, Blue, Cyan, Yellow, Blue,"220000.0", F_GroteskBold16x32);
}

void bottom_block()
{
	Draw_H_Line(1,800,60,Black);
	Draw_H_Line(1,800,61,Black);

#ifdef XWRM_10
//	if(show_keyboard_flag==1)
//	{
//
//	}
//	else
       print_str(100,70, 1,Maroon, BackColor, "Winding Resistance Meter Model-XWRM-10A",F_GroteskBold16x32);
#elif defined(XWRM_25)
    print_str(100,70, 1,Black, BackColor, "Winding Resistance Meter Model-XWRM-25A",F_GroteskBold16x32);
#elif defined(XWRM_50)
    print_str(100,70, 1,Black, BackColor, "Winding Resistance Meter Model-XWRM-50A",F_GroteskBold16x32);
#endif


    print_str(10,20,1,TextColor1,BackColor,"Date:",F_GroteskBold16x32);
    	//print_str(90,20,1,Blue,BackColor,date,F_GroteskBold16x32);

    print_str(550,20,1,TextColor1,BackColor,"Time:",F_GroteskBold16x32);
    //show_date_time();

    if(!second_scr_flag && !third_scr_flag){
	Draw_H_Line(1,800,405,Maroon);
	SSD1963_fillScreen_Block(1,410,800,430,Maroon);
	Draw_H_Line(1,800,435,Maroon);
    }
    else if(third_scr_flag)
    {
    	Draw_H_Line(1,800,385,Maroon);
		SSD1963_fillScreen_Block(1,390,800,410,Maroon);
		Draw_H_Line(1,800,415,Maroon);
    }

	if(home_scr_flag)
	   print_str(250,412,1,White,Maroon,"LONG PRESS FOR SELECT/NEXT",F_console_font_12x16);   //for first  screen
	else if(first_scr_flag)
	   print_str(250,412,1,White,Maroon,"LONG PRESS FOR SELECT/NEXT",F_console_font_12x16);
/*	else if(second_scr_flag)
	   print_str(200,412,1,White,Maroon,"Scroll by Up / Down key and Press Enter",F_console_font_12x16);*/
	else if(third_scr_flag)
	   print_str(250,392,1,White,Maroon,"LONG PRESS FOR SELECT/NEXT",F_console_font_12x16);
	else if(fourth_scr_flag)
	   print_str(250,412,1,White,Maroon,"LONG PRESS FOR SELECT/NEXT",F_console_font_12x16);
//	else
//	   print_str(250,412,1,White,Maroon,"LONG PRESS FOR SELECT/NEXT",F_console_font_12x16);



	//SSD1963_fillScreen_Block(200,435, 600, 478,Blue);

	/*Draw_V_Line(200,436,478,Black);
	Draw_V_Line(400,436,478,Black);
	Draw_V_Line(600,436,478,Black);

	if(third_scr_flag==1||fourth_scr_flag==1||show_keyboard_flag==1)
	{
		print_str(70,443,1,Maroon,BackColor,"LEFT",F_Grotesk16x32);
		print_str(660,443, 1,Maroon,BackColor,"RIGHT",F_Grotesk16x32);
	}
    if(!third_scr_flag)
    {
	print_str(270,443,1,Maroon,BackColor,"UP",F_Grotesk16x32);
	print_str(445,443, 1,Maroon,BackColor,"DOWN",F_Grotesk16x32);
    }*/
}

void view_report_screen()
{
	//1 sr.no.     2 date      3 test name     4
}
