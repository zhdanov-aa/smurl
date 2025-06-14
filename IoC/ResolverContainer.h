#ifndef __RESOLVERCONTAINER_H_INCLUDED__
#define __RESOLVERCONTAINER_H_INCLUDED__

#include <memory>
#include <functional>
#include <IResolverContainer.h>

template<typename ResolverType>
class ResolverContainer: public IResolverContainer
{
    ResolverType m_Resolver;
public:
    ResolverContainer(const ResolverType& content) : m_Resolver(content) {}
    ResolverType getResolver() { return m_Resolver; }
};

template<typename ResolverFuncPrototype>
IResolverContainerPtr make_container(ResolverFuncPrototype resolver)
{
    return std::static_pointer_cast<IResolverContainer>(
        std::make_shared<ResolverContainer<ResolverFuncPrototype>>(resolver));
}

template<typename F>
IResolverContainerPtr RESOLVER(F&& lambda)
{
    auto func = std::function(lambda);
    return std::make_shared<ResolverContainer<decltype(func)>>(func);
}

#endif
