using NetTalk.Contracts.Services;
using System.Windows.Input;

namespace NetTalk.ViewModels
{
    public class MainViewModel : BaseViewModel
    {
        private readonly IClientService clientService;
        private BaseViewModel viewModel;

        public MainViewModel(IClientService clientService)
        {
            this.clientService = clientService;
            this.DisplayLoginView.Execute(this);
        }

        #region Properties

        public BaseViewModel ViewModel
        {
            get { return viewModel; }
            set
            {
                viewModel = value;
                OnPropertyChanged();
            }
        }

        #endregion Properties

        #region Commands

        public ICommand DisplayLoginView
        {
            get { return new RelayCommand(x => ViewModel = new LoginViewModel(this, clientService), x => true); }
        }

        public ICommand DisplayMainView
        {
            get { return new RelayCommand(x => ViewModel = new ClientViewModel(), x => !string.IsNullOrWhiteSpace(clientService.AuthToken)); }
        }

        public ICommand DisplayRegistrationView
        {
            get { return new RelayCommand(x => ViewModel = new RegistrationViewModel(clientService), x => true); }
        }

        #endregion Commands
    }
}