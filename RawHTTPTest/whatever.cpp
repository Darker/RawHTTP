//#include <string>
//#include <map>
//#include <functional>
//#include <memory>
//
//template<typename ResourceType, typename AllocatorType>
//  class ResourceManager
//{
//public:
//
//  using IDType = std::string;
//  
//  using ResourceHandle = std::shared_ptr<ResourceType>;
//
//  static ResourceHandle GetResource(const IDType& id, AllocatorType& alloc)
//  {
//    auto itr = m_resources.find(id);
//
//    if (itr != m_resources.end())
//      return itr->second;
//
//    ResourceHandle r = LoadFunc(id, alloc);
//
//    m_resources[id] = r;
//
//    return r;
//  }
//
//  static ResourceType* LoadFunc(const IDType&, AllocatorType&) { /*static_assert(false, "Load func not defined for these types!");*/ }
//
//  static std::map<IDType, ResourceHandle> m_resources;
//};
//
//struct PretendAllocator
//{
//
//};
//
//struct SomeResource
//{
//  int i;
//};
//
//template<typename Allocator>
//SomeResource* load_some_resouce_from_file(const std::string& filename,
//  Allocator& alloc)
//{
//  SomeResource* x = new SomeResource{ 12 };
//  // let's pretend that the allocator was used and the filename was used
//  return x;
//}
//
///// This does not work, no idea why.
////template<typename AllocatorType>
////SomeResource* ResourceManager<AllocatorType, SomeResource>::LoadFunc(const std::string& id, AllocatorType& alloc)
////{
////  return load_some_resouce_from_file<AllocatorType>(id, alloc);
////}
//
//template<>
//SomeResource* ResourceManager<SomeResource, PretendAllocator>::LoadFunc(const IDType& id, PretendAllocator& alloc)
//{
//  return load_some_resouce_from_file<PretendAllocator>(id, alloc);
//}
//
//using SomeResourceManager = ResourceManager<SomeResource, PretendAllocator>;
//
//int main()
//{
//  // I don't know what kind of allocator I may have in real-world
//  PretendAllocator pretendAllocator;
//
//
//  // But I would use it to allocate a resource managed through Manager
//  SomeResourceManager::ResourceHandle resource
//    = SomeResourceManager::GetResource("some file",
//      pretendAllocator);
//
//  return 0;
//}

cout << R"(<?xml version="1.0"encoding=\"ISO-8859-1"\?>)" << endl;
cout << R"(<results>)" << endl;
cout << R"(  <row>)" << endl;

for (int i = 0; i < items.size(); i++)
{
  if (i % 3 == 0 && i != 0)
  {
    cout << "  </row>\n  <row>\n";
  }
  cout << R"(    <field>)" << items[i] << R"(</field>)" << endl;
}
cout << R"(  </row>)" << endl;
cout << R"(</results>)" << endl;