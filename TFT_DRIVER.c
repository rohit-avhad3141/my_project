/*
 * TFT_DRIVER.c
 *
 *  Created on: Mar 28, 2024
 *      Author: RnD
 */


/*
 * TFT_Drivers.c
 *
 *  Created on: Feb 22, 2021
 *      Author: RnD
 */

#include "main.h"

unsigned int  asciisize = 16, Add_X_Pos = 16;

void TFT_set_display_address_window(signed int xs, signed int ys, signed int xe, signed int ye)
{
//    wr_reg(0x0044, (xs + (xe << 8)));
//    wr_reg(0x0045, ys);
//    wr_reg(0x0046, ye);
//    TFT_set_cursor(xs, ys);
}

void TFT_set_cursor(signed int x_pos, signed int y_pos,signed int X_pos,signed int Y_pos)
{


	uint16_t start_x = x_pos;
	uint16_t end_x   = X_pos;
	uint16_t start_y = y_pos;
	uint16_t end_y   = Y_pos;

	Write_Command(0x2A);
	//nCS_LOW;
	Write_Data(start_x>>8);
	Write_Data(start_x);
	Write_Data(end_x>>8);
	Write_Data(end_x);
	//nCS_HIGH;
	Write_Command(0x2B);
	//nCS_LOW;
	Write_Data(start_y>>8);
	Write_Data(start_y);
	Write_Data(end_y>>8);
	Write_Data(end_y);
	//nCS_HIGH;

	Write_Command(0x2C);
}


void TFT_fill(unsigned int colour)
{
//    unsigned long index = (MAX_X * MAX_Y);
//
//    CS_Low;
//    TFT_set_display_address_window(0, 0, 239, 319);
//    Write_Data(colour);//TFT_write(colour, DAT);
//
//    while(index)
//    {
//    	WR_Low;
//        WR_HIGH;
//       index--;
//    };
//
//    CS_HIGH;
}


unsigned int TFT_BGR2RGB(unsigned int colour)
{
     unsigned int r = 0x0000;
     unsigned int g = 0x0000;
     unsigned int b = 0x0000;
     unsigned int rgb_colour = 0x0000;

     b = ((colour >> 0)  & 0x1F);
     g = ((colour >> 5)  & 0x3F);
     r = ((colour >> 11) & 0x1F);

     rgb_colour = ((b << 11) + (g << 5) + r);

     return rgb_colour;
}


unsigned int RGB565_converter(unsigned char r, unsigned char g, unsigned char b)
{
    return (((((unsigned int)r) >> 3) << 11) | ((((unsigned int)g) >> 2) << 5) | (((unsigned int)b) >> 3));
}


void swap(signed int *a, signed int *b)
{
    signed int temp = 0x0000;

    temp = *b;
    *b = *a;
    *a = temp;
}

void Draw_Pixel(signed int x_pos, signed int y_pos, unsigned int colour)
{
    if((x_pos >= MAX_X) || (y_pos >= MAX_Y) || (x_pos < 0) || (y_pos < 0))
    {
        return;
    }

    CS_LOW;
    TFT_set_cursor(x_pos , y_pos,x_pos , y_pos);
    Write_Data(colour);//TFT_write(colour, DAT);
    CS_HIGH;
}

