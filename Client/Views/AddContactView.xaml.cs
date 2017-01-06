using Microsoft.Practices.Unity;
using NetTalk.ViewModels;
using System.Windows.Controls;

namespace NetTalk.Views
{
    /// <summary>
    /// Interaction logic for AddContactView.xaml
    /// </summary>
    public partial class AddContactView : UserControl
    {
        public AddContactView()
        {
            InitializeComponent();
            DataContext = UnityConfig.GetConfiguredContainer().Resolve<AddContactViewModel>();
        }
    }
}