#include <lemonxx/unittest/unittest.hpp>
#include <lemonxx/type_traits/type_traits.hpp>
#include <lemonxx/type_traits/parameters.hpp>
namespace lemon{namespace test{
	struct TypeTraitsUnittest{void test();};

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_same_test)
	{
		LEMON_CHECK((is_same<int,int>::value == true));

		LEMON_CHECK((is_same<int const,int>::value == false));

		LEMON_CHECK((is_same<int&,int>::value == false));

		LEMON_CHECK((is_same<int*,int>::value == false));

		LEMON_CHECK((is_same<const int,int const>::value == true));

		LEMON_CHECK((is_same<const int volatile,int volatile const>::value == true));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,add_const_test)
	{
		LEMON_CHECK((is_same<add_const<int>::type,int const>::value));

		LEMON_CHECK((is_same<add_const<int&>::type,int&>::value));
		//int * const the int * pointer is const
		LEMON_CHECK((is_same<add_const<int*>::type,int* const>::value));
		//const int * ,the pointer int can not modify
		LEMON_CHECK((is_same<add_const<int*>::type,const int*>::value == false));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,add_pointer_test)
	{
		LEMON_CHECK((is_same<add_pointer<int>::type,int*>::value));

		LEMON_CHECK((is_same<add_pointer<int&>::type,int*>::value));
		//int * const the int * pointer is const
		LEMON_CHECK((is_same<add_pointer<int*>::type,int**>::value));

		LEMON_CHECK((is_same<add_pointer<int*&>::type,int**>::value));
		//const int * ,the pointer int can not modify
		LEMON_CHECK((is_same<add_pointer<const int>::type,const int*>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,add_volatile_test)
	{
		LEMON_CHECK((is_same<add_volatile<int>::type,int volatile>::value));

		LEMON_CHECK((is_same<add_volatile<int&>::type,int&>::value));
		//int * const the int * pointer is const
		LEMON_CHECK((is_same<add_volatile<int*>::type,int* volatile>::value));

		LEMON_CHECK((is_same<add_volatile<int const>::type,int const volatile>::value));
		//const int * ,the pointer int can not modify
		LEMON_CHECK((is_same<add_volatile<int*>::type,volatile int*>::value == false));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,add_cv_test)
	{
		LEMON_CHECK((is_same<add_cv<int>::type,int const volatile>::value));

		LEMON_CHECK((is_same<add_cv<int&>::type,int&>::value));
		//int * const the int * pointer is const
		LEMON_CHECK((is_same<add_cv<int*>::type,int* const volatile>::value));

		LEMON_CHECK((is_same<add_cv<int const>::type,int const volatile>::value));
		
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,add_lvalue_reference_test)
	{
		LEMON_CHECK((is_same<add_lvalue_reference<int>::type,int&>::value));

		LEMON_CHECK((is_same<add_lvalue_reference<int&>::type,int&>::value));

		LEMON_CHECK((is_same<add_lvalue_reference<int const&>::type,int const&>::value));

		LEMON_CHECK((is_same<add_lvalue_reference<int*>::type,int*&>::value));
#ifdef LEMON_COMPILER_SUPPORT_RVALUE
		LEMON_CHECK((is_same<add_lvalue_reference<int&&>::type,int&>::value));
#endif //LEMON_COMPILER_SUPPORT_RVALUE

		LEMON_CHECK((is_same<add_lvalue_reference<void>::type,void>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,remove_reference_test)
	{
		LEMON_CHECK((is_same<remove_reference<int>::type,int>::value));	

		LEMON_CHECK((is_same<remove_reference<int&>::type,int>::value));	

		LEMON_CHECK((is_same<remove_reference<int const&>::type,int const>::value));

#ifdef LEMON_COMPILER_SUPPORT_RVALUE
		LEMON_CHECK((is_same<remove_reference<int&&>::type,int>::value));
#endif //LEMON_COMPILER_SUPPORT_RVALUE

		LEMON_CHECK((is_same<remove_reference<int*>::type,int*>::value));

		LEMON_CHECK((is_same<remove_reference<int* &>::type,int*>::value));
	}

#ifdef LEMON_COMPILER_SUPPORT_RVALUE
	LEMON_UNITTEST_CASE(TypeTraitsUnittest,add_rvalue_reference_test)
	{
		LEMON_CHECK((is_same<add_rvalue_reference<int>::type,int&&>::value));

		LEMON_CHECK((is_same<add_rvalue_reference<int&>::type,int&>::value));

		LEMON_CHECK((is_same<add_rvalue_reference<int const&>::type,int const&>::value));

		LEMON_CHECK((is_same<add_rvalue_reference<int*>::type,int*&&>::value));

		LEMON_CHECK((is_same<add_rvalue_reference<int&&>::type,int&&>::value));

		LEMON_CHECK((is_same<add_rvalue_reference<void>::type,void>::value));
	}
#endif

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,alignment_of_test)
	{
		std::cout << "alignment_of<int>::value :" <<  alignment_of<int>::value << std::endl;

		std::cout << "alignment_of<float>::value :" <<  alignment_of<float>::value << std::endl;

		std::cout << "alignment_of<double>::value :" <<  alignment_of<double>::value << std::endl;

		std::cout << "alignment_of<lemon_int32_t>::value :" <<  alignment_of<lemon_int32_t>::value << std::endl;

		std::cout << "alignment_of<lemon_int64_t>::value :" <<  alignment_of<lemon_int64_t>::value << std::endl;
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,aligned_storage_test)
	{
		LEMON_CHECK(sizeof(aligned_storage<60,8>::type) == 64);

		LEMON_CHECK(sizeof(aligned_storage<60,4>::type) == 60);

		LEMON_CHECK(sizeof(aligned_storage<30,2>::type) == 30);

		LEMON_CHECK(sizeof(aligned_storage<30,4>::type) == 32);
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,conditional_test)
	{
		LEMON_CHECK((is_same<conditional<true,int,char>::type,int>::value));

		LEMON_CHECK((is_same<conditional<false,int,char>::type,char>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,remove_extent_test)
	{
		LEMON_CHECK((is_same<remove_extent<int>::type,int>::value));

		LEMON_CHECK((is_same<remove_extent<int const[2]>::type,int const>::value));

		LEMON_CHECK((is_same<remove_extent<int[2][4]>::type,int[4]>::value));

		LEMON_CHECK((is_same<remove_extent<int[][4]>::type,int[4]>::value));

		LEMON_CHECK((is_same<remove_extent<int const*>::type,int const *>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_array_test)
	{
		LEMON_CHECK((is_array<int[2]>::value));	

		LEMON_CHECK((is_array<char[3][2]>::value));	

		LEMON_CHECK((is_array<double[2]>::value));	
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_function_test)
	{
		LEMON_CHECK((!is_function<int[2]>::value));		
		LEMON_CHECK((is_function<int(void)>::value));		
		LEMON_CHECK((is_function<long(double,int)>::value));		
		LEMON_CHECK((!is_function<long(*)(double,int)>::value));
		LEMON_CHECK((!is_function<long(&)(double,int)>::value));
		LEMON_CHECK((!is_function<void(TypeTraitsUnittest::*)(double,int)>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,decay_test)
	{
		LEMON_CHECK((is_same<decay<int[2][3]>::type,remove_extent<int[2][3]>::type*>::value));

		LEMON_CHECK((is_same<decay<int(&)[3]>::type,int*>::value));

		LEMON_CHECK((is_same<decay<int(&)(double)>::type,int(*)(double)>::value));

		LEMON_CHECK((is_same<decay<int(*)(double)>::type,int(*)(double)>::value));

		LEMON_CHECK((is_same<decay<int(double)>::type,int(*)(double)>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,extent_test)
	{
		LEMON_CHECK((extent<int[1]>::value == 1));

		LEMON_CHECK((extent<double[2][3][4], 0>::value == 2));

		LEMON_CHECK((extent<double[2][3][4], 1>::value == 3));

		LEMON_CHECK((extent<double[2][3][4], 2>::value == 4));

		LEMON_CHECK((extent<double[], 0>::value == 0));

		LEMON_CHECK((extent<double[]>::value == 0));

		LEMON_CHECK((extent<double*>::value == 0));
	}

	class abc{virtual ~abc() = 0;};

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_abstract_test)
	{
		LEMON_CHECK(is_abstract<abc>::value);

		LEMON_CHECK(is_abstract<abc const>::value);

		LEMON_CHECK(!is_abstract<int>::value);
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_integral_test)
	{
		LEMON_CHECK(is_integral<lemon_int16_t>::value);

		LEMON_CHECK(is_integral<lemon_int32_t>::value);

		LEMON_CHECK(is_integral<lemon_int64_t>::value);

		LEMON_CHECK(is_integral<char>::value);

		LEMON_CHECK(is_integral<unsigned char>::value);

		LEMON_CHECK(is_integral<signed char>::value);

		LEMON_CHECK(is_integral<short>::value);

		LEMON_CHECK(is_integral<int>::value);

		LEMON_CHECK(is_integral<long>::value);
#ifdef LEMON_COMPILER_SUPPORT_LONGLONG
		LEMON_CHECK(is_integral<long long>::value);
#endif //LEMON_COMPILER_SUPPORT_LONGLONG
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_floating_point_test)
	{
		LEMON_CHECK(is_floating_point<float>::value);

		LEMON_CHECK(is_floating_point<double>::value);

		LEMON_CHECK(is_floating_point<long double>::value);

		LEMON_CHECK(!is_floating_point<int>::value);
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_arithmetic_test)
	{
		LEMON_CHECK(is_arithmetic<lemon_int16_t>::value);

		LEMON_CHECK(is_arithmetic<lemon_int32_t>::value);

		LEMON_CHECK(is_arithmetic<lemon_int64_t>::value);

		LEMON_CHECK(is_arithmetic<char>::value);

		LEMON_CHECK(is_arithmetic<unsigned char>::value);

		LEMON_CHECK(is_arithmetic<signed char>::value);

		LEMON_CHECK(is_arithmetic<short>::value);

		LEMON_CHECK(is_arithmetic<int>::value);

		LEMON_CHECK(is_arithmetic<long>::value);
#ifdef LEMON_COMPILER_SUPPORT_LONGLONG
		LEMON_CHECK(is_arithmetic<long long>::value);
#endif //LEMON_COMPILER_SUPPORT_LONGLONG

		LEMON_CHECK(is_arithmetic<float>::value);

		LEMON_CHECK(is_arithmetic<double>::value);

		LEMON_CHECK(is_arithmetic<long double>::value);

	}
	
	class Base{}; class Derived : public Base{}; 

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_base_of_test)
	{
		LEMON_CHECK((is_base_of<Base,Derived>::value));

		LEMON_CHECK((!is_base_of<Derived,Base>::value));

		LEMON_CHECK((is_base_of<Base,Base>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_class_test)
	{
		LEMON_CHECK((is_class<Base>::value));

		LEMON_CHECK((is_class<Derived>::value));

		LEMON_CHECK((!is_class<int>::value));
	}

	enum my_enum { one, two }; 


	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_enum_test)
	{
		LEMON_CHECK((is_enum<my_enum>::value));

		LEMON_CHECK((is_enum<my_enum const>::value));

		LEMON_CHECK((!is_enum<my_enum*>::value));

		LEMON_CHECK((!is_enum<my_enum&>::value));

		LEMON_CHECK((!is_enum<int>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_member_function_pointer_test)
	{
		LEMON_CHECK((is_member_function_pointer<int (TypeTraitsUnittest::*)(void)>::value));

		LEMON_CHECK((is_member_function_pointer<int (TypeTraitsUnittest::*)(char)>::value));

		LEMON_CHECK((is_member_function_pointer<int (TypeTraitsUnittest::*)(char) const>::value));

		LEMON_CHECK((!is_member_function_pointer<int (TypeTraitsUnittest::*)>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_member_object_pointer_test)
	{
		LEMON_CHECK((!is_member_object_pointer<int (TypeTraitsUnittest::*)(void)>::value));

		LEMON_CHECK((!is_member_object_pointer<int (TypeTraitsUnittest::*)(char)>::value));

		LEMON_CHECK((!is_member_object_pointer<int (TypeTraitsUnittest::*)(char) const>::value));

		LEMON_CHECK((is_member_object_pointer<int (TypeTraitsUnittest::*)>::value));

		LEMON_CHECK((is_member_object_pointer<const int (TypeTraitsUnittest::*)>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_void_test)
	{
		LEMON_CHECK(is_void<void>::value);

		LEMON_CHECK(is_void<const void>::value);

		LEMON_CHECK(is_void<const void volatile>::value);

		LEMON_CHECK(!is_void<const void *>::value);
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_reference_test)
	{
		LEMON_CHECK(is_reference<int&>::value);
#ifdef LEMON_COMPILER_SUPPORT_RVALUE
		LEMON_CHECK(is_reference<int&&>::value);
#endif
		LEMON_CHECK(is_reference<int(&)(long)>::value);
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_object_test)
	{
		LEMON_CHECK(is_object<int>::value);

		LEMON_CHECK(is_object<int*>::value);

		LEMON_CHECK(is_object<int(TypeTraitsUnittest::*)(char)>::value);

		LEMON_CHECK(!is_object<int&>::value);

		LEMON_CHECK(!is_object<int(double)>::value);

		LEMON_CHECK(!is_object<const void>::value);
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_member_pointer_test)
	{
		LEMON_CHECK((is_member_pointer<int (TypeTraitsUnittest::*)>::value));

		LEMON_CHECK((is_member_pointer<const int (TypeTraitsUnittest::*)>::value));

		LEMON_CHECK((is_member_pointer<int (TypeTraitsUnittest::*)(void)>::value));

		LEMON_CHECK((is_member_pointer<int (TypeTraitsUnittest::*)(char)>::value));

		LEMON_CHECK((is_member_pointer<int (TypeTraitsUnittest::*)(char) const>::value));

		LEMON_CHECK((!is_member_pointer<int*>::value));
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_pointer_test)
	{
		LEMON_CHECK(is_pointer<int*>::value);

		LEMON_CHECK(is_pointer<char* const>::value);

		LEMON_CHECK(is_pointer<const char* >::value);

		LEMON_CHECK(is_pointer<const char* (*)(long)>::value);

		LEMON_CHECK(!is_pointer<const char*(long)>::value);

		LEMON_CHECK(!is_pointer<const char*(TypeTraitsUnittest::*)(long)>::value);

		LEMON_CHECK(!is_pointer<const char*(TypeTraitsUnittest::*)>::value);
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_scalar_test)
	{
		LEMON_CHECK(is_scalar<int*>::value);

		LEMON_CHECK(is_scalar<int>::value);

		LEMON_CHECK(is_scalar<double>::value);

		LEMON_CHECK(is_scalar<int (*)(long)>::value);

		LEMON_CHECK(is_scalar<int (TypeTraitsUnittest::*)(long)>::value);

		LEMON_CHECK(is_scalar<int (TypeTraitsUnittest::*)>::value);
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,is_pod_test)
	{
		LEMON_CHECK(is_pod<int>::value);

		LEMON_CHECK(is_pod<char*>::value);

		LEMON_CHECK(is_pod<int(*)()>::value);

		LEMON_CHECK(is_pod<int[]>::value);

		LEMON_CHECK(is_pod<int[][1][2]>::value);
	
		LEMON_CHECK(is_pod<TypeTraitsUnittest>::value);

		LEMON_CHECK(!is_pod<abc>::value);

		LEMON_CHECK(is_pod<my_enum>::value);
	}

	LEMON_UNITTEST_CASE(TypeTraitsUnittest,parameter_test)
	{
		LEMON_CHECK((is_same<parameter<int>::type,int>::value));

		LEMON_CHECK((is_same<parameter<char*>::type,char*>::value));

		LEMON_CHECK((is_same<parameter<const char*>::type,const char*>::value));

		LEMON_CHECK((is_same<parameter<char&>::type,char&>::value));

		LEMON_CHECK((is_same<parameter<TypeTraitsUnittest&>::type,TypeTraitsUnittest&>::value));

		LEMON_CHECK((is_same<parameter<TypeTraitsUnittest>::type,TypeTraitsUnittest>::value));

		LEMON_CHECK((is_same<parameter<abc>::type,const abc &>::value));
	}
}}




