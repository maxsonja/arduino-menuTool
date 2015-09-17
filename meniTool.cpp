
//base class
class MenuItem{
public:
  MenuItem(char ,int ,int);
  char name;
  int state;
  int max;
  int min;

  MenuItem *parent;
  MenuItem *child;
  MenuItem *handle;

  bool up();
  bool down();
  virtual bool ok()=0;
  virtual bool display()=0;
};

MenuItem::MenuItem(char inName,int inMax,int inMin){
  name = inName;
  state = 0;
  max = inMax;
  min = inMin;
}

bool MenuItem::up(){
  state++;
  if(state>max)state=min;
  return false;
}
bool MenuItem::down(){
  state--;
  if(state<min)state=max;
  return false;
}


//example
class basicNumber: public MenuItem{
public:
  basicNumber(char ,int ,int);
  
  bool ok(){
    return true;
  }
  bool display(){
    //cout<<name<<" "<<state<<endl;
  }
};

basicNumber::basicNumber(char inName,int inMax,int inMin):MenuItem(inName,inMax,inMin){

}