void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour)
{
    signed int dx = 0x0000;
    signed int dy = 0x0000;
    signed int stepx = 0x0000;
    signed int stepy = 0x0000;
    signed int fraction = 0x0000;

    dy = (y2 - y1);
    dx = (x2 - x1);

    if(dy < 0)
    {
        dy = -dy;
        stepy = -1;
    }
    else
    {
        stepy = 1;
    }

    if(dx < 0)
    {
        dx = -dx;
        stepx = -1;
    }
    else
    {
        stepx = 1;
    }

    dx <<= 0x01;
    dy <<= 0x01;

    Draw_Pixel(x1, y1, colour);

    if(dx > dy)
    {
        fraction = (dy - (dx >> 1));
        while(x1 != x2)
        {
            if(fraction >= 0)
            {
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;

            Draw_Pixel(x1, y1, colour);
        }
    }
    else
    {
        fraction = (dx - (dy >> 1));

        while(y1 != y2)
        {
            if (fraction >= 0)
            {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;
            Draw_Pixel(x1, y1, colour);
        }
    }

//    for(x1;x1<x2;x1++)
//    {
//    	if(y2>y1)
//    	{
//    		Draw_Pixel(x1,y2,Black);
//    		y2--;
//    	}
//    }
}


void Draw_V_Line(signed int x1, signed int y1, signed int y2, unsigned colour)
{
//    signed int pos = 0;
//    signed int temp = 0;

    if(y1 > y2)
    {
       swap(&y1, &y2);
    }

    while(y2 > (y1 - 1))
    {
        Draw_Pixel(x1, y2, colour);
        y2--;
    }

//    for(y2;y2>y1;y2--)
//    {
//    	Draw_Pixel(x1,y2,Black);
//    }

}


void Draw_H_Line(signed int x1, signed int x2, signed int y1, unsigned colour)
{
//    signed int pos = 0;
//    signed int temp = 0;
   // x2=800;
    if(x1 > x2)
    {
       swap(&x1, &x2);
    }

    while(x2 > (x1 - 1))
    {
        Draw_Pixel(x2, y1, colour);
        x2--;
    }

	      //set_cursor(x1,y1)
		  // int size=x2-x1;
//		    for(x2;x2>x1;x2--)
//		    {
//		       Draw_Pixel(x2,y1,Black);
//
//		    }
}


void Draw_Triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned int colour)
{
    signed int a = 0;
    signed int b = 0;
    signed int sa = 0;
    signed int sb = 0;
    signed int yp = 0;
    signed int last = 0;
    signed int dx12 = 0;
    signed int dx23 = 0;
    signed int dx13 = 0;
    signed int dy12 = 0;
    signed int dy23 = 0;
    signed int dy13 = 0;

    switch(fill)
    {
        case YES:
        {
            if(y1 > y2)
            {
                swap(&y1, &y2);
                swap(&x1, &x2);
            }
            if(y2 > y3)
            {
                swap(&y3, &y2);
                swap(&x3, &x2);
            }
            if(y1 > y2)
            {
                swap(&y1, &y2);
                swap(&x1, &x2);
            }

            if(y1 == y3)
            {
                a = b = x1;

                if(x2 < a)
                {
                    a = x2;
                }
                else if(x2 > b)
                {
                    b = x2;
                }
                if(x2 < a)
                {
                    a = x3;
                }
                else if(x3 > b)
                {
                    b = x3;
                }

                Draw_H_Line(a, (a + (b - (a + 1))), y1, colour);
                return;
            }

            dx12 = (x2 - x1);
            dy12 = (y2 - y1);
            dx13 = (x3 - x1);
            dy13 = (y3 - y1);
            dx23 = (x3 - x2);
            dy23 = (y3 - y2);
            sa = 0,
            sb = 0;

            if(y2 == y3)
            {
                last = y2;
            }
            else
            {
                last = (y2 - 1);
            }

            for(yp = y1; yp <= last; yp++)
            {
                a = (x1 + (sa / dy12));
                b = (x1 + (sb / dy13));
                sa += dx12;
                sb += dx13;
                if(a > b)
                {
                    swap(&a, &b);
                }
                Draw_H_Line(a, (a + (b - (a + 1))), yp, colour);
            }

            sa = (dx23 * (yp - y2));
            sb = (dx13 * (yp - y1));
            for(; yp <= y3; yp++)
            {
                a = (x2 + (sa / dy23));
                b = (x1 + (sb / dy13));
                sa += dx23;
                sb += dx13;

                if(a > b)
                {
                    swap(&a, &b);
                }
                Draw_H_Line(a, (a + (b - (a + 1))), yp, colour);
            }


            break;
        }
        default:
        {
            Draw_Line(x1, y1, x2, y2, colour);
            Draw_Line(x2, y2, x3, y3, colour);
            Draw_Line(x3, y3, x1, y1, colour);
            break;
        }
    }
}


void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char type, unsigned int colour, unsigned int back_colour)
{
     signed int i = 0x0000;
     signed int xmin = 0x0000;
     signed int xmax = 0x0000;
     signed int ymin = 0x0000;
     signed int ymax = 0x0000;

     switch(fill)
     {
         case YES:
         {
             if(x1 < x2)
             {
                xmin = x1;
                xmax = x2;
             }
             else
             {
                xmin = x2;
                xmax = x1;
             }

             if(y1 < y2)
             {
                ymin = y1;
                ymax = y2;
             }
             else
             {
                ymin = y2;
                ymax = y1;
             }

             for(; xmin <= xmax; ++xmin)
             {
                 for(i = ymin; i <= ymax; ++i)
                 {
                     Draw_Pixel(xmin, i, colour);
                 }
             }

             break;
         }
         default:
         {
             Draw_V_Line(x1, y1, y2, colour);
             Draw_V_Line(x2, y1, y2, colour);
             Draw_H_Line(x1, x2, y1, colour);
             Draw_H_Line(x1, x2, y2, colour);
             break;
         }
     }

     if(type != SQUARE)
     {
         Draw_Pixel(x1, y1, back_colour);
         Draw_Pixel(x1, y2, back_colour);
         Draw_Pixel(x2, y1, back_colour);
         Draw_Pixel(x2, y2, back_colour);
     }
}


void Draw_H_Bar(signed int x1, signed int x2, signed int y1, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border)
{
    switch(border)
    {
        case YES:
        {
            Draw_Rectangle((x1 + 1), (y1 + 1), (x1 + bar_value), (y1 + bar_width - 1), YES, SQUARE, bar_colour, back_colour);
            Draw_Rectangle((x2 - 1), (y1 + 1), (x1 + bar_value + 1), (y1 + bar_width - 1), YES, SQUARE, back_colour, back_colour);
            Draw_Rectangle(x1, y1, x2, (y1 + bar_width), NO, SQUARE, border_colour, back_colour);
            break;
        }
        default:
        {
            Draw_Rectangle(x1, y1, (x1 + bar_value), (y1 + bar_width), YES, SQUARE, bar_colour, back_colour);
            Draw_Rectangle(x2, y1, (x1 + bar_value), (y1 + bar_width), YES, SQUARE, back_colour, back_colour);
            break;
        }
    }
}


