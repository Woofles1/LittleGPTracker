#include "UIStaticField.h"
#include "Application/AppWindow.h"

UIStaticField::UIStaticField(GUIPoint &position,const char *string):UIField(position) {
	string_=string ;
} ;

void UIStaticField::Draw(GUIWindow &w,int offset) {

	GUITextProperties props ;
	GUIPoint position=GetPosition() ;
	position._y+=offset ;
	
	// Static text is a label/heading -> draw it in the label accent colour
	// so it reads distinctly from the (black) values next to it.
	((AppWindow&)w).SetColor(CD_COL_TITLE) ;
	w.DrawString(string_,position,props) ;
} ;

void UIStaticField::ProcessArrow(unsigned short mask){
} ;

bool UIStaticField::IsStatic() {
	return true ;
} ;
