//File: Locator.h
#ifndef LOCATOR_H
#define LOCATOR_H
#include <cassert>
#include "gpl_type.h"
#include "Game_object.h"
class Statement;

class Locator {
  private:
    const Gpl_type intrinsic_type;
  public:
    Locator(Gpl_type enum_name) 
      : intrinsic_type(enum_name) {}
    virtual void mutate(int)                {throw intrinsic_type;}
    virtual void mutate(double)             {throw intrinsic_type;}
    virtual void mutate(const std::string& ){throw intrinsic_type;}
    Gpl_type type() const;
};

class Integer_locator : public Locator {
  private:
    int& data;
  public:
    Integer_locator(int& d) 
      : Locator(INT), data(d) {}
    virtual void mutate(int val) { data=val; }
};

class Double_locator : public Locator {
  private:
    double& data;
  public:
    Double_locator(double& d) 
      : Locator(DOUBLE), data(d) {}
    virtual void mutate(double val) { data=val; }
};

class String_locator : public Locator {
  private:
    std::string& data;
  public:
    String_locator(std::string& d) 
      : Locator(STRING), data(d) {}
    virtual void mutate(const std::string& val) { data=val;}
};

class Game_attribute_locator : public Locator {
  private:
    Game_object* gop;
    std::string attribute_name;
  public:
    Game_attribute_locator(Game_object* gop, const std::string& attribute_name) 
      : Locator(gop->attribute_type(attribute_name)), gop(gop), attribute_name(attribute_name) {}
    virtual void mutate(int val);
    virtual void mutate(double val);
    virtual void mutate(const std::string& val);
};

#endif