void Draw_V_Bar(signed int x1, signed int y1, signed int y2, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border)
{
    switch(border)
    {
        case YES:
        {
            Draw_Rectangle((x1 + 1), (y2 - 1), (x1 + bar_width - 1), (y2 - bar_value), YES, SQUARE, bar_colour, back_colour);
            Draw_Rectangle((x1 + 1), (y2 - bar_value - 1), (x1 + bar_width - 1), (y1 + 1), YES, SQUARE, back_colour, back_colour);
            Draw_Rectangle(x1, y1, (x1 + bar_width), y2, NO, SQUARE, border_colour, back_colour);
            break;
        }
        default:
        {
            Draw_Rectangle(x1, y2, (x1 + bar_width), (y2 - bar_value), YES, SQUARE, bar_colour, back_colour);
            Draw_Rectangle(x1, (y2 - bar_value), (x1 + bar_width), y1, YES, SQUARE, back_colour, back_colour);
            break;
        }
    }
}


void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned int colour)
{
     signed int a = 0x0000;
     signed int b = 0x0000;
     signed int p = 0x0000;

     b = radius;
     p = (1 - b);

     do
     {
          switch(fill)
          {
              case YES:
              {
                  Draw_Line((xc - a), (yc + b), (xc + a), (yc + b), colour);
                  Draw_Line((xc - a), (yc - b), (xc + a), (yc - b), colour);
                  Draw_Line((xc - b), (yc + a), (xc + b), (yc + a), colour);
                  Draw_Line((xc - b), (yc - a), (xc + b), (yc - a), colour);
                  break;
              }
              default:
              {
                  Draw_Pixel((xc + a), (yc + b), colour);
                  Draw_Pixel((xc + b), (yc + a), colour);
                  Draw_Pixel((xc - a), (yc + b), colour);
                  Draw_Pixel((xc - b), (yc + a), colour);
                  Draw_Pixel((xc + b), (yc - a), colour);
                  Draw_Pixel((xc + a), (yc - b), colour);
                  Draw_Pixel((xc - a), (yc - b), colour);
                  Draw_Pixel((xc - b), (yc - a), colour);
                  break;
              }
          }

          if(p < 0)
          {
              p += (0x03 + (0x02 * a++));
          }
          else
          {
              p += (0x05 + (0x02 * ((a++) - (b--))));
          }
    }while(a <= b);
}


