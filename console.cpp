#include "console.h"

namespace cio{

  Console console; // Global console 
  void Console::display(const char* str, int row, int col, int fieldLen){
    int i;
    console.setPos(row, col);
    if(fieldLen == 0){
      for(i=0;str[i] != 0;i++){
        console.putChar(str[i]);
      }
    }
    else{
      for(i=0;str[i] != 0 && i<fieldLen;i++){
        console.putChar(str[i]);
      }
      for(;i<fieldLen;i++){
        console.putChar(' ');
      }
    }
  }
  int  Console::edit(char *str, int row, int col, int fieldLength, int maxStrLength, 
         bool* insertMode, int* strOffset, int* curPosition,  
         bool IsTextEditor, bool ReadOnly){
    int key = 0;
	////////CUSTOM VARIABLES//////////////
	bool Imode = 0;
	int x;
	int strloc = *strOffset + *curPosition; //current cursor position 
	int len = bio::strlen(str);
	///////////////////////////////////////
	bool done = false;
    while(!done){
      display(str + *strOffset , row, col, fieldLength); 
      setPos(row, col + *curPosition);
      key = getKey();
	  ///////custom/////
	  len = bio::strlen(str);
	  strloc = *strOffset + *curPosition;
	  //////////////////
      switch(key){
	  case RIGHT:
		  if(*curPosition != (fieldLength-1)){
		  (*curPosition)++;
		}
		  else if(*strOffset != maxStrLength){
		  (*strOffset)++;
		}
		break;
      case LEFT:
        if(*curPosition != 0){
          (*curPosition)--;
        }
        else if(*strOffset != 0){
          (*strOffset)--;
        }
        break;
      case HOME:
        *strOffset = *curPosition = 0;
        break;
	  case END:
		  if (len > fieldLength)
		  {
			  *strOffset = len - fieldLength+1;
			  *curPosition = fieldLength-1;
		  }
		  else
		  {
			  *strOffset = 0;
			  *curPosition = len;
		  }
		  
		  
		  break;
      case ESCAPE:
        done = true;
        break;
	  case INSERT:
		  if (Imode == 0){
			  Imode = 1;
		  }
		  else
		  {
			  Imode = 0;
		  }
		  break;
	  case DEL:
		  ///strloc = *strOffset + *curPosition;
		  for (x = strloc; x <= len && x <= maxStrLength; x++)
		  {
			str[x] = str[x+1];
		  }
		  //str[len] = ' ';
		   if ( strloc < len){
					str[len-1] = '\0';
		  }

		  break;
	  case BACKSPACE:
		  //static int strpos = *strOffset + *curPosition;
		  //strloc = *strOffset + *curPosition;
		  
		  for (x = strloc; x < len; x++)
		  {
			  if (strloc != 0)
			  {
				  str[x-1] = str[x];

			  }
		  }
		  if ( strloc <= len){
					str[len-1] = '\0';
		  }
				  //str[len+1] = 'x';

		  if(*curPosition != 0){
					(*curPosition)--;
			}
		  else if(*strOffset != 0){
					(*strOffset)--;
			}
		  break;
	  default:
		  //if (key >= 32 && key >= 126)
		//  {
		  if (len < strloc && strloc < maxStrLength)
		  {
			  for (x = len; x < strloc; x++)
			  {
				  str[x] = ' ';
			  }
		  }		  
		  if (Imode == 0)
		  {
			  //str[strloc]=key;
			  if (strloc < maxStrLength)
			  {
			  for (x = (len+1); x > strloc; x--)
			  {
				  str[x] = str[x-1];
				  str[len+1]='\0';
			  }
			  str[strloc]=key;
			  if(*curPosition != (fieldLength-1)){
						(*curPosition)++;
					}
					else if(*strOffset != maxStrLength){
						(*strOffset)++;
					}
			  }
		  }
		  else
		  {
			  //str[strloc]=key;
				if (strloc < maxStrLength)
				{
					str[strloc]=key;
				    str[strloc+1]='\0';
					if(*curPosition != (fieldLength-1)){
						(*curPosition)++;
					}
					else if(*strOffset != maxStrLength){
						(*strOffset)++;
					}
				}
			}
		  break;
		  }
    }
    return key;
  }
  
	Console& operator<<(Console& cn, const char* str){
    int i;  
    for(i=0;str[i] != 0;i++){
      cn.putChar(str[i]);
    }
    return cn;
  }






};