#ifdef WIN32
#include <lemonxx/wmi/wmi.hpp>
#include <lemonxx/function/bind.hpp>
#include <lemonxx/unittest/unittest.hpp>


ATL::CComModule _Module; 

namespace lemon{namespace win32{namespace test{

	class WmiUnittest
	{
	public:
		WmiUnittest()
		{
			_Module.Init(0,NULL);
		}

		~WmiUnittest()
		{
			_Module.Term();
		}

		multi_thread_comodel comodel;
	};

	LEMON_UNITTEST_CASE(WmiUnittest,COMInitialzieTest)
	{
		multi_thread_comodel comodel;
	}

	LEMON_UNITTEST_CASE(WmiUnittest,ContextTest)
	{
		wmi::context ctx;

		ctx[LEMON_TEXT("name")] = ATL::CComVariant(LEMON_TEXT("yayanyang"));

		ctx[LEMON_TEXT("password")] = ATL::CComVariant(LEMON_TEXT("test1234"));

		LEMON_CHECK(ctx[LEMON_TEXT("name")] == ATL::CComVariant(LEMON_TEXT("yayanyang")));
	}

	LEMON_UNITTEST_CASE(WmiUnittest,ConnectionOpenTest)
	{
		wmi::context ctx;

		wmi::connection cnn(LEMON_TEXT("ROOT\\DEFAULT"));
	}

	LEMON_UNITTEST_CASE(WmiUnittest,ObjectTest)
	{
		wmi::context ctx;

		wmi::connection cnn(LEMON_TEXT("root\\cimv2"));

		wmi::object sysClass = cnn.get_object(LEMON_TEXT("__SystemClass"));

		LEMON_CHECK(sysClass[LEMON_TEXT("__Class")] == ATL::CComVariant(LEMON_TEXT("__SystemClass")));
	}

	LEMON_UNITTEST_CASE(WmiUnittest,DHCAPTest)
	{
		wmi::context ctx;

		wmi::connection cnn(LEMON_TEXT("root\\cimv2"));

		wmi::object networkConfig = cnn[LEMON_TEXT("Win32_NetworkAdapterConfiguration")];

		wmi::method renewDHCPLease(LEMON_TEXT("RenewDHCPLease"),networkConfig);

		// invoke the method on open connection.
		// cnn.invoke(LEMON_TEXT("Win32_NetworkAdapterConfiguration.Index='????'"),renewDHCPLease,0,0);
		// 
	}

	LEMON_UNITTEST_CASE(WmiUnittest,QueryTest)
	{

		wmi::context ctx;

		wmi::connection cnn(LEMON_TEXT("root\\cimv2"));

		wmi::connection::const_query_result_iterator iter = cnn.query(LEMON_TEXT("select * from Win32_NetworkAdapter where AdapterTypeID=0"));

		wmi::connection::const_query_result_iterator end;

		for(;iter != end; ++ iter)
		{
			LEMON_COUT << (*iter)[LEMON_TEXT("Index")].intVal << std::endl;

			//LEMON_COUT << (*iter)[LEMON_TEXT("Description")].bstrVal << std::endl;

			LEMON_COUT << (*iter)[LEMON_TEXT("Manufacturer")].bstrVal << std::endl;

			LEMON_COUT << (*iter)[LEMON_TEXT("MacAddress")].bstrVal << std::endl;
		}
	}

	void Result(condition_variable & cv,mutex_t & mutex,LONG counter, IWbemClassObject** argv)
	{
		for(LONG i = 0 ; i < counter; ++ i)
		{
			wmi::object obj(ATL::CComPtr<IWbemClassObject>(*(argv + i)));

			LEMON_COUT << obj[LEMON_TEXT("Index")].intVal << std::endl;

			//LEMON_COUT << (*iter)[LEMON_TEXT("Description")].bstrVal << std::endl;

			LEMON_COUT << obj[LEMON_TEXT("Manufacturer")].bstrVal << std::endl;

			LEMON_COUT << obj[LEMON_TEXT("MacAddress")].bstrVal << std::endl;
		}

		mutex_t::scope_lock lock(mutex);

		cv.notify();
	}

	void Status(LONG flag, HRESULT, BSTR, IWbemClassObject*)
	{
		LEMON_COUT << LEMON_TEXT("process ... :") << flag << std::endl;
	}

	LEMON_UNITTEST_CASE(WmiUnittest,AsyncQueryTest)
	{
		condition_variable cv;

		mutex_t mutex;

		wmi::context ctx;

		wmi::connection cnn(LEMON_TEXT("root\\cimv2"));

		wmi::async_observer observer(lemon::bind(&Result,ref(cv),ref(mutex),_0,_1),lemon::bind(&Status,_0,_1,_2,_3));

		cnn.async_query(LEMON_TEXT("select * from Win32_NetworkAdapter where AdapterTypeID=0"),observer);

		mutex_t::scope_lock lock(mutex);

		cv.wait(lock);

		lemon::sleep(3000);
	}

	void OnChange(LONG counter, IWbemClassObject** argv)
	{
		for(LONG i = 0 ; i < counter; ++ i)
		{
			wmi::object obj(ATL::CComPtr<IWbemClassObject>(*(argv + i)));

			wmi::object adapter(obj[LEMON_TEXT("TargetInstance")].punkVal);

			LEMON_COUT << LEMON_TEXT("======================================") << std::endl;
			
			LEMON_COUT << LEMON_TEXT("= NO. :") << adapter[LEMON_TEXT("Index")].intVal << std::endl;

			//LEMON_COUT << (*iter)[LEMON_TEXT("Description")].bstrVal << std::endl;

			LEMON_COUT << LEMON_TEXT("= Manufacturer :") << (adapter[LEMON_TEXT("Manufacturer")].bstrVal ? adapter[LEMON_TEXT("Manufacturer")].bstrVal : LEMON_TEXT("NULL")) << std::endl;

			LEMON_COUT << LEMON_TEXT("= Availability :") << adapter[LEMON_TEXT("Availability")].uiVal << std::endl;

			LEMON_COUT << LEMON_TEXT("= NetConnectionStatus :") << adapter[LEMON_TEXT("NetConnectionStatus")].uiVal << std::endl;

			LEMON_COUT << LEMON_TEXT("======================================") << std::endl;

		}
	}

	LEMON_UNITTEST_CASE(WmiUnittest,AsyncNotifyTest)
	{
		wmi::context ctx;

		wmi::connection cnn(LEMON_TEXT("root\\cimv2"));

		wmi::async_observer observer(lemon::bind(&OnChange,_0,_1),lemon::bind(&Status,_0,_1,_2,_3));

		cnn.async_query_notify(LEMON_TEXT("SELECT * FROM __InstanceOperationEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_NetworkAdapter'"),observer);

		lemon::sleep(100000);
	}
}}}

#endif
