#include <string>
#include <string>
#include <iostream>

#include <lemonxx/function/function.hpp>
#include <lemonxx/unittest/unittest.hpp>
#include <lemonxx/function/stack.hpp>
#include <lemonxx/function/bind.hpp>
#include <lemonxx/utility/nocopyable.hpp>
#include <lemonxx/utility/ref.hpp>

namespace lemon{namespace test{

	struct FunctionUnittest{};

	void call(int i){LEMON_CHECK(i == 1);}

	class Caller
	{
	public:
	        Caller(){}
		void call(int i){LEMON_CHECK(i == 1);}

		void const_call(int i) const{LEMON_CHECK(i == 1);}
	};

	LEMON_UNITTEST_CASE(FunctionUnittest,FreeFunctionTest)
	{
		const static size_t maxC = 1000000;

		function<void(int)> test(&call);

		test(1);
	}

	LEMON_UNITTEST_CASE(FunctionUnittest,MemberFunctionTest)
	{
		Caller caller;

		function<void(int)> test(&Caller::call,&caller);

		test(1);

		const Caller constCaller;

		function<void(int)> constTest(&Caller::const_call,&constCaller);

		constTest(1);

		function<void(int)> a = constTest;

		a(1);

		constTest(1);
	}

	LEMON_UNITTEST_CASE(FunctionUnittest,BindStackTest)
	{
		typedef mpl::make_list<placeholder<2>,placeholder<0>,placeholder<1>,const char*,placeholder<1>,std::string>::type L;

		typedef mpl::make_list<int,char,float,const char*,size_t,std::string>::type R;

		typedef mpl::make_list<char,float,int>::type R1;

		LEMON_CHECK((is_same<binds::call_parameters<L,R,0>::type,char>::value));

		LEMON_CHECK((is_same<binds::call_parameters<L,R,1>::type,float>::value));

		LEMON_CHECK((is_same<binds::call_parameters<L,R,2>::type,int>::value));
	}

	LEMON_UNITTEST_CASE(FunctionUnittest,BindUnwindTest)
	{
		std::string helloWorld = "hello world!!!!";

		typedef mpl::make_list<const char*,int,float,const char*>::type Seq;

		typedef tuple<placeholder<1>,placeholder<0>,placeholder<2>,const char *> L;

		typedef tuple<int,const char*,float> R;

		tuple<placeholder<1>,placeholder<0>,placeholder<2>,const char *> l(_1,_0,_2,helloWorld.c_str());

		tuple<int,const char*,float> r(2000,helloWorld.c_str(),3.0);

		LEMON_CHECK((helloWorld == binds::unwind<Seq,0>(l,r)));

		LEMON_CHECK((2000 == binds::unwind<Seq,1>(l,r)));

		LEMON_CHECK((3.0 == binds::unwind<Seq,2>(l,r)));

		LEMON_CHECK((helloWorld == binds::unwind<Seq,3>(l,r)));

	}

	void call2(short a,float b){LEMON_CHECK(a == 2);LEMON_CHECK(b == 1);}

	class RefObj : private nocopyable
	{
	public:
		RefObj(int i):_i(i){}

		int Counter()const{return _i;}

		void Counter(int i){_i = i;}

		void Hello(int i) const{LEMON_CHECK(i == _i);}

	private:
		int _i;
	};

	void CallRefObj(const RefObj &){}
	void CallRefObj1(const RefObj & object,int){LEMON_CHECK(object.Counter() == 1);}


	LEMON_UNITTEST_CASE(FunctionUnittest,BindTest)
	{
		bind(&call,1)();

		bind(&call2,_1,_0)(1.0,2);

		RefObj object(1);

		const RefObj constObject(1);

		bind(&CallRefObj,cref(object))();

		bind(&CallRefObj1,_0,1)(object);

		bind(&RefObj::Counter,&object,1)();

		bind(&RefObj::Counter,&object,_0)(1);

		bind(&RefObj::Counter,&object)();

		bind(&RefObj::Counter,&constObject)();

		bind(&RefObj::Hello,&constObject,1)();

		bind(&RefObj::Hello,&constObject,_0)(bind(&RefObj::Counter,&constObject)());

		function<void()> a = bind(&RefObj::Hello,&constObject,1);

		function<void(int)> b = bind(&RefObj::Hello,&constObject,_0);

		a();

		b(1);
	}
}}
