using Microsoft.Practices.Unity;
using NetTalk.ViewModels;
using System.Windows.Controls;

namespace NetTalk.Views
{
    /// <summary>
    /// Interaction logic for ContactsView.xaml
    /// </summary>
    public partial class ContactsView : UserControl
    {
        public ContactsView()
        {
            InitializeComponent();
            DataContext = UnityConfig.GetConfiguredContainer().Resolve<ContactsViewModel>();
        }
    }
}