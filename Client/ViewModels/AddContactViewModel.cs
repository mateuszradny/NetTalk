using NetTalk.Contracts.Services;
using System.Windows.Input;

namespace NetTalk.ViewModels
{
    public class AddContactViewModel : BaseViewModel
    {
        private readonly IClientService clientService;
        private string contactName;
        private string message;

        public AddContactViewModel(IClientService clientService)
        {
            this.clientService = clientService;
        }

        #region Properties

        public string ContactName
        {
            get { return contactName; }
            set
            {
                contactName = value;
                OnPropertyChanged();
            }
        }

        public string Message
        {
            get { return message; }
            set
            {
                message = value;
                OnPropertyChanged();
            }
        }

        #endregion Properties

        #region Commands

        public ICommand AddContact
        {
            get { return new RelayCommand(OnAddContact, OnValidateAddContact); }
        }

        #endregion Commands

        private async void OnAddContact(object obj)
        {
            //TODO: Change message
            Message = (await clientService.AddContactAsync(contactName)).ToString();
        }

        private bool OnValidateAddContact(object arg)
        {
            return !string.IsNullOrWhiteSpace(ContactName);
        }
    }
}