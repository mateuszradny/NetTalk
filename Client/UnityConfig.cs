using Microsoft.Practices.Unity;
using NetTalk.Contracts.Services;
using NetTalk.Services;
using NetTalk.ViewModels;
using System;

namespace NetTalk
{
    public static class UnityConfig
    {
        private static Lazy<IUnityContainer> container = new Lazy<IUnityContainer>(() =>
        {
            IUnityContainer container = new UnityContainer();
            RegisterTypes(container);
            return container;
        });

        public static IUnityContainer GetConfiguredContainer()
        {
            return container.Value;
        }

        public static void RegisterTypes(IUnityContainer container)
        {
            container.RegisterType<ICommunicationService, CommunicationService>(new ContainerControlledLifetimeManager());
            container.RegisterType<IClientService, ClientService>(new ContainerControlledLifetimeManager());
            container.RegisterType<ChatViewModel, ChatViewModel>(new ContainerControlledLifetimeManager());
        }
    }
}