using NetTalk.Contracts.Services;
using NetTalk.Model;
using NetTalk.Protocol.Responses;
using System;
using System.Collections.ObjectModel;
using System.Windows.Input;

namespace NetTalk.ViewModels
{
    public class ChatTabViewModel : BaseViewModel
    {
        private readonly IClientService clientService;
        private string body;

        public ChatTabViewModel(string interlocutor, IClientService clientService)
        {
            this.Interlocutor = interlocutor;
            this.clientService = clientService;
        }

        #region Properties

        public string Body
        {
            get { return body; }
            set
            {
                body = value;
                OnPropertyChanged();
            }
        }

        public string Interlocutor { get; private set; }
        public ObservableCollection<Message> Messages { get; } = new ObservableCollection<Message>();

        #endregion Properties

        #region Commands

        public ICommand SendMessage
        {
            get { return new RelayCommand(OnSendMessage, OnValidateSendMessage); }
        }

        #endregion Commands

        private async void OnSendMessage(object obj)
        {
            SendMessageResult result = await clientService.SendMessageAsync(Interlocutor, Body);

            if (result == SendMessageResult.Ok)
                Messages.Add(new Message() { Body = Body, PostDate = DateTime.Now, Direction = MessageDirection.Outgoing });

            Body = string.Empty;
        }

        private bool OnValidateSendMessage(object arg)
        {
            return !string.IsNullOrEmpty(Body);
        }
    }
}