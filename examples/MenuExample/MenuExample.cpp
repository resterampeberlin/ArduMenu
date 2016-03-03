#include <Menu.h>
#include <Adafruit_SSD1306.h>
#include <RotaryEncoder.h>

class CustomMenuItem:MenuItem {
	public:
		CustomMenuItem(int aId);
		
		void display(Adafruit_GFX & aDisplay, boolean aSelected = false);
};

CustomMenuItem customItems[] = {
	CustomMenuItem(1),
	CustomMenuItem(2),
	CustomMenuItem(3),
	NULL
};

Menu customMenu(customItems);

boolean checkedValues[5] = {
	TRUE,
	FALSE
	TRUE,
	FALSE,
	TRUE };
	
MenuItem checked[] = {
	CheckedMenuItem("Checked 1", &checkedValues[0]),
	CheckedMenuItem("Checked 2", &checkedValues[1]),
	CheckedMenuItem("Checked 3", &checkedValues[2]),
	CheckedMenuItem("Checked 4", &checkedValues[3]),
	CheckedMenuItem("Checked 5", &checkedValues[4]),
	MenuItem(NULL),
	NULL
};

Menu checkedMenu(checked);

uint8_t choiceValue=0;

MenuItem choice[] = {
	ChoiceMenuItem("Choice 1", &choiceValue, 0),
	ChoiceMenuItem("Choice 2", &choiceValue, 1),
	ChoiceMenuItem("Choice 3", &choiceValue, 2),
	ChoiceMenuItem("Choice 4", &choiceValue, 3),
	ChoiceMenuItem("Choice 5", &choiceValue, 4),
	MenuItem(NULL),
	NULL
};

Menu choiceMenu(choice);

MenuItem level0[] = {
	MenuItem("Menü 1.1", 1, checkedMenu),
	MenuItem("Menü 1.2", 2, choiceMenu),
	MenuItem("Menü 1,3", 3),
	MenuItem("Menü 1.4", 4),
	MenuItem("Menü 1.5", 5),
	MenuItem("Menü 1,6", 6),
	NULL
};

Menu level0Menu(level0, customMenu);
MenuManager menu;

Adafruit_SSD1306 display();
RotaryEncoder encoder();


void setup(void){
	menu.begin(display, level0Menu);
}

void loop(void){
	result = encoder.waitForEvent();
	
	switch(result) {
		case next:
			menu.next();
			break;
			
		case previous:
			menu.previous();
			break;
			
		case click:
			menu.select();
			break;
			
		case clickLong
			menu.nextMenu();
			break;
	}
}