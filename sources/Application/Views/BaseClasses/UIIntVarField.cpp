#include "UIIntVarField.h"


#include "UIIntVarField.h"
#include "UIFramework/Interfaces/I_GUIGraphics.h"
#include "System/Console/Trace.h"
#include "Application/AppWindow.h"
#include <string.h>

#define abs(x) (x<0?-x:x)

UIIntVarField::UIIntVarField(
  GUIPoint &position,
  Variable &v,
  const char *format,
  int min,
  int max,
  int xOffset,
  int yOffset,
  int displayOffset)
:UIField(position)
,src_(v) 
{
	format_=format ;
	min_=min ;
	max_=max ;
	xOffset_=xOffset ;
	yOffset_=yOffset ;
  displayOffset_ = displayOffset;
} ;

void UIIntVarField::Draw(GUIWindow &w,int offset) {

	GUITextProperties props ;
	GUIPoint position=GetPosition() ;
	position._y+=offset ;

	// Build the "label + value" string first
	Variable::Type type=src_.GetType() ;
	char buffer[80] ;
	switch (type) {
		case Variable::INT:
			{
			int ivalue=src_.GetInt()+displayOffset_ ;
			sprintf(buffer,format_,ivalue,ivalue) ;
			}
			break ;
		case Variable::CHAR_LIST:
		case Variable::BOOL:
			{
			const char *cvalue=src_.GetString() ;
			sprintf(buffer,format_,cvalue) ;
			}
			break ;

		default:
			strcpy(buffer,"++wtf++");
	}

	if (focus_) {
		// Focused field: highlight the whole thing as before
		((AppWindow&)w).SetColor(CD_HILITE2) ;
		props.invert_=true ;
		w.DrawString(buffer,position,props) ;
	} else {
		// Unfocused: draw the label (text before the value, i.e. up to the
		// first format specifier) in the accent colour, the value in normal,
		// so the subject reads apart from its number.
		int labelLen=0 ;
		const char *pct=strchr(format_,'%') ;
		labelLen = pct ? (int)(pct-format_) : (int)strlen(buffer) ;
		int blen=(int)strlen(buffer) ;
		if (labelLen>blen) labelLen=blen ;
		if (labelLen>0) {
			char lab[80] ;
			strncpy(lab,buffer,labelLen) ;
			lab[labelLen]=0 ;
			((AppWindow&)w).SetColor(CD_COL_TITLE) ;
			w.DrawString(lab,position,props) ;
		}
		GUIPoint vpos=position ;
		vpos._x+=labelLen ;
		((AppWindow&)w).SetColor(CD_NORMAL) ;
		w.DrawString(buffer+labelLen,vpos,props) ;
	}
} ;

void UIIntVarField::ProcessArrow(unsigned short mask) {
	int value=src_.GetInt() ;

	switch(mask) {
		case EPBM_UP:
			value+=yOffset_ ;
			break ;
		case EPBM_DOWN:
			value-=yOffset_ ;
			break ;
		case EPBM_LEFT:
			value-=xOffset_ ;
			break ;
  		case EPBM_RIGHT:
			value+=xOffset_ ;
			break ;
	} ;
	if (value<min_) {
		value=min_ ;
	} ;
	if (value>max_) {
		value=max_ ;
	}
	
	src_.SetInt(value) ;
} ;

FourCC UIIntVarField::GetVariableID() {
    return src_.GetID() ;
} ;

Variable &UIIntVarField::GetVariable() {
	return src_ ;
} ;
