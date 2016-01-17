#include "DataSearcher.h"


using namespace NewData;

//template <class C>
//CDataSearcherBase<C>::CDataSearcherBase(const std::vector<C> &datalist, tstring string)// : targetlist(datalist), name(string)
//{
//	//SearchName();
//}
//
/////*CDataSearcher::CDataSearcher(const std::vector<CData> *datalist, tstring string)
//{
//	SetTargetList(*datalist);
//	SetSearchName(string);
//
//	begin = targetlist.begin();
//	end = targetlist.end();
//
//
//	SearchName();
//}*/
//template<class C>
//CDataSearcherBase<C>::CDataSearcherBase(const CDataSearcherBase<C> &sercher, tstring string)// : targetlist(sercher.GetResultList()), name(string)
//{
//	//SearchName();
//}
//
//template<class C>
//CDataSearcherBase<C>::~CDataSearcherBase(void) {}
//
//template<class C>
//void CDataSearcherBase<C>::SearchName(void)
//{
//	using namespace std;
//
//	std::copy_if(
//		begin, 
//		end, 
//		std::back_inserter(resultlist), 
//		[&](C &data) { return data.GetName() == name; }
//	);
//
//
//	/*auto fp = remove_if(
//		begin, 
//		end, 
//		[&](CData data) { return data.GetName() == name; }
//	);
//
//	targetlist.erase(fp, end);
//	*/
//	//copy(fp, end, back_inserter(resultlist));
//
//}