void print_str(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char *ch, unsigned char Sel_font)
{
	while((*ch >= 0x20) && (*ch <= 0x7F))
	{
		print_char(x_pos, y_pos, font_size, colour, back_colour, *ch++ , Sel_font);
		switch(Sel_font)
		{
		case F_ASCII16x24 :
			x_pos += 15;
			break;
		case F_ASCII12x12 :
			x_pos += 11;
			break;
		case F_ASCII8x8 :
			x_pos += 7;
			break;
		case F_ASCII8x12 :
			x_pos += 7;
			break;
		case F_BigFont :
			x_pos += 11;
			break;
		case F_arial_bold :
			x_pos += 11;
			break;
		case F_arial_normal :
			x_pos += 11;
			break;
		case F_Arial_round_16x24 :
			x_pos += 15;
			break;
		case F_GroteskBold16x32 :
			x_pos += 15;
			break;
		case F_GroteskBold24x48 :
			x_pos += 31;
			break;
		case F_GroteskBold32x64 :
			x_pos += 31;
			break;
		case F_Grotesk16x32 :
			x_pos += 15;
			break;
		case F_Grotesk24x48 :
			x_pos += 31;
			break;
		case F_Grotesk32x64 :
			x_pos += 31;
			break;
		case F_console_font_12x16 :
			x_pos += 11;
			break;
		case F_console_font_16x32 :
			x_pos += 15;
			break;
		case F_font10x14 :
			x_pos += 9;
			break;
		case F_Grotesk_1_Bold32x64 :
			x_pos += 31;
			break;
		case F_font16x16 :
			x_pos += 15;
			break;
		case F_fixednums_15x31 :
			x_pos += 29;
			break;
		case F_font16x8 :
			x_pos += 15;
			break;
		case F_GLCDFONTDECL_Callibri11_italic11x12 :
			x_pos += 10;
			break;
		case F_GLCDFONTDEC_LX11fixed7x14 :
			x_pos += 6;
			break;
		case F_GLCDFONTDECL_ZevvPeep8x16 :
			x_pos += 7;
			break;
		case F_GLCDFONTDECL_fixed_bold10x15 :
			x_pos += 9;
			break;
		case F_hallfetica_normal :
			x_pos += 15;
			break;
		case F_arial_italic :
			x_pos += 15;
			break;
		case F_franklingothic_normal :
			x_pos += 13;
			break;
		case F_Sinclair_M :
			x_pos += 13;
			break;
		case F_Ubuntu :
			x_pos += 27;
			break;
		case F_UbuntuBold :
			x_pos += 27;
			break;
		case F_Retro8x16 :
			x_pos += 7;
			break;
		case F_MyFont :
			x_pos += 15;
			break;
//		case F_Font_Six :
//			x_pos+=8;
//			break;
		}
	}

}
void print_char(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch ,  unsigned char Sel_font)
{
     unsigned char i = 0x00, Shift_i = 0;
     unsigned char j = 0x00;
     unsigned int value = 0x0000, value1 = 0, value2 = 0, value3 = 0, value4 = 0, MSB = 0;		//, LSB = 0

     if(font_size <= 0)
     {
         font_size = 1;
     }
     if((x_pos >= MAX_X) || (y_pos > MAX_Y))
     {

     }
     switch(Sel_font)
     {
     case F_ASCII16x24 :
                     x_pos += 16;
                     for(i = 0x00; i < 24; i++)   //5
                     {
                         for(j = 0x00; j < 16; j++)
                         {
                             value = 0x0000;value2 = 0x0000;
                             value = ((ASCII16x24[((unsigned char)ch) - 0x20][i]));
                            for( Shift_i = 0; Shift_i < 16; Shift_i++)
                            {
                                MSB = (value & 0x01);
                                value = (value >> 1);
                                value2 = value2 | (MSB << (15-Shift_i));
                            }
                            value = value2;
//                            test_val  = ((value >> j) & 0x01);
                             if(((value >> j) & 0x01) != 0x00)
                             {
                                 Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                             }
                             else
                             {
                                 Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                             }
                            x_pos -= font_size;
                         }
                            x_pos += ((font_size << 0x04));
                            y_pos++;
                     }
     break;
      case F_ASCII12x12 :
                       x_pos += 16;
                       for(i = 0x00; i < 12; i++)   //5
                       {

                           for(j = 0x00; j < 16; j++)
                           {
                               value = 0x0000;
                               value = ((ASCII12x12[((unsigned char)ch) - 0x20][i]));
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x04));
                              y_pos++;
                       }
     break;

           case F_ASCII8x8 :
                       x_pos += 8;
                       for(i = 0x00; i < 8; i++)   //5
                       {

                           for(j = 0x00; j < 8; j++)
                           {
                               value = 0x0000;
                               value = ((ASCII8x8[((unsigned char)ch) - 0x20][i]));
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x03));
                              y_pos++;
                       }
     break;

     case F_ASCII8x12:
                       x_pos += 8;
                       for(i = 0x02; i < 13; i++)   //5
                       {

                           for(j = 0x00; j < 8; j++)
                           {
                               value = 0x0000;
                               value = ((ASCII8x12[((unsigned char)ch) - 0x20][i]));
                              if( i == 13){value = 0x0000;}
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x03));
                              y_pos++;
                       }
     break;
     case F_console_font_12x16:
                       x_pos += 12;
                       for(i = 0x00; i < 18; i++)   //5
                       {
                           for(j = 0x00; j < 12; j++)
                           {
                        	   value = 0;
                               if(i > 1) {
									value1 = ((console_font_12x16[((unsigned char)ch) - 0x20][(i-2)*2]));
									value2 = ((console_font_12x16[((unsigned char)ch) - 0x20][((i-2)*2)+1]));
									value =( (value1 << 8) | (value2));
									value = (value >> 4);
                               }
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
//                               if(j < 12){
                              x_pos -= font_size;//}
                           }
                              x_pos += ((font_size << 0x04)-4);
                              y_pos++;
                       }
     break;
     case F_BigFont:
                       x_pos += 12;
                       for(i = 0x01; i < 16; i++)   //5
                       {

                           for(j = 0x00; j < 12; j++)
                           {
                               value = 0x0000;
                               value1 = ((BigFont[((unsigned char)ch) - 0x20][i*2]));
                               value2 = ((BigFont[((unsigned char)ch) - 0x20][(i*2)+1]));
                               value =( (value1 << 8) | (value2));
                               value = (value >> 2);
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x04)-4);
                              y_pos++;
                       }
     break;

     case F_arial_bold:
                       x_pos += 12;
                       for(i = 0x00; i < 16; i++)   //5
                       {

                           for(j = 0x00; j < 12; j++)
                           {
                               value = 0x0000;
                               value1 = ((arial_bold[((unsigned char)ch) - 0x20][i*2]));
                               value2 = ((arial_bold[((unsigned char)ch) - 0x20][(i*2)+1]));
                               value =( (value1 << 8) | (value2));
                               value = (value >> 2);
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x04) - 4);
                              y_pos++;
                       }
     break;

     case F_arial_normal:
                       x_pos += 12;
                       for(i = 0x00; i < 16; i++)   //5
                       {

                           for(j = 0x00; j < 12; j++)
                           {
                               value = 0x0000;
                               value1 = ((arial_normal[((unsigned char)ch) - 0x20][i*2]));
                               value2 = ((arial_normal[((unsigned char)ch) - 0x20][(i*2)+1]));
                               value =( (value1 << 8) | (value2));
                                value = (value >> 2);
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x04) - 4);
                              y_pos++;
                       }
     break;

     case F_Arial_round_16x24:
                       x_pos += 16;
                       for(i = 0x00; i < 24; i++)   //5
                       {

                           for(j = 0x00; j < 16; j++)
                           {
                               value = 0x0000;
                               value1 = ((Arial_round_16x24[((unsigned char)ch) - 0x20][i*2]));
                               value2 = ((Arial_round_16x24[((unsigned char)ch) - 0x20][(i*2)+1]));
                               value =( (value1 << 8) | (value2));
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x04));
                              y_pos++;
                       }
     break;
     case F_GroteskBold16x32:
                       x_pos += 16;
                       for(i = 0x00; i < 32; i++)   //5
                       {

                           for(j = 0x00; j < 16; j++)
                           {
                               value = 0x0000;
                               value1 = ((GroteskBold16x32[((unsigned char)ch) - 0x20][i*2]));
                               value2 = ((GroteskBold16x32[((unsigned char)ch) - 0x20][(i*2)+1]));
                               value =( (value1 << 8) | (value2));
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x04));
                              y_pos++;
                       }
     break;
     case F_GroteskBold24x48:
                       x_pos += 32;
                       for(i = 0x00; i < 48; i++)   //5
                       {

                           for(j = 0x00; j < 32; j++)
                           {
                               value = 0x0000;value1= 0;value2 = 0;value3  = 0;
                               value1 = ((GroteskBold24x48[(((unsigned char)ch) - 0x20)][(i * 3)]));
                               value2 = ((GroteskBold24x48[(((unsigned char)ch) - 0x20)][(i * 3) + 1]));
                               value3 = ((GroteskBold24x48[(((unsigned char)ch) - 0x20)][(i * 3) + 2]));
                               value =( (value1 << 16) | (value2 << 8) | (value3));
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x05) );
                              y_pos++;
                       }
     break;
     case F_GroteskBold32x64:
                       x_pos += 32;
                       for(i = 0x00; i < 64; i++)   //5
                       {

                           for(j = 0x00; j < 32; j++)
                           {
                               value = 0x0000;value1= 0;value2 = 0;value3  = 0;
                               value1 = ((GroteskBold32x64[(((unsigned char)ch) - 0x20)][(i * 4)]));
                               value2 = ((GroteskBold32x64[(((unsigned char)ch) - 0x20)][(i * 4) + 1]));
                               value3 = ((GroteskBold32x64[(((unsigned char)ch) - 0x20)][(i * 4) + 2]));
                               value4 = ((GroteskBold32x64[(((unsigned char)ch) - 0x20)][(i * 4) + 3]));
                               value = ( (value1 << 24) | (value2 << 16) | (value3 << 8) | (value4));
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x05) );
                              y_pos++;
                       }
     break;
     case F_Grotesk16x32:
                       x_pos += 16;
                       for(i = 0x00; i < 32; i++)   //5
                       {

                           for(j = 0x00; j < 16; j++)
                           {
                               value = 0x0000;
                               value1 = ((Grotesk16x32[((unsigned char)ch) - 0x20][i*2]));
                               value2 = ((Grotesk16x32[((unsigned char)ch) - 0x20][(i*2)+1]));
                               value =( (value1 << 8) | (value2));
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x04));
                              y_pos++;
                       }
     break;
     case F_Grotesk24x48:
                       x_pos += 32;
                       for(i = 0x00; i < 48; i++)   //5
                       {

                           for(j = 0x00; j < 32; j++)
                           {
                               value = 0x0000;value1= 0;value2 = 0;value3  = 0;
                               value1 = ((Grotesk24x48[(((unsigned char)ch) - 0x20)][(i * 3)]));
                               value2 = ((Grotesk24x48[(((unsigned char)ch) - 0x20)][(i * 3) + 1]));
                               value3 = ((Grotesk24x48[(((unsigned char)ch) - 0x20)][(i * 3) + 2]));
                               value =( (value1 << 16) | (value2 << 8) | (value3));
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x05) );
                              y_pos++;
                       }
     break;
      case F_Grotesk32x64:
                       x_pos += 32;
                       for(i = 0x00; i < 64; i++)   //5
                       {

                           for(j = 0x00; j < 32; j++)
                           {
                               value = 0x0000;value1= 0;value2 = 0;value3  = 0;
                               value1 = ((Grotesk32x64[(((unsigned char)ch) - 0x20)][(i * 4)]));
                               value2 = ((Grotesk32x64[(((unsigned char)ch) - 0x20)][(i * 4) + 1]));
                               value3 = ((Grotesk32x64[(((unsigned char)ch) - 0x20)][(i * 4) + 2]));
                               value4 = ((Grotesk32x64[(((unsigned char)ch) - 0x20)][(i * 4) + 3]));
                               value = ( (value1 << 24) | (value2 << 16) | (value3 << 8) | (value4));
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x05) );
                              y_pos++;
                       }
     break;
     case F_console_font_16x32:
                       x_pos += 16;
                       for(i = 0x00; i < 32; i++)   //5
                       {

                           for(j = 0x00; j < 16; j++)
                           {
                               value = 0x0000;
                               value1 = ((console_font_16x32[((unsigned char)ch) - 0x20][i*2]));
                               value2 = ((console_font_16x32[((unsigned char)ch) - 0x20][(i*2)+1]));
                               value =( (value1 << 8) | (value2));
//                               test_val  = ((value >> j) & 0x01);
                               if(((value >> j) & 0x01) != 0x00)
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
                               }
                               else
                               {
                                   Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
                               }
                              x_pos -= font_size;
                           }
                              x_pos += ((font_size << 0x04));
                              y_pos++;
                       }
     break;
