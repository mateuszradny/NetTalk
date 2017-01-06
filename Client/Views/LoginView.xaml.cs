using NetTalk.ViewModels;
using System.Windows;
using System.Windows.Controls;

namespace NetTalk.Views
{
    /// <summary>
    /// Interaction logic for LoginView.xaml
    /// </summary>
    public partial class LoginView : UserControl
    {
        public LoginView()
        {
            InitializeComponent();
        }

        private void PasswordBox_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if (this.DataContext != null)
                ((LoginViewModel)DataContext).Password = ((PasswordBox)sender).Password;
        }
    }
}