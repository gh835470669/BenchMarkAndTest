#include <type_traits>
#include <typeinfo>
#include <utility>
#include <gtest/gtest.h>

enum class E
{
    e
};
const char *str = "str";
const char str_array[] = "str";

struct ClassOneMember
{
    int m;
};
int ClassOneMember::*mp = &ClassOneMember::m;

class ClassInheritOneMember : public ClassOneMember
{
    int n;
};

struct ClassMemberAccessControl
{
public:
    int m;

protected:
    int n;

private:
    int o;
};

struct ClassSelfDefinedConstructor
{
    ClassSelfDefinedConstructor() {}
};

// 函数的访问控制不影响下面所有类的测试
class ClassPrivateDefaultConstructor
{
private:
    ClassPrivateDefaultConstructor() = default;
};

struct ClassEmptyVirtualMethod
{
    virtual void foo() {};
};

struct ClassOneMemberVirtualMethod
{
    int a;
    virtual void foo() {};
};

auto lambda_v = [](int a, int b)
{ return a + b; };

TEST(NamingRequirements, ScalarType)
{
    // Scalar 就是不包括类，引用，数组
    // The following types are collectively called scalar types:
    // arithmetic types
    // enumeration types
    // pointer types
    // pointer-to-member types
    // std::nullptr_t (since C++11)
    // cv-qualified versions of these types
    EXPECT_EQ(std::is_scalar_v<decltype(42)>, true);
    EXPECT_EQ(std::is_arithmetic_v<decltype(42)>, true);
    EXPECT_EQ(std::is_scalar_v<decltype(3.14)>, true);
    EXPECT_EQ(std::is_arithmetic_v<decltype(3.14)>, true);
    EXPECT_EQ(std::is_scalar_v<decltype(E::e)>, true);
    EXPECT_EQ(std::is_enum_v<decltype(E::e)>, true);
    EXPECT_EQ(std::is_scalar_v<decltype(str)>, true);
    EXPECT_EQ(std::is_pointer_v<decltype(str)>, true);
    EXPECT_EQ(std::is_scalar_v<decltype(mp)>, true);
    EXPECT_EQ(std::is_member_pointer_v<decltype(mp)>, true);
    EXPECT_EQ(std::is_scalar_v<decltype(nullptr)>, true);
    EXPECT_EQ(std::is_null_pointer_v<decltype(nullptr)>, true);

    EXPECT_EQ(std::is_scalar_v<decltype("str")>, false); // no arrays
    EXPECT_EQ(std::is_pointer_v<decltype("str")>, false);
    static_assert(std::is_reference_v<decltype("str")> == true);
    EXPECT_EQ(std::is_scalar_v<decltype(str_array)>, false);
    EXPECT_EQ(std::is_pointer_v<decltype(str_array)>, false);
    static_assert(std::is_reference_v<decltype(str_array)> == false);
    static_assert(std::is_array_v<decltype(str_array)> == true);

    EXPECT_EQ(std::is_scalar_v<ClassOneMember>, false);
    static_assert(std::is_scalar_v<decltype(lambda_v)> == false);
    static_assert(std::is_class_v<decltype(lambda_v)> == true);
}