//     case F_Font_Six:
//                           x_pos += 8;
//                           for(i = 0x00; i < 10; i++)   //5
//                           {
//
//                               for(j = 0x00; j < 8; j++)
//                               {
//                                   value = 0x0000;
//                                   value = ((Font_Six[((unsigned char)ch) - 0x20][i]));
//    //                               test_val  = ((value >> j) & 0x01);
//                                   if(((value >> j) & 0x01) != 0x00)
//                                   {
//                                       Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
//                                   }
//                                   else
//                                   {
//                                       Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
//                                   }
//                                  x_pos -= font_size;
//                               }
//                                  x_pos += ((font_size << 0x03));
//                                  y_pos++;
//                           }
//         break;
     }
}

void Draw_Font_Pixel(unsigned int x_pos, unsigned int y_pos, unsigned int colour, unsigned char pixel_size)
{
	unsigned int i = 0x0000;
	CS_LOW;
	TFT_set_cursor(x_pos, y_pos,x_pos,y_pos);
	//     TFT_set_cursor(x_pos, y_pos);
	for(i = 0x0000; i < (pixel_size * pixel_size); i++)
	{
		Write_Data(colour);// TFT_write(colour, DAT);
	}

	CS_HIGH;

}

void print_C(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value, unsigned char Sel_font)
{
      char ch[4] = {0x20, 0x20, 0x20, 0x20};


     if((value > 99) && (value <= 999))
     {
         ch[1] = ((value / 100) + 0x30);
         ch[2] = (((value % 100) / 10) + 0x30);
         ch[3] = ((value % 10) + 0x30);
     }
     else if((value > 9) && (value <= 99))
     {
         ch[1] = (((value % 100) / 10) + 0x30);
         ch[2] = ((value % 10) + 0x30);
         ch[3] = 0x00;
     }
     else if((value >= 0) && (value <= 9))
     {
         ch[1] = ((value % 10) + 0x30);
         ch[2] = 0x00;
         ch[3] = 0x00;
     }

     print_str(x_pos, y_pos, font_size, colour, back_colour, ch, Sel_font);
}


