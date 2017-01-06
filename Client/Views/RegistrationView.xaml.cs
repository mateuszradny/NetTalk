using NetTalk.ViewModels;
using System.Windows.Controls;

namespace NetTalk.Views
{
    /// <summary>
    /// Interaction logic for RegistrationView.xaml
    /// </summary>
    public partial class RegistrationView : UserControl
    {
        public RegistrationView()
        {
            InitializeComponent();
        }

        private void ConfirmPasswordBox_PasswordChanged(object sender, System.Windows.RoutedEventArgs e)
        {
            if (this.DataContext != null)
                ((RegistrationViewModel)DataContext).ConfirmPassword = ((PasswordBox)sender).Password;
        }

        private void PasswordBox_PasswordChanged(object sender, System.Windows.RoutedEventArgs e)
        {
            if (DataContext != null)
                ((RegistrationViewModel)DataContext).Password = ((PasswordBox)sender).Password;
        }
    }
}