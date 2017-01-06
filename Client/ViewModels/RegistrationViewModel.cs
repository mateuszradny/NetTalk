using NetTalk.Contracts.Services;
using System.Windows.Input;

namespace NetTalk.ViewModels
{
    public class RegistrationViewModel : BaseViewModel
    {
        private readonly IClientService clientService;

        private string confirmPassword;
        private string message;
        private string password;
        private string userName;

        public RegistrationViewModel(IClientService clientService)
        {
            this.clientService = clientService;
        }

        #region Properties

        public string ConfirmPassword
        {
            get { return confirmPassword; }
            set
            {
                confirmPassword = value;
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

        public ICommand SignUp
        {
            get { return new RelayCommand(OnSignUp, OnValidateSignUp); }
        }

        #endregion Commands

        private async void OnSignUp(object obj)
        {
            //TODO: Change message
            Message = (await clientService.RegisterAsync(UserName, Password)).ToString();
        }

        private bool OnValidateSignUp(object arg)
        {
            return !string.IsNullOrWhiteSpace(UserName)
                && !string.IsNullOrEmpty(Password)
                && Password == ConfirmPassword;
        }
    }
}