void print_I(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed long value,  unsigned char Sel_font)
{
     char ch[6] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20};

//    if(value < 0)
//    {
//        ch[0] = 0x2D;
//        value = -value;
//    }
//    else
//    {
//        ch[0] = 0x20;
//    }

    if(value > 9999)
    {
        ch[0] = ((value / 10000) + 0x30);
        ch[1] = (((value % 10000)/ 1000) + 0x30);
        ch[2] = (((value % 1000) / 100) + 0x30);
        ch[3] = (((value % 100) / 10) + 0x30);
        ch[4] = ((value % 10) + 0x30);
    }

    else if((value > 999) && (value <= 9999))
    {
        ch[0] = (((value % 10000)/ 1000) + 0x30);
        ch[1] = (((value % 1000) / 100) + 0x30);
        ch[2] = (((value % 100) / 10) + 0x30);
        ch[3] = ((value % 10) + 0x30);
        ch[4] = 0x00;
    }
    else if((value > 99) && (value <= 999))
    {
        ch[0] = (((value % 1000) / 100) + 0x30);
        ch[1] = (((value % 100) / 10) + 0x30);
        ch[2] = ((value % 10) + 0x30);
        ch[3] = 0x00;
        ch[4] = 0x00;
    }
    else if((value > 9) && (value <= 99))
    {
        ch[0] = (((value % 100) / 10) + 0x30);
        ch[1] = ((value % 10) + 0x30);
        ch[2] = 0x00;
        ch[3] = 0x00;
        ch[4] = 0x00;
    }
    else
    {
        ch[0] = ((value % 10) + 0x30);
        ch[1] = 0x00;
        ch[2] = 0x00;
        ch[3] = 0x00;
        ch[4] = 0x00;
    }

    print_str(x_pos, y_pos, font_size, colour, back_colour, ch , Sel_font);
}


void print_D(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value, unsigned char points,  unsigned char Sel_font)
{
    char ch[5] = {0x2E, 0x20, 0x20, 0x20, 0x20};

    ch[1] = ((value / 1000) + 0x30);

    if(points > 1)
    {
        ch[2] = (((value % 1000) / 100) + 0x30);

        if(points > 2)
        {
            ch[3] = (((value % 100) / 10) + 0x30);

            if(points > 3)
            {
                ch[4] = ((value % 10) + 0x30);
            }
            else{
//                 ch[2] = 0x00;
//                 ch[3] = 0x00;
                 ch[4] = 0x00;
            }
        }
        else{
//         ch[2] = 0x00;
         ch[3] = 0x00;
         ch[4] = 0x00;
    }
    }
    else{
         ch[2] = 0x00;
         ch[3] = 0x00;
         ch[4] = 0x00;
    }

    print_str(x_pos, y_pos, font_size, colour, back_colour, ch , Sel_font);
}