TEST(NamingRequirements, LiteralType)
{
    // A literal type is any of the following:
    // possibly cv-qualified void (so that constexpr functions can return void); (since C++14)
    // scalar type;
    // reference type;
    // an array of literal type;
    //      possibly cv-qualified class type that has all of the following properties:
    //      has a trivial(until C++20)constexpr(since C++20) destructor,
    //      all of its non-static non-variant data members and base classes are of non-volatile literal types, and
    //      is one of
    //      a lambda type,
    //      (since C++17)
    //      an aggregate union type that
    //      has no variant members, or
    //      has at least one variant member of non-volatile literal type,
    //      a non-union aggregate type, and each of its anonymous union members
    //      has no variant members, or
    //      has at least one variant member of non-volatile literal type,
    //      a type with at least one constexpr (possibly template) constructor that is not a copy or move constructor.
    static_assert(std::is_literal_type_v<decltype("str")> == true);
    static_assert(std::is_literal_type_v<decltype(str_array)> == true);

    static_assert(std::is_literal_type_v<ClassOneMember> == true);
    static_assert(std::is_literal_type_v<ClassInheritOneMember> == true);
    static_assert(std::is_literal_type_v<ClassMemberAccessControl> == true);
    static_assert(std::is_literal_type_v<ClassEmptyVirtualMethod> == true); // 特例，带虚函数的类是literal_type
    static_assert(std::is_literal_type_v<ClassOneMemberVirtualMethod> == true);
    static_assert(std::is_literal_type_v<ClassSelfDefinedConstructor> == false);
    static_assert(std::is_literal_type_v<ClassPrivateDefaultConstructor> == true);
    static_assert(std::is_literal_type_v<decltype(lambda_v)> == false);
}

TEST(NamingRequirements, PODType)
{
    // The following types are collectively called POD types:
    // scalar types
    // POD classes
    // arrays of such types
    // cv-qualified versions of these types
    static_assert(std::is_pod_v<decltype("str")> == false);
    static_assert(std::is_reference_v<decltype("str")> == true);
    static_assert(std::is_pod_v<decltype(str_array)> == true);
    static_assert(std::is_reference_v<decltype(str_array)> == false);

    static_assert(std::is_pod_v<ClassOneMember> == true);
    static_assert(std::is_pod_v<ClassInheritOneMember> == false);
    static_assert(std::is_pod_v<ClassMemberAccessControl> == false);
    static_assert(std::is_pod_v<ClassEmptyVirtualMethod> == false);
    static_assert(std::is_pod_v<ClassOneMemberVirtualMethod> == false);
    static_assert(std::is_pod_v<ClassSelfDefinedConstructor> == false);
    static_assert(std::is_pod_v<ClassPrivateDefaultConstructor> == true);
    static_assert(std::is_pod_v<decltype(lambda_v)> == false);
}

TEST(NamingRequirements, TrivialType)
{
    // The following types are collectively called trivial types:
    // scalar types
    // trivial class types
    // arrays of such types
    // cv-qualified versions of these types
    static_assert(std::is_trivial_v<ClassOneMember> == true);
    static_assert(std::is_trivial_v<ClassInheritOneMember> == true);
    static_assert(std::is_trivial_v<ClassMemberAccessControl> == true);
    static_assert(std::is_trivial_v<ClassEmptyVirtualMethod> == false);
    static_assert(std::is_trivial_v<ClassOneMemberVirtualMethod> == false);
    static_assert(std::is_trivial_v<ClassSelfDefinedConstructor> == false);
    // The following class shows why std::is_trivial(_v) may be a pitfall.
    static_assert(std::is_trivial_v<ClassPrivateDefaultConstructor> == true);
    static_assert(std::is_trivially_default_constructible_v<ClassPrivateDefaultConstructor> == false);
    static_assert(std::is_trivial_v<decltype(lambda_v)> == false);
}

TEST(NamingRequirements, StandardLayoutType)
{
    // The following types are collectively called standard-layout types:
    // scalar types
    // standard-layout class types
    // arrays of such types
    // cv-qualified versions of these types

    static_assert(std::is_standard_layout_v<ClassOneMember> == true);
    static_assert(std::is_standard_layout_v<ClassInheritOneMember> == false);
    static_assert(std::is_standard_layout_v<ClassMemberAccessControl> == false);
    static_assert(std::is_standard_layout_v<ClassEmptyVirtualMethod> == false);
    static_assert(std::is_standard_layout_v<ClassOneMemberVirtualMethod> == false);
    static_assert(std::is_standard_layout_v<ClassSelfDefinedConstructor> == true);
    static_assert(std::is_standard_layout_v<ClassPrivateDefaultConstructor> == true);
    static_assert(std::is_standard_layout_v<decltype(lambda_v)> == true);
}