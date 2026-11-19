#ifndef _UI_FIELD_H_
#define _UI_FIELD_H_

#include "UIFramework/BasicDatas/GUIPoint.h"
#include "UIFramework/SimpleBaseClasses/GUIWindow.h"
#include "View.h"
#include "System/Console/Trace.h"

class UIField {
public:
	UIField(GUIPoint &position) ;
	virtual ~UIField() ;
	virtual void Draw(GUIWindow &w,int offset=0)=0 ;
	virtual void OnClick()=0 ; // A depressed
	virtual void ProcessArrow(unsigned short mask)=0 ;
	virtual void OnBClick() {} ; // B depressed
	virtual void ProcessBArrow(unsigned short mask) {} ;
	void SetFocus() ;
	void ClearFocus() ;
	bool HasFocus() ;
	void SetPosition(GUIPoint &) ;
	GUIPoint GetPosition() ;
	GUIColor GetColor() ;

	virtual bool IsStatic() ;

protected:
	// Draw "label + value": the label (text before the first format specifier)
	// in the accent colour, the value in normal. Focused fields highlight whole.
	static void drawLabelValue(GUIWindow &w,const char *buffer,const char *format,
	                           GUIPoint &position,bool focused) ;
	int x_ ;
	int y_ ;
	bool focus_ ;
} ;
#endif

