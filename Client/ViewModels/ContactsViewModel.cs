using NetTalk.Contracts.Services;
using NetTalk.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Input;
using System.Windows.Threading;

namespace NetTalk.ViewModels
{
    public class ContactsViewModel : BaseViewModel
    {
        private readonly ChatViewModel chatViewModel;
        private readonly IClientService clientService;
        private readonly DispatcherTimer dispatcherTimer;

        public ContactsViewModel(ChatViewModel chatViewModel, IClientService clientService)
        {
            this.chatViewModel = chatViewModel;
            this.clientService = clientService;

            RefreshContacts(this, EventArgs.Empty);
            dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Interval = new TimeSpan(0, 0, 5);
            dispatcherTimer.Tick += RefreshContacts;
            dispatcherTimer.Start();
        }

        #region Properties

        public ObservableCollection<Contact> Contacts { get; } = new ObservableCollection<Contact>();
        public Contact SelectedContact { get; set; }

        #endregion Properties

        #region Commands

        public ICommand OpenChatTab
        {
            get { return new RelayCommand(obj => OnOpenChatTab(SelectedContact), x => true); }
        }

        #endregion Commands

        public void OnOpenChatTab(Contact contact)
        {
            if (contact == null)
                return;

            ChatTabViewModel chatTab = chatViewModel.ChatTabs.SingleOrDefault(x => x.Interlocutor == contact.Name);
            if (chatTab == null)
            {
                chatTab = new ChatTabViewModel(contact.Name, clientService);
                chatViewModel.ChatTabs.Add(chatTab);
            }

            chatViewModel.SelectedTab = chatTab;
        }

        private async void RefreshContacts(object sender, EventArgs e)
        {
            IEnumerable<Contact> contacts = (await clientService.GetContacts()).OrderByDescending(x => x.IsOnline).ThenBy(x => x.Name);

            Contacts.Clear();
            foreach (Contact contact in contacts)
                Contacts.Add(contact);
        }
    }
}