void Draw_HV_Line(unsigned int x_pos, unsigned int y_pos,unsigned int x1_pos, unsigned int y1_pos,unsigned int colour, unsigned int back_colour){

}
void print_F(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, float value, unsigned char points ,  unsigned char Sel_font)
{
    signed long tmp = 0x0000;

    unsigned char Int_Dgt = 0;
    tmp = value;
   if(tmp < 10){
    Int_Dgt = 1;
   }
   else if((tmp >= 10) && (tmp < 100)){
    Int_Dgt = 2;
   }
   else if((tmp >= 100) && (tmp < 1000)){
    Int_Dgt = 3;
   }
    print_I(x_pos, y_pos, font_size, colour, back_colour, tmp , Sel_font);
   tmp = ((value - tmp+0.0005) * 10000);
        switch(Sel_font)
        {
          case F_ASCII16x24 :
//                          x_pos += 16;
                          Add_X_Pos = 16 + 16*Int_Dgt;
                          break;
          case F_ASCII12x12 :
//                          x_pos += 12;
                          Add_X_Pos = 12 + 12*Int_Dgt;
                          break;
          case F_ASCII8x8 :
//                          x_pos += 8;
                            Add_X_Pos =   8*Int_Dgt;
                          break;
          case F_ASCII8x12 :
//                          x_pos += 8;
                          Add_X_Pos =   8*Int_Dgt;
                          break;
          case F_BigFont :
//                          x_pos += 12;
                          Add_X_Pos =  12*Int_Dgt;
                          break;
          case F_arial_bold :
//                          x_pos += 12;
                          Add_X_Pos =   12*Int_Dgt;
                          break;
          case F_arial_normal :
//                          x_pos += 12;
                          Add_X_Pos =  12*Int_Dgt;
                          break;
          case F_Arial_round_16x24 :
//                          x_pos += 16;
                          Add_X_Pos =  16*Int_Dgt;
                          break;
          case F_GroteskBold16x32 :
//                          x_pos += 16;
                          Add_X_Pos =   16*Int_Dgt;
                          break;
          case F_GroteskBold24x48 :
//                          x_pos += 32;
                          Add_X_Pos =  32*Int_Dgt;
                          break;
          case F_GroteskBold32x64 :
//                          x_pos += 32;
                          Add_X_Pos = 32*Int_Dgt;
                          break;
          case F_Grotesk16x32 :
//                          x_pos += 16;
                          Add_X_Pos =  16*Int_Dgt;
                          break;
          case F_Grotesk24x48 :
//                          x_pos += 32;
                          Add_X_Pos =   32*Int_Dgt;
                          break;
          case F_Grotesk32x64 :
//                          x_pos += 32;
                          Add_X_Pos =  32*Int_Dgt;
                          break;
          case F_console_font_12x16 :
//                          x_pos += 12;
                          Add_X_Pos =  12*Int_Dgt;
                          break;
        }
    if(tmp < 0)
    {
       tmp = -tmp;
    }

    if((value >= 10000) && (value < 100000))
    {
        print_D((x_pos + Add_X_Pos), y_pos, font_size, colour, back_colour, tmp, points , Sel_font);
    }
    else if((value >= 1000) && (value < 10000))
    {
        print_D((x_pos + Add_X_Pos), y_pos, font_size, colour, back_colour, tmp, points , Sel_font);
    }
    else if((value >= 100) && (value < 1000))
    {
        print_D((x_pos + Add_X_Pos), y_pos, font_size, colour, back_colour, tmp, points ,Sel_font);
    }
    else if((value >= 10) && (value < 100))
    {
        print_D((x_pos + Add_X_Pos), y_pos, font_size, colour, back_colour, tmp, points ,  Sel_font);//18
    }
    else if(value < 10)
    {
        print_D((x_pos + Add_X_Pos), y_pos, font_size, colour, back_colour, tmp, points , Sel_font);

    }
}


void Draw_BMP(unsigned int x_pos, unsigned int y_pos, signed int W, signed int H, const unsigned short *bitmap) // int
{
     signed int xp = 0;
     signed int yp = (y_pos + H);
     unsigned long index = 0;

     CS_LOW;

     while(yp > y_pos)
     {
         for(xp = x_pos; xp < (x_pos + W); xp++)
         {
            Draw_Pixel(xp, yp, bitmap[index]);
             if(yp > y_pos+1){
              index++;
            }
           //HAL_Delay(10);
         }
         yp--;

     }

     CS_HIGH;
}


void LCD_StringLine(unsigned int PosX, unsigned int PosY, unsigned char *str)
{
//	unsigned char  TempChar;
//
//	do
//	{
//		TempChar = *str++;
//		LCD_PutChar(PosX, PosY, TempChar);
//		if (PosX < 232)
//		{
//                  PosX += 8;
//                  if(asciisize==24)
//                  {
//                    PosX+=8;
//                  }
//                  else if(asciisize==14)
//                  {
//                   PosX+=4;
//                  }
//		}
//
//		else if (PosY < 304)
//		{
//
//			PosX = 0;
//			PosY += 16;
//		}
//		else
//		{
//			PosX = 0;
//			PosY = 0;
//		}
//	}
//	while (*str != 0);
}
void LCD_PutChar(unsigned int PosX, unsigned int PosY, char c)
{
//  unsigned char i = 0;
//   unsigned char j = 0;
//  if(asciisize==8)
//  {
//   unsigned char  Buffer[8];
//   unsigned char TmpChar = 0;
//
//    GetASCIICode1(Buffer,c);
//	for (i=0;i<8;i++)
//	{
//		TmpChar = Buffer[i];
//		for (j=0;j<8;j++)
//		{
//			if ( ((TmpChar >> (7-j)) & 0x01) == 0x01)
//			{
//                          Pixel(PosX +j, PosY + i, TextColor1);
//			}
//			else
//			{
//			Pixel(PosX + j, PosY + i, BackColor);
//			}
//		}
//	}
//  }
//  //----------------------------------------------------------------------------
//    if(asciisize==12)
//  {
//   unsigned char Buffer[12];
//   unsigned char TmpChar = 0;
//
//    GetASCIICode2(Buffer,c);
//	for (i=0;i<12;i++)
//	{
//		TmpChar = Buffer[i];
//		for (j=0;j<8;j++)
//		{
//			if ( ((TmpChar >> (7-j)) & 0x01) == 0x01)
//			{
//                          Pixel(PosX +j, PosY + i, TextColor1);
//			}
//			else
//			{
//			Pixel(PosX + j, PosY + i, BackColor);
//			}
//		}
//	}
//  }
//  //----------------------------------------------------------------------------
//    if(asciisize==16)
//  {
//  unsigned char Buffer[16];
//   unsigned char TmpChar = 0;
//
//    GetASCIICode4(Buffer,c);
//	for (i=0;i<16;i++)
//	{
//		TmpChar = Buffer[i];
//		for (j=0;j<8;j++)
//		{
//			if ( ((TmpChar >> (7-j)) & 0x01) == 0x01)
//			{
//                          Pixel(PosX +j, PosY + i, TextColor1);
//			}
//			else
//			{
//			Pixel(PosX + j, PosY + i, BackColor);
//			}
//		}
//	}
//  }
//  //----------------------------------------------------------------------------
//      if(asciisize==14)
//  {
//  short int  Buffer[12];
//   unsigned int TmpChar = 0;
//
//    GetASCIICode3(Buffer,c);
//	for (i=0;i<12;i++)
//	{
//		TmpChar = Buffer[i];
//		for (j=0;j<12;j++)
//		{
//                        if ( ((TmpChar >> j ) & (0x01)) == 0x01)
//			{
//                          Pixel(PosX +j, PosY + i, TextColor1);
//			}
//			else
//			{
//			Pixel(PosX + j, PosY + i, BackColor);
//			}
//		}
//	}
//  }
//  //----------------------------------------------------------------------------
//      if(asciisize==24)
//  {
//  short int  Buffer[24];
//   unsigned int TmpChar = 0;
//    GetASCIICode5(Buffer,c);
//	for (i=0;i<24;i++)
//	{
//		TmpChar = Buffer[i];
//		for (j=0;j<16;j++)
//		{
//			if (( (TmpChar >>j)&(0x01)) == 0x01)
//			{
//                          Pixel(PosX +j, PosY + i, TextColor1);
//			}
//			else
//			{
//			Pixel(PosX + j, PosY + i, BackColor);
//			}
//		}
//	}
//  }
//  //----------------------------------------------------------------------------
}


