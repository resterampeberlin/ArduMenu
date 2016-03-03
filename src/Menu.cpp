//! 
//! class constructor for "back" menu item
//!
MenuItem::MenuItem() {
	id = BACK_MENUITEM;
	text = NULL;
	subMenu = NULL;
}
		
//! 
//! class constructor for submenu menu item
//!
MenuItem::MenuItem(char * aText, Menu * aSubMenu) {
	id = SUB_MENUITEM;
	text = aText;
	subMenu = aSubMenu;
}
		
//! 
//! class constructor for a regular menu item
//!
MenuItem::MenuItem(char * aText, int aId) {
	id = aId;
	text = aText;
	subMenu = NULL;
}

//!
//! display menu item
//!
void MenuItem::display(Adafruit_GFX & aDisplay, boolean aSelected) {
	display.textColor(aSelected ? 1 : 0);
	
	if (getId() == BACK_MENUITEM) {
		display.print("< Zurück");
	}
	else {
		display.print(text);
	}
}
		
//!
//! menu item selected
//! 
int MenuItem::select(void) {
	return getId();
}
		
//! 
//! return id of menu item
//!
int MenuItem::getId(void) {
	return id;
}