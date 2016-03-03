#include <Adafruit_GFX.h>

class Menu;

//! 
//! container for one menuItem
//!
//! This class encapsulates one menu item for a menu. 
//! 
//! 

class MenuItem {
	public:
		//! 
		//! class constructor for "back" menu item
		//!
		//! constructs a menu item which displays a predefined text
		//! and selection returns to the previous menu level
		//!
		MenuItem();
		
		//! 
		//! class constructor for submenu menu item
		//!
		//! constructs a menu item which displays a user defined text
		//! and selection switches to the next menu level
		//!
		//! @param aText text to be displayed
		//! @param aSubMenu associated submenu, should not be NULL
		//!
		MenuItem(char * aText, Menu * aSubMenu);
		
		//! 
		//! class constructor for a regular menu item
		//!
		//! @param aText text to be displayed, should not be NULL
		//! @param aId associated id. Should be positive for regular items
		//!
		MenuItem(char * aText, int aId);
		
		//! 
		//! display menu item
		//!
		//! @param aDisplay associated display
		//! @param aSelected show item as selected
		//!
		virtual void display(Adafruit_GFX & aDisplay, boolean aSelected = false);
		
		//!
		//! menu item selected
		//! 
		//! will be called when menu item is selected. basic 
		//! implememtation returns only id 
		//! will be useful in sub class
		//!
		//! @returns id of selected item
		virtual int select(void);
		
		//! 
		//! return id of menu item
		//!
		//! @returns associated id of menu item.
		//!          -1 if menu item is "back" type
		//!          -2 if menu item is submenu type
		//!
		int getId(void);
		
	protected:
		char * pText;
		int id;
		Menu * pSubMenu;
};

#define BACK_MENUITEM -1
#define SUB_MENUITEM  -2

class CheckedMenuItem:MenuItem {
	public:
		//! class constructor for a regular menu item
		//!
		//! @param aText text to be displayed, should not be NULL
		//! @param aValue pointer to the variable which holds the checked 
		//!        state
		//!
		CheckedMenuItem(char * aText, boolean * aValue);
		
		void display(Adafruit_GFX & aDisplay, boolean aSelected = false);
		
		int select(void);
	
	protected:
		boolean * pValue;
};

class ChoiceMenuItem:MenuItem {
	public:
		//! class constructor for a regular menu item
		//!
		//! @param aText text to be displayed, should not be NULL
		//! @param aValue pointer to the variable, item will be marked
		//!        if id matches value of the variable
		//! @param aId associated value 
		//!
		ChoiceMenuItem(char * aText, int * aValue, int aId);
		
		void display(Adafruit_GFX & aDisplay, boolean aSelected = false);
		
		int select(void);
		
	protected:
		int * pValue;
};

class Menu {
	public:
		//! 
		//! class constructor
		//!
		//! @param aMenuItem NULL-terminated array of menu items
		//! @param aNextMenu next menu to be displayed when nextMenu 
		//!        is called. NULL will cause MenuManager to start with 
		//!        initial menu
		//! @sa MenuManager::begin()
		//!
		Menu(MenuItem * aMenuItem, Menu * aNextMenu = NULL);
		
		//! 
		//! displays menu
		//!
		//! @param aDisplay associated display
		//!
		void display(Adafruit_GFX & aDisplay);
		
		void previous(void);
		void next(void);
		int select(void);
		void nextMenu(void);
	
	protected:
		MenuItem * pMenuItem;
		Menu * pNextMenu;
		uint8_t menuItemCount;
}

//! 
//! Main interface from the application to the menu
//!
//! This class encapsulates the whole menu for the application. 
//! 
//! 

class MenuManager {
	public:
		//! 
		//! start menu handling
		//! 
		//! displays current menu entirely and selects current item
		//!
		//! @param aDisplay associated display
		//! @param Initial menu
		//! @sa Menu::Menu()
		//!
		void begin(Adafruit_GFX & aDisplay, Menu * aInitialMenu);
		void end(void);
		
		void next(void);
		void previous(void);
		
		//! 
		//! select current menu item
		//! 
		//! select current menu item and elaborate subsequent action
		//! - display associated submenu (if any)
		//! - return to previous menu (if any)
		//! - return associated id 
		//! @returns associated id
		//!
		int select(void);
		void nextMenu(void);
		
	protected:
		MenuItem * pCurrentItem;
		Menu * pCurrentMenu;
		Menu * pInitialMenu;
};
