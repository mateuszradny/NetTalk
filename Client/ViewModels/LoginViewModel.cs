using NetTalk.Contracts.Services;
using NetTalk.Protocol.Responses;
using System.Windows.Input;

namespace NetTalk.ViewModels
{
    public class LoginViewModel : BaseViewModel
    {
        private readonly IClientService clientService;
        private readonly MainViewModel parentViewModel;
        private string message;
        private string password;
        private string userName;

        public LoginViewModel(MainViewModel parentViewModel, IClientService clientService)
        {
            this.clientService = clientService;
            this.parentViewModel = parentViewModel;
        }

        #region Properties

        public string Message
        {
            get { return message; }
            set
            {
                message = value;
                OnPropertyChanged();
            }
        }

        public string Password
        {
            get { return password; }
            set
            {
                password = value;
                OnPropertyChanged();
            }
        }

        public string UserName
        {
            get { return userName; }
            set
            {
                userName = value;
                OnPropertyChanged();
            }
        }

        #endregion Properties

        #region Commands

        public ICommand SignIn
        {
            get { return new RelayCommand(OnSignIn, OnValidateSignIn); }
        }

        #endregion Commands

        private async void OnSignIn(object obj)
        {
            LoginResult result = await clientService.LoginAsync(UserName, Password);

            if (result == LoginResult.Ok)
                parentViewModel.DisplayMainView.Execute(this);
            else
                Message = result.ToString(); //TODO: Change message
        }

        private bool OnValidateSignIn(object arg)
        {
            return !string.IsNullOrEmpty(UserName)
                && !string.IsNullOrEmpty(Password);
        }
    }
}