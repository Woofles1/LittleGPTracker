
#include "UINoteVarField.h"
#include "Application/Utils/char.h"
#include "Application/AppWindow.h"

UINoteVarField::UINoteVarField(GUIPoint &position,Variable &v,const char *format,int min,int max,int xOffset,int yOffset)
               :UIIntVarField(position,v,format,min,max,xOffset,yOffset) {
} ;

void UINoteVarField::Draw(GUIWindow &w,int offset) {


	GUITextProperties props ;
	GUIPoint position=GetPosition() ;
	position._y+=offset ;

	char buffer[80] ;
	char note[5] ;

	unsigned char pitch=src_.GetInt() ;
	note2char(pitch,note) ;
	note[4]=0 ;
	sprintf(buffer,format_,note) ;
	drawLabelValue(w,buffer,format_,position,focus_) ;
} ;
