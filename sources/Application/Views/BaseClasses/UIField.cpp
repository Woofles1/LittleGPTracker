#include "UIField.h"
#include "Application/AppWindow.h"
#include "UIFramework/Framework/GUITextProperties.h"
#include <string.h>

void UIField::drawLabelValue(GUIWindow &w,const char *buffer,const char *format,
                             GUIPoint &position,bool focused) {
	GUITextProperties props ;
	if (focused) {
		((AppWindow&)w).SetColor(CD_HILITE2) ;
		props.invert_=true ;
		w.DrawString(buffer,position,props) ;
		return ;
	}
	int labelLen=0 ;
	const char *pct = format ? strchr(format,'%') : 0 ;
	labelLen = pct ? (int)(pct-format) : (int)strlen(buffer) ;
	int blen=(int)strlen(buffer) ;
	if (labelLen>blen) labelLen=blen ;
	if (labelLen>0) {
		char lab[96] ;
		int n = labelLen>95 ? 95 : labelLen ;
		strncpy(lab,buffer,n) ;
		lab[n]=0 ;
		((AppWindow&)w).SetColor(CD_COL_TITLE) ;
		w.DrawString(lab,position,props) ;
	}
	GUIPoint vpos=position ;
	vpos._x += labelLen ;
	((AppWindow&)w).SetColor(CD_NORMAL) ;
	w.DrawString(buffer+labelLen,vpos,props) ;
}

UIField::UIField(GUIPoint &position) {
    x_=position._x ;
    y_=position._y ;
    focus_=false ;
} ;

UIField::~UIField() {
} ;

GUIPoint UIField::GetPosition() {
	GUIPoint point (x_,y_) ;
	return  point; 
}

void UIField::SetPosition(GUIPoint &p) {
	x_=p._x ;
	y_=p._y ;
} ;

void UIField::ClearFocus() {
	focus_=false ;
} ;

void UIField::SetFocus() {
	focus_=true ;
} ;

bool UIField::HasFocus() {
	return focus_;
} ;

bool UIField::IsStatic() {
	return false ;
} ;
