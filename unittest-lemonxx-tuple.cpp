#include <string>
#include <iostream>
#include <lemonxx/unittest/unittest.hpp>
#include <lemonxx/utility/tuple.hpp>

namespace lemon{namespace test{
	struct TupleUnittest {};

	LEMON_UNITTEST_CASE(TupleUnittest,BasicTupleTest)
	{
		typedef mpl::make_list<int,float,char,char*,size_t>::type Seq;

		typedef mpl::make_list<float,char,char*,size_t>::type Seq1;

		typedef mpl::begin<Seq>::type begin;

		typedef mpl::end<Seq>::type end;

		typedef mpl::begin<Seq1>::type begin1;

		typedef mpl::end<Seq1>::type end1;

		typedef basic_tuple<begin,end> tuple;

		typedef basic_tuple<begin1,end1> tuple1;

		LEMON_CHECK(typeid(basic_tuple_cast<Seq,0>::type)  == typeid(tuple));

		LEMON_CHECK(typeid(basic_tuple_cast<Seq,1>::type)  == typeid(tuple1));

	}

	LEMON_UNITTEST_CASE(TupleUnittest,TupleGetterTest)
	{
		tuple<int,float,char,const char*,size_t> t;

		std::string helloworld("helloworld");

		t.set<0>(1);

		t.set<1>(2.0);

		t.set<2>('a');

		t.set<3>(helloworld.c_str());

		t.set<4>(strlen(t.get<3>()));

		LEMON_CHECK(t.get<0>() == 1);

		LEMON_CHECK(t.get<1>() == 2.0);

		LEMON_CHECK(t.get<2>() == 'a');

		LEMON_CHECK(t.get<3>() == helloworld);

		LEMON_CHECK(t.get<4>() == helloworld.size());

		tuple<TupleUnittest,int> t1;

		t1.set<0>(TupleUnittest());

		tuple<int,float,char,const char*,size_t> t2(1,2.0,'a',helloworld.c_str(),helloworld.size());

		LEMON_CHECK(t2.get<0>() == 1);

		LEMON_CHECK(t2.get<1>() == 2.0);

		LEMON_CHECK(t2.get<2>() == 'a');

		LEMON_CHECK(t2.get<3>() == helloworld);

		LEMON_CHECK(t2.get<4>() == helloworld.size());

		LEMON_CHECK((t == t2));

		tuple<int,float,char,const char*,size_t> t3;

		LEMON_CHECK(t3 != t);

		t3.swap(t2);

		LEMON_CHECK(t3 == t);

		LEMON_CHECK(t2 != t);
	}
}}