#include <LiquidCrystal.h>
#include "Arduino.h"
#include "extended.h"

//base class -------------------------------------------------------------------
class MenuItem{
public:
  MenuItem(String ,int& ,int ,int);
  String name;
  int *state;
  int max;
  int min;

  MenuItem *parent;
  MenuItem *child;
  MenuItem *handle;

  bool up();
  bool down();
  void bla123();
  virtual bool ok()=0;
  virtual bool display(LiquidCrystal &lcd)=0;
  virtual bool update(LiquidCrystal &lcd)=0;
};
 //-----
 
MenuItem::MenuItem(String inName,int &inState, int inMax,int inMin){
  name = inName;
  state = &inState;
  max = inMax;
  min = inMin;
}

bool MenuItem::up(){
  *state= *state+1;
  if(*state>max)*state=min;
  return false;
}
bool MenuItem::down(){
  *state=*state-1;
  if(*state<min)*state=max;
  return false;
}

void MenuItem::bla123(){
  *state=*state+1;
}

//example parent class -------------------------------------------------------------------

class basicNumber: public MenuItem{
public:
            //  name, max, min   //
  basicNumber(String ,int ,int);
  int val;
  
  bool ok(){
    //ok button stuff
  }
  bool display(){
    //display everything
  }
  bool update(){
    //only update whats needs to be updated
  }
};

basicNumber::basicNumber(String inName,int inMax,int inMin):MenuItem(inName,val,inMax,inMin){

}

//test menu module -------------------------------------------------------------------

class valueItem: public MenuItem{
public:
  int *value;
  valueItem(String, int&, int, int);
  bool ok(){
    handle = parent;
    return true;
  }
  bool display(LiquidCrystal &lcd){
    lcd.setCursor(0,0);
    lcd.print("--");
    lcd.setCursor(14,0);
    lcd.print("--");
    lcd.setCursor(getMiddle(name.length(),16),0);
    lcd.print(name);
    lcd.setCursor(0,1);
    lcd.print("set:");
    String numb = String(*state);
    lcd.setCursor(16-numb.length(),1);
    lcd.print (numb);
  }
  bool update(LiquidCrystal &lcd){
    String numb = String(*state);
    lcd.setCursor(10, 1);
    for(byte i = 0; i<6-numb.length(); i++) lcd.write(' ');
    lcd.print(numb);
  }

};
valueItem::valueItem(String setName, int &setVal, int setMax, int setMin):MenuItem(setName, setVal, setMax, setMin){
    //value = &setVal;
  }

//Menu root class -------------------------------------------------------------------
//wip
class Root{
public:
  MenuItem *item;
  LiquidCrystal *device;

  Root(LiquidCrystal &setDisplay, MenuItem &setItem){
    item=&setItem;
    device = &setDisplay;
  }

  void up(){ if(item->up()) item=item->handle; }
  void down(){ if(item->down()) item=item->handle; }
  void ok(){ if(item->ok()) item=item->handle; }
  void display(){ if(item->display(*device)) item=item->handle; }
  void update(){ if(item->update(*device)) item=item->handle; }
};


