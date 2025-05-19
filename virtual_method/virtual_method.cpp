#include <gtest/gtest.h>
#include <iostream>

using namespace std;

class LvZero0
{
public:
    virtual void vmethod_lvzero_0()
    {
        cout << "LvZero0 vmethod_lvzero_0()" << endl;
    }
    virtual void vmethod_lvzero_1()
    {
        cout << "LvZero0 vmethod_lvzero_1()" << endl;
    }
    virtual void vmethod_lvzero_2()
    {
        cout << "LvZero0 vmethod_lvzero_2()" << endl;
    }
};

class LvOne0_derive_LvZero0 : public LvZero0
{
public:
    // overriding vmethod_lvzero_0()
    void vmethod_lvzero_0() override
    {
        cout << "LvOne0_derive_LvZero0 vmethod_lvzero_0() override" << endl;
    }
    // not overriding vmethod_lvzero_1() and vmethod_lvzero_2()

    virtual void vmethod_lv1_0()
    {
        cout << "LvOne0_derive_LvZero0 vmethod_lv1_0()" << endl;
    }
};

// class derived from LvOne0_derive_LvZero0
class LvTwo0_derive_LvOne0 : public LvOne0_derive_LvZero0
{
public:
    // again overriding vmethod_lvzero_1()
    void vmethod_lvzero_1() override
    {
        cout << "LvTwo0_derive_LvOne0 vmethod_lvzero_1() override" << endl;
    }
    // not overriding vmethod_lvzero_0() and vmethod_lvzero_2()

    void vmethod_lv1_0()
    {
        cout << "LvOne0_derive_LvZero0 function_d_1()" << endl;
    }
};

class LvOne1_derive_LvZero0 : public LvZero0
{
    // overriding vmethod_lvzero_0()
    void vmethod_lvzero_0() override
    {
        cout << "LvOne1_derive_LvZero0 vmethod_lvzero_0() override" << endl;
    }
};

class LvTwo0_derive_lvOne0_lvOne1 : public LvOne0_derive_LvZero0, public LvOne1_derive_LvZero0
{
    // overriding vmethod_lvzero_0()
    void vmethod_lvzero_0() override
    {
        cout << "LvTwo0_derive_lvOne0_lvOne1 vmethod_lvzero_0() override" << endl;
    }
};

// driver code
TEST(VirtualMethod, Basic)
{
    LvZero0 *ptr1 = new LvZero0();
    LvZero0 *ptr2 = new LvOne0_derive_LvZero0();
    LvZero0 *ptr3 = new LvTwo0_derive_LvOne0();
    LvZero0 *ptr4 = new LvOne1_derive_LvZero0();

    LvOne0_derive_LvZero0 *ptr5 = new LvOne0_derive_LvZero0();
    LvOne0_derive_LvZero0 *ptr6 = new LvTwo0_derive_LvOne0();
    LvTwo0_derive_LvOne0 *ptr7 = new LvTwo0_derive_LvOne0();

    // LvZero0 *ptr8 = new LvTwo0_derive_lvOne0_lvOne1(); // error: base class "LvZero0" is ambiguous
    LvTwo0_derive_lvOne0_lvOne1 *ptr8 = new LvTwo0_derive_lvOne0_lvOne1();
    LvOne0_derive_LvZero0 *ptr9 = new LvTwo0_derive_lvOne0_lvOne1();
    LvOne1_derive_LvZero0 *ptr10 = new LvTwo0_derive_lvOne0_lvOne1();

    // deleting objects
    delete ptr1;
    delete ptr2;
    delete ptr3;
    delete ptr4;
    delete ptr5;
    delete ptr6;
    delete ptr7;
    delete ptr8;
    delete ptr9;
    delete ptr10;
}