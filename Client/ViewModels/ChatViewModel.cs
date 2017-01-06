using NetTalk.Contracts.Services;
using NetTalk.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Threading;

namespace NetTalk.ViewModels
{
    public class ChatViewModel : BaseViewModel
    {
        private readonly IClientService clientService;
        private readonly DispatcherTimer dispatcherTimer;
        private ChatTabViewModel selectedTab;

        public ChatViewModel(IClientService clientService)
        {
            this.clientService = clientService;

            dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Interval = new TimeSpan(0, 0, 1);
            dispatcherTimer.Tick += ReceiveMessages;
            dispatcherTimer.Start();
        }

        public ObservableCollection<ChatTabViewModel> ChatTabs { get; } = new ObservableCollection<ChatTabViewModel>();

        public ChatTabViewModel SelectedTab
        {
            get { return selectedTab; }
            set
            {
                selectedTab = value;
                OnPropertyChanged();
            }
        }

        private async void ReceiveMessages(object sender, EventArgs e)
        {
            IEnumerable<Message> messages = (await clientService.ReceiveMessages()).OrderBy(x => x.PostDate);
            IEnumerable<string> interlocutors = ChatTabs.Select(x => x.Interlocutor);

            foreach (Message message in messages)
            {
                if (!interlocutors.Contains(message.Sender))
                    ChatTabs.Add(new ChatTabViewModel(message.Sender, clientService));

                ChatTabs.Single(x => x.Interlocutor == message.Sender).Messages.Add(message);
            }
        }
    }
}