void Pixel(unsigned int x, unsigned int y,unsigned int c)
{
        if (( x > 239 )||( y > 319 )) return;
	LCD_SetCursor(x,y);
	Write_Command(0x22);
	Write_Data(c);
}
void LCD_SetCursor(unsigned int Xpos, unsigned int Ypos)
{
	Write_Reg(0x4E, Xpos);
	Write_Reg(0x4F, Ypos);
}
void Write_Reg(unsigned char reg, unsigned short val)
{
	Write_Command(reg);
	Write_Data(val);
}

void Selec_Clear_Disply(unsigned short X1 ,unsigned short X2 ,unsigned short Y1 ,unsigned short Y2 ,unsigned int Color)
{
    int i,j;
     TFT_set_cursor(X1, Y1,X1,Y1);
//    wr_reg(0x004f,X1);        //Set GDDRAM X	address counter
//    wr_reg(0x004e,Y1);        //Set GDDRAM Y	address counter
//    wr_cmd(0x22);
    for(j=Y1;j<Y2;j++)
        for(i=X1;i<X2;i++){

        TFT_set_cursor(i, j,i,j);
        Write_Data(Color);
        }
}
/*******************************************************************************
* Clear display                                                                *
*   Parameter:    color:  color for clearing display                           *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_clear(unsigned short color)
{
	TFT_set_cursor(0,0,DISP_HOR_RESOLUTION,DISP_VER_RESOLUTION);
//	for(i = 0; i < (DISP_HOR_RESOLUTION*DISP_VER_RESOLUTION); i++)
//	{
//		Write_Data(color);
//	}
	uint16_t i,j;
	for(i=0;i<DISP_HOR_RESOLUTION;i++){
		for (j=0;j<DISP_VER_RESOLUTION;j++){
			Write_Data(color);
		}
	}
}
void SSD1963_fillScreen(short color)
{

	uint16_t start_x = 0;
	uint16_t end_x   = 800;//480;
	uint16_t start_y = 0;
	uint16_t end_y   = 480;//272;

	Write_Command(0x2A);
	//nCS_LOW;
	Write_Data(start_x>>8);
	Write_Data(start_x);
	Write_Data(end_x>>8);
	Write_Data(end_x);
	//nCS_HIGH;
	Write_Command(0x2B);
	//nCS_LOW;
	Write_Data(start_y>>8);
	Write_Data(start_y);
	Write_Data(end_y>>8);
	Write_Data(end_y);
	//nCS_HIGH;

	Write_Command(0x2C);

	uint16_t i,j;
	for(i=0;i<DISP_HOR_RESOLUTION;i++){
		for (j=0;j<DISP_VER_RESOLUTION;j++){
			Write_Data(color);
		}
	}
}

void SSD1963_fillScreen_Block(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,short color)
	{

		uint16_t start_x =x1;
		uint16_t end_x   =x2;//480;
		uint16_t start_y =y1;
		uint16_t end_y   =y2;//272;

		Write_Command(0x2A);
		//nCS_LOW;
		Write_Data(start_x>>8);
		Write_Data(start_x);
		Write_Data(end_x>>8);
		Write_Data(end_x);
		//nCS_HIGH;
		Write_Command(0x2B);
		//nCS_LOW;
		Write_Data(start_y>>8);
		Write_Data(start_y);
		Write_Data(end_y>>8);
		Write_Data(end_y);
		//nCS_HIGH;

		Write_Command(0x2C);

		uint16_t i,j;
		for(i=0;i<DISP_HOR_RESOLUTION;i++){
			for (j=0;j<DISP_VER_RESOLUTION;j++){
				Write_Data(color);
			}
		}